#include "decoration.h"

#include "button.h"
#include "shadow.h"
#include "style.h"

#include <KDecoration3/DecoratedWindow>
#include <KDecoration3/DecorationButtonGroup>

#include <QEasingCurve>
#include <QFontMetricsF>
#include <QPainter>
#include <QRegion>
#include <QtMath>
#include <QVariantAnimation>

namespace Endfield
{

Decoration::Decoration(QObject *parent, const QVariantList &args)
    : KDecoration3::Decoration(parent, args)
{
}

bool Decoration::init()
{
    auto *w = window();
    m_focus = w->isActive() ? 1.0 : 0.0;

    // focus change: the tick grows in and the title slides right / brightens
    m_focusAnim = new QVariantAnimation(this);
    m_focusAnim->setDuration(FocusMs);
    m_focusAnim->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_focusAnim, &QVariantAnimation::valueChanged, this, [this](const QVariant &v) {
        m_focus = v.toReal();
        update();
    });
    connect(w, &KDecoration3::DecoratedWindow::activeChanged, this, [this, w] {
        m_focusAnim->stop();
        m_focusAnim->setStartValue(m_focus);
        m_focusAnim->setEndValue(w->isActive() ? 1.0 : 0.0);
        m_focusAnim->start();
    });

    connect(w, &KDecoration3::DecoratedWindow::captionChanged, this, [this] { update(); });
    connect(w, &KDecoration3::DecoratedWindow::widthChanged, this, &Decoration::updateLayout);
    connect(w, &KDecoration3::DecoratedWindow::maximizedChanged, this, &Decoration::updateLayout);

    m_buttons = new KDecoration3::DecorationButtonGroup(KDecoration3::DecorationButtonGroup::Position::Right, this, &Button::create);
    m_buttons->setSpacing(0);
    connect(m_buttons, &KDecoration3::DecorationButtonGroup::geometryChanged, this, &Decoration::updateLayout);

    setShadow(makeShadow());
    updateLayout();
    return true;
}

void Decoration::updateLayout()
{
    auto *w = window();
    const qreal b = w->isMaximized() ? 0 : 1; // .win.max: no frame
    setBorders(QMarginsF(b, TitleHeight + b, b, b));
    setResizeOnlyBorders(w->isMaximized() ? QMarginsF() : QMarginsF(ResizeGrip, ResizeGrip, ResizeGrip, ResizeGrip));
    setTitleBar(QRectF(b, b, w->width(), TitleHeight));
    // frosted glass: KWin's blur effect blurs whatever is behind the frame (the mock's glass)
    setBlurRegion(QRegion(QRect(0, 0, qCeil(w->width() + 2 * b), qCeil(TitleHeight + b))));
    if (m_buttons) {
        m_buttons->setPos(QPointF(b + w->width() - m_buttons->geometry().width(), b));
    }
    update();
}

QString Decoration::appName() const
{
    // windowClass is "resourceName resourceClass" (X11) or the app id (Wayland, e.g. org.kde.dolphin)
    const QString cls = window()->windowClass().section(QLatin1Char(' '), -1).section(QLatin1Char('.'), -1);
    return cls.isEmpty() ? window()->caption() : cls;
}

void Decoration::paint(QPainter *painter, const QRectF &repaintArea)
{
    Q_UNUSED(repaintArea)
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);

    const QRectF tb = titleBar();
    painter->fillRect(tb, TitleBg);
    painter->fillRect(QRectF(tb.left(), tb.bottom() - 1, tb.width(), 1), Hairline);

    if (!window()->isMaximized()) {
        painter->setPen(QPen(mix(BorderBlur, BorderFocus, m_focus), 1));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(rect().adjusted(0.5, 0.5, -0.5, -0.5));
    }

    paintTitle(painter, tb);
    painter->restore();

    m_buttons->paint(painter, repaintArea);
}

void Decoration::paintTitle(QPainter *painter, const QRectF &tb)
{
    // tick: 3x11 yellow block, grows from the centre line as focus arrives
    const qreal x0 = tb.left() + TitlePadding;
    const qreal cy = tb.top() + TitleHeight / 2.0;
    if (m_focus > 0.001) {
        const qreal h = TickHeight * m_focus;
        painter->fillRect(QRectF(x0, cy - h / 2.0, TickWidth, h), Yellow);
    }

    // title slides from the padding to after the tick
    qreal x = x0 + (TickWidth + TickGap) * m_focus;
    const qreal right = tb.right() - (m_buttons ? m_buttons->geometry().width() : 0) - 12;
    const qreal opacity = 0.5 + 0.5 * m_focus; // .win.blur .wtitle { opacity: .5 }

    painter->setRenderHint(QPainter::TextAntialiasing, true);
    const QFont nameFont = titleFont();
    const QString name = appName().toUpper();
    const QFontMetricsF nm(nameFont);
    QColor nameColor = mix(Ink2, Ink, m_focus);
    nameColor.setAlphaF(opacity);
    painter->setFont(nameFont);
    painter->setPen(nameColor);
    const QString nameShown = nm.elidedText(name, Qt::ElideRight, qMax<qreal>(0, right - x));
    painter->drawText(QRectF(x, tb.top(), right - x, TitleHeight), Qt::AlignVCenter | Qt::AlignLeft, nameShown);
    x += nm.horizontalAdvance(nameShown);

    const QString caption = window()->caption();
    if (caption.isEmpty() || caption.compare(name, Qt::CaseInsensitive) == 0 || x >= right) {
        return;
    }
    const QFont subFont = subtitleFont();
    const QFontMetricsF sm(subFont);
    QColor subColor = Faint;
    subColor.setAlphaF(opacity);
    painter->setFont(subFont);
    painter->setPen(subColor);
    const QString sub = sm.elidedText(QStringLiteral(" · ") + caption, Qt::ElideRight, right - x);
    painter->drawText(QRectF(x, tb.top(), right - x, TitleHeight), Qt::AlignVCenter | Qt::AlignLeft, sub);
}

} // namespace Endfield
