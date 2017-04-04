#ifndef BOOKMARKMODULE_HPP
#define BOOKMARKMODULE_HPP



#include <qt5/QtCore/QIODevice>
#include <qt5/QtCore/QString>
#include <qt5/QtCore/QList>
#include <qt5/QtCore/QXmlStreamReader>
#include "bookmark.hpp"
class Bookmarkmodule
{
public:
    Bookmarkmodule();
    ~Bookmarkmodule();

    bool read(QIODevice *device);

    QString errorString() const;
    QList<Bookmark> getBookrmarks();

private:
    void readXBEL();
    QString readTitle();
    void readSeparator();
    void readFolder();
    void readBookmark();
    void readInfoAndMetadata(QString p_blockname);

    QXmlStreamReader xml;
    QList<Bookmark> m_bookmarks;
    QString s_currentpath;
};


#endif
