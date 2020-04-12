#include <bookmarksmodule_test.h>
#include <QtCore/QSharedPointer>
#include<QtCore/QModelIndex>
#include <QtCore/QDebug>
#include <bookmarkmodel.hpp>
bookmarksmodule_test::bookmarksmodule_test() : QObject() {
}
void bookmarksmodule_test::init() {
  //     m_model=QSharedPointer<Bookmarkmodel>(new Bookmarkmodel());
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForChromeBookamarks("Bookmarks");
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks.xml");
  m_model->setPathForOkularBookmarks("okular_bookmarks.xml");
}
void bookmarksmodule_test::initTestCase() {
  // will be called before the first testfunction is executed.
}
void bookmarksmodule_test::cleanup() {
  // will be called after every testfunction.
}
void bookmarksmodule_test::cleanupTestCase() {
  // will be called after the last testfunction was executed.
}
//helpers

QStringList bookmarksmodule_test::list_all_entries_of_the_model_at_this_hierarchical_level(const QModelIndex& parent_index)
{
    QStringList list_of_entries{};
    for(int i=0;i<m_model->rowCount();++i)
    {
        QModelIndex current_index=m_model->index(i,0,parent_index);
        list_of_entries.append(m_model->data(current_index,Qt::DisplayRole).toString());
    }
    return list_of_entries;
}
QJsonObject bookmarksmodule_test::convert_model_to_qjsonobject()
{
    QJsonObject json_object;
    for (int row = 0; row < m_model->getModel()->rowCount(); ++row)
    {
        QModelIndex index = m_model->getModel()->index(row,0,QModelIndex());
        QStandardItem *item = m_model->getModel()->itemFromIndex(index);
        if (item->hasChildren())
        {
            json_object.insert(item->text(),"Folder");
        }
        else 
        {
            json_object.insert(item->text(),item->data(Qt::UserRole+3).toString());
        }
    }
    qDebug()<<json_object;
    return json_object;
}



//Tests
void bookmarksmodule_test::path_are_set_correctly() {
  QVERIFY2(m_model->getPathForChromeBookmarks() == "Bookmarks", "Path for chrome bookmark is wrong");
  QVERIFY2(m_model->getPathForKonquerorBookmarks() == "konqueror_bookmarks.xml",
           "Path for Konqueror bookmark is wrong");
  QVERIFY2(m_model->getPathForOkularBookmarks() == "okular_bookmarks.xml", "Path for Okular bookmark is wrong");
}

void bookmarksmodule_test::get_correct_number_of_element_for_konqueror_bookmarks() {
  int expected_number_of_row = 4;
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks.xml");
  m_model->ReadAllSources(true);
  QVERIFY2(m_model->rowCount() == expected_number_of_row,
           "Do not get the correct number of element when reading form konqueror bookmarks");
  
  QStringList expected_items{"google","News","Linux","Youtube"};
  QCOMPARE(list_all_entries_of_the_model_at_this_hierarchical_level(),expected_items);
}
void bookmarksmodule_test::scan_complete_hierarchy_of_konqueror_model_bookmark()
{
    m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
    m_model->setPathForKonquerorBookmarks("konqueror_bookmarks.xml");
    m_model->ReadAllSources(true);
    QModelIndex parent;
    QStringList expected_items{"google","News","Linux","Youtube"};
    QCOMPARE(list_all_entries_of_the_model_at_this_hierarchical_level(),expected_items);
    
    convert_model_to_qjsonobject();
    /*
    for (int row = 0; row < m_model->getModel()->rowCount(); ++row)
    {
         QModelIndex index = m_model->getModel()->index(row,0,QModelIndex());
        QStandardItem *item = m_model->getModel()->itemFromIndex(index);
        qDebug()<<item->text();
        qDebug()<<item->hasChildren();
//         m_model->getModel()->setData(index,0);
        
    }
    */
    
    
    
    /*

    parent=m_model->index(2,0,QModelIndex());
    qDebug()<<m_model->getModel()->itemFromIndex(parent);
    expected_items=QStringList{"TVs","Washington post","The intercept"};
//     qDebug()<<list_all_entries_of_the_model_at_this_hierarchical_level();
//     qDebug()<<m_model->data(m_model->index(1,1,parent));
    QCOMPARE(list_all_entries_of_the_model_at_this_hierarchical_level(parent),expected_items);
//     parent=m_model->inde
    */
}





void bookmarksmodule_test::get_correct_number_of_element_for_okular_bookmarks() {
  int expected_number_of_row = 2;
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForOkularBookmarks("okular_bookmarks.xml");
  m_model->ReadAllSources(true);
  QVERIFY2(m_model->rowCount() == expected_number_of_row,
           "Do not get the correct number of element when reading form konqueror bookmarks");
}

void bookmarksmodule_test::get_correct_number_of_element_for_chrome_bookmarks() {
  int expected_number_of_row = 1;
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForChromeBookamarks("Bookmarks");
  m_model->ReadAllSources(true);
  QCOMPARE(m_model->rowCount() , expected_number_of_row);
  QCOMPARE(list_all_entries_of_the_model_at_this_hierarchical_level(),QStringList("Chrome bookmarks bar"));
}





QTEST_MAIN(bookmarksmodule_test)
#include "moc_bookmarksmodule_test.cpp"
