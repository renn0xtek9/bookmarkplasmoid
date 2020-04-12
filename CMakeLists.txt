# Set minimum CMake version (required for CMake 3.0 or later)
ENABLE_TESTING()
CMAKE_MINIMUM_REQUIRED (VERSION 2.8.12)
SET (PROJECT_VERSION_MAJOR 2)
SET (PROJECT_VERSION_MINOR 0)
SET (PROJECT_VERSION_PATCH 2)

# Use Extra CMake Modules (ECM) for common functionality. See
# http://api.kde.org/ecm/manual/ecm.7.html and
# http://api.kde.org/ecm/manual/ecm-kde-modules.7.html
FIND_PACKAGE (ECM REQUIRED NO_MODULE)
# Needed by find_package(KF5Plasma) below.
SET (CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR}
                       ${CMAKE_MODULE_PATH})

SET (CMAKE_INSTALL_PREFIX=/usr)
# Locate plasma_install_package macro.
FIND_PACKAGE (KF5Plasma REQUIRED)
# add_subdirectory(DataEngine/)
ADD_SUBDIRECTORY (libbookmarksmodule)
# Add installatation target ("make install").
PLASMA_INSTALL_PACKAGE (plasmoid org.kde.bookmarkplasmoid)
