#include <libbookmarksmodule/bookmarkmodel.h>
#include <libbookmarksmodule/xbel_file_reader.h>
#include <libbookmarksmodule/xbel_parser.h>
#include <KF5/KIconThemes/KIconTheme>
#include <QtCore/QAbstractItemModel>
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
      return;
    }
  }
  m_model->clear();

  XbelParser konqueror_parser(BookmarkSource::Konqueror, m_theme_facade);
  XbelFileReader konqueror_reader(konqueror_parser);
  if (konqueror_reader.setFilePath(m_konquerorpath)) {
    konqueror_reader.read(m_model->invisibleRootItem());
  }

  XbelParser okular_parser(BookmarkSource::Okular, m_theme_facade);
  XbelFileReader okular_reader(okular_parser);
  if (okular_reader.setFilePath(m_okularpath)) {
    QStandardItem* toplevelitem = new QStandardItem("Okular bookmarks");
    toplevelitem->setData(m_theme_facade.getCustomOrThemeIconPath(true,BookmarkSource::Okular,"okular"), Qt::UserRole);
    okular_reader.read(toplevelitem);
    m_model->invisibleRootItem()->appendRow(toplevelitem);
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

QHash<int, QByteArray> Bookmarkmodel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[Iconpathrole] = "icon";
  roles[Displayrole] = "display";
  roles[Tooltiprole] = "ttp";
  roles[IsFolderRole] = "isFolder";
  return roles;
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
  m_searchfield = searchfield;
  this->setFilterRegExp(QRegExp(m_searchfield, Qt::CaseInsensitive, QRegExp::FixedString));
  if (m_searchfield.length() == 0) {
    this->setSourceModel(m_model);
  } else {
    if (m_filteritemsonly == true) {
      this->setSourceModel(&m_model_items_only);
    }
  }
  emit searchfieldchanged(m_searchfield);
}
void Bookmarkmodel::setOkularBookmarkFolded(const bool& is_folded) {
  m_okular_bookmark_should_be_folded = is_folded;
  emit okularbookmarkfoldedChanged(m_okular_bookmark_should_be_folded);
}
void Bookmarkmodel::setFilterItemsOnly(const bool& filterItemsOnly) {
  m_filteritemsonly = filterItemsOnly;
  if (m_filteritemsonly && m_searchfield.length() > 0) {
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
    if (item->data(BookmarkRoles::IsFolderRole) == false) {
      QStandardItem* new_item = new QStandardItem;
      new_item->setData(item->data(BookmarkRoles::Iconpathrole), BookmarkRoles::Iconpathrole);
      new_item->setData(item->data(BookmarkRoles::Displayrole), BookmarkRoles::Displayrole);
      new_item->setData(item->data(BookmarkRoles::Tooltiprole), BookmarkRoles::Tooltiprole);
      new_item->setData(item->data(BookmarkRoles::IsFolderRole), BookmarkRoles::IsFolderRole);
      new_item->setData(item->data(BookmarkRoles::SourceRole), BookmarkRoles::SourceRole);
      m_model_items_only.appendRow(new_item);
    }
  }
}
