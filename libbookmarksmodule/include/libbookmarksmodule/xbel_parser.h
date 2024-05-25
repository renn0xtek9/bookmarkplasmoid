#ifndef XBEL_PARSER_H
#define XBEL_PARSER_H
#include <libbookmarksmodule/bookmarkmodel.h>
#include <libbookmarksmodule/xml_parser_interface.h>
#include <libbookmarksmodule/environment_theme_facade.h>

#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItemModel>
#include <memory>

class XbelParser :public XmlParserInterface {
 public:
  explicit XbelParser(const BookmarkSource bookmark_source, const AbstractEnvironmentThemeFacade& theme_facade);
  virtual ~XbelParser() = default;
  virtual void read(QXmlStreamReader& xml_stream, QStandardItem* parent) final;
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
