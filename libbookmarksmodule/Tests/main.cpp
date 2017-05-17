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
	Bookmarkmodel reader;
// 	reader.appendXBELFile(filename);
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
	
	qDebug()<<"Now inside Utiles";
	
	if(reader.findItems("Utiles").count()>0)
	{
		QStandardItem* utiles=reader.findItems("Utiles").at(0);
		for (int i=0 ; i<reader.rowCount(utiles->index()) ; i++)
		{	
			current=reader.index(i,0,utiles->index());
			int rowforthis=current.row();
			qDebug()<<reader.data(current,Qt::DisplayRole)<<" row for this:"<<rowforthis;
			qDebug()<<reader.data(current,Qt::ToolTipRole)<<" is the tooltip";
		}
		
	}
	return 0;
	
	
	
	
	while (i<reader.rowCount(parent)){
		qDebug()<<i;
		current=reader.index(i,0,parent);
		qDebug()<<reader.data(current,Qt::DisplayRole);
		qDebug()<<"Tooltip"<<reader.data(current,Qt::ToolTip);
		if(reader.hasChildren(current)){
			i=0;
			parent=current;
			current=reader.index(0,0,current);
		}
		i++;
		if(i==reader.rowCount(parent)){
			if (parent.parent().isValid()){
				i=0;
				parent=parent.parent();
			}
		}
		
		
	}	
	return 0;
}

