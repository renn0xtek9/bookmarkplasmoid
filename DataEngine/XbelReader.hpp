#ifndef XBELREADER_HPP
#define XBELREADER_HPP

class XbelReader
{
public:
    XbelReader(QTreeWidget *treeWidget);

    bool read(QIODevice *device);

    QString errorString() const;

private:
    void readXBEL();
//     void readTitle(QTreeWidgetItem *item);
//     void readSeparator(QTreeWidgetItem *item);
//     void readFolder(QTreeWidgetItem *item);
//     void readBookmark(QTreeWidgetItem *item);

    QXmlStreamReader xml;
};

#endif
