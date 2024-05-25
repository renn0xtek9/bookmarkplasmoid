#ifndef XBEL_FILE_READER_TEST_H
#define XBEL_FILE_READER_TEST_H

#include <QtCore/QObject>
#include <QtTest/QTest>

class XbelFileReaderTest : public QObject {
  Q_OBJECT

 private Q_SLOTS:
  void test_constructor();
  void test_set_file_path_of_non_existing_file();
  void test_set_file_path_of_existing_file();
  void test_read_calls_read_on_xml_parser();
};

#endif  // XBEL_FILE_READER_TEST_H
