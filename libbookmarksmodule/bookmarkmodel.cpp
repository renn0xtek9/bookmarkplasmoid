#include "bookmarkmodel.hpp"
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtGui/QIcon>



Bookmarkmodel::Bookmarkmodel() :QStandardItemModel(nullptr)
{
	m_bkmrk=invisibleRootItem();
	appendXBELFile("/home/max/.local/share/konqueror/bookmarks.xml");	
}
Bookmarkmodel::~Bookmarkmodel()
{

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
	
	Q_ASSERT(xml.isStartElement() && xml.name() == "xbel");
// 	readXBELFolder();
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
	QStandardItem* l_bkmrstore=m_bkmrk;		//Store the parent to give it back after
	Q_ASSERT(xml.isStartElement() && xml.name() == "folder");
	while (xml.readNextStartElement()) 
	{
		if (xml.name() == "title")
		{	
			QString title=readXBELTitle();
			qDebug()<<m_bkmrk->text();
			m_bkmrk->setText(title);
			qDebug()<<"Read New folder with title"<<m_bkmrk->text();
		}
		else{
			if (xml.name() == "folder")
			{
				QStandardItem* newbookmark=new Bookmark();
				m_bkmrk->appendRow(newbookmark);   	//TODO ensure that it affect this as parent of new bookmarkt
				m_bkmrk=newbookmark;				//Here we "Enter" the folder
				readXBELFolder();
			}
			else {
				if (xml.name() == "bookmark")
				{
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
	m_bkmrk=l_bkmrstore;		//Once the folder is completely parsed, you go back to the parent folder etc..
}
void Bookmarkmodel::readXBELInfoAndMetadata(QString p_blockname)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == p_blockname);
	while(xml.readNextStartElement())
	{
		if(xml.name()=="icon")	//we are at bookmark::icon
		{
			//TODO make default icons !!
// 			QIcon l_icon(xml.attributes().value("name").toString());
// 			m_bkmrk->setIcon(l_icon);
		}
		readXBELInfoAndMetadata(xml.name().toString());	 
	}
}
void Bookmarkmodel::readXBELBookmark()
{
	QStandardItem* newbookmark=new QStandardItem();		//This is the bookmark (not a folder) that we are going to build
	QStandardItem* l_bkmrstore=m_bkmrk;
	m_bkmrk->appendRow(newbookmark);
	m_bkmrk=newbookmark;
	Q_ASSERT(xml.isStartElement() && xml.name() == "bookmark");
	m_bkmrk->setWhatsThis(xml.attributes().value("href").toString());	//The link goes on the whatsthis
	while (xml.readNextStartElement()) {
		if (xml.name() == "title")
		{
			m_bkmrk->setText(readXBELTitle());
			qDebug()<<"Bookmark title"<<m_bkmrk->text();
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
	m_bkmrk=l_bkmrstore;   //Go "back" to the parent (a bookmark in itself can not has children so we won't append row to this one)
}
QString Bookmarkmodel::readXBELTitle()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "title");

	QString title = xml.readElementText();
	qDebug()<<"has read title:"<<title;
// 	if(m_bookmarks.length()>0){
// 		m_bookmarks.last().setName(title);
// 	}
	return title;
}
void Bookmarkmodel::readXBELSeparator()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "separator");
	xml.skipCurrentElement();
}
// int Bookmarkmodel::columnCount(const QModelIndex& parent) const
// {
// 	if (parent.isValid())
//  	{
//         	return static_cast<Bookmark*>(parent.internalPointer())->columnCount();
// 	}
// 	else
// 	{
//         	return m_rootitem->columnCount();
// 	}
// }
// int Bookmarkmodel::rowCount(const QModelIndex& parent) const
// {
// 	QStandardItem *parentItem;
// 	if (parent.column() > 0){
//         	return 0;
// 	}
// 	if (!parent.isValid()){
//         	parentItem = m_rootitem;
// 	}
// 	else{
//         	parentItem = static_cast<Bookmark*>(parent.internalPointer());
// 	}
//     	return parentItem->childCount();
// }
// QVariant Bookmarkmodel::data(const QModelIndex& index, int role) const
// {
// 	if (!index.isValid())
//         return QVariant();
// 
//     	if (role != Qt::DisplayRole)
//     	{
// 		return QVariant();
// 	}
// 
//     	Bookmark *item = static_cast<Bookmark*>(index.internalPointer());
// 
//     	return item->data(index.column());
// }
// Qt::ItemFlags Bookmarkmodel::flags(const QModelIndex& index) const
// {
// 	if (!index.isValid())
//  	{
//         	return 0;
// 	}
// 	return QAbstractItemModel::flags(index);
// }
// QHash<int, QByteArray> Bookmarkmodel::roleNames() const {
// 	QHash<int, QByteArray> roles;
// 	roles[NameRole]="bookmarkname";
// 	roles[UrlRole]="bookmarkurl";
// 	roles[IconPathRole]="iconpath";
// 	roles[OriginRole]="origin";
// 	roles[IsFolderRole]="isfolder";
// 	roles[mimetypeRole]="mimetype";
// 	return roles;
// }
// QModelIndex Bookmarkmodel::index(int row, int column, const QModelIndex& parent) const
// {
// 	if (!hasIndex(row, column, parent))
//  	{
//         	return QModelIndex();
// 	}
// 	Bookmark *parentItem;
// 	if (!parent.isValid()){
//         	parentItem = m_rootitem;
// 	}
// 	else{
//         	parentItem = static_cast<Bookmark*>(parent.internalPointer());
// 	}
//     	Bookmark *childItem = parentItem->child(row);
//     	if (childItem){
//         	return createIndex(row, column, childItem);
// 	}
// 	else{
//         	return QModelIndex();
// 	}
// }
// QVariant Bookmarkmodel::headerData(int section, Qt::Orientation orientation, int role) const
// {
// 	if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
//          	return m_rootitem->data(section);
// 	}
//      	return QVariant();
// }
// QModelIndex Bookmarkmodel::parent(const QModelIndex& index) const
// {
// 	if (!index.isValid()){
// 		return QModelIndex();
// 	}
// 	Bookmark *childItem = static_cast<Bookmark*>(index.internalPointer());
// 	Bookmark *parentItem = childItem->parentItem();
// 	if (parentItem == m_rootitem){
// 		return QModelIndex();
// 	}
// 	return createIndex(parentItem->row(), 0, parentItem);
// }




















