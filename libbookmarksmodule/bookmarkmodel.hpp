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
	//data: 1 name 2 url 3 iconpath 4 origin 5 is folder 6 mimetype
	enum BookmarkRoles {
        	NameRole = Qt::UserRole + 1,
		UrlRole = Qt::UserRole + 2,
		IconPathRole=Qt::UserRole +3,
		OriginRole=Qt::UserRole+4,
		IsFolderRole=Qt::UserRole+5,
		mimetypeRole=Qt::UserRole+6
    	};
	
	void appendXBELFile(QString path); //TODO make it Q_INVOKABLE
	//NEW
// 	QVariant data(const QModelIndex &index, int role) const override;
// 	Qt::ItemFlags flags(const QModelIndex &index) const override;
// // 	QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;
// 	QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;
// 	QModelIndex parent(const QModelIndex &index) const override;
// 	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
// 	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
// 	QHash<int, QByteArray> roleNames() const override;

private:
	//New
	void setupModelData( Bookmark *parent);
	
	//Methods to read an xbel based bookmark fodlder
	bool readXBEL(QIODevice* device);
	QString readXBELTitle();
	void readXBELSeparator();
	void readXBELFolder();
	void readXBELBookmark();
	void readXBELInfoAndMetadata(QString p_blockname);

	QStandardItem* m_bkmrk=nullptr;
	
	
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
        	Q_ASSERT(uri == QLatin1String("bookmarkmodelplugin"));
        	qmlRegisterType<Bookmarkmodel,1>(uri, 1, 0, "bookmarkmodelplugin");
    	}
};


// undefined reference to `QQmlExtensionPlugin::qt_metacast(char const*)'

#endif

