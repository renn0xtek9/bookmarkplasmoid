#include "bookmarkmodel.hpp"
#include <KF5/KIconThemes/KIconTheme>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtGui/QIcon>

Bookmarkmodel::Bookmarkmodel() : QSortFilterProxyModel(nullptr) {
  m_model = new QStandardItemModel(this);
  this->setSourceModel(m_model);
  this->setRecursiveFilteringEnabled(true);
  m_searchfield = "";
  emit searchfieldchanged(m_searchfield);
  connect(this, SIGNAL(rowCountChanged(int)), this, SLOT(updateModelItemsOnly()));
}
Bookmarkmodel::~Bookmarkmodel() {
}
void Bookmarkmodel::setPathForKonquerorBookmarks(const QString& fullpath) {
  m_konquerorpathhaschangedsincelastread = false;
  if (m_konquerorpath != fullpath) {
    m_konquerorpath = fullpath;
    m_konquerorpathhaschangedsincelastread = true;
    emit konquerorpathChanged(fullpath);
  }
}
void Bookmarkmodel::setPathForOkularBookmarks(const QString& fullpath) {
  m_okularpathhaschangedsincelasteread = false;
  if (m_okularpath != fullpath) {
    m_okularpath = fullpath;
    m_currentlyparsed = BookmarkSource::Okular;
    m_okularpathhaschangedsincelasteread = true;
    emit okularpathChanged(fullpath);
  }
}
void Bookmarkmodel::setPathForFirefoxBookmarks(const QString& fullpath) {
  m_firefoxpathhaschangedsincelastread = false;
  if (m_firefoxpath != fullpath) {
    m_firefoxpath = fullpath;
    m_firefoxpathhaschangedsincelastread = true;
    emit firefoxpathChanged(fullpath);
  }
}
void Bookmarkmodel::setPathForChromeBookamarks(const QString& fullpath) {
  m_chromepathhaschnagedsincelastread = false;
  if (m_chromepath != fullpath) {
    m_chromepath = fullpath;
    m_chromepathhaschnagedsincelastread = true;
    emit chromepathChanged(fullpath);
  }
}
void Bookmarkmodel::ReadAllSources(bool forcereread) {
  if (!forcereread) {
    if (!m_okularpathhaschangedsincelasteread && !m_firefoxpathhaschangedsincelastread &&
        !m_konquerorpathhaschangedsincelastread && !m_chromepathhaschnagedsincelastread) {
      return;  // If nothing has changed just leave it
    }
  }
  m_model->clear();
  if (FileExists(m_konquerorpath)) {
    m_currentlyparsed = BookmarkSource::Konqueror;
    appendXBELFile(m_konquerorpath);
  }
  if (FileExists(m_okularpath)) {
    if (m_okular_bookmark_should_be_folded) {
      QStandardItem* toplevelitem = new QStandardItem("Okular bookmarks");
      toplevelitem->setData(getCustomOrThemeIconPath("okular", toplevelitem), Qt::UserRole);
      m_item_to_append_to = toplevelitem;
      m_model->invisibleRootItem()->appendRow(toplevelitem);
    }
    m_currentlyparsed = BookmarkSource::Okular;
    appendXBELFile(m_okularpath);
  }
  if (FileExists(m_firefoxpath)) {
    m_currentlyparsed = BookmarkSource::Firefox;
    // TODO implement json bookmarks
  }
  if (FileExists(m_chromepath)) {
    m_currentlyparsed = BookmarkSource::Chrome;
    appendChromeBookmarks(m_chromepath);
  }
  emit rowCountChanged(rowCount());
}
QString Bookmarkmodel::getPathForFirefoxBookmarks() const {
  return m_firefoxpath;
}
QString Bookmarkmodel::getPathForKonquerorBookmarks() const {
  return m_konquerorpath;
}
QString Bookmarkmodel::getPathForOkularBookmarks() const {
  return m_okularpath;
}
QString Bookmarkmodel::getPathForChromeBookmarks() const {
  return m_chromepath;
}
void Bookmarkmodel::appendXBELFile(QString path) {
  QFile xbelfile(path);
  if (xbelfile.open(QIODevice::OpenModeFlag::ReadOnly)) {
    if (!(readXBEL(&xbelfile))) {
    }
  } else {
  }
}
bool Bookmarkmodel::readXBEL(QIODevice* device) {
  xml.setDevice(device);
  if (xml.readNextStartElement()) {
    if (xml.name() != "xbel") {
      xml.raiseError(QObject::tr("The file is not an XBEL version 1.0 file."));
      return false;
    }
  }
  if (xml.error() != QXmlStreamReader::NoError) {
    return false;
  }
  Q_ASSERT(xml.isStartElement() && xml.name() == "xbel");
  if (m_item_to_append_to == nullptr) {
    m_item_to_append_to = m_model->invisibleRootItem();
  }
  while (xml.readNextStartElement()) {
    if (xml.name() == "folder") {
      m_item_to_append_to->appendRow(readXBELFolder());
    } else {
      if (xml.name() == "bookmark") {
        m_item_to_append_to->appendRow(readXBELBookmark());
      } else {
        if (xml.name() == "separator") {
          readXBELSeparator();
        } else {
          xml.skipCurrentElement();
        }
      }
    }
  }
  return !xml.error();
}
QStandardItem* Bookmarkmodel::readXBELFolder() {
  QStandardItem* ret = new QStandardItem();
  ret->setData(true, BookmarkRoles::IsFolderRole);
  Q_ASSERT(xml.isStartElement() && xml.name() == "folder");
  ret->setData(getStandardIcon(ret), Qt::UserRole);  // This ensure there is a default icon on the folder
  if (m_currentlyparsed == BookmarkSource::Okular)   // Force icon for okular books
  {
    ret->setData(getCustomOrThemeIconPath("okular", ret), Qt::UserRole);
  }
  while (xml.readNextStartElement()) {
    if (xml.name() == "title") {
      QString title = readXBELTitle();
      ret->setText(title);
    } else {
      if (xml.name() == "folder") {
        ret->appendRow(readXBELFolder());  // TODO ensure that it affect this as parent of new bookmarkt
      } else {
        if (xml.name() == "bookmark") {
          ret->appendRow(readXBELBookmark());
        } else {
          if (xml.name() == "info") {
            readXBELInfoAndMetadata("info", ret);
          } else {
            if (xml.name() == "separator") {
              readXBELSeparator();
            } else {
              xml.skipCurrentElement();
            }
          }
        }
      }
    }
  }
  return ret;
}
QStandardItem* Bookmarkmodel::readXBELBookmark() {
  Q_ASSERT(xml.isStartElement() && xml.name() == "bookmark");
  QStandardItem* ret = new QStandardItem();  // This is the bookmark (not a folder) that we are going to build
  ret->setData(false, BookmarkRoles::IsFolderRole);
  ret->setToolTip(xml.attributes().value("href").toString());               // The link goes on the whatsthis
  ret->setData(int(BookmarkSource::Konqueror), BookmarkRoles::SourceRole);  // We save the source in the item model
  while (xml.readNextStartElement()) {
    if (xml.name() == "title") {
      ret->setText(readXBELTitle());
    } else {
      if (xml.name() == "info") {
        readXBELInfoAndMetadata("info", ret);
      } else {
        xml.skipCurrentElement();
      }
    }
  }
  return ret;
}
void Bookmarkmodel::readXBELInfoAndMetadata(QString p_blockname, QStandardItem* p_item) {
  Q_ASSERT(xml.isStartElement() && xml.name() == p_blockname);
  while (xml.readNextStartElement()) {
    if (xml.name() == "icon")  // we are at bookmark::icon
    {
      QString iconname = xml.attributes().value("name").toString();
      QString customortheme = getCustomOrThemeIconPath(iconname, p_item);
      p_item->setData(customortheme, Qt::UserRole);
    }
    readXBELInfoAndMetadata(xml.name().toString(), p_item);
  }
}
QString Bookmarkmodel::readXBELTitle() {
  Q_ASSERT(xml.isStartElement() && xml.name() == "title");
  QString title = xml.readElementText();
  return title;
}
void Bookmarkmodel::readXBELSeparator() {
  Q_ASSERT(xml.isStartElement() && xml.name() == "separator");
  xml.skipCurrentElement();
}
QHash<int, QByteArray> Bookmarkmodel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[Iconpathrole] = "icon";
  roles[Displayrole] = "display";
  roles[Tooltiprole] = "ttp";
  roles[IsFolderRole] = "isFolder";
  return roles;
}
QString Bookmarkmodel::getCustomOrThemeIconPath(QString iconpathfromxml, QStandardItem* p_item) {
  QFileInfo finfo(iconpathfromxml);
  QString path, standard, iconsource;
  QStringList themelist("hicolor");
  iconsource = iconpathfromxml;
  if (!finfo.isFile()) {
    iconsource = "";
    themelist.append(KIconTheme::current());
    foreach (QString str, themelist) {
      KIconTheme theme(str);
      path = theme.iconPathByName(iconpathfromxml, 24, KIconLoader::MatchBest);
      if (!path.isEmpty()) {
        iconsource = path;
        break;
      }
    }
    if (iconsource.isEmpty()) {
      themelist.append(KIconTheme::current());
      standard = getStandardIcon(p_item);
      foreach (QString str, themelist) {
        KIconTheme theme(str);
        path = theme.iconPathByName(standard, 24, KIconLoader::MatchBest);
        if (!path.isEmpty()) {
          iconsource = path;
          break;
        }
      }
    }
  }
  return iconsource;
}
QString Bookmarkmodel::getStandardIcon(const QStandardItem* p_item) const noexcept {
  if (p_item->data(BookmarkRoles::IsFolderRole).toBool() == true) {
    switch (m_currentlyparsed) {
      case (BookmarkSource::Konqueror): {
        return QString("folder-bookmark");
      }
      case (BookmarkSource::Okular): {
        return QString("okular");
      }
      case (BookmarkSource::Firefox): {
        return QString("firefox");
      }
      case (BookmarkSource::Chrome): {
        return QString("folder-bookmark");
      }
    }
  } else {
    switch (m_currentlyparsed) {
      case (BookmarkSource::Konqueror): {
        return QString("text-html");
      }
      case (BookmarkSource::Okular): {
        return QString("application-pdf");
      }
      case (BookmarkSource::Firefox): {
        return QString("text-html");
      }
      case (BookmarkSource::Chrome): {
        return QString("google-chrome");
      }
    }
  }
  return QString("text-html");
}
bool Bookmarkmodel::FileExists(const QString& path) const noexcept {
  QFileInfo finfo(path);
  return finfo.exists();
}
void Bookmarkmodel::setSearchField(const QString& searchfield) {
  m_searchfield=searchfield;
  this->setFilterRegExp(QRegExp(m_searchfield, Qt::CaseInsensitive, QRegExp::FixedString));
  emit searchfieldchanged(m_searchfield);
}
void Bookmarkmodel::setOkularBookmarkFolded(const bool& is_folded) {
  m_okular_bookmark_should_be_folded = is_folded;
  emit okularbookmarkfoldedChanged(m_okular_bookmark_should_be_folded);
}
void Bookmarkmodel::setFilterItemsOnly(const bool& filterItemsOnly) {
  m_filteritemsonly = filterItemsOnly;
  if (m_filteritemsonly && m_searchfield.length()>0) {
    this->setSourceModel(&m_model_items_only);
  }
  emit filteritemonlyChanged(m_filteritemsonly);
}
QString Bookmarkmodel::getSearchField() const {
  return m_searchfield;
}
void Bookmarkmodel::appendChromeBookmarks(QString path) {
  QFile jsonfile(path);
  if (jsonfile.open(QIODevice::OpenModeFlag::ReadOnly | QIODevice::Text)) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonfile.readAll());
    jsonfile.close();
    QJsonObject rootobj = jsonDoc.object();
    if (rootobj.contains("roots")) {
      rootobj = rootobj["roots"].toObject();
    } else {
      return;
    }
    QJsonObject current = rootobj;

    if (rootobj.keys().contains("bookmark_bar")) {
      current = current["bookmark_bar"].toObject();
      m_model->invisibleRootItem()->appendRow(appendFolderFromJsonBookmark(current, "Chrome bookmarks bar"));
    }
    if (rootobj.keys().contains("others")) {
      current = rootobj["other"].toObject();
      m_model->invisibleRootItem()->appendRow(appendFolderFromJsonBookmark(current, "Chrome"));
    }
  } else {
  }
}
QStandardItem* Bookmarkmodel::appendFolderFromJsonBookmark(QJsonObject obj, QString name) {
  QStandardItem* ret = new QStandardItem();
  ret->setData(true, BookmarkRoles::IsFolderRole);
  ret->setData(getStandardIcon(ret), Qt::UserRole);  // This ensure there is a default icon on the folder
  ret->setText(name);
  if (obj.keys().contains("children")) {
    if (obj["children"].isArray()) {
      for (int i = 0; i < obj["children"].toArray().count(); i++) {
        QJsonObject localobj = obj["children"].toArray().at(i).toObject();
        if (!localobj.contains("type")) {
          break;
        }
        if (localobj["type"] == "folder") {
          // we have spotted a fodler in the bookmarks list
          ret->appendRow(appendFolderFromJsonBookmark(localobj, localobj["name"].toString()));
        }
        if (localobj["type"] == "url") {
          // we have spotted a url in the bookmark list
          QStandardItem* bookmark = new QStandardItem();
          bookmark->setData(false, BookmarkRoles::IsFolderRole);
          bookmark->setToolTip(localobj["url"].toString());  // The link goes on the whatsthis
          bookmark->setData(getStandardIcon(bookmark), Qt::UserRole);
          bookmark->setText(localobj["name"].toString());
          ret->appendRow(bookmark);
        }
      }
    }
  }
  return ret;
}
void Bookmarkmodel::save(BookmarkSource src, QString filename) {
  // TODO implement me !
}

QList<QStandardItem*> Bookmarkmodel::parseChildsAndListItem(QModelIndex parent, int col_start) {
  QList<QStandardItem*> list{};
  for (int row = 0; row < m_model->rowCount(parent); ++row) {
    QModelIndex index = m_model->index(row, 0, parent);
    QStandardItem* item = m_model->itemFromIndex(index);
    if (item->hasChildren()) {
      list.append(parseChildsAndListItem(index, col_start + 1));
    } else {
      list.append(item);
    }
  }
  return list;
}

void Bookmarkmodel::updateModelItemsOnly() {
  QList<QStandardItem*> list{};
  list = parseChildsAndListItem(QModelIndex());
  m_model_items_only.clear();
  for (const auto& item : list) {
    QStandardItem* new_item = new QStandardItem;  // We cannot have one item for two different model
    new_item->setData(item->data(BookmarkRoles::Iconpathrole), BookmarkRoles::Iconpathrole);
    new_item->setData(item->data(BookmarkRoles::Displayrole), BookmarkRoles::Displayrole);
    new_item->setData(item->data(BookmarkRoles::Tooltiprole), BookmarkRoles::Tooltiprole);
    new_item->setData(item->data(BookmarkRoles::IsFolderRole), BookmarkRoles::IsFolderRole);
    new_item->setData(item->data(BookmarkRoles::SourceRole), BookmarkRoles::SourceRole);
    m_model_items_only.appendRow(new_item);
  }
}
