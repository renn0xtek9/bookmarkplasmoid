#ifndef BOOKMARKSMODULE_CHROME_TEST_H
#define BOOKMARKSMODULE_CHROME_TEST_H
#include <QtCore/QObject>
#include <bookmarkmodel.hpp>
class BookmarksmoduleChromeTest : public QObject {
  Q_OBJECT
 private Q_SLOTS:
  void init();
  void scan_complete_hierarchy_of_chrome_bookmark_model();

 private:
  QSharedPointer<Bookmarkmodel> m_model{};
  void load_model_with_chrome_bookmarks();
};

#endif  // BOOKMARKSMODULE_CHROME_TEST_H
