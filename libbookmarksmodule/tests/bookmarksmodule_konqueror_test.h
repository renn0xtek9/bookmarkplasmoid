#ifndef BOOKMARKSMODULE_KONQUEROR_TEST_H
#define BOOKMARKSMODULE_KONQUEROR_TEST_H
#include <test_utils.h>

#include <QtCore/QSharedPointer>
#include <QtTest/QTest>
#include <bookmarkmodel.hpp>

class BookmarksmoduleKonquerorTest : public QObject {
  Q_OBJECT
 private Q_SLOTS:
  void init();

  void filters_folder_and_items();
  void filters_folder_and_items_when_filtering_items_only();
  void scan_complete_hierarchy_of_konqueror_model_bookmark();
  void model_is_not_filter_when_searchfield_is_empty();
  void model_is_not_filtered_anymore_when_searchfield_is_empty_again();

 private:
  QSharedPointer<Bookmarkmodel> m_model{};
  void load_model_with_konqueror_bookmarks();
};

#endif  // BOOKMARKSMODULE_KONQUEROR_TEST_H
