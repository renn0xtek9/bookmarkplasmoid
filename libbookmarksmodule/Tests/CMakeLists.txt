set(bookmarkmoduleTEST)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets )


file (GLOB SRC "*.cpp" ) 
set (SRC ${SRC} ./../bookmarksmodule.cpp ./../bookmark.cpp)
include_directories(./../)

add_executable(bookmarkmoduleTEST ${SRC})
target_link_libraries(bookmarkmoduleTEST Qt5::Widgets)
