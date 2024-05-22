#include <bookmarksmodule_chrome_test.h>
#include <libbookmarksmodule/bookmarkmodel.h>
#include <test_utils.h>

#include <QtCore/QSharedPointer>
#include <QtTest/QTest>

void BookmarksmoduleChromeTest::init() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
}
void BookmarksmoduleChromeTest::scan_complete_hierarchy_of_chrome_bookmark_model() {
  load_model_with_chrome_bookmarks();
  TwoDimensionTree expected;
  expected.append(qMakePair(0, QStringList{"Chrome bookmarks bar", "Folder"}));
  expected.append(qMakePair(1, QStringList{"google", "chrome://newtab/"}));
  expected.append(qMakePair(1, QStringList{"Local", "Folder"}));
  expected.append(qMakePair(2, QStringList{"Router", "http://url_one/"}));
  expected.append(qMakePair(2, QStringList{"Raspberry", "http://url_two/"}));
  expected.append(qMakePair(2, QStringList{"Drive", "https://www.foo.bar"}));
  expected.append(qMakePair(1, QStringList{"YouTube", "https://www.youtube.com/"}));
  expected.append(qMakePair(1, QStringList{"Folder1", "Folder"}));
  expected.append(qMakePair(2, QStringList{"Link1", "https://de.wikipedia.org/wiki/GitHub"}));
  expected.append(qMakePair(2, QStringList{"Link2", "https://en.wikipedia.org/wiki/GitHub"}));
  expected.append(qMakePair(2, QStringList{"Subfolder1", "Folder"}));
  expected.append(qMakePair(3, QStringList{"Subfolder1-Link1", "https://github.blog/"}));
  expected.append(qMakePair(3, QStringList{"Subfolder1-Link2", "https://twitter.com/github"}));
  expected.append(qMakePair(2, QStringList{"Subfolder2", "Folder"}));
  expected.append(qMakePair(3, QStringList{"Subfolder2Link1", "https://www.githubstatus.com/"}));
  expected.append(qMakePair(3, QStringList{"Subfolder2Link2", "https://git-scm.com/"}));

  QCOMPARE(get_tree_of_data_model(QModelIndex(), m_model), expected);
}

void BookmarksmoduleChromeTest::load_model_with_chrome_bookmarks() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForChromeBookamarks("Bookmarks");
  m_model->ReadAllSources(true);
}

QTEST_MAIN(BookmarksmoduleChromeTest)
#include "moc_bookmarksmodule_chrome_test.cpp"
