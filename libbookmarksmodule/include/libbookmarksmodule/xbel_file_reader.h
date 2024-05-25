#ifndef XBEL_FILE_READER_H
#define XBEL_FILE_READER_H
#include <libbookmarksmodule/xml_bookmark_reader_interface.h>
#include <libbookmarksmodule/data_types.h>

#include <QtGui/QStandardItem>

class XbelFileReader : public XmlBookmarkReaderInterface {
 public:
  XbelFileReader(XmlParserInterface& xml_parser,const BookmarkSource& bookmark_source);
  virtual ~XbelFileReader() = default;

  bool setFilePath(const QString& file_path);

  virtual void read(QStandardItem* root_item) final;
  private:
  QString m_file_path;
};

#endif  // XBEL_FILE_READER_H
