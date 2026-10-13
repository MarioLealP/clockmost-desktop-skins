#include "button.h"

#include "decoration.h"
#include "style.h"

#include <KDecoration3/DecoratedWindow>

#include <QPainter>
#include <QVariantAnimation>

namespace Endfield
{

using KDecoration3::DecorationButtonType;

Button::Button(DecorationButtonType type, KDecoration3::Decoration *decoration, QObject *parent)
    : KDecoration3::DecorationButton(type, decoration, parent)
{
    setGeometry(QRectF(0, 0, ButtonWidth, TitleHeight));

    m_hoverAnim = new QVariantAnimation(this);
    m_hoverAnim->setDuration(HoverMs);
    connect(m_hoverAnim, &QVariantAnimation::valueChanged, this, [this](const QVariant &v) {
        m_hover = v.toReal();
        update();
    });
    auto animateTo = [this](qreal target) {
        m_hoverAnim->stop();
        m_hoverAnim->setStartValue(m_hover);
        m_hoverAnim->setEndValue(target);
        m_hoverAnim->start();
    };
    connect(this, &DecorationButton::pointerEntered, this, [animateTo] { animateTo(1.0); });
    connect(this, &DecorationButton::pointerLeft, this, [animateTo] { animateTo(0.0); });
    // focus changes animate on the decoration; repaint along with it
    connect(decoration->window(), &KDecoration3::DecoratedWindow::activeChanged, this, [this] { update(); });
}

KDecoration3::DecorationButton *Button::create(DecorationButtonType type, KDecoration3::Decoration *decoration, QObject *parent)
{
    switch (type) {
    case DecorationButtonType::Minimize:
    case DecorationButtonType::Maximize:
    case DecorationButtonType::Close:
        return new Button(type, decoration, parent);
    default:
        return nullptr;
    }
}

void Button::paint(QPainter *painter, const QRectF &repaintArea)
{
    Q_UNUSED(repaintArea)
    if (!isVisible()) {
        return;
    }
    const qreal focus = static_cast<Decoration *>(decoration())->focus();
    const QRectF g = geometry();
    const bool close = type() == DecorationButtonType::Close;

    painter->save();
    // hover: close = crimson block, others = faint white wash (.wb.x-hover / .wb.hover)
    if (m_hover > 0.001) {
        QColor bg = close ? Crimson : QColor(255, 255, 255, 18);
        bg.setAlphaF(bg.alphaF() * m_hover);
        painter->fillRect(g, bg);
    }

    QColor fg = mix(Dim, Ink2, focus); // .wb dim -> .win.focus .wb ink2
    fg.setAlphaF(0.5 + 0.5 * focus);
    fg = mix(fg, close ? QColor(Qt::white) : Ink, m_hover);
    if (isPressed()) {
        fg = close ? QColor(Qt::white) : Yellow;
    }

    painter->setRenderHint(QPainter::Antialiasing, true);
    QPen pen(fg, GlyphStroke);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    const QRectF box(g.center().x() - GlyphSize / 2.0, g.center().y() - GlyphSize / 2.0, GlyphSize, GlyphSize);
    paintGlyph(painter, box);
    painter->restore();
}

void Button::paintGlyph(QPainter *painter, const QRectF &box)
{
    // glyphs are the mock's 24-unit SVG paths, scaled into the 11px box
    const qreal s = box.width() / 24.0;
    auto pt = [&](qreal x, qreal y) {
        return QPointF(box.left() + x * s, box.top() + y * s);
    };
    switch (type()) {
    case DecorationButtonType::Minimize: // M5 12h14
        painter->drawLine(pt(5, 12), pt(19, 12));
        break;
    case DecorationButtonType::Maximize: // rect 5,5 14x14 (restore: same box, smaller)
        if (decoration()->window()->isMaximized()) {
            painter->drawRect(QRectF(pt(7, 7), pt(17, 17)));
        } else {
            painter->drawRect(QRectF(pt(5, 5), pt(19, 19)));
        }
        break;
    case DecorationButtonType::Close: // broken X: M5 5l5 5 M14 14l5 5 M19 5l-5 5 M10 14l-5 5
        painter->drawLine(pt(5, 5), pt(10, 10));
        painter->drawLine(pt(14, 14), pt(19, 19));
        painter->drawLine(pt(19, 5), pt(14, 10));
        painter->drawLine(pt(10, 14), pt(5, 19));
        break;
    default:
        break;
    }
}

} // namespace Endfield
