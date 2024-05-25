#ifndef XBEL_READER_TEST_H
#define XBEL_READER_TEST_H

#include <QtCore/QObject>
#include <QtTest/QTest>
#include <QtGui/QStandardItemModel>
#include <functional>

#include <test_utils.h>


void affect_expected_bookmark_item(QStandardItem* item) ;
void affect_expected_title(QStandardItem* item) ;
void affect_expected_metdata(QStandardItem* item);
void affect_expected_icon(QStandardItem* item);
void affect_expected_empty_folder(QStandardItem* item);
void affect_expected_second_empty_folder(QStandardItem* item);
void affect_expected_folder_with_one_bookmark(QStandardItem* item);
void affect_expected_folder_with_two_bookmark(QStandardItem* item);
void affect_expected_two_folder_side_by_side(QStandardItem* item);
void affect_expected_nested_folder(QStandardItem* item);
void affect_expected_nested_folder_and_side_by_side(QStandardItem* item);


class XbelReaderTest : public QObject {
  Q_OBJECT
 private Q_SLOTS:
  void test_read_xbel_title();
  void test_read_xbel_icon();
  void test_read_xbel_metadata();
  void test_read_xbel_bookmark();
  void test_empty_folder();
  void test_folder_with_one_bookmark();
  void test_folder_with_two_bookmark();
  void test_two_folder_side_by_side();
  void test_nested_folder();
  void test_nested_folder_and_side_by_side();

 private:
  void fixture_test_xbel(QXmlStreamReader& xml_stream, std::function<void(QStandardItem*)> expected_builder, const QString& message);
};

#endif  // XBEL_READER_TEST_H
