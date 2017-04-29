#ifndef BOOKMARK_HPP
#define BOOKMARK_HPP
#include <QtCore/QObject>
#include <QtGui/QStandardItem>
#include <QtCore/qstring.h>
class Bookmarkmodel;

class Bookmark :public QStandardItem {
	
public:
	Bookmark();
// 	Bookmark(Bookmark* parent);
	Bookmark(const QString & text);
	~Bookmark();
	
	
	
	
	//data: 1 name 2 url 3 iconpath 4 origin 5 is folder 6 mimetype
	
	void setName(QString p_name);
	void setPath(QString p_path);
	void setOrigin(QString p_origin);
	void setType(bool p_isfolder);
	void setIconPath(QString p_iconpath);
	void setURL(QString p_url);

	QString getName();
	QString getOrigin();
	QString getPath();
	bool getType();
	QString getIconPath();
	QString getURL();
	
	
	void appendChild(Bookmark *child);
	Bookmark *child(int row);
	int childCount() const;
	int columnCount() const;
// 	int rowCount() const;
	QVariant data(int column) const;
	int row() const;
	Bookmark *parentItem();
private:
	QList<Bookmark*> m_childItems;
	QList<QVariant> m_itemData;
	Bookmark *m_parentItem;
	QString s_iconpath;
	bool is_folder;
	QString s_name;
	QString s_origin;	//e.g. "Firefox" "Konqueror" "Okular" etc..
	QString s_path;		//This is not url but the path where it is located inside the bookmarks folders 
	QString s_url;
};

#endif //BOOKMARK_HPP
