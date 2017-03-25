# A name for the project
project(plasma-testtime)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")



find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Find KDE modules
find_package(KF5Plasma REQUIRED)
find_package(KF5KDELibs4Support REQUIRED)
# find_package(KF5KDELibs4Support REQUIRED)
# find_package(KDELIBS4SUPPORT REQUIRED)
# find_package(KF5 REQUIRED COMPONENTS KI18n)




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
set(testtime_engine_SRCS testtimeengine.cpp)
message(STATUS "DATAENGINE: KDE4Support_LIBRARIES------------------------------------------------\n" "${KDE4Support_LIBRARIES}")
# Now make sure all files get to the right place
# kde4_add_plugin(plasma_engine_testtime ${testtime_engine_SRCS})
add_library(plasma_engine_testtime ${testtime_engine_SRCS})
target_link_libraries(plasma_engine_testtime Qt5::Core KF5::Plasma  KF5::KDELibs4Support)

install(TARGETS plasma_engine_testtime DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma-engine-testtime.desktop DESTINATION ${SERVICES_INSTALL_DIR})
