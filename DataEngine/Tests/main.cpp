#include<iostream>
#include<qt5/QtCore/QString>
#include<qt5/QtCore/QFile>
#include<qt5/QtCore/QDebug>
#include "bookmark.hpp"
#include "XbelReader.hpp"
using namespace std;

int main(int argc, char **argv) 
{  
	QString filename="/home/max/.local/share/konqueror/bookmarks.xml";
	QFile konquerorbookmarkfile(filename);
	XbelReader reader;
	
	if (reader.read(&konquerorbookmarkfile))
 	{
		foreach (Bookmark bkmr, reader.getBookrmarks()){
			qDebug()<<"Name: "<<bkmr.getName()<<" Type: "<<bkmr.getType()<<" IconPath: "<<bkmr.getIconPath();
		}
	}
	else{
		qDebug()<<"could not read bookmark";
	}
	
	return 0;
}

