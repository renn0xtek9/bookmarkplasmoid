# Set minimum CMake version (required for CMake 3.0 or later)
cmake_minimum_required(VERSION 2.8.12)
set(PROJECT_VERSION_MAJOR 2)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)



# Use Extra CMake Modules (ECM) for common functionality.
# See http://api.kde.org/ecm/manual/ecm.7.html
# and http://api.kde.org/ecm/manual/ecm-kde-modules.7.html
find_package(ECM REQUIRED NO_MODULE)
# Needed by find_package(KF5Plasma) below.
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH})

set(CMAKE_INSTALL_PREFIX=/usr)
# Locate plasma_install_package macro.
find_package(KF5Plasma REQUIRED)
# add_subdirectory(DataEngine/)
add_subdirectory(libbookmarksmodule/)
# Add installatation target ("make install").
plasma_install_package(plasmoid org.kde.bookmarkplasmoid)

