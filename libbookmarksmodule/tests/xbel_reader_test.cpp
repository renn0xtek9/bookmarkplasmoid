#include <libbookmarksmodule/data_types.h>
#include <libbookmarksmodule/xbel_reader.h>
#include <mocks.h>
#include <xbel_reader_test.h>

#include <QDebug>
#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItemModel>
#include <QtTest/QtTest>

void XbelReaderTest::test_read_xbel_bookmark() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<bookmark href="http://www.url.com">
<title>bookmarktitle</title>
<info>
    <metadata owner="medata_owner">
      <bookmark: icon name ="icon name"/>
    </metadata>
</info>
</bookmark>)");
  xml_stream.readNextStartElement();

  QStandardItem parent_item{};
  MockEnvironmentThemeFacade facade{};
  XbelReader xbel_reader{BookmarkSource::Konqueror, facade};
  xbel_reader.readXbelBookmark(xml_stream, parent_item);
  QVERIFY2(parent_item.data(BookmarkRoles::IsFolderRole).toBool() == false, "The bookmark is a folder");
  QVERIFY2(parent_item.toolTip() == QString("http://www.url.com"),
           QString("The tooltip is not correct: " + parent_item.toolTip()).toStdString().c_str());
  QVERIFY2(parent_item.data(BookmarkRoles::Displayrole).toString() == QString("bookmarktitle"),
           QString("The title is notcorrect: " + parent_item.data(BookmarkRoles::Displayrole).toString())
               .toStdString()
               .c_str());
}

// void XbelReaderTest::test_read_xbel_folder() {
//   QXmlStreamReader xml_stream;
//   xml_stream.addData(
//       R"(<folder folded="no">
//    <title>TVs</title>
//    <info>
//     <metadata owner="http://freedesktop.org">
//      <bookmark:icon name="bookmark_folder"/>
//     </metadata>
//    </info>
//    <bookmark href="https://www.foobar.com/">
//     <title>foobar</title>
//     <info>
//      <metadata owner="http://freedesktop.org">
//       <bookmark:icon name="www"/>
//      </metadata>
//     </info>
//    </bookmark>
//    <bookmark href="https://edition.cnn.com/">
//     <title>CNN</title>
//     <info>
//      <metadata owner="http://freedesktop.org">
//       <bookmark:icon name="www"/>
//      </metadata>
//     </info>
//    </bookmark>
//   </folder>)");
//   xml_stream.readNextStartElement();

//   QStandardItem parent_item{};
//   XbelReader xbel_reader{BookmarkSource::Konqueror};
//   xbel_reader.readXbelFolder(xml_stream, parent_item);
//   QVERIFY2(parent_item.data(BookmarkRoles::IsFolderRole).toBool() == true, "The bookmark is not a folder");
//   QVERIFY2(parent_item.text() == "TVs", "Title is wrong");
//   // QVERIFY2(parent_item.hasChildren() == true, "Did not read children element");
//   QVERIFY2(parent_item.rowCount() > 0, "Did not read children element");
// }

void XbelReaderTest::test_read_xbel_icon() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<bookmark:icon name="www"/>)");
  xml_stream.readNextStartElement();

  QStandardItem expected;
  expected.setData("mocked_getCustomOrThemeIconPath", Qt::UserRole);
  fixture_test_xbel(xml_stream, expected, "<bookmark: icon name>");
}

void XbelReaderTest::test_read_xbel_title() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<title>bookmarktitle</title>)");
  xml_stream.readNextStartElement();

  fixture_test_xbel(xml_stream, QStandardItem("bookmarktitle"), "<title>");
}

void XbelReaderTest::test_read_xbel_metadata() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<metadata owner="http://freedesktop.org">
  <bookmark:icon name="bookmark_folder"/>
  </metadata>)");
  xml_stream.readNextStartElement();

  QStandardItem expected{};
  QStandardItem child{};
  child.setData("mocked_getCustomOrThemeIconPath", Qt::UserRole);
  expected.setChild(0, 0, &child);

  fixture_test_xbel(xml_stream, expected, "<metadata>");
}

void XbelReaderTest::fixture_test_xbel(QXmlStreamReader& xml_stream,
                                       const QStandardItem& expected,
                                       const QString& message) {
  QStandardItem parent;
  MockEnvironmentThemeFacade facade{};
  XbelReader xbel_reader{BookmarkSource::Konqueror, facade};
  xbel_reader.readXbelElement(xml_stream, parent);

  ASSERT_EQ(parent.text(), expected.text(), message + ": text does not match");
  ASSERT_EQ(parent.data(BookmarkRoles::IsFolderRole).toBool(), expected.data(BookmarkRoles::IsFolderRole).toBool(),
            message + ": isFolder does not match");
  ASSERT_EQ(parent.toolTip(), expected.toolTip(), message + ": tooltip does not match");
  ASSERT_EQ(parent.data(Qt::UserRole), expected.data(Qt::UserRole), message + ": UserRole does not match");
  ASSERT_EQ(parent.data(BookmarkRoles::SourceRole).toInt(), expected.data(BookmarkRoles::SourceRole).toInt(),
            message + ": SourceRole does not match");
  ASSERT_EQ(parent.data(BookmarkRoles::Displayrole).toString(), expected.data(BookmarkRoles::Displayrole).toString(),
            message + ": Displayrole does not match");
  ASSERT_EQ(parent.data(BookmarkRoles::Iconpathrole).toString(), expected.data(BookmarkRoles::Iconpathrole).toString(),
            message + ": Iconpathrole does not match");
}

QTEST_GUILESS_MAIN(XbelReaderTest)
#include "moc_xbel_reader_test.cpp"
