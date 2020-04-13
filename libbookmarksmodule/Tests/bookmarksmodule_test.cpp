#include <bookmarksmodule_test.h>
#include <QtCore/QDebug>
#include <QtCore/QModelIndex>
#include <QtCore/QSharedPointer>
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
// helpers

TwoDimensionTree bookmarksmodule_test::get_tree_of_data_model(QModelIndex parent, int col_start) {
  TwoDimensionTree tree{};
  for (int row = 0; row < m_model->getModel()->rowCount(parent); ++row) {
    QModelIndex index = m_model->getModel()->index(row, 0, parent);
    QStandardItem* item = m_model->getModel()->itemFromIndex(index);
    if (item->hasChildren()) {
      tree.append(qMakePair(col_start, QStringList{item->text(), "Folder"}));
      tree.append(get_tree_of_data_model(index, col_start + 1));
    } else {
      tree.append(qMakePair(col_start, QStringList{item->text(), item->data(Qt::ToolTipRole).toString()}));
    }
  }
  return tree;
}

// Tests
void bookmarksmodule_test::path_are_set_correctly() {
  QVERIFY2(m_model->getPathForChromeBookmarks() == "Bookmarks", "Path for chrome bookmark is wrong");
  QVERIFY2(m_model->getPathForKonquerorBookmarks() == "konqueror_bookmarks.xml",
           "Path for Konqueror bookmark is wrong");
  QVERIFY2(m_model->getPathForOkularBookmarks() == "okular_bookmarks.xml", "Path for Okular bookmark is wrong");
}

void bookmarksmodule_test::scan_complete_hierarchy_of_konqueror_model_bookmark() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks.xml");
  m_model->ReadAllSources(true);

  TwoDimensionTree expected_tree;
  expected_tree.append(qMakePair(0, QStringList{"google", "http://www.google.com"}));
  expected_tree.append(qMakePair(0, QStringList{"News", "Folder"}));
  expected_tree.append(qMakePair(1, QStringList{"TVs", "Folder"}));
  expected_tree.append(qMakePair(2, QStringList{"russia today", "https://www.rt.com/"}));
  expected_tree.append(qMakePair(2, QStringList{"CNN", "https://edition.cnn.com/"}));
  expected_tree.append(qMakePair(1, QStringList{"Washington post", "https://www.washingtonpost.com/"}));
  expected_tree.append(qMakePair(1, QStringList{"The intercept", "https://theintercept.com/"}));
  expected_tree.append(qMakePair(0, QStringList{"Linux", "Folder"}));
  expected_tree.append(qMakePair(1, QStringList{"Bash scripting", "Folder"}));
  expected_tree.append(
      qMakePair(2, QStringList{"Bash tutorial", "https://linuxconfig.org/bash-scripting-tutorial-for-beginners"}));
  expected_tree.append(qMakePair(2, QStringList{"Bash scripting cheat sheet", "https://devhints.io/bash"}));
  expected_tree.append(
      qMakePair(1, QStringList{"how to install device driver",
                               "https://opensource.com/article/18/11/how-install-device-driver-linux"}));
  expected_tree.append(qMakePair(1, QStringList{"github-torvald", "https://github.com/torvalds"}));
  expected_tree.append(qMakePair(0, QStringList{"Youtube", "https://www.youtube.com/"}));

  QCOMPARE(get_tree_of_data_model(QModelIndex()), expected_tree);
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
  QCOMPARE(m_model->rowCount(), expected_number_of_row);
  QCOMPARE(list_all_entries_of_the_model_at_this_hierarchical_level(), QStringList("Chrome bookmarks bar"));
}

QTEST_MAIN(bookmarksmodule_test)
#include "moc_bookmarksmodule_test.cpp"
