#ifndef XBELREADER_HPP
#define XBELREADER_HPP

#include <qt5/QtCore/QIODevice>
#include <qt5/QtCore/QString>
#include <qt5/QtCore/QXmlStreamReader>

class XbelReader
{
public:
    XbelReader();

    bool read(QIODevice *device);

    QString errorString() const;

private:
    void readXBEL();
    void readTitle();
    void readSeparator();
    void readFolder();
    void readBookmark();

    QXmlStreamReader xml;
};

#endif
