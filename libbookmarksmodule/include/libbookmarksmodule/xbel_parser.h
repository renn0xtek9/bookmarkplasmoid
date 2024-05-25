#ifndef XBEL_PARSER_H
#define XBEL_PARSER_H
#include <libbookmarksmodule/bookmarkmodel.h>
#include <libbookmarksmodule/environment_theme_facade.h>

#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItemModel>
#include <memory>

class XbelParser {
 public:
  explicit XbelParser(const BookmarkSource bookmark_source, const AbstractEnvironmentThemeFacade& theme_facade);
  void read(QXmlStreamReader& xml_stream, QStandardItem* parent);
 private:
  void readXbelTitle(QXmlStreamReader& xml_stream, QStandardItem* parent);
  void readXbelInfo(QXmlStreamReader& xml_stream, QStandardItem* parent);
  void readXbelIcon(QXmlStreamReader& xml_stream, QStandardItem* parent);
  void readXbelBookmark(QXmlStreamReader& xml_stream, QStandardItem* parent);
  void readXbelFolder(QXmlStreamReader& xml_stream, QStandardItem* parent);
  BookmarkSource m_bookmark_source;
  const AbstractEnvironmentThemeFacade& m_theme_facade;
};

#endif  // xbel_parser_H
