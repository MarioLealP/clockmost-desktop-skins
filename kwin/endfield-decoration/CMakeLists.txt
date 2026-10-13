cmake_minimum_required(VERSION 3.20)
project(endfield-decoration LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
# ECM picks the Qt plugin dir when KDEInstallDirs loads - it must know it's Qt 6 by then
set(QT_MAJOR_VERSION 6)
find_package(Qt6 REQUIRED COMPONENTS Core Gui)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

find_package(KF6 REQUIRED COMPONENTS CoreAddons)
find_package(KDecoration3 REQUIRED)

add_library(org.clockmost.endfield MODULE
    src/plugin.cpp
    src/decoration.cpp
    src/button.cpp
    src/shadow.cpp
)
target_link_libraries(org.clockmost.endfield PRIVATE Qt6::Core Qt6::Gui KF6::CoreAddons KDecoration3::KDecoration)

install(TARGETS org.clockmost.endfield DESTINATION ${KDE_INSTALL_PLUGINDIR}/org.kde.kdecoration3)
