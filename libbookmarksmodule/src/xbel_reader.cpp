#include <libbookmarksmodule/data_types.h>
#include <libbookmarksmodule/utils.h>
#include <libbookmarksmodule/xbel_reader.h>

#include <QDebug>
#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItemModel>

bool isFolder(const QStandardItem* item) {
  return item->data(BookmarkRoles::IsFolderRole).toBool();
}

XbelReader::XbelReader(const BookmarkSource bookmark_source, const AbstractEnvironmentThemeFacade& theme_facade)
    : m_bookmark_source(bookmark_source), m_theme_facade{theme_facade} {
}

void XbelReader::readXbelTitle(QXmlStreamReader& xml_stream, QStandardItem* parent) {
  parent->setText(xml_stream.readElementText());
}


void XbelReader::readXbelMetadata(QXmlStreamReader& xml_stream, QStandardItem* parent) {

}

void XbelReader::readXbelIcon(QXmlStreamReader& xml_stream, QStandardItem* parent) {
  qDebug()<<__LINE__<<"Parsing icon";
  const auto iconname = xml_stream.attributes().value("name").toString();
  const auto customortheme = m_theme_facade.getCustomOrThemeIconPath(isFolder(parent), m_bookmark_source, iconname);
  parent->setData(customortheme, Qt::UserRole);
}
void XbelReader::readXbelInfo(QXmlStreamReader& xml_stream, QStandardItem* parent) {
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

void XbelReader::readXbelBookmark(QXmlStreamReader& xml_stream, QStandardItem* parent) {
  QStandardItem* bookmark=new QStandardItem();
  bookmark->setData(false, BookmarkRoles::IsFolderRole);
  bookmark->setToolTip(xml_stream.attributes().value("href").toString());
  bookmark->setData(int(m_bookmark_source), BookmarkRoles::SourceRole);
  parent->appendRow(bookmark);
  readXbelElement(xml_stream, bookmark);
}

void XbelReader::readXbelFolder(QXmlStreamReader& xml_stream, QStandardItem* parent) {
  QStandardItem* folder=new QStandardItem();

  folder->setData(true, BookmarkRoles::IsFolderRole);
  parent->setChild(parent->rowCount(),0,folder);
  readXbelElement(xml_stream, folder);
}

void XbelReader::readXbelElement(QXmlStreamReader& xml_stream, QStandardItem* parent) {
  while(!xml_stream.atEnd()&& !xml_stream.hasError())
  {
    QXmlStreamReader::TokenType token = xml_stream.readNext();
        if (token == QXmlStreamReader::StartDocument) {
            qDebug() << "Start Document";
            continue;
        }
        qDebug()<<"Name: "<<xml_stream.name()<<" qualified_name: "<<xml_stream.qualifiedName();
        if (token == QXmlStreamReader::StartElement) {
            if (xml_stream.name() == "bookmark") {
              readXbelBookmark(xml_stream, parent);
            } else if (xml_stream.name() == "folder") {
              readXbelFolder(xml_stream, parent);
            } else if (xml_stream.name() == "metadata") {
              readXbelMetadata(xml_stream, parent);
            } else if (xml_stream.name() == "title") {
              readXbelTitle(xml_stream, parent);
            }
        } else if (xml_stream.qualifiedName() == "bookmark:icon") {
              readXbelIcon(xml_stream, parent);
        }
    }
}
