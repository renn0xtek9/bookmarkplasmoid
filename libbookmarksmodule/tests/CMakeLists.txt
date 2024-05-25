FIND_PACKAGE (Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets Qml
                                                               Test)

FIND_PACKAGE (KF5IconThemes)

SET (
  TESTRC
  resources/Bookmarks resources/konqueror_bookmarks.xml
  resources/okular_bookmarks.xml
  resources/konqueror_bookmarks_same_name_for_folder_and_items.xml)

FOREACH (file ${TESTRC})
  FILE (COPY ${file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
ENDFOREACH ()

ADD_EXECUTABLE (bookmarksmodule_test bookmarksmodule_test.cpp)
ADD_TEST (bookmarksmodule_test bookmarksmodule_test)
TARGET_INCLUDE_DIRECTORIES (bookmarksmodule_test
                            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
TARGET_LINK_LIBRARIES (bookmarksmodule_test PRIVATE ${LIBNAME} Qt5::Test)

ADD_EXECUTABLE (bookmarksmodule_okular_test bookmarksmodule_okular_test.cpp)
ADD_TEST (bookmarksmodule_okular_test bookmarksmodule_okular_test)
TARGET_INCLUDE_DIRECTORIES (bookmarksmodule_okular_test
                            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
TARGET_LINK_LIBRARIES (bookmarksmodule_okular_test PRIVATE ${LIBNAME} Qt5::Test)

ADD_EXECUTABLE (bookmarksmodule_konqueror_test
                bookmarksmodule_konqueror_test.cpp)
ADD_TEST (bookmarksmodule_konqueror_test bookmarksmodule_konqueror_test)
TARGET_INCLUDE_DIRECTORIES (bookmarksmodule_konqueror_test
                            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
TARGET_LINK_LIBRARIES (bookmarksmodule_konqueror_test PRIVATE ${LIBNAME}
                                                              Qt5::Test)

ADD_EXECUTABLE (bookmarksmodule_chrome_test bookmarksmodule_chrome_test.cpp)
ADD_TEST (bookmarksmodule_chrome_test bookmarksmodule_chrome_test)
TARGET_INCLUDE_DIRECTORIES (bookmarksmodule_chrome_test
                            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
TARGET_LINK_LIBRARIES (bookmarksmodule_chrome_test PRIVATE ${LIBNAME} Qt5::Test)

ADD_EXECUTABLE (xbel_parser_test xbel_parser_test.cpp)
ADD_TEST (xbel_parser_test xbel_parser_test)
TARGET_INCLUDE_DIRECTORIES (xbel_parser_test
                            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
TARGET_LINK_LIBRARIES (xbel_parser_test PRIVATE ${LIBNAME} Qt5::Test)
