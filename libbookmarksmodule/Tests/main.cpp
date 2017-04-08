#include<iostream>
#include<qt5/QtCore/QString>
#include<qt5/QtCore/QFile>
#include<qt5/QtCore/QDebug>
#include<qt5/QtCore/QModelIndex>
#include "bookmark.hpp"
#include "bookmarkmodel.hpp"
using namespace std;

int main(int argc, char **argv) 
{  
	QString filename="/home/max/.local/share/konqueror/bookmarks.xml";
	Bookmarkmodel reader("");
	reader.appendXBELFile(filename);
	qDebug()<<reader.rowCount();
	qDebug()<<reader.columnCount();
// 	QModelIndex index=reader.createIndex();
// 	QModelIndex index=reader.index(0,0,index);
	QModelIndex index;
	int i=0;
	
	
	
	
	i=0;
	while (i<reader.rowCount(index)){
		qDebug()<<i;
		index=reader.index(i,0,index);
		qDebug()<<reader.data(index,Qt::DisplayRole);
		index=index.parent();
		i++;
	}
	index=reader.index(0,0,index);
// 	index.
// 	while (reader.index)
	
	
// 	qDebug()<<reader.hasIndex(1,0,index);
	
	
	
	
	qDebug()<<index;
// 	qDebug()<<index.data(0);
	
	
	return 0;
}

