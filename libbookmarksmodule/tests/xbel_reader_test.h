#ifndef XBEL_READER_TEST_H
#define XBEL_READER_TEST_H

#include <QtCore/QObject>
#include <QtTest/QTest>
#include <QtGui/QStandardItemModel>
#include <functional>

#define ASSERT_EQ(actual, expected, message)                                                   \
  QVERIFY2(actual == expected, QString(message + " - Actual: " + QVariant(actual).toString() + \
                                       " Expected: " + QVariant(expected).toString())          \
                                   .toStdString()                                              \
                                   .c_str())

  QStandardItem* created_expected_bookmark_item() ;
  QStandardItem* created_expected_title() ;
  QStandardItem* created_expected_metdata();
  QStandardItem* created_expected_icon();
  QStandardItem* created_expected_empty_folder();


class XbelReaderTest : public QObject {
  Q_OBJECT
 private Q_SLOTS:
  void test_read_xbel_bookmark();
  void test_empty_folder();
  // void test_read_xbel_folder();
  void test_read_xbel_title();
  void test_read_xbel_icon();
  void test_read_xbel_metadata();

 private:
  void fixture_test_xbel(QXmlStreamReader& xml_stream, std::function<QStandardItem*()> expecatance_builder, const QString& message);
};

#endif  // XBEL_READER_TEST_H
