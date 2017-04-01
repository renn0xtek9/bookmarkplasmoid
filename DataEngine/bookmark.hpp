#ifndef BOOKMARK_HPP
#define BOOKMARK_HPP
#include <qt5/QtCore/qstring.h>

class Bookmark{
public:
	Bookmark();
	~Bookmark();
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
	
	
private:
	QString s_iconpath;
	bool is_folder;
	QString s_name;
	QString s_origin;	//e.g. "Firefox" "Konqueror" "Okular" etc..
	QString s_path;		//This is not url but the path where it is located inside the bookmarks folders 
	QString s_url;
};

#endif //BOOKMARK_HPP
