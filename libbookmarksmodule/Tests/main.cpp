#include<iostream>
#include<QtCore/QString>
#include<QtCore/QFile>
#include<QtCore/QDebug>
#include<QtCore/QModelIndex>
#include<QtGui/QStandardItem>
// #include "bookmark.hpp"
#include "bookmarkmodel.hpp"
using namespace std;

int main(int argc, char **argv) 
{  
	QString filename="/home/max/.local/share/konqueror/bookmarks.xml";
	QString okularfilename="/home/max/.local/share/okular/bookmarks.xml";
	Bookmarkmodel reader;
	reader.setPathForOkularBookmarks(okularfilename);
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
	
	return 0;
}

