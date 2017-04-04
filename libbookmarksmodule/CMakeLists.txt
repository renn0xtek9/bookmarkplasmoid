enable_language(CXX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")	#Usage of C++11
set(PROJECT_NAME bookmarkmodule)
PROJECT(${PROJECT_NAME} CXX)
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets )


find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Find KDE modules
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets )

# include(KDEInstallDirs)
# include(KDECMakeSettings)
# include(KDECompilerSettings)
include(FeatureSummary)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
# feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
add_definitions (${QT_DEFINITIONS} )
include_directories(${CMAKE_SOURCE_DIR}${CMAKE_BINARY_DIR} ${QT_INCLUDES} )


file (GLOB SRC "*.cpp" ) 
set (SRC ${SRC} bookmarksmodule.cpp bookmark.cpp)
include_directories(./../)

add_library(${PROJECT_NAME} SHARED ${SRC})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets )


install(TARGETS ${PROJECT_NAME} DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/dataengine)
install(FILES bookmarkengine.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
