set(bookmarkmodelTEST)
enable_testing(true)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets Qml Test )

find_package(KF5IconThemes)

set (TESTSRC bookmarksmodule_test.cpp)

set(TESTEXE bookmarkmodel_test)

add_executable(${TESTEXE} ${TESTSRC})
add_test(test_one ${TESTEXE})


target_link_libraries(${TESTEXE} PRIVATE ${LIBNAME} Qt5::Test)
