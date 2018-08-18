#ifndef BOOKMARKMODULE_HPP
#define BOOKMARKMODULE_HPP
#include <QtCore/QObject>
#include <QtGui/QStandardItemModel>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QIODevice>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QHash>
#include <QtQml/QtQml>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/QQmlExtensionInterface>


class Bookmarkmodel :public QSortFilterProxyModel
{
	Q_OBJECT
	Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged);
	Q_PROPERTY(QString konquerorBookmarks READ getPathForKonquerorBookmarks WRITE setPathForKonquerorBookmarks NOTIFY konquerorpathChanged);
	Q_PROPERTY(QString okularBookmarks READ getPathForOkularBookmarks WRITE setPathForOkularBookmarks NOTIFY okularpathChanged);
	Q_PROPERTY(QString firefoxBookmarks READ getPathForFirefoxBookmarks WRITE setPathForFirefoxBookmarks NOTIFY firefoxpathChanged);
	Q_PROPERTY(QString chromeBookmarks READ getPathForChromeBookmarks WRITE setPathForChromeBookamarks NOTIFY chromepathChanged );
	Q_PROPERTY(QString searchfield READ getSearchField WRITE setSearchField NOTIFY searchfieldchanged);
	
	
	enum class  CurrentlyParsing 
	{
		Okular,	/**< We are currently parsing an okular bookmarks repository */
		Konqueror, /**< We are currently parsing an konqueror bookmarks repository */
		Firefox, /**< We are currently parsing an firefox bookmarks repository */
		Chrome /**< We are currently parsing an chrome bookmarks repository */
	};
	
signals:
	void rowCountChanged(int newcount);
	void konquerorpathChanged(QString newpath);
	void okularpathChanged(QString newpath);
	void firefoxpathChanged(QString newpath);
	void chromepathChanged(QString newpath);
	void searchfieldchanged(QString searchfield);
	

public:
	Bookmarkmodel();
	virtual ~Bookmarkmodel();

	enum BookmarkRoles {
		Iconpathrole = Qt::UserRole,
		Displayrole =Qt::DisplayRole,
		Tooltiprole =Qt::ToolTipRole,
		IsFolderRole = Qt::UserRole+2
	};
	Q_INVOKABLE void setPathForKonquerorBookmarks(const QString& fullpath);
	Q_INVOKABLE void setPathForOkularBookmarks(const QString& fullpath);
	Q_INVOKABLE void setPathForFirefoxBookmarks(const QString& fullpath);
	Q_INVOKABLE void setPathForChromeBookamarks(const QString& fullpath);
	Q_INVOKABLE void setSearchField(const QString & searchfield);
	
	QString getPathForKonquerorBookmarks()const;
	QString getPathForOkularBookmarks()const;
	QString getPathForFirefoxBookmarks()const;
	QString getPathForChromeBookmarks()const;
	QString getSearchField()const;
	QHash<int, QByteArray> roleNames() const ;
	
	
	
public slots:
// 	void itemSelectedAsRoot(int index);
// 	void parentItemSelectedAsRoot();
	Q_INVOKABLE void ReadAllSources(bool forcereread);

private:
	void appendXBELFile(QString path); //TODO make it Q_INVOKABLE
	void appendChromeBookmarks(QString path);
	QStandardItem* appendFolderFromJsonBookmark(QJsonObject obj,QString name);
	QModelIndex* m_rootmodelindex;
	QString getCustomOrThemeIconPath(QString iconpathfromxml,QStandardItem* p_item);
	bool FileExists(const QString & path) const noexcept;
	//path
	QString m_konquerorpath;
	QString m_okularpath;
	QString m_firefoxpath;
	QString m_chromepath;
	//
	QString m_searchfield;
	bool m_konquerorpathhaschangedsincelastread={true};
	bool m_okularpathhaschangedsincelasteread={true};
	bool m_firefoxpathhaschangedsincelastread={true};
	bool m_chromepathhaschnagedsincelastread={true};
	
	QString getStandardIcon(const QStandardItem* p_item) const noexcept;
	CurrentlyParsing m_currentlyparsed;
	//Methods to read an xbel based bookmark fodlder
	bool readXBEL(QIODevice* device);
	QString readXBELTitle();
	void readXBELSeparator();
	QStandardItem* readXBELFolder();
	QStandardItem* readXBELBookmark();
	void readXBELInfoAndMetadata(QString p_blockname,QStandardItem* p_item);	
	QXmlStreamReader xml;
	
	QStandardItemModel* m_model;
};

class BookmarkmodelPlugin : public QQmlExtensionPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
	BookmarkmodelPlugin()
	{
		
	}
	~BookmarkmodelPlugin()
	{
		
	}
    	void registerTypes(const char *uri)
    	{
        	Q_ASSERT(uri == QLatin1String("MyPlugins"));
        	qmlRegisterType<Bookmarkmodel,1>(uri, 1, 0, "Bookmarkmodel");
// 		qmlRegisterType<Launcher,1>(uri,1,0,"Launcher");
    	}
};


// undefined reference to `QQmlExtensionPlugin::qt_metacast(char const*)'

#endif

