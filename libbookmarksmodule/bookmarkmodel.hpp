#ifndef BOOKMARKMODULE_HPP
#define BOOKMARKMODULE_HPP
#include <QtCore/QObject>
// #include <QtCore/QAbstractItemModel>
#include <QtGui/QStandardItemModel>
#include <QtCore/QIODevice>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QHash>
#include <QtQml/QtQml>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/QQmlExtensionInterface>
#include "bookmark.hpp"


class Bookmarkmodel :public QStandardItemModel
{
	Q_OBJECT
// 	Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
// 	Q_DISABLE_COPY(Bookmarmodel)
	Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
// 	Q_PROPERTY(s)
// 	
	
signals:
	void rowCountChanged(int newcount);
	
public:
	Bookmarkmodel();
// 	explicit Bookmarkmodel(const QString &data, QObject* parent=0);
	~Bookmarkmodel();
// 	void registerTypes(const char *uri)
// 	{
// 		qmlRegisterType<BookmarkModel>(uri, 1, 0,"Bookmarkmodel");
// 	}
	
	 enum BookmarkRoles {
		Iconpathrole = Qt::UserRole,
		Displayrole =Qt::DisplayRole,
		Tooltiprole=Qt::ToolTipRole
	};
	QHash<int, QByteArray> roleNames() const ;
	
	void appendXBELFile(QString path); //TODO make it Q_INVOKABLE
private:
	QString getCustomOrThemeIconPath(QString iconpathfromxml);
	
	
	//Methods to read an xbel based bookmark fodlder
	bool readXBEL(QIODevice* device);
	QString readXBELTitle();
	void readXBELSeparator();
	QStandardItem* readXBELFolder();
	QStandardItem* readXBELBookmark();
	void readXBELInfoAndMetadata(QString p_blockname,QStandardItem* p_item);	
	QXmlStreamReader xml;
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
    	}
};


// undefined reference to `QQmlExtensionPlugin::qt_metacast(char const*)'

#endif

