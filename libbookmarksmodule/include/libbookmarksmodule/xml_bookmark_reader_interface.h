#ifndef XML_BOOKMARK_READER_INTERFACE_H
#define XML_BOOKMARK_READER_INTERFACE_H

#include <libbookmarksmodule/bookmark_source_reader_interface.h>
#include <libbookmarksmodule/xml_parser_interface.h>

class XmlBookmarkReaderInterface : public BookmarkSourceReaderInterface {
 public:
    explicit XmlBookmarkReaderInterface(XmlParserInterface& xml_parser):m_xml_parser{xml_parser}{}
  virtual ~XmlBookmarkReaderInterface() = default;
  protected:
    XmlParserInterface& m_xml_parser;
};


#endif //XML_BOOKMARK_READER_INTERFACE_H
