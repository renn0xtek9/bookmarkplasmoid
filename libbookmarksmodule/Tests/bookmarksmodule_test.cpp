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

void bookmarksmodule_test::scan_complete_hierarchy_of_okular_model_bookmark() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForOkularBookmarks("okular_bookmarks.xml");
  m_model->ReadAllSources(true);
  TwoDimensionTree expected_tree;
  expected_tree.append(qMakePair(0, QStringList{"Making America Great Again", "Folder"}));
  expected_tree.append(
      qMakePair(1, QStringList{"Being true, always, again and again", "file:///home/Donald/mybook.pdf#:10"}));
  expected_tree.append(
      qMakePair(1, QStringList{"How to tweet faster than anyone", "file:///home/Donald/mybook.pdf#:12"}));
  expected_tree.append(
      qMakePair(0, QStringList{"Future of Feminism and Woman Empowerment By Vladimir Putin", "Folder"}));
  expected_tree.append(
      qMakePair(1, QStringList{"Gulag", "file:///home/VladimirPutin/Bullshit.pdf#20;C2:0.499632:0.302495:1"}));
  expected_tree.append(
      qMakePair(1, QStringList{"I said Gulag !", "file:///home/VladimirPutin/Bullshit.pdf#20;C2:0.499632:0.302495:2"}));
  expected_tree.append(qMakePair(
      1, QStringList{"I saaiiiddd GULAG !", "file:///home/VladimirPutin/Bullshit.pdf#20;C2:0.499632:0.302495:12"}));
  QCOMPARE(get_tree_of_data_model(QModelIndex()), expected_tree);
}

void bookmarksmodule_test::scan_complete_hierarchy_of_okular_model_bookmark_when_folded() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForOkularBookmarks("okular_bookmarks.xml");
  m_model->setOkularBookmarkFolded(true);
  m_model->ReadAllSources(true);
  TwoDimensionTree expected_tree;
  expected_tree.append(qMakePair(0, QStringList{"Okular bookmarks", "Folder"}));
  expected_tree.append(qMakePair(1, QStringList{"Making America Great Again", "Folder"}));
  expected_tree.append(
      qMakePair(2, QStringList{"Being true, always, again and again", "file:///home/Donald/mybook.pdf#:10"}));
  expected_tree.append(
      qMakePair(2, QStringList{"How to tweet faster than anyone", "file:///home/Donald/mybook.pdf#:12"}));
  expected_tree.append(
      qMakePair(1, QStringList{"Future of Feminism and Woman Empowerment By Vladimir Putin", "Folder"}));
  expected_tree.append(
      qMakePair(2, QStringList{"Gulag", "file:///home/VladimirPutin/Bullshit.pdf#20;C2:0.499632:0.302495:1"}));
  expected_tree.append(
      qMakePair(2, QStringList{"I said Gulag !", "file:///home/VladimirPutin/Bullshit.pdf#20;C2:0.499632:0.302495:2"}));
  expected_tree.append(qMakePair(
      2, QStringList{"I saaiiiddd GULAG !", "file:///home/VladimirPutin/Bullshit.pdf#20;C2:0.499632:0.302495:12"}));
  QCOMPARE(get_tree_of_data_model(QModelIndex()), expected_tree);
}

void bookmarksmodule_test::scan_complete_hierarchy_of_chrome_bookmark_model() {
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

void bookmarksmodule_test::filters_folder_and_items() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks.xml");
  m_model->ReadAllSources(true);
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
void bookmarksmodule_test::filters_folder_and_items_when_filtering_items_only() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks.xml");
  m_model->ReadAllSources(true);
  m_model->setFilterItemsOnly(true);
  m_model->setSearchField("Bash");

  TwoDimensionTree expected_tree;
  expected_tree.append(
      qMakePair(0, QStringList{"Bash tutorial", "https://linuxconfig.org/bash-scripting-tutorial-for-beginners"}));
  expected_tree.append(qMakePair(0, QStringList{"Bash scripting cheat sheet", "https://devhints.io/bash"}));

  QCOMPARE(get_tree_of_data_model(QModelIndex()), expected_tree);
}

QTEST_MAIN(bookmarksmodule_test)
#include "moc_bookmarksmodule_test.cpp"
