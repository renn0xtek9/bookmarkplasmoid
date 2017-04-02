#include <qt5/QtCore/QDebug>
#include "XbelReader.hpp"
XbelReader::XbelReader()
{
}


bool XbelReader::read(QIODevice *device)
{
	m_bookmarks.clear();
	xml.setDevice(device);
	if (xml.readNextStartElement()) {
		if (xml.name() == "xbel"){
			readXBEL();
		}
		else{
			xml.raiseError(QObject::tr("The file is not an XBEL version 1.0 file."));
		}
	}

	return !xml.error();
}
QString XbelReader::errorString() const
{
	return QObject::tr("%1\nLine %2, column %3")
		.arg(xml.errorString())
		.arg(xml.lineNumber())
		.arg(xml.columnNumber());
}
void XbelReader::readXBEL()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "xbel");

	while (xml.readNextStartElement()) {
		if (xml.name() == "folder")
		readFolder();
		else if (xml.name() == "bookmark")
		readBookmark();
		else if (xml.name() == "separator")
		readSeparator();
		else
		xml.skipCurrentElement();
	}
}
void XbelReader::readFolder()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "folder");
	Bookmark l_bookmark;
	l_bookmark.setPath(s_currentpath);
	l_bookmark.setType(true);
	m_bookmarks.append(l_bookmark);
	while (xml.readNextStartElement()) 
	{
		if (xml.name() == "title")
		{	
			QString title=readTitle();
			s_currentpath+="/"+title;	
		}
		else{
			if (xml.name() == "folder")
			{
				readFolder();
			}
			else {
				if (xml.name() == "bookmark")
				{
					readBookmark();
				}
				else 
				{
					if (xml.name() == "separator")
					{
						readSeparator();
					}
				
					else
					{
						xml.skipCurrentElement();
					}
				}		
			}
		}
	}
	//TODO enlever la dernier elemnet du setIconPath
	s_currentpath=s_currentpath.left(s_currentpath.lastIndexOf("/"));
}
void XbelReader::readInfoAndMetadata(QString p_blockname)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == p_blockname);
	while(xml.readNextStartElement())
	{
		if(xml.name()=="icon")	//we are at bookmark::icon
		{
			if(m_bookmarks.length()>0)
   			{
				m_bookmarks.last().setIconPath(xml.attributes().value("name").toString());
			}
		}
		readInfoAndMetadata(xml.name().toString());	 
	}
}
void XbelReader::readBookmark()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "bookmark");
	QString title;
	Bookmark l_bookmark;
	l_bookmark.setPath(s_currentpath);
	l_bookmark.setType(false);
	l_bookmark.setURL(xml.attributes().value("href").toString());
	m_bookmarks.append(l_bookmark);
	
	while (xml.readNextStartElement()) {
		if (xml.name() == "title")
		{
			title=readTitle();
		}
		else{
			if (xml.name()=="info")
			{
				readInfoAndMetadata("info");
			}
			else{
				xml.skipCurrentElement();
			}
		}
	}
}

QString XbelReader::readTitle()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "title");

	QString title = xml.readElementText();
	if(m_bookmarks.length()>0){
		m_bookmarks.last().setName(title);
	}
	return title;
}
void XbelReader::readSeparator()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "separator");
	xml.skipCurrentElement();
}
QList<Bookmark> XbelReader::getBookrmarks()
{
	return m_bookmarks;
}

