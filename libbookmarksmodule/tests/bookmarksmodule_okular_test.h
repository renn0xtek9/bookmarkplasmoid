#ifndef BOOKMARKSMODULE_OKULAR_TEST_H
#define BOOKMARKSMODULE_OKULAR_TEST_H
#include <libbookmarksmodule/bookmarkmodel.h>
#include <test_utils.h>

#include <QtCore/QObject>

class BookmarksmoduleOkularTest : public QObject {
  Q_OBJECT
 public:
 private Q_SLOTS:
  void init();
  void test_scan_complete_hierarchy_of_okular_bookmark();
  void test_scan_complete_hierarchy_of_okular_model_bookmark_when_folded();

 private:
  QSharedPointer<Bookmarkmodel> m_model{};
  void load_model_with_okular_bookmarks();
};

#endif  // BOOKMARKSMODULE_OKULAR_TEST_H
