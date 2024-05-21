#ifndef BOOKMARKSMODULE_TEST_HPP
#define BOOKMARKSMODULE_TEST_HPP
#include <test_utils.h>

#include <QtCore/QSharedPointer>
#include <QtTest/QTest>
#include <bookmarkmodel.hpp>

class BookMarksModuleTest : public QObject {
  Q_OBJECT
 private Q_SLOTS:
  void init();

  void path_are_set_correctly();

  void filters_folder_are_not_shown_even_if_they_match_when_filtering_items_only();
  void filters_order_of_setting_items_only_and_setting_search_field_has_no_impact();

 private:
  QSharedPointer<Bookmarkmodel> m_model{};
  void load_model_with_konqueror_bookmarks();
};

#endif  // BOOKMARKSMODULE_TEST_HPP
