#ifndef BOOKMARKMODULE_HPP
#define BOOKMARKMODULE_HPP
#include <qt5/QtCore/QObject>
#include <qt5/QtCore/QAbstractItemModel>
#include <qt5/QtCore/QIODevice>
#include <qt5/QtCore/QString>
#include <qt5/QtCore/QList>
#include <qt5/QtCore/QXmlStreamReader>
#include <qt5/QtCore/QHash>
#include "bookmark.hpp"

class Bookmarkmodel :public QAbstractItemModel
{
	Q_OBJECT
public:
	explicit Bookmarkmodel(const QString &data, QObject* parent=0);
	~Bookmarkmodel();
	
	//data: 1 name 2 url 3 iconpath 4 origin 5 is folder 6 mimetype
	enum BookmarkRoles {
        	NameRole = Qt::UserRole + 1,
		UrlRole = Qt::UserRole + 2,
		IconPathRole=Qt::UserRole +3,
		OriginRole=Qt::UserRole+4,
		IsFolderRole=Qt::UserRole+5,
		mimetypeRole=Qt::UserRole+6
    	};
	
	
	void appendXBELFile(QString path);
	//NEw
	QVariant data(const QModelIndex &index, int role) const override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;
	QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;
	QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &index) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;


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
	
	
	
	Bookmark* m_bkmrk=nullptr;
	Bookmark* m_rootitem=nullptr;
	QList<QVariant> m_attributelist;
	void clearAttributeList();
	
	
	
	
	QXmlStreamReader xml;
	QList<Bookmark> m_bookmarks;
	QString s_currentpath;

};



#endif

