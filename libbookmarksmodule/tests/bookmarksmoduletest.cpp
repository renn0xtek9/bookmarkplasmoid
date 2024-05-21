#include <bookmarksmoduletest.h>
#include <test_utils.h>

#include <QtCore/QDebug>
#include <QtCore/QModelIndex>
#include <QtCore/QSharedPointer>
#include <bookmarkmodel.hpp>

void BookMarksModuleTest::init() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
}

void BookMarksModuleTest::path_are_set_correctly() {
  m_model->setPathForChromeBookamarks("Bookmarks");
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks.xml");
  m_model->setPathForOkularBookmarks("okular_bookmarks.xml");
  QVERIFY2(m_model->getPathForChromeBookmarks() == "Bookmarks", "Path for chrome bookmark is wrong");
  QVERIFY2(m_model->getPathForKonquerorBookmarks() == "konqueror_bookmarks.xml",
           "Path for Konqueror bookmark is wrong");
  QVERIFY2(m_model->getPathForOkularBookmarks() == "okular_bookmarks.xml", "Path for Okular bookmark is wrong");
}

void BookMarksModuleTest::filters_folder_are_not_shown_even_if_they_match_when_filtering_items_only() {
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks_same_name_for_folder_and_items.xml");
  m_model->setSearchField("News");
  m_model->setFilterItemsOnly(true);
  m_model->ReadAllSources(true);
  TwoDimensionTree expected_tree;
  expected_tree.append(qMakePair(0, QStringList{"News2", "http://www.google.com"}));
  expected_tree.append(qMakePair(0, QStringList{"News", "https://www.news.com/"}));

  QCOMPARE(get_tree_of_data_model(QModelIndex(), m_model), expected_tree);
}

void BookMarksModuleTest::filters_order_of_setting_items_only_and_setting_search_field_has_no_impact() {
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks_same_name_for_folder_and_items.xml");
  m_model->setFilterItemsOnly(true);
  m_model->setSearchField("News");
  m_model->ReadAllSources(true);
  TwoDimensionTree items_only_before_searchfield = get_tree_of_data_model(QModelIndex(), m_model);

  QSharedPointer<Bookmarkmodel> model_two(new Bookmarkmodel);
  model_two->setPathForKonquerorBookmarks("konqueror_bookmarks_same_name_for_folder_and_items.xml");
  model_two->setSearchField("News");
  model_two->setFilterItemsOnly(true);
  model_two->ReadAllSources(true);
  TwoDimensionTree searchfield_before_items_only = get_tree_of_data_model(QModelIndex(), model_two);

  QCOMPARE(items_only_before_searchfield, searchfield_before_items_only);
}

QTEST_MAIN(BookMarksModuleTest)
#include "moc_bookmarksmoduletest.cpp"
