#include "bookmarkmodel.hpp"
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QVariant>
#include <QtCore/QString>



Bookmarkmodel::Bookmarkmodel() :QAbstractItemModel(nullptr)
{
	m_attributelist.append("Bookmarks");
	m_attributelist.append("/");
	m_attributelist.append("folder");
	m_attributelist.append("KDE");
	m_attributelist.append(true);
	m_attributelist.append("inode/directory");
	//data: 1 name 2 url 3 iconpath 4 origin 5 is folder 6 mimetype
	m_rootitem=new Bookmark(m_attributelist);
	appendXBELFile("/home/max/.local/share/konqueror/bookmarks.xml");	
	setupModelData(m_rootitem);
}
Bookmarkmodel::~Bookmarkmodel()
{
	delete m_rootitem;
}
void Bookmarkmodel::clearAttributeList()
{
	m_attributelist[0].setValue(QString(""));
	m_attributelist[1].setValue(QString("www.kde.org"));
	m_attributelist[2].setValue(QString("www"));
	m_attributelist[3].setValue(QString(""));
	m_attributelist[4].setValue(false);
	m_attributelist[5].setValue(QString(""));
}
void Bookmarkmodel::appendXBELFile(QString path)
{
	QFile xbelfile(path);
	if (xbelfile.open(QIODevice::OpenModeFlag::ReadOnly)){
		qDebug()<<"The QFile is open";
		if(!(readXBEL(&xbelfile)))
		{
	  		qDebug()<<"Problem when reading file";
		}
	}
	else{
		qDebug()<<"Could not open File";
	}
}
bool Bookmarkmodel::readXBEL(QIODevice* device)
{
	m_bkmrk=m_rootitem;
	m_bookmarks.clear();
	xml.setDevice(device);
	if (xml.readNextStartElement()) {
		if (xml.name() != "xbel"){
			xml.raiseError(QObject::tr("The file is not an XBEL version 1.0 file."));
			return false;
		}
	}
	if (xml.error()!=QXmlStreamReader::NoError)
 	{	
		return false ;
	}
	
	
	clearAttributeList();
	Q_ASSERT(xml.isStartElement() && xml.name() == "xbel");
	while (xml.readNextStartElement()) {
		if (xml.name() == "folder")
		readXBELFolder();
		else if (xml.name() == "bookmark")
		readXBELBookmark();
		else if (xml.name() == "separator")
		readXBELSeparator();
		else
		xml.skipCurrentElement();
	}
	return !xml.error();
}
void Bookmarkmodel::readXBELFolder()
{
	clearAttributeList();
	Q_ASSERT(xml.isStartElement() && xml.name() == "folder");
	m_attributelist[4].setValue(true);
	while (xml.readNextStartElement()) 
	{
		if (xml.name() == "title")
		{	
			m_attributelist[0].setValue(readXBELTitle());
		}
		else{
			if (xml.name() == "folder")
			{
				Bookmark* newbookmark=new Bookmark(m_attributelist,m_bkmrk);
				m_bkmrk->appendChild(newbookmark);
				m_bkmrk=newbookmark;
				readXBELFolder();
			}
			else {
				if (xml.name() == "bookmark")
				{
					Bookmark* newbookmark=new Bookmark(m_attributelist,m_bkmrk);
					m_bkmrk->appendChild(newbookmark);
					m_bkmrk=newbookmark;
					readXBELBookmark();
				}
				else 
				{
					if (xml.name() == "separator")
					{
						readXBELSeparator();
					}
					else
					{
						xml.skipCurrentElement();
					}
				}		
			}
		}
	}
}
void Bookmarkmodel::readXBELInfoAndMetadata(QString p_blockname)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == p_blockname);
	while(xml.readNextStartElement())
	{
		if(xml.name()=="icon")	//we are at bookmark::icon
		{
			if(m_bookmarks.length()>0)
   			{
				m_attributelist[2].setValue(xml.attributes().value("name").toString());
			}
		}
		readXBELInfoAndMetadata(xml.name().toString());	 
	}
}
void Bookmarkmodel::readXBELBookmark()
{
	clearAttributeList();
	Q_ASSERT(xml.isStartElement() && xml.name() == "bookmark");
	m_attributelist[4].setValue(false);
	m_attributelist[1].setValue(xml.attributes().value("href").toString());
	while (xml.readNextStartElement()) {
		if (xml.name() == "title")
		{
			m_attributelist[0].setValue(readXBELTitle());
		}
		else{
			if (xml.name()=="info")
			{
				readXBELInfoAndMetadata("info");
			}
			else{
				xml.skipCurrentElement();
			}
		}
	}
	Bookmark* newbookmark=new Bookmark(m_attributelist,m_bkmrk);
	m_bkmrk->appendChild(newbookmark);
}
QString Bookmarkmodel::readXBELTitle()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "title");

	QString title = xml.readElementText();
	if(m_bookmarks.length()>0){
		m_bookmarks.last().setName(title);
	}
	return title;
}
void Bookmarkmodel::readXBELSeparator()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "separator");
	xml.skipCurrentElement();
}
int Bookmarkmodel::columnCount(const QModelIndex& parent) const
{
	if (parent.isValid())
 	{
        	return static_cast<Bookmark*>(parent.internalPointer())->columnCount();
	}
	else
	{
        	return m_rootitem->columnCount();
	}
}
int Bookmarkmodel::rowCount(const QModelIndex& parent) const
{
	Bookmark *parentItem;
	if (parent.column() > 0){
        	return 0;
	}
	if (!parent.isValid()){
        	parentItem = m_rootitem;
	}
	else{
        	parentItem = static_cast<Bookmark*>(parent.internalPointer());
	}
    	return parentItem->childCount();
}
QVariant Bookmarkmodel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
        return QVariant();

    	if (role != Qt::DisplayRole)
    	{
		return QVariant();
	}

    	Bookmark *item = static_cast<Bookmark*>(index.internalPointer());

    	return item->data(index.column());
}
Qt::ItemFlags Bookmarkmodel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
 	{
        	return 0;
	}
	return QAbstractItemModel::flags(index);
}
QHash<int, QByteArray> Bookmarkmodel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[NameRole]="bookmarkname";
	roles[UrlRole]="bookmarkurl";
	roles[IconPathRole]="iconpath";
	roles[OriginRole]="origin";
	roles[IsFolderRole]="isfolder";
	roles[mimetypeRole]="mimetype";
	return roles;
}
QModelIndex Bookmarkmodel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent))
 	{
        	return QModelIndex();
	}
	Bookmark *parentItem;
	if (!parent.isValid()){
        	parentItem = m_rootitem;
	}
	else{
        	parentItem = static_cast<Bookmark*>(parent.internalPointer());
	}
    	Bookmark *childItem = parentItem->child(row);
    	if (childItem){
        	return createIndex(row, column, childItem);
	}
	else{
        	return QModelIndex();
	}
}
QVariant Bookmarkmodel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
         	return m_rootitem->data(section);
	}
     	return QVariant();
}
QModelIndex Bookmarkmodel::parent(const QModelIndex& index) const
{
	if (!index.isValid()){
		return QModelIndex();
	}
	Bookmark *childItem = static_cast<Bookmark*>(index.internalPointer());
	Bookmark *parentItem = childItem->parentItem();
	if (parentItem == m_rootitem){
		return QModelIndex();
	}
	return createIndex(parentItem->row(), 0, parentItem);
}
void Bookmarkmodel::setupModelData(Bookmark* parent)
{
	QList<Bookmark*> parents;
	QList<int> indentations;
	parents << parent;
	indentations << 0;
	int number = 0;
}




















