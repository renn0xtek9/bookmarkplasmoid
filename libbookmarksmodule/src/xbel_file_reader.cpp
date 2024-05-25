#include <libbookmarksmodule/xbel_file_reader.h>


XbelFileReader::XbelFileReader(XmlParserInterface& xml_parser,const BookmarkSource& bookmark_source)
    : XmlBookmarkReaderInterface(xml_parser)
{
}

void XbelFileReader::read(QStandardItem* root_item)
{
    return;
}
