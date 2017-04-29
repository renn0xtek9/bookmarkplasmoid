#include <qt5/QtCore/QVariant>
#include <qt5/QtCore/QList>
#include "bookmark.hpp"


Bookmark::Bookmark():QStandardItem()
{
	
}
// Bookmark::Bookmark(Bookmark* parent):QStandardItem
// {
// 	m_parentItem=parent;
// }


Bookmark::Bookmark(const QString& text):QStandardItem(text)
{
}




Bookmark::~Bookmark()
{
	qDeleteAll(m_childItems);
}
QString Bookmark::getName()
{
	return s_name;
}
QString Bookmark::getOrigin()
{
	return s_origin;
}
QString Bookmark::getPath()
{
	return s_path;
}
bool Bookmark::getType()
{
	return is_folder;
}
QString Bookmark::getURL()
{
	return s_url;
}
QString Bookmark::getIconPath()
{
	return s_iconpath;
}
void Bookmark::setName(QString p_name)
{
	s_name=p_name;
}
void Bookmark::setOrigin(QString p_origin)
{
	s_origin=p_origin;
	//TODO shall we prefix the path with the origin ?
}
void Bookmark::setType(bool p_isfolder)
{
	is_folder=p_isfolder;
	//TODO set different default icon path base on type (folder or bookmark)
}
void Bookmark::setPath(QString p_path)
{
	s_path=p_path;
}

void Bookmark::setIconPath(QString p_iconpath)
{
	s_iconpath=p_iconpath;
	//TODO check if file exist otherwise, default to a defautl path
}
void Bookmark::setURL(QString p_url)
{
	s_url=p_url;
}


//New
void Bookmark::appendChild(Bookmark *child)
{
	m_childItems.append(child);
	child->m_parentItem=this;
}
Bookmark *Bookmark::child(int row)
{
	return m_childItems.value(row);
}
int Bookmark::childCount() const
{
	return m_childItems.count();
}
int Bookmark::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<Bookmark*>(this));

    return 0;
}
int Bookmark::columnCount() const
{
    return m_itemData.count();
}
QVariant Bookmark::data(int column) const
{
    return m_itemData.value(column);
}
Bookmark *Bookmark::parentItem()
{
    return m_parentItem;
}
