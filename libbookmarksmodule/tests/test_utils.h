#ifndef TEST_UTILS_H
#define TEST_UTILS_H
#include <libbookmarksmodule/bookmarkmodel.h>
#include <libbookmarksmodule/data_types.h>

#include <QDebug>
#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtTest/QTest>
#include <QtGui/QStandardItemModel>

#define ASSERT_EQ(actual, expected, message)                                                   \
  QVERIFY2(actual == expected, QString(message + " - Actual: " + QVariant(actual).toString() + \
                                       " Expected: " + QVariant(expected).toString())          \
                                   .toStdString()                                              \
                                   .c_str())

typedef QPair<int, QStringList> TreeElement;
typedef QList<TreeElement> TwoDimensionTree;

inline QDebug operator<<(QDebug d, const TwoDimensionTree& tree) {
  for (const auto& row : tree) {
    d << "\n";
    for (int i = 0; i < row.first; ++i) {
      d << "  ";
    }
    d << row.second.at(0) << " " << row.second.at(1);
  }
  return d;
}

inline QDebug operator<<(QDebug d, const TreeElement& treelement) {
  d << " index" << treelement.first << " content: " << treelement.second;
  return d;
}

inline char* toString(const TreeElement& treelement) {
  QString content, index;
  for (int i = 0; i < treelement.second.size(); ++i) {
    content += treelement.second.at(i) + " ";
  }
  index.setNum(treelement.first);
  return QTest::toString(QString("index: ") + index + QString(" content: ") + content);
}

inline TwoDimensionTree FoldTree(const QString folding_title, TwoDimensionTree tree) {
  tree.prepend(qMakePair(0, QStringList({folding_title, "Folder"})));
  for (int row = 1; row < tree.count(); ++row) {
    tree[row].first++;
  }
  return tree;
}

inline TwoDimensionTree get_tree_of_data_model(QModelIndex parent,
                                               QSharedPointer<Bookmarkmodel> model,
                                               int col_start = 0) {
  TwoDimensionTree tree{};
  for (int row = 0; row < model->rowCount(parent); ++row) {
    QModelIndex index = model->index(row, 0, parent);
    if (index.child(0, 0).isValid()) {
      tree.append(qMakePair(col_start, QStringList({index.data(BookmarkRoles::Displayrole).toString(), "Folder"})));
      tree.append(get_tree_of_data_model(index, model, col_start + 1));
    } else {
      tree.append(qMakePair(col_start, QStringList({index.data(BookmarkRoles::Displayrole).toString(),
                                                    index.data(BookmarkRoles::Tooltiprole).toString()})));
    }
  }
  return tree;
}

inline void assert_equal(QStandardItem* actual,QStandardItem* expected, QString message)
{
  ASSERT_EQ(actual->hasChildren(), expected->hasChildren(), message + ": hasChildren does not match");
  ASSERT_EQ(actual->text(), expected->text(), message + ": text does not match");
  ASSERT_EQ(actual->data(BookmarkRoles::IsFolderRole).toBool(), expected->data(BookmarkRoles::IsFolderRole).toBool(), message + ": isFolder does not match");
  ASSERT_EQ(actual->toolTip(), expected->toolTip(), message + ": tooltip does not match");
  ASSERT_EQ(actual->data(Qt::UserRole), expected->data(Qt::UserRole), message + ": UserRole does not match");
  ASSERT_EQ(actual->data(BookmarkRoles::SourceRole).toInt(), expected->data(BookmarkRoles::SourceRole).toInt(), message + ": SourceRole does not match");
  ASSERT_EQ(actual->data(BookmarkRoles::Displayrole).toString(), expected->data(BookmarkRoles::Displayrole).toString(), message + ": Displayrole does not match");
  ASSERT_EQ(actual->data(BookmarkRoles::Iconpathrole).toString(), expected->data(BookmarkRoles::Iconpathrole).toString(), message + ": Iconpathrole does not match");
  for (int row_index = 0; row_index < actual->rowCount(); ++row_index) {
    assert_equal(actual->child(row_index,0),expected->child(row_index,0), "Children "+QString::number(row_index)+": "+ message);
  }
}

#endif  // TEST_UTILS_H
