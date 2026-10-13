#!/usr/bin/env bash
# claude-statusline.sh - Endfield status line for Claude Code (ds-kitty-v3 .sl row).
# Claude Code runs this as its statusLine command and passes one JSON object on
# stdin. Output: ONE line, ANSI colours only - they resolve to the Endfield kitty
# palette when Claude Code's theme is "dark (ANSI)" (/config).
# Needs: bash, python3 (Arch base), git (branch segment). See kitty/README.md.
set -u

INPUT="$(cat)"
ENDFIELD_STATUS_JSON="$INPUT" python3 - <<'PY'
import json, os, subprocess, sys

RESET = '\x1b[0m'


def sgr(*codes):
    return '\x1b[' + ';'.join(str(c) for c in codes) + 'm'


def load_json():
    raw = os.environ.get('ENDFIELD_STATUS_JSON', '')
    try:
        data = json.loads(raw) if raw.strip() else {}
        return data if isinstance(data, dict) else {}
    except Exception:
        return {}


def git_segment(cwd):
    """(branch, changed_count) or None when not in a git repo."""
    try:
        br = subprocess.run(['git', '-C', cwd, 'rev-parse', '--abbrev-ref', 'HEAD'],
                            capture_output=True, text=True, timeout=2)
        if br.returncode != 0:
            return None
        branch = br.stdout.strip() or '?'
        st = subprocess.run(['git', '-C', cwd, 'status', '--porcelain'],
                            capture_output=True, text=True, timeout=2)
        n = len([ln for ln in st.stdout.splitlines() if ln.strip()]) if st.returncode == 0 else 0
        return branch, n
    except Exception:
        return None


def context_pct(transcript):
    """Context window use in %, estimated from the last assistant usage entry."""
    try:
        usage = None
        with open(transcript, 'r', encoding='utf-8', errors='replace') as fh:
            for line in fh:
                line = line.strip()
                if not line:
                    continue
                try:
                    entry = json.loads(line)
                except Exception:
                    continue
                if isinstance(entry, dict):
                    msg = entry.get('message')
                    if isinstance(msg, dict) and isinstance(msg.get('usage'), dict):
                        usage = msg['usage']
        if not isinstance(usage, dict):
            return None
        ctx = (usage.get('input_tokens') or 0) \
            + (usage.get('cache_creation_input_tokens') or 0) \
            + (usage.get('cache_read_input_tokens') or 0)
        return max(0, min(100, round(100 * ctx / 200000)))
    except Exception:
        return None


def main():
    try:
        sys.stdout.reconfigure(encoding='utf-8')
    except Exception:
        pass

    data = load_json()
    segs = []

    # yellow block: " ◆ MODEL " black-on-yellow, bold (mockup .sl .blk)
    model = (data.get('model') or {}).get('display_name') or (data.get('model') or {}).get('id') or '?'
    segs.append(sgr(1, 30, 43) + ' ◆ ' + str(model).upper() + ' ' + RESET)

    # cwd in cyan, ~ for $HOME (keep the real path for git)
    ws = data.get('workspace') or {}
    real_cwd = ws.get('current_dir') or data.get('cwd') or os.getcwd()
    home = os.path.expanduser('~')
    if real_cwd == home:
        cwd = '~'
    elif real_cwd.startswith(home + os.sep):
        cwd = '~' + real_cwd[len(home):]
    else:
        cwd = real_cwd
    segs.append(sgr(36) + cwd + RESET)

    # git branch yellow + changed count red (mockup: "main ● 2")
    git = git_segment(real_cwd if os.path.isdir(real_cwd) else os.getcwd())
    if git is not None:
        branch, changed = git
        count = sgr(31) if changed else sgr(90)
        segs.append(sgr(33) + branch + RESET + ' ' + count + '● ' + str(changed) + RESET)

    # context bar (10 segments) + % (mockup: "ctx ▮▮▮▮▯▯▯▯▯▯ 38%")
    # Claude Code sends the real figure; the transcript estimate is only a fallback for older versions
    used = (data.get('context_window') or {}).get('used_percentage')
    if used is not None:
        pct = round(used)
    else:
        pct = context_pct(data['transcript_path']) if data.get('transcript_path') else None
    if pct is None:
        segs.append('ctx ' + sgr(90) + '▯' * 10 + ' ' + '--%' + RESET)
    else:
        filled = max(0, min(10, round(pct / 10)))
        segs.append('ctx ' + sgr(32) + '▮' * filled + RESET + sgr(90) + '▯' * (10 - filled) + RESET
                    + ' ' + sgr(97) + f'{pct}%' + RESET)

    # mode (mockup: "⏵⏵ auto" magenta). statusLine JSON carries the output
    # style, not the permission mode - see README "Could not match".
    mode = (data.get('output_style') or {}).get('name') or 'default'
    segs.append(sgr(35) + '⏵⏵ ' + str(mode) + RESET)

    sep = ' ' + sgr(90) + '│' + RESET + ' '
    sys.stdout.write(sep.join(segs) + '\n')


if __name__ == '__main__':
    main()
PY
