#pragma once

#include <KDecoration3/DecorationShadow>

#include <memory>

namespace Endfield
{

// .win.focus box-shadow: 0 24px 60px rgba(0,0,0,.55)
std::shared_ptr<KDecoration3::DecorationShadow> makeShadow();

} // namespace Endfield
