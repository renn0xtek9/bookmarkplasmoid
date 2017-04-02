
set(xbelreaderopTEST)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets )


file (GLOB SRC "*.cpp" ) 
set (SRC ${SRC} ./../XbelReader.cpp ./../bookmark.cpp)
include_directories(./../)

add_executable(xbelreaderopTEST ${SRC})
target_link_libraries(xbelreaderopTEST Qt5::Widgets)
