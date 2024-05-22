#ifndef XBEL_READER_TEST_H
#define XBEL_READER_TEST_H

#include <QtCore/QObject>
#include <QtTest/QTest>

#define ASSERT_EQ(actual, expected, message)                                                   \
  QVERIFY2(actual == expected, QString(message + " - Actual: " + QVariant(actual).toString() + \
                                       " Expected: " + QVariant(expected).toString())          \
                                   .toStdString()                                              \
                                   .c_str())

class XbelReaderTest : public QObject {
  Q_OBJECT
 private Q_SLOTS:
  void test_read_xbel_bookmark();
  // void test_read_xbel_folder();
  void test_read_xbel_title();
  void test_read_xbel_icon();
  void test_read_xbel_metadata();

 private:
  void fixture_test_xbel(QXmlStreamReader& xml_stream, const QStandardItem& expected, const QString& message);
};

#endif  // XBEL_READER_TEST_H
