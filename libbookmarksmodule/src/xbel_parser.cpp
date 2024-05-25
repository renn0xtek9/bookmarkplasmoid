#include <libbookmarksmodule/data_types.h>
#include <libbookmarksmodule/utils.h>
#include <libbookmarksmodule/xbel_parser.h>

#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItemModel>

bool isFolder(const QStandardItem* item) {
  return item->data(BookmarkRoles::IsFolderRole).toBool();
}

XbelParser::XbelParser(const BookmarkSource bookmark_source, const AbstractEnvironmentThemeFacade& theme_facade)
    : m_bookmark_source(bookmark_source), m_theme_facade{theme_facade} {
}

void XbelParser::readXbelTitle(QXmlStreamReader& xml_stream, QStandardItem* parent) {
  parent->setText(xml_stream.readElementText());
}

void XbelParser::readXbelIcon(QXmlStreamReader& xml_stream, QStandardItem* parent) {
  const auto iconname = xml_stream.attributes().value("name").toString();
  const auto customortheme = m_theme_facade.getCustomOrThemeIconPath(isFolder(parent), m_bookmark_source, iconname);
  parent->setData(customortheme, Qt::UserRole);
}
void XbelParser::readXbelInfo(QXmlStreamReader& xml_stream, QStandardItem* parent) {
  while (xml_stream.readNextStartElement()) {
    if (xml_stream.name() == "metadata") {
      while (xml_stream.readNextStartElement()) {
        if (xml_stream.name() == "icon") {
          readXbelIcon(xml_stream, parent);
        }
      }
    }
  }
}

void XbelParser::readXbelBookmark(QXmlStreamReader& xml_stream, QStandardItem* parent) {
  QStandardItem* bookmark=new QStandardItem();
  bookmark->setData(false, BookmarkRoles::IsFolderRole);
  bookmark->setToolTip(xml_stream.attributes().value("href").toString());
  bookmark->setData(int(m_bookmark_source), BookmarkRoles::SourceRole);
  parent->appendRow(bookmark);
  read(xml_stream, bookmark);
}

void XbelParser::readXbelFolder(QXmlStreamReader& xml_stream, QStandardItem* parent) {
  QStandardItem* folder=new QStandardItem();

  folder->setData(true, BookmarkRoles::IsFolderRole);
  parent->setChild(parent->rowCount(),0,folder);
  read(xml_stream, folder);
}

void XbelParser::read(QXmlStreamReader& xml_stream, QStandardItem* parent) {
  while(!xml_stream.atEnd()&& !xml_stream.hasError())
  {
    QXmlStreamReader::TokenType token = xml_stream.readNext();
        if (token == QXmlStreamReader::StartDocument) {
            continue;
        }
        if (token == QXmlStreamReader::StartElement) {
            if (xml_stream.name() == "bookmark") {
              readXbelBookmark(xml_stream, parent);
            } else if (xml_stream.name() == "folder") {
              readXbelFolder(xml_stream, parent);
            } else if (xml_stream.name() == "title") {
              readXbelTitle(xml_stream, parent);
            }
        } else if (xml_stream.qualifiedName() == "bookmark:icon") {
              readXbelIcon(xml_stream, parent);
        }
    }
}
