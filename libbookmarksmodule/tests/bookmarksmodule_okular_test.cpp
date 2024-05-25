#include <bookmarksmodule_okular_test.h>

TwoDimensionTree OkularBookMarksTree() {
  TwoDimensionTree okular_tree;
  okular_tree.append(qMakePair(0, QStringList{"Folder one", "Folder"}));
  okular_tree.append(
      qMakePair(1, QStringList{"Being true, always, again and again", "file:///home/Donald/mybook.pdf#:10"}));
  okular_tree.append(
      qMakePair(1, QStringList{"How to tweet faster than anyone", "file:///home/Donald/mybook.pdf#:12"}));
  okular_tree.append(qMakePair(0, QStringList{"Folder two", "Folder"}));
  okular_tree.append(
      qMakePair(1, QStringList{"Bulshit one", "file:///home/RandomAuthor/Bullshit.pdf#20;C2:0.499632:0.302495:1"}));
  okular_tree.append(
      qMakePair(1, QStringList{"Bullshit two", "file:///home/RandomAuthor/Bullshit.pdf#20;C2:0.499632:0.302495:2"}));
  okular_tree.append(
      qMakePair(1, QStringList{"Bullshit three", "file:///home/RandomAuthor/Bullshit.pdf#20;C2:0.499632:0.302495:12"}));
  return okular_tree;
}

void BookmarksmoduleOkularTest::init() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
}

void BookmarksmoduleOkularTest::test_scan_complete_hierarchy_of_okular_bookmark() {
  load_model_with_okular_bookmarks();
  QCOMPARE(get_tree_of_data_model(QModelIndex(), m_model), OkularBookMarksTree());
}

void BookmarksmoduleOkularTest::test_scan_complete_hierarchy_of_okular_model_bookmark_when_folded() {
  m_model->setOkularBookmarkFolded(true);
  load_model_with_okular_bookmarks();
  m_model->ReadAllSources(true);
  QCOMPARE(get_tree_of_data_model(QModelIndex(), m_model), FoldTree("Okular bookmarks", OkularBookMarksTree()));
}

void BookmarksmoduleOkularTest::load_model_with_okular_bookmarks() {
  m_model->setPathForOkularBookmarks("okular_bookmarks.xml");
  m_model->ReadAllSources(true);
}

QTEST_GUILESS_MAIN(BookmarksmoduleOkularTest)
#include "moc_bookmarksmodule_okular_test.cpp"
