// Endfield window frame - every number here comes from ds-window-v2.html / ds-shell.css.
#pragma once

#include <QColor>
#include <QFont>

namespace Endfield
{

inline constexpr qreal TitleHeight = 34; // .wtop height
inline constexpr qreal TitlePadding = 14; // .wtop padding-left
inline constexpr qreal TickWidth = 3; // .wtitle::before
inline constexpr qreal TickHeight = 11;
inline constexpr qreal TickGap = 10; // ::before margin-right
inline constexpr qreal ButtonWidth = 40; // .wb
inline constexpr qreal GlyphSize = 11; // .wb svg
inline constexpr qreal GlyphStroke = 3.0 * GlyphSize / 24.0; // stroke-width 3 in a 24 viewBox
inline constexpr qreal ResizeGrip = 4; // invisible extra resize area
inline constexpr int FocusMs = 180; // focus in/out
inline constexpr int HoverMs = 120; // button hover

inline const QColor Ink{0xf1, 0xf1, 0xf4};
inline const QColor Ink2{0xc9, 0xcc, 0xd3};
inline const QColor Dim{0x7d, 0x80, 0x89};
inline const QColor Faint{0x55, 0x57, 0x5e};
inline const QColor Yellow{0xff, 0xfa, 0x00};
inline const QColor Crimson{0xd9, 0x1e, 0x36};
// .wtop rgba(10,11,13,.55) over .win rgba(13,14,16,.86): composite alpha .937
inline const QColor TitleBg{11, 12, 14, 239};
inline const QColor Hairline{255, 255, 255, 18}; // .wtop::after .07
inline const QColor BorderBlur{255, 255, 255, 26}; // .win .10
inline const QColor BorderFocus{255, 255, 255, 56}; // .win.focus .22

inline QColor mix(const QColor &a, const QColor &b, qreal t)
{
    return QColor::fromRgbF(a.redF() + (b.redF() - a.redF()) * t,
                            a.greenF() + (b.greenF() - a.greenF()) * t,
                            a.blueF() + (b.blueF() - a.blueF()) * t,
                            a.alphaF() + (b.alphaF() - a.alphaF()) * t);
}

// .wtitle: 700 10px mono, letter-spacing .26em, uppercase
inline QFont titleFont()
{
    QFont f(QStringLiteral("JetBrains Mono"));
    f.setPixelSize(10);
    f.setWeight(QFont::Bold);
    f.setLetterSpacing(QFont::AbsoluteSpacing, 2.6);
    return f;
}

// .wtitle span: 400, letter-spacing .1em, as typed
inline QFont subtitleFont()
{
    QFont f(QStringLiteral("JetBrains Mono"));
    f.setPixelSize(10);
    f.setWeight(QFont::Normal);
    f.setLetterSpacing(QFont::AbsoluteSpacing, 1.0);
    return f;
}

} // namespace Endfield
