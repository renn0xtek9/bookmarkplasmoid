#include <libbookmarksmodule/xbel_file_reader.h>
#include <libbookmarksmodule/data_types.h>
#include <xbel_file_reader_test.h>
#include <mocks.h>

void XbelFileReaderTest::test_constructor()
{
    MockEnvironmentThemeFacade theme_facade;
    MockXbelParserInterface xml_parser(BookmarkSource::Konqueror,theme_facade);
    XbelFileReader reader(xml_parser, BookmarkSource::Konqueror);

    QVERIFY(false);
}


QTEST_GUILESS_MAIN(XbelFileReaderTest)
#include "moc_xbel_file_reader_test.cpp"
