#ifndef XML_PARSER_INTERFACE_H
#define XML_PARSER_INTERFACE_H
#include <libbookmarksmodule/abstract_environment_theme_facade.h>

#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItemModel>

class XmlParserInterface {
 public:
  XmlParserInterface(const BookmarkSource, const AbstractEnvironmentThemeFacade&) {
  }
  virtual ~XmlParserInterface() = default;
  virtual void read(QXmlStreamReader& xml_stream, QStandardItem* parent) = 0;
};

#endif  // XML_PARSER_INTERFACE_H
