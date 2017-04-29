#include "bookmarkmodel.hpp"
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtGui/QIcon>



Bookmarkmodel::Bookmarkmodel() :QStandardItemModel(nullptr)
{
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
		if (xml.name() == "folder"){
			invisibleRootItem()->appendRow(readXBELFolder());
		}
		else{
			if (xml.name() == "bookmark"){
				invisibleRootItem()->appendRow(readXBELBookmark());		
			}
			else{
				if (xml.name() == "separator"){
					readXBELSeparator();
				}	
				else{
					xml.skipCurrentElement();
				}
			}
		}
	}
	return !xml.error();
}
QStandardItem* Bookmarkmodel::readXBELFolder()
{
	QStandardItem* ret=new QStandardItem();
	Q_ASSERT(xml.isStartElement() && xml.name() == "folder");
	while (xml.readNextStartElement()) 
	{
		if (xml.name() == "title")
		{	
			QString title=readXBELTitle();
			ret->setText(title);
		}
		else{
			if (xml.name() == "folder")
			{
				ret->appendRow(readXBELFolder());   	//TODO ensure that it affect this as parent of new bookmarkt
			}
			else {
				if (xml.name() == "bookmark")
				{
					ret->appendRow(readXBELBookmark());
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
	return ret;
}
void Bookmarkmodel::readXBELInfoAndMetadata(QString p_blockname,QStandardItem* p_item)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == p_blockname);
	while(xml.readNextStartElement())
	{
		if(xml.name()=="icon")	//we are at bookmark::icon
		{
			//TODO make default icons !!
// 			QIcon l_icon(xml.attributes().value("name").toString());
// 			p_item->setIcon(l_icon);
		}
		readXBELInfoAndMetadata(xml.name().toString(),p_item);	 
	}
}
QStandardItem* Bookmarkmodel::readXBELBookmark()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "bookmark");
	QStandardItem* ret=new QStandardItem();		//This is the bookmark (not a folder) that we are going to build	
	ret->setWhatsThis(xml.attributes().value("href").toString());	//The link goes on the whatsthis
	while (xml.readNextStartElement()) {
		if (xml.name() == "title")
		{
			ret->setText(readXBELTitle());
		}
		else{
			if (xml.name()=="info")
			{
				readXBELInfoAndMetadata("info",ret);
			}
			else{
				xml.skipCurrentElement();
			}
		}
	}
	return ret;
}
QString Bookmarkmodel::readXBELTitle()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "title");
	QString title = xml.readElementText();
	return title;
}
void Bookmarkmodel::readXBELSeparator()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "separator");
	xml.skipCurrentElement();
}
