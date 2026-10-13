#pragma once

#include <KDecoration3/DecorationButton>

class QVariantAnimation;

namespace Endfield
{

class Button : public KDecoration3::DecorationButton
{
    Q_OBJECT

public:
    Button(KDecoration3::DecorationButtonType type, KDecoration3::Decoration *decoration, QObject *parent);

    // DecorationButtonGroup creator: only minimize / maximize / close exist in the mock
    static KDecoration3::DecorationButton *create(KDecoration3::DecorationButtonType type, KDecoration3::Decoration *decoration, QObject *parent);

    void paint(QPainter *painter, const QRectF &repaintArea) override;

private:
    void paintGlyph(QPainter *painter, const QRectF &box);

    qreal m_hover = 0;
    QVariantAnimation *m_hoverAnim = nullptr;
};

} // namespace Endfield
