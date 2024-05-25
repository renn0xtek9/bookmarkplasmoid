#ifndef BOOKMARK_SOURCE_READER_INTERFACE_H
#define BOOKMARK_SOURCE_READER_INTERFACE_H

#include <QtGui/QStandardItem>

class BookmarkSourceReaderInterface {
 public:
  virtual ~BookmarkSourceReaderInterface() = default;
  virtual void read(QStandardItem* root_item) = 0;
};

#endif // BOOKMARK_SOURCE_READER_INTERFACE_H
