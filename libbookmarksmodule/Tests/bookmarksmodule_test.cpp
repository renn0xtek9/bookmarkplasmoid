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

QStringList bookmarksmodule_test::list_all_entries_of_the_model_at_this_hierarchical_level()
{
    QStringList list_of_entries{};
    for(int i=0;i<m_model->rowCount();++i)
    {
        QModelIndex parent_index;
        QModelIndex current_index=m_model->index(i,0,parent_index);
        list_of_entries.append(m_model->data(current_index,Qt::DisplayRole).toString());
    }
    return list_of_entries;
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
