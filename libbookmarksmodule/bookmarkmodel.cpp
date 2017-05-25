#include "bookmarkmodel.hpp"
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QFileInfo>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtGui/QIcon>
#include <QtCore/QFileInfo>
#include <KF5/KIconThemes/KIconTheme>

Bookmarkmodel::Bookmarkmodel() :QStandardItemModel(nullptr)
{
	
}
Bookmarkmodel::~Bookmarkmodel()
{

}
void Bookmarkmodel::setPathForKonquerorBookmarks(const QString& fullpath)
{
	if (FileExists(fullpath))
	{
		m_konquerorpath=fullpath;
		appendXBELFile(m_konquerorpath);
		emit konquerorpathChanged(fullpath);
	}
}
void Bookmarkmodel::setPathForOkularBookmarks(const QString& fullpath)
{
	if (FileExists(fullpath))
	{
		m_okularpath=fullpath;
		appendXBELFile(m_okularpath);
		emit okularpathChanged(fullpath);
	}
}
void Bookmarkmodel::setPathForFirefoxBookmarks(const QString& fullpath)
{
	if(FileExists(fullpath))
	{
		m_firefoxpath=fullpath;
		//TODO implement json bookmarks
		emit firefoxpathChanged(fullpath);
	}
}
void Bookmarkmodel::setPathForChromeBookamarks(const QString& fullpath)
{
	if(FileExists(fullpath))
	{
		m_chromepath=fullpath;
		//TODO read the json bookmark
		emit chromepathChanged(fullpath);
	}
}
QString Bookmarkmodel::getPathForFirefoxBookmarks() const
{
	return m_firefoxpath;
}
QString Bookmarkmodel::getPathForKonquerorBookmarks() const
{
	return m_konquerorpath;
}
QString Bookmarkmodel::getPathForOkularBookmarks() const
{
	return m_okularpath;
}
QString Bookmarkmodel::getPathForChromeBookmarks() const
{
	return m_chromepath;
}





void Bookmarkmodel::appendXBELFile(QString path)
{
	QFile xbelfile(path);
	if (xbelfile.open(QIODevice::OpenModeFlag::ReadOnly)){
		if(!(readXBEL(&xbelfile)))
		{
		}
	}
	else{
		qDebug()<<"Could not open File";
	}
	emit this->rowCountChanged(this->rowCount());
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
	ret->setData(true,BookmarkRoles::IsFolderRole);
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
					if (xml.name()=="info")
					{
						readXBELInfoAndMetadata("info",ret);
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
	return ret;
}
QString Bookmarkmodel::getCustomOrThemeIconPath(QString iconpathfromxml,QStandardItem* p_item)
{
	QFileInfo finfo(iconpathfromxml);
	QString path,standard,iconsource;
	QStringList themelist("hicolor");
	iconsource=iconpathfromxml;
	if(!finfo.isFile())
	{
		iconsource="";
		themelist.append(KIconTheme::current());
		foreach(QString str, themelist)
		{
			KIconTheme theme(str);
			path=theme.iconPathByName(iconpathfromxml,24,KIconLoader::MatchBest);
			if(!path.isEmpty())
			{
				iconsource=path;
				break;
			}	
		}
		if(iconsource.isEmpty())
		{
			themelist.append(KIconTheme::current());
			if(p_item->data(BookmarkRoles::IsFolderRole).toBool()==true)
			{
				standard="folder-bookmark";
			}
			else
			{
				standard="text-html";
			}
			foreach(QString str, themelist)
			{
				KIconTheme theme(str);
				path=theme.iconPathByName(standard,24,KIconLoader::MatchBest);
				if(!path.isEmpty())
				{
					iconsource=path;
					break;
				}	
			}
		}
	}
	return iconsource;
}


void Bookmarkmodel::readXBELInfoAndMetadata(QString p_blockname,QStandardItem* p_item)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == p_blockname);
	while(xml.readNextStartElement())
	{
		if(xml.name()=="icon")	//we are at bookmark::icon
		{
			QString iconname=xml.attributes().value("name").toString();
			QString customortheme=getCustomOrThemeIconPath(iconname,p_item);
			p_item->setData(customortheme,Qt::UserRole);
		}
		readXBELInfoAndMetadata(xml.name().toString(),p_item);	 
	}
}
QStandardItem* Bookmarkmodel::readXBELBookmark()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "bookmark");
	QStandardItem* ret=new QStandardItem();		//This is the bookmark (not a folder) that we are going to build	
	ret->setData(false,BookmarkRoles::IsFolderRole);
	ret->setToolTip(xml.attributes().value("href").toString());	//The link goes on the whatsthis
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
QHash<int, QByteArray> Bookmarkmodel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[Iconpathrole] = "icon";
	roles[Displayrole] = "display";
	roles[Tooltiprole] = "ttp";
	roles[IsFolderRole] = "isFolder";
	return roles;
}
void Bookmarkmodel::itemSelectedAsRoot(int index)
{		
}
void Bookmarkmodel::parentItemSelectedAsRoot()
{
// 	this->setRootIndex(this->invisibleRootItem());
}
bool Bookmarkmodel::FileExists(const QString & path) const noexcept
{
	QFileInfo finfo(path);
	return finfo.exists();	
}

