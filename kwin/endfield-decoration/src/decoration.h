#pragma once

#include <KDecoration3/Decoration>

class QVariantAnimation;

namespace KDecoration3
{
class DecorationButtonGroup;
}

namespace Endfield
{

class Decoration : public KDecoration3::Decoration
{
    Q_OBJECT

public:
    explicit Decoration(QObject *parent, const QVariantList &args);

    bool init() override;
    void paint(QPainter *painter, const QRectF &repaintArea) override;

    // 0 = unfocused, 1 = focused; animated, so buttons and title ease between states
    qreal focus() const { return m_focus; }

private:
    void updateLayout();
    void paintTitle(QPainter *painter, const QRectF &titleBar);
    QString appName() const;

    qreal m_focus = 0;
    QVariantAnimation *m_focusAnim = nullptr;
    KDecoration3::DecorationButtonGroup *m_buttons = nullptr;
};

} // namespace Endfield
