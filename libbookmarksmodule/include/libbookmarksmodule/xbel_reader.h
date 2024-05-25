#ifndef XBEL_READER_H
#define XBEL_READER_H
#include <libbookmarksmodule/bookmarkmodel.h>
#include <libbookmarksmodule/environment_theme_facade.h>

#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItemModel>
#include <memory>

class XbelReader {
 public:
  explicit XbelReader(const BookmarkSource bookmark_source, const AbstractEnvironmentThemeFacade& theme_facade);
  void readXbelTitle(QXmlStreamReader& xml_stream, QStandardItem* parent);
  void readXbelInfo(QXmlStreamReader& xml_stream, QStandardItem* parent);
  void readXbelIcon(QXmlStreamReader& xml_stream, QStandardItem* parent);
  void readXbelBookmark(QXmlStreamReader& xml_stream, QStandardItem* parent);
  void readXbelFolder(QXmlStreamReader& xml_stream, QStandardItem* parent);
  void read(QXmlStreamReader& xml_stream, QStandardItem* parent);

 private:
  BookmarkSource m_bookmark_source;
  const AbstractEnvironmentThemeFacade& m_theme_facade;
};

#endif  // XBEL_READER_H
