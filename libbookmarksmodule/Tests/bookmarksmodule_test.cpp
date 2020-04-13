#include <bookmarksmodule_test.h>
#include <QtCore/QDebug>
#include <QtCore/QModelIndex>
#include <QtCore/QSharedPointer>
#include <bookmarkmodel.hpp>

bool operator==(const Subfolder& subfolder1, const Subfolder& subfolder2) {
  if (subfolder1.first != subfolder2.first) {
    return false;
  }
  if (subfolder1.second.size() != subfolder2.second.size()) {
    return false;
  }
  for (int i = 0; i < subfolder1.second.size(); ++i) {
    if (subfolder1.second.at(i).canConvert(QMetaType::QStringList)) {
      if (subfolder2.second.at(i).canConvert(QMetaType::QStringList)) {
        if (subfolder1.second.at(i).toStringList() != subfolder2.second.at(i).toStringList()) {
          return false;
        }
      } else {
        return false;
      }
    } else {
      if (subfolder1 != subfolder2) {
        return false;
      }
    }
  }
  return true;
}
bool CompareTwoTree(QList<QVariant> tree1, QList<QVariant> tree2) {
  if (tree1.count() != tree2.count()) {
    qDebug() << "List size differs (" << tree1.count() << " against " << tree2.count() << " :\n"
             << tree1 << "\n"
             << tree2;
    return false;
  }
  for (int i = 0; i < tree1.count(); ++i) {
    if (tree1.at(i) != tree2.at(i)) {
      qDebug() << "List differs for element" << i << " " << tree1.at(i) << " " << tree2.at(i);
      
      return false;
    }
  }
  return true;
}

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

QStringList bookmarksmodule_test::list_all_entries_of_the_model_at_this_hierarchical_level(
    const QModelIndex& parent_index) {
  QStringList list_of_entries{};
  for (int i = 0; i < m_model->rowCount(); ++i) {
    QModelIndex current_index = m_model->index(i, 0, parent_index);
    list_of_entries.append(m_model->data(current_index, Qt::DisplayRole).toString());
  }
  return list_of_entries;
}

void bookmarksmodule_test::get_tree_of_data_model(QModelIndex parent, QList<QVariant>& top_level_of_list) {
  for (int row = 0; row < m_model->getModel()->rowCount(parent); ++row) {
    QModelIndex index = m_model->getModel()->index(row, 0, parent);
    QStandardItem* item = m_model->getModel()->itemFromIndex(index);
    if (item->hasChildren()) {
      Subfolder subfolder(qMakePair(item->text(), decltype(m_tree){}));
      //       top_level_of_list.append(QVariant::fromValue(subfolder));
      //       qDebug() << "Appending subolder" << item->text();
      QList<QVariant> content{};
      get_tree_of_data_model(index, subfolder.second);
      //       qDebug() << "The content" << subfolder.second;
      //       Subfolder subfolder(item->text(),{QVariant::fromValue(content)});
      top_level_of_list.append(QVariant::fromValue(subfolder));
      //       qDebug() << "The second contains" << subfolder.second;

      //       qDebug() << subfolder.second.at(0).value<Subfolder>().first;
      //       qDebug() << subfolder.second.at(0).value<Subfolder>().second;

    } else {
      QStringList item_data{item->text(), item->data(Qt::ToolTipRole).toString()};
      top_level_of_list.append(item_data);
    }
  }
}

// Tests
void bookmarksmodule_test::path_are_set_correctly() {
  QVERIFY2(m_model->getPathForChromeBookmarks() == "Bookmarks", "Path for chrome bookmark is wrong");
  QVERIFY2(m_model->getPathForKonquerorBookmarks() == "konqueror_bookmarks.xml",
           "Path for Konqueror bookmark is wrong");
  QVERIFY2(m_model->getPathForOkularBookmarks() == "okular_bookmarks.xml", "Path for Okular bookmark is wrong");
}

void bookmarksmodule_test::get_correct_number_of_element_for_konqueror_bookmarks() {
  int expected_number_of_row = 4;
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks.xml");
  m_model->ReadAllSources(true);
  QVERIFY2(m_model->rowCount() == expected_number_of_row,
           "Do not get the correct number of element when reading form konqueror bookmarks");

  QStringList expected_items{"google", "News", "Linux", "Youtube"};
  QCOMPARE(list_all_entries_of_the_model_at_this_hierarchical_level(), expected_items);
}
void bookmarksmodule_test::scan_complete_hierarchy_of_konqueror_model_bookmark() {
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForKonquerorBookmarks("konqueror_bookmarks.xml");
  m_model->ReadAllSources(true);

  QStringList expected_items{"google", "News", "Linux", "Youtube"};
  QCOMPARE(list_all_entries_of_the_model_at_this_hierarchical_level(), expected_items);

  //     decltype(m_tree) tvs_subfolder_content{QStringList{"russia
  //     today","https://www.rt.com/"},QStringList{"CNN","https://edition.cnn.com/"}}; Subfolder
  //     tv_subfolder{"TVs",tvs_subfolder_content};

  Subfolder tv_subfolder{
      "TVs", {QStringList{"russia today", "https://www.rt.com/"}, QStringList{"CNN", "https://edition.cnn.com/"}}};
  Subfolder news_subfolder{
      "News",
      {QVariant::fromValue(tv_subfolder), QStringList{"Washington post", "https://www.washingtonpost.com/"},
       QStringList{"The intercept", "https://theintercept.com/"}}};

  Subfolder bash_scriptig_subfolder{
      "Bash scripting",
      {QStringList{"Bash tutorial", "https://linuxconfig.org/bash-scripting-tutorial-for-beginners"},
       QStringList{"Bash scripting cheat sheet", "https://devhints.io/bash"}}};
  Subfolder linux_subfolder{"Linux",
                            {QVariant::fromValue(bash_scriptig_subfolder),
                             QStringList{"how to install device driver",
                                         "https://opensource.com/article/18/11/how-install-device-driver-linux"},
                             QStringList{"github-torvald", "https://github.com/torvalds"}}};

  decltype(m_tree) expected_konqueror_tree{QStringList{"google", "http://www.google.com"},
                                           QVariant::fromValue(news_subfolder), QVariant::fromValue(linux_subfolder),
                                           QStringList{"Youtube", "https://www.youtube.com/"}};

  QModelIndex parent{};
  m_tree = decltype(m_tree){};
  get_tree_of_data_model(parent, m_tree);

  QVERIFY(CompareTwoTree(m_tree, expected_konqueror_tree));
  //   QCOMPARE(m_tree, expected_konqueror_tree);

  //     news_subfolder.second.append(QVariant::fromValue(tv_subfolder));

  //     decltype(m_tree) news_subfolder_content{tv_subfolder,QStringList{"Washington
  //     post","https://www.washingtonpost.com/"},
  //                                    QStringList{"The intercept","https://theintercept.com/"}};

  //     Subfolder news_subfolder
  //     TVs.append(
  //     decltype(m_tree) TVs{Subfolder(qMakePair("TVs",tvs_subfolder),QList<QStringList>{QStringList{"Washington
  //     post","https://www.washingtonpost.com/"},
  //                                    QStringList{"The intercept","https://theintercept.com/"}}};

  //     expected_tree
  //   Subfolder test;
  //   test.first = "fucl";
  //   QModelIndex parent{};
  //   get_tree_of_data_model(parent);
  //   qDebug() << "DOOONME";
  //   qDebug() << m_tree.at(1).value<Subfolder>().first;

  //     convert_model_to_qjsonobject();
  /*
  for (int row = 0; row < m_model->getModel()->rowCount(); ++row)
  {
       QModelIndex index = m_model->getModel()->index(row,0,QModelIndex());
      QStandardItem *item = m_model->getModel()->itemFromIndex(index);
      qDebug()<<item->text();
      qDebug()<<item->hasChildren();
//         m_model->getModel()->setData(index,0);

  }
  */

  /*

  parent=m_model->index(2,0,QModelIndex());
  qDebug()<<m_model->getModel()->itemFromIndex(parent);
  expected_items=QStringList{"TVs","Washington post","The intercept"};
//     qDebug()<<list_all_entries_of_the_model_at_this_hierarchical_level();
//     qDebug()<<m_model->data(m_model->index(1,1,parent));
  QCOMPARE(list_all_entries_of_the_model_at_this_hierarchical_level(parent),expected_items);
//     parent=m_model->inde
  */
}

void bookmarksmodule_test::get_correct_number_of_element_for_okular_bookmarks() {
  int expected_number_of_row = 2;
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForOkularBookmarks("okular_bookmarks.xml");
  m_model->ReadAllSources(true);
  QVERIFY2(m_model->rowCount() == expected_number_of_row,
           "Do not get the correct number of element when reading form konqueror bookmarks");
}

void bookmarksmodule_test::get_correct_number_of_element_for_chrome_bookmarks() {
  int expected_number_of_row = 1;
  m_model = QSharedPointer<Bookmarkmodel>(new Bookmarkmodel);
  m_model->setPathForChromeBookamarks("Bookmarks");
  m_model->ReadAllSources(true);
  QCOMPARE(m_model->rowCount(), expected_number_of_row);
  QCOMPARE(list_all_entries_of_the_model_at_this_hierarchical_level(), QStringList("Chrome bookmarks bar"));
}

QTEST_MAIN(bookmarksmodule_test)
#include "moc_bookmarksmodule_test.cpp"
