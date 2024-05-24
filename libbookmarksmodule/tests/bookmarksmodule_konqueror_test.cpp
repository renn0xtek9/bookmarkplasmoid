#include <bookmarksmodule_konqueror_test.h>

#include <QtTest/QTest>

TwoDimensionTree KonquerorBookMarksTree() {
  TwoDimensionTree konqueror_tree;
  konqueror_tree.append(qMakePair(0, QStringList{"google", "http://www.google.com"}));
  konqueror_tree.append(qMakePair(0, QStringList{"News", "Folder"}));
  konqueror_tree.append(qMakePair(1, QStringList{"TVs", "Folder"}));
  konqueror_tree.append(qMakePair(2, QStringList{"foobar", "https://www.foobar.com/"}));
  konqueror_tree.append(qMakePair(2, QStringList{"CNN", "https://edition.cnn.com/"}));
  konqueror_tree.append(qMakePair(1, QStringList{"Washington post", "https://www.washingtonpost.com/"}));
  konqueror_tree.append(qMakePair(1, QStringList{"The intercept", "https://theintercept.com/"}));
  konqueror_tree.append(qMakePair(0, QStringList{"Linux", "Folder"}));
  konqueror_tree.append(qMakePair(1, QStringList{"Bash scripting", "Folder"}));
  konqueror_tree.append(
      qMakePair(2, QStringList{"Bash tutorial", "https://linuxconfig.org/bash-scripting-tutorial-for-beginners"}));
  konqueror_tree.append(qMakePair(2, QStringList{"Bash scripting cheat sheet", "https://devhints.io/bash"}));
  konqueror_tree.append(
      qMakePair(1, QStringList{"how to install device driver",
                               "https://opensource.com/article/18/11/how-install-device-driver-linux"}));
  konqueror_tree.append(qMakePair(1, QStringList{"github-torvald", "https://github.com/torvalds"}));
  konqueror_tree.append(qMakePair(0, QStringList{"Youtube", "https://www.youtube.com/"}));
  return konqueror_tree;
}

void BookmarksmoduleKonquerorTest::load_model_with_konqueror_bookmarks() {
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks.xml");
  m_model->ReadAllSources(true);
}

void BookmarksmoduleKonquerorTest::model_is_not_filter_when_searchfield_is_empty() {
  load_model_with_konqueror_bookmarks();
  m_model->setSearchField("");
  m_model->setFilterItemsOnly(true);
  QCOMPARE(get_tree_of_data_model(QModelIndex(), m_model), KonquerorBookMarksTree());
}

void BookmarksmoduleKonquerorTest::model_is_not_filtered_anymore_when_searchfield_is_empty_again() {
  load_model_with_konqueror_bookmarks();
  m_model->setSearchField("Bash");
  m_model->setFilterItemsOnly(true);
  m_model->setSearchField("");
  QCOMPARE(get_tree_of_data_model(QModelIndex(), m_model), KonquerorBookMarksTree());
}

void BookmarksmoduleKonquerorTest::filters_folder_and_items() {
  load_model_with_konqueror_bookmarks();
  m_model->setFilterItemsOnly(false);
  m_model->setSearchField("Bash");

  TwoDimensionTree expected_tree;
  expected_tree.append(qMakePair(0, QStringList{"Linux", "Folder"}));
  expected_tree.append(qMakePair(1, QStringList{"Bash scripting", "Folder"}));
  expected_tree.append(
      qMakePair(2, QStringList{"Bash tutorial", "https://linuxconfig.org/bash-scripting-tutorial-for-beginners"}));
  expected_tree.append(qMakePair(2, QStringList{"Bash scripting cheat sheet", "https://devhints.io/bash"}));
  QCOMPARE(get_tree_of_data_model(QModelIndex(), m_model), expected_tree);
}
void BookmarksmoduleKonquerorTest::filters_folder_and_items_when_filtering_items_only() {
  load_model_with_konqueror_bookmarks();
  m_model->setSearchField("Bash");
  m_model->setFilterItemsOnly(true);

  TwoDimensionTree expected_tree;
  expected_tree.append(
      qMakePair(0, QStringList{"Bash tutorial", "https://linuxconfig.org/bash-scripting-tutorial-for-beginners"}));
  expected_tree.append(qMakePair(0, QStringList{"Bash scripting cheat sheet", "https://devhints.io/bash"}));

  QCOMPARE(get_tree_of_data_model(QModelIndex(), m_model), expected_tree);
}

void BookmarksmoduleKonquerorTest::init() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
}

void BookmarksmoduleKonquerorTest::scan_complete_hierarchy_of_konqueror_model_bookmark() {
  load_model_with_konqueror_bookmarks();
  QCOMPARE(get_tree_of_data_model(QModelIndex(), m_model), KonquerorBookMarksTree());
}

QTEST_GUILESS_MAIN(BookmarksmoduleKonquerorTest)
#include "moc_bookmarksmodule_konqueror_test.cpp"
