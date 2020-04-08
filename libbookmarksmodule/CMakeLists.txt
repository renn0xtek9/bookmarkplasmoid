enable_language(CXX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")	#Usage of C++11
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(CMAKE_INSTALL_PREFIX=/usr)


include(FeatureSummary)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake) 
set(CMAKE_INCLUDE_CURRENT_DIR ON) # Find includes in corresponding build directories
set(CMAKE_AUTOMOC ON) # Instruct CMake to run moc automatically when needed.

set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")
find_package(KF5Plasma REQUIRED)
find_package(KF5I18n NO_MODULE)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Qml)
find_package(KF5IconThemes)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
add_definitions (${QT_DEFINITIONS} )
set(PROJECT_NAME bookmarkmodelplugin)
PROJECT(${PROJECT_NAME} CXX)

# file (GLOB SRC "*.cpp" ) 
include_directories(./../)
include_directories(${CMAKE_SOURCE_DIR}${CMAKE_BINARY_DIR} ${QT_INCLUDES})

# Copy qmldir file to build dir for running in QtCreator
add_custom_target(${PROJECT_NAME}-qmldir ALL
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/qmldir ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${QMLFILES}
)

# query_qmake(QT_INSTALL_PLUGINS QT_PLUGINS_DIR)
# query_qmake(QT_INSTALL_IMPORTS QT_IMPORTS_DIR)
set(QT_IMPORTS_DIR /usr/lib/x86_64-linux-gnu/qt5/qml/)		#TODO this should be set in platform independant
message(STATUS "${PROJECT_NAME}:  QT_IMPORTS_DIR.------------------------------------------------\n" "${QT_IMPORTS_DIR}")

set (LIBNAME bookmarkmodelplugin)
set (SRC ${SRC} bookmarkmodel.cpp )
set(CMAKE_CXX_VISIBILITY_PRESET)
add_library(${LIBNAME} SHARED ${SRC})
qt5_use_modules(${LIBNAME}  Qml)

set_target_properties(${LIBNAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_NAME})
target_include_directories( ${LIBNAME}
 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
 PUBLIC $<INSTALL_INTERFACE:include>)
target_link_libraries(${LIBNAME} Qt5::Core Qt5::Qml KF5::IconThemes)

install(TARGETS ${LIBNAME} DESTINATION ${QT_IMPORTS_DIR}/MyPlugins/)
install(FILES   qmldir DESTINATION ${QT_IMPORTS_DIR}/MyPlugins/)
# install(FILES bookmarkmodule.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
add_subdirectory(Tests)
