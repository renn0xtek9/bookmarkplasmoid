# A name for the project

set(ENGINE_NAME bookmarkengine)
project(${ENGINE_NAME})

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Find KDE modules
find_package(KF5Plasma REQUIRED)
find_package(KF5KDELibs4Support REQUIRED)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core  )

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
# feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
add_definitions (${QT_DEFINITIONS} )
include_directories(${CMAKE_SOURCE_DIR}${CMAKE_BINARY_DIR} ${QT_INCLUDES} /usr/include/KF5/KDELibs4Support/ )

# We add our source code here
file (GLOB ".src" ${ENGINE_SRCs}) 
message(STATUS "DATAENGINE: KDE_INSTALL_PLUGINDIR------------------------------------------------\n" "${KDE_INSTALL_PLUGINDIR}")
message(STATUS "DATAENGINE: KDE_INSTALL_KSERVICES5DIR------------------------------------------------\n" "${KDE_INSTALL_KSERVICES5DIR}")

# Now make sure all files get to the right place
add_library(${ENGINE_NAME} ${ENGINE_SRCs})
target_link_libraries(${ENGINE_NAME} Qt5::Gui  KF5::KDELibs4Support  KF5::Plasma  KF5::Service  KF5::I18n)

kcoreaddons_desktop_to_json(${ENGINE_NAME} bookmarkengine.desktop SERVICE_TYPES plasma-dataengine.desktop)

install(TARGETS ${ENGINE_NAME} DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/dataengine)
install(FILES bookmarkengine.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})


