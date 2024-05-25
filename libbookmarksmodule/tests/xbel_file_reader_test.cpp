#include <libbookmarksmodule/xbel_file_reader.h>
#include <libbookmarksmodule/data_types.h>
#include <xbel_file_reader_test.h>
#include <mocks.h>

void XbelFileReaderTest::test_constructor()
{
    MockEnvironmentThemeFacade theme_facade;
    MockXbelParserInterface xml_parser(BookmarkSource::Konqueror,theme_facade);
    XbelFileReader reader(xml_parser);
}

void XbelFileReaderTest::test_set_file_path_of_non_existing_file()
{
    MockEnvironmentThemeFacade theme_facade;
    MockXbelParserInterface xml_parser(BookmarkSource::Konqueror,theme_facade);
    XbelFileReader reader(xml_parser);
    QVERIFY2(!reader.setFilePath({"non_existing_file"}), "setFilePath() failed to return true for non existing file");
}

void XbelFileReaderTest::test_set_file_path_of_existing_file()
{
    MockEnvironmentThemeFacade theme_facade;
    MockXbelParserInterface xml_parser(BookmarkSource::Konqueror,theme_facade);
    XbelFileReader reader(xml_parser);
    QVERIFY2(reader.setFilePath({"existing_file"}), "setFilePath() failed to return true for existing file");
}

void XbelFileReaderTest::test_read_calls_read_on_xml_parser()
{
    MockEnvironmentThemeFacade theme_facade;
    MockXbelParserInterface xml_parser(BookmarkSource::Konqueror,theme_facade);
    XbelFileReader reader(xml_parser);
    QStandardItem root_item;
    reader.setFilePath({"existing_file"});
    reader.read(&root_item);

    QVERIFY2(xml_parser.readCallCount == 1, "read() failed to call read on xml_parser");
}
QTEST_GUILESS_MAIN(XbelFileReaderTest)
#include "moc_xbel_file_reader_test.cpp"
