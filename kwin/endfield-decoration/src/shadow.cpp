#include "shadow.h"

#include <QImage>

#include <cmath>

namespace Endfield
{

std::shared_ptr<KDecoration3::DecorationShadow> makeShadow()
{
    // CSS blur radius 60px = gaussian sigma 30; the tail is negligible past ~80px
    constexpr int reach = 80;
    constexpr int offsetY = 24;
    constexpr double sigma = 30.0;
    constexpr double alpha = 0.55;
    constexpr int size = 2 * reach + 1;

    // a box shadow is separable: coverage(x) * coverage(y), each the gaussian CDF past the edge
    auto coverage = [](double outside) {
        return 0.5 * std::erfc(outside / (sigma * std::sqrt(2.0)));
    };

    QImage image(size, size, QImage::Format_ARGB32_Premultiplied);
    for (int y = 0; y < size; ++y) {
        auto *line = reinterpret_cast<QRgb *>(image.scanLine(y));
        const double cy = coverage(std::abs(y - reach));
        for (int x = 0; x < size; ++x) {
            const int a = qRound(255.0 * alpha * coverage(std::abs(x - reach)) * cy);
            line[x] = qRgba(0, 0, 0, a);
        }
    }

    auto shadow = std::make_shared<KDecoration3::DecorationShadow>();
    shadow->setShadow(image);
    shadow->setInnerShadowRect(QRectF(reach, reach, 1, 1));
    // the offset pushes the shadow down: less above the window, more below
    shadow->setPadding(QMarginsF(reach, reach - offsetY, reach, reach + offsetY));
    return shadow;
}

} // namespace Endfield
