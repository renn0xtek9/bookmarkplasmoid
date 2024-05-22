#include <libbookmarksmodule/data_types.h>
#include <libbookmarksmodule/utils.h>
#include <libbookmarksmodule/xbel_reader.h>

#include <QDebug>
#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItemModel>

bool isFolder(const QStandardItem& item) {
  return item.data(BookmarkRoles::IsFolderRole).toBool();
}

XbelReader::XbelReader(const BookmarkSource bookmark_source, const AbstractEnvironmentThemeFacade& theme_facade)
    : m_bookmark_source(bookmark_source), m_theme_facade{theme_facade} {
}

void XbelReader::readXbelTitle(QXmlStreamReader& xml_stream, QStandardItem& parent) {
  parent.setText(xml_stream.readElementText());
}

void XbelReader::readXbelBookmark(QXmlStreamReader& xml_stream, QStandardItem& parent) {
  if (!(xml_stream.name() == "bookmark")) {
    return;
  }
  parent.setData(false, BookmarkRoles::IsFolderRole);
  parent.setToolTip(xml_stream.attributes().value("href").toString());
  parent.setData(int(BookmarkSource::Konqueror), BookmarkRoles::SourceRole);
  while (xml_stream.readNextStartElement()) {
    if (xml_stream.name() == "title") {
      readXbelTitle(xml_stream, parent);
      continue;
    }
    if (xml_stream.name() == "info") {
      readXbelInfo(xml_stream, parent);
      continue;
    }
  }
}
void XbelReader::readXbelMetadata(QXmlStreamReader& xml_stream, QStandardItem& parent) {
  while (xml_stream.readNextStartElement()) {
    readXbelElement(xml_stream, parent);
  }
}

void XbelReader::readXbelIcon(QXmlStreamReader& xml_stream, QStandardItem& parent) {
  const auto iconname = xml_stream.attributes().value("name").toString();
  const auto customortheme = m_theme_facade.getCustomOrThemeIconPath(isFolder(parent), m_bookmark_source, iconname);
  parent.setData(customortheme, Qt::UserRole);
}
void XbelReader::readXbelInfo(QXmlStreamReader& xml_stream, QStandardItem& parent) {
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

void XbelReader::readXbelFolder(QXmlStreamReader& xml_stream, QStandardItem& parent) {
  parent.setData(true, BookmarkRoles::IsFolderRole);
  while (xml_stream.readNextStartElement()) {
    qDebug() << "Parent Name: " << xml_stream.name();

    while (xml_stream.readNextStartElement()) {
      qDebug() << "Child Name: " << xml_stream.name();
      xml_stream.skipCurrentElement();
    }
  }
}

void XbelReader::readXbelElement(QXmlStreamReader& xml_stream, QStandardItem& parent) {
  qDebug() << "Element Name: " << xml_stream.name();
  fflush(stderr);
  if (xml_stream.name() == "bookmark") {
    readXbelBookmark(xml_stream, parent);
  } else if (xml_stream.name() == "folder") {
    readXbelFolder(xml_stream, parent);
  } else if (xml_stream.name() == "icon") {
    readXbelIcon(xml_stream, parent);
  } else if (xml_stream.name() == "metadata") {
    readXbelMetadata(xml_stream, parent);
  } else if (xml_stream.name() == "info") {
    readXbelInfo(xml_stream, parent);
  } else if (xml_stream.name() == "title") {
    readXbelTitle(xml_stream, parent);
  } else {
    xml_stream.skipCurrentElement();
  }
}
