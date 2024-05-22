#ifndef BOOKMARKMODULE_HPP
#define BOOKMARKMODULE_HPP

#include <libbookmarksmodule/data_types.h>

#include <QtCore/QHash>
#include <QtCore/QIODevice>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QString>
#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItemModel>
#include <QtQml/QQmlExtensionInterface>
#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/QtQml>

class Bookmarkmodel : public QSortFilterProxyModel {
  Q_OBJECT
  Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged);
  Q_PROPERTY(QString konquerorBookmarks READ getPathForKonquerorBookmarks WRITE setPathForKonquerorBookmarks NOTIFY
                 konquerorpathChanged);
  Q_PROPERTY(
      QString okularBookmarks READ getPathForOkularBookmarks WRITE setPathForOkularBookmarks NOTIFY okularpathChanged);
  Q_PROPERTY(QString firefoxBookmarks READ getPathForFirefoxBookmarks WRITE setPathForFirefoxBookmarks NOTIFY
                 firefoxpathChanged);
  Q_PROPERTY(
      QString chromeBookmarks READ getPathForChromeBookmarks WRITE setPathForChromeBookamarks NOTIFY chromepathChanged);
  Q_PROPERTY(QString searchfield READ getSearchField WRITE setSearchField NOTIFY searchfieldchanged);
  Q_PROPERTY(bool okularBookarkFolded WRITE setOkularBookmarkFolded NOTIFY okularbookmarkfoldedChanged)
  Q_PROPERTY(bool filterItemsOnly WRITE setFilterItemsOnly NOTIFY filteritemonlyChanged)

 signals:
  void rowCountChanged(int newcount);
  void konquerorpathChanged(QString newpath);
  void okularpathChanged(QString newpath);
  void firefoxpathChanged(QString newpath);
  void chromepathChanged(QString newpath);
  void searchfieldchanged(QString searchfield);
  void okularbookmarkfoldedChanged(bool is_folded);
  void filteritemonlyChanged(bool filterItemsOnly);

 public:
  Bookmarkmodel();
  virtual ~Bookmarkmodel();

  Q_INVOKABLE void setPathForKonquerorBookmarks(const QString& fullpath);
  Q_INVOKABLE void setPathForOkularBookmarks(const QString& fullpath);
  Q_INVOKABLE void setPathForFirefoxBookmarks(const QString& fullpath);
  Q_INVOKABLE void setPathForChromeBookamarks(const QString& fullpath);
  Q_INVOKABLE void setSearchField(const QString& searchfield);
  Q_INVOKABLE void setOkularBookmarkFolded(const bool& is_folded);
  Q_INVOKABLE void setFilterItemsOnly(const bool& filterItemsOnly);

  QString getPathForKonquerorBookmarks() const;
  QString getPathForOkularBookmarks() const;
  QString getPathForFirefoxBookmarks() const;
  QString getPathForChromeBookmarks() const;
  QString getSearchField() const;
  QHash<int, QByteArray> roleNames() const override;

 public slots:
  // 	void itemSelectedAsRoot(int index);
  // 	void parentItemSelectedAsRoot();
  Q_INVOKABLE void ReadAllSources(bool forcereread);

 private:
  void appendXBELFile(QString path);  // TODO make it Q_INVOKABLE
  void appendChromeBookmarks(QString path);
  QStandardItem* appendFolderFromJsonBookmark(QJsonObject obj, QString name);
  QModelIndex* m_rootmodelindex;
  QString getCustomOrThemeIconPath(QString iconpathfromxml, QStandardItem* p_item);
  bool FileExists(const QString& path) const noexcept;
  bool m_okular_bookmark_should_be_folded{false};

  // path
  QString m_konquerorpath;
  QString m_okularpath;
  QString m_firefoxpath;
  QString m_chromepath;
  //
  QString m_searchfield;
  bool m_konquerorpathhaschangedsincelastread = {true};
  bool m_okularpathhaschangedsincelasteread = {true};
  bool m_firefoxpathhaschangedsincelastread = {true};
  bool m_chromepathhaschnagedsincelastread = {true};
  bool m_filteritemsonly = {false};

  QString getStandardIcon(const QStandardItem* p_item) const noexcept;
  BookmarkSource m_currentlyparsed;
  // Methods to read an xbel based bookmark fodlder
  bool readXBEL(QIODevice* device);
  QString readXBELTitle();
  void readXBELSeparator();
  QStandardItem* readXBELFolder();
  QStandardItem* readXBELBookmark();
  void readXBELInfoAndMetadata(QString p_blockname, QStandardItem* p_item);
  QXmlStreamReader xml;

  QStandardItemModel* m_model;
  QStandardItemModel m_model_items_only{this};

  QStandardItem* m_item_to_append_to{nullptr};

  QList<QStandardItem*> parseChildsAndListItem(QModelIndex parent, int col_start = 0);
 private slots:
  void updateModelItemsOnly();
};

#endif
