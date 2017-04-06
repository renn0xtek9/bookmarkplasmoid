#include<iostream>
#include<qt5/QtCore/QString>
#include<qt5/QtCore/QFile>
#include<qt5/QtCore/QDebug>
#include "bookmark.hpp"
#include "bookmarksmodule.hpp"
using namespace std;

int main(int argc, char **argv) 
{  
	QString filename="/home/max/.local/share/konqueror/bookmarks.xml";
	QFile konquerorbookmarkfile(filename);
	if (konquerorbookmarkfile.open(QIODevice::OpenModeFlag::ReadOnly)){
		qDebug()<<"The QFile is open";
	}
	Bookmarkmodule reader;
	
	if (reader.read(&konquerorbookmarkfile))
 	{
		foreach (Bookmark bkmr, reader.getBookrmarks()){
			qDebug()<<"Name: "<<bkmr.getName()<<" Type: "<<bkmr.getType()<<" IconPath: "<<bkmr.getIconPath()<<" Path: "<<bkmr.getPath();
		}
	}
	else{
		qDebug()<<"could not read bookmark";
	}
	
	return 0;
}

