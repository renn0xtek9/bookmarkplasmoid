#include <bookmarksmoduletest.h>
#include <QtCore/QDebug>
#include <QtCore/QModelIndex>
#include <QtCore/QSharedPointer>
#include <bookmarkmodel.hpp>

TwoDimensionTree KonquerorBookMarksTree() {
  TwoDimensionTree konqueror_tree;
  konqueror_tree.append(qMakePair(0, QStringList{"google", "http://www.google.com"}));
  konqueror_tree.append(qMakePair(0, QStringList{"News", "Folder"}));
  konqueror_tree.append(qMakePair(1, QStringList{"TVs", "Folder"}));
  konqueror_tree.append(qMakePair(2, QStringList{"russia today", "https://www.rt.com/"}));
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
TwoDimensionTree OkularBookMarksTree() {
  TwoDimensionTree okular_tree;
  okular_tree.append(qMakePair(0, QStringList{"Making America Great Again", "Folder"}));
  okular_tree.append(
      qMakePair(1, QStringList{"Being true, always, again and again", "file:///home/Donald/mybook.pdf#:10"}));
  okular_tree.append(
      qMakePair(1, QStringList{"How to tweet faster than anyone", "file:///home/Donald/mybook.pdf#:12"}));
  okular_tree.append(qMakePair(0, QStringList{"Future of Feminism and Woman Empowerment By Vladimir Putin", "Folder"}));
  okular_tree.append(
      qMakePair(1, QStringList{"Gulag", "file:///home/VladimirPutin/Bullshit.pdf#20;C2:0.499632:0.302495:1"}));
  okular_tree.append(
      qMakePair(1, QStringList{"I said Gulag !", "file:///home/VladimirPutin/Bullshit.pdf#20;C2:0.499632:0.302495:2"}));
  okular_tree.append(qMakePair(
      1, QStringList{"I saaiiiddd GULAG !", "file:///home/VladimirPutin/Bullshit.pdf#20;C2:0.499632:0.302495:12"}));
  return okular_tree;
}
TwoDimensionTree FoldTree(const QString folding_title, TwoDimensionTree tree) {
  tree.prepend(qMakePair(0, QStringList({folding_title, "Folder"})));
  for (int row = 1; row < tree.count(); ++row) {
    tree[row].first++;
  }
  return tree;
}

BookMarksModuleTest::BookMarksModuleTest() : QObject() {
}
void BookMarksModuleTest::init() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
}
void BookMarksModuleTest::initTestCase() {
  // will be called before the first testfunction is executed.
}
void BookMarksModuleTest::cleanup() {
  // will be called after every testfunction.
}
void BookMarksModuleTest::cleanupTestCase() {
  // will be called after the last testfunction was executed.
}
// helpers

void BookMarksModuleTest::load_model_with_konqueror_bookmarks() {
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks.xml");
  m_model->ReadAllSources(true);
}
void BookMarksModuleTest::load_model_with_okular_bookmarks() {
  m_model->setPathForOkularBookmarks("okular_bookmarks.xml");
  m_model->ReadAllSources(true);
}

TwoDimensionTree BookMarksModuleTest::get_tree_of_data_model(QModelIndex parent, int col_start) {
  TwoDimensionTree tree{};
  for (int row = 0; row < m_model->rowCount(parent); ++row) {
    QModelIndex index = m_model->index(row, 0, parent);
    if (index.child(0, 0).isValid()) {
      tree.append(qMakePair(col_start,
                            QStringList({index.data(Bookmarkmodel::BookmarkRoles::Displayrole).toString(), "Folder"})));
      tree.append(get_tree_of_data_model(index, col_start + 1));
    } else {
      tree.append(
          qMakePair(col_start, QStringList({index.data(Bookmarkmodel::BookmarkRoles::Displayrole).toString(),
                                            index.data(Bookmarkmodel::BookmarkRoles::Tooltiprole).toString()})));
    }
  }
  return tree;
}

// Tests
void BookMarksModuleTest::path_are_set_correctly() {
  m_model->setPathForChromeBookamarks("Bookmarks");
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks.xml");
  m_model->setPathForOkularBookmarks("okular_bookmarks.xml");
  QVERIFY2(m_model->getPathForChromeBookmarks() == "Bookmarks", "Path for chrome bookmark is wrong");
  QVERIFY2(m_model->getPathForKonquerorBookmarks() == "konqueror_bookmarks.xml",
           "Path for Konqueror bookmark is wrong");
  QVERIFY2(m_model->getPathForOkularBookmarks() == "okular_bookmarks.xml", "Path for Okular bookmark is wrong");
}

void BookMarksModuleTest::scan_complete_hierarchy_of_konqueror_model_bookmark() {
  load_model_with_konqueror_bookmarks();
  QCOMPARE(get_tree_of_data_model(QModelIndex()), KonquerorBookMarksTree());
}

void BookMarksModuleTest::scan_complete_hierarchy_of_okular_model_bookmark() {
  load_model_with_okular_bookmarks();
  QCOMPARE(get_tree_of_data_model(QModelIndex()), OkularBookMarksTree());
}

void BookMarksModuleTest::scan_complete_hierarchy_of_okular_model_bookmark_when_folded() {
  m_model->setOkularBookmarkFolded(true);
  load_model_with_okular_bookmarks();
  m_model->ReadAllSources(true);
  QCOMPARE(get_tree_of_data_model(QModelIndex()), FoldTree("Okular bookmarks", OkularBookMarksTree()));
}

void BookMarksModuleTest::scan_complete_hierarchy_of_chrome_bookmark_model() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForChromeBookamarks("Bookmarks");
  m_model->ReadAllSources(true);
  TwoDimensionTree expected;
  expected.append(qMakePair(0, QStringList{"Chrome bookmarks bar", "Folder"}));
  expected.append(qMakePair(1, QStringList{"google", "chrome://newtab/"}));
  expected.append(qMakePair(1, QStringList{"Local", "Folder"}));
  expected.append(qMakePair(2, QStringList{"Router", "http://192.168.0.1/"}));
  expected.append(qMakePair(2, QStringList{"Raspberry", "http://192.168.0.2/"}));
  expected.append(qMakePair(2, QStringList{"Drive", "https://www.google.com/intl/en/drive/"}));
  expected.append(qMakePair(1, QStringList{"YouTube", "https://www.youtube.com/?gl=DE"}));
  expected.append(qMakePair(1, QStringList{"Folder1", "Folder"}));
  expected.append(qMakePair(2, QStringList{"Link1", "https://de.wikipedia.org/wiki/GitHub"}));
  expected.append(qMakePair(2, QStringList{"Link2", "https://en.wikipedia.org/wiki/GitHub"}));
  expected.append(qMakePair(2, QStringList{"Subfolder2", "Folder"}));
  expected.append(qMakePair(3, QStringList{"Subfolder1-Link1", "https://github.blog/"}));
  expected.append(qMakePair(3, QStringList{"Subfolder1-Link2", "https://twitter.com/github"}));
  expected.append(qMakePair(2, QStringList{"Subfolder2", "Folder"}));
  expected.append(qMakePair(3, QStringList{"Subfolder2Link1", "https://www.githubstatus.com/"}));
  expected.append(qMakePair(3, QStringList{"Subfolder2Link2", "https://git-scm.com/"}));

  QCOMPARE(get_tree_of_data_model(QModelIndex()), expected);
}

void BookMarksModuleTest::filters_folder_and_items() {
  load_model_with_konqueror_bookmarks();
  m_model->setFilterItemsOnly(false);
  m_model->setSearchField("Bash");

  TwoDimensionTree expected_tree;
  expected_tree.append(qMakePair(0, QStringList{"Linux", "Folder"}));
  expected_tree.append(qMakePair(1, QStringList{"Bash scripting", "Folder"}));
  expected_tree.append(
      qMakePair(2, QStringList{"Bash tutorial", "https://linuxconfig.org/bash-scripting-tutorial-for-beginners"}));
  expected_tree.append(qMakePair(2, QStringList{"Bash scripting cheat sheet", "https://devhints.io/bash"}));
  QCOMPARE(get_tree_of_data_model(QModelIndex()), expected_tree);
}
void BookMarksModuleTest::filters_folder_and_items_when_filtering_items_only() {
  load_model_with_konqueror_bookmarks();
  m_model->setSearchField("Bash");
  m_model->setFilterItemsOnly(true);

  TwoDimensionTree expected_tree;
  expected_tree.append(
      qMakePair(0, QStringList{"Bash tutorial", "https://linuxconfig.org/bash-scripting-tutorial-for-beginners"}));
  expected_tree.append(qMakePair(0, QStringList{"Bash scripting cheat sheet", "https://devhints.io/bash"}));

  QCOMPARE(get_tree_of_data_model(QModelIndex()), expected_tree);
}
void BookMarksModuleTest::model_is_not_filter_when_searchfield_is_empty() {
  load_model_with_konqueror_bookmarks();
  m_model->setSearchField("");
  m_model->setFilterItemsOnly(true);
  QCOMPARE(get_tree_of_data_model(QModelIndex()), KonquerorBookMarksTree());
}

void BookMarksModuleTest::model_is_not_filtered_anymore_when_searchfield_is_empty_again(){
  load_model_with_konqueror_bookmarks();
  m_model->setSearchField("Bash");
  m_model->setFilterItemsOnly(true);
  m_model->setSearchField("");
  QCOMPARE(get_tree_of_data_model(QModelIndex()), KonquerorBookMarksTree());
}

QTEST_MAIN(BookMarksModuleTest)
#include "moc_bookmarksmoduletest.cpp"
