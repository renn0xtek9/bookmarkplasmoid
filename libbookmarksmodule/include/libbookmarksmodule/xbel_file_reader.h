#ifndef XBEL_FILE_READER_H
#define XBEL_FILE_READER_H
#include <libbookmarksmodule/bookmark_source_reader_interface.h>
#include <libbookmarksmodule/data_types.h>

#include <QtGui/QStandardItem>

class XbelFileReader : public BookmarkSourceReaderInterface {
 public:
  explicit XbelFileReader(const BookmarkSource& bookmark_source);
  virtual ~XbelFileReader() = default;

  void setFilePath(const QString& file_path);

  virtual void read(QStandardItem* root_item) final;
};

#endif  // XBEL_FILE_READER_H
