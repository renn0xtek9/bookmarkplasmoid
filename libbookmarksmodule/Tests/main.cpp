#include<iostream>
#include<QtCore/QString>
#include<QtCore/QFile>
#include<QtCore/QDebug>
#include<QtCore/QModelIndex>
#include<QtGui/QStandardItem>
#include<QtTest/QTest>
#include "bookmarkmodel.hpp"
using namespace std;







int main(int argc, char **argv) 
{  
	
// 	/home/max/.config/google-chrome/Default/Bookmarks
	QString filename="/home/max/.local/share/konqueror/bookmarks.xml";
	QString okularfilename="/home/max/.local/share/okular/bookmarks.xml";
	/*
	‎kbrosnan‎>‎ places.sqlite
‎[18:38] ‎<‎kbrosnan‎>‎ places.squlte.wal*/
	Bookmarkmodel reader;
	reader.setPathForOkularBookmarks(okularfilename);
	reader.setPathForKonquerorBookmarks(filename);
	
	reader.ReadAllSources(true);
	qDebug()<<reader.rowCount();
	qDebug()<<reader.columnCount();
// 	QModelIndex index=reader.createIndex();
// 	QModelIndex index=reader.index(0,0,index);

	QModelIndex parent;
	QModelIndex current;
	int i=0;
	int n=reader.rowCount(parent);
	
	
	
	for (int i=0 ; i<n ; i++)
 	{
		current=reader.index(i,0,parent);
		int rowforthis=current.row();
// 		int subrows=current.
		qDebug()<<reader.data(current,Qt::DisplayRole)<<" row for this:"<<rowforthis;
		qDebug()<<reader.data(current,Qt::ToolTipRole)<<" is the tooltip";
	}
	qDebug()<<"Filtering";
	reader.setSearchField("Onvista");
	qDebug()<<reader.rowCount(parent);
	
	for (int i=0 ; i<reader.rowCount() ; i++)
 	{
		current=reader.index(i,0,parent);
		int rowforthis=current.row();
// 		int subrows=current.
		qDebug()<<reader.data(current,Qt::DisplayRole)<<" row for this:"<<rowforthis;
// 		if current.has
	}
	
	return 0;
}

