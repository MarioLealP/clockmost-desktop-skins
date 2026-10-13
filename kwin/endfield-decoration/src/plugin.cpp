#include "decoration.h"

#include <KPluginFactory>

K_PLUGIN_FACTORY_WITH_JSON(EndfieldDecorationFactory, "endfield.json", registerPlugin<Endfield::Decoration>();)

#include "plugin.moc"
