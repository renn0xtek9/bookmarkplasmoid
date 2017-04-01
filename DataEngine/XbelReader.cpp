#include "XbelReader.hpp"
XbelReader::XbelReader()
{
}


bool XbelReader::read(QIODevice *device)
{
    xml.setDevice(device);

    if (xml.readNextStartElement()) {
        if (xml.name() == "xbel" && xml.attributes().value("version") == "1.0")
            readXBEL();
        else
            xml.raiseError(QObject::tr("The file is not an XBEL version 1.0 file."));
    }

    return !xml.error();
}
QString XbelReader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
}
void XbelReader::readXBEL()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "xbel");

    while (xml.readNextStartElement()) {
        if (xml.name() == "folder")
            readFolder(0);
        else if (xml.name() == "bookmark")
            readBookmark(0);
        else if (xml.name() == "separator")
            readSeparator(0);
        else
            xml.skipCurrentElement();
    }
}
void XbelReader::readFolder(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "folder");

    QTreeWidgetItem *folder = createChildItem(item);
    bool folded = (xml.attributes().value("folded") != "no");
    treeWidget->setItemExpanded(folder, !folded);

    while (xml.readNextStartElement()) {
        if (xml.name() == "title")
            readTitle(folder);
        else if (xml.name() == "folder")
            readFolder(folder);
        else if (xml.name() == "bookmark")
            readBookmark(folder);
        else if (xml.name() == "separator")
            readSeparator(folder);
        else
            xml.skipCurrentElement();
    }
}
void XbelReader::readTitle(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "title");

    QString title = xml.readElementText();
    item->setText(0, title);
}

void XbelReader::readSeparator(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "separator");

    QTreeWidgetItem *separator = createChildItem(item);
    separator->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    separator->setText(0, QString(30, 0xB7));
    xml.skipCurrentElement();
}

