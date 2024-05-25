#include <libbookmarksmodule/data_types.h>
#include <libbookmarksmodule/xbel_reader.h>
#include <mocks.h>
#include <xbel_reader_test.h>

#include <QDebug>
#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItemModel>
#include <QtTest/QtTest>


QStandardItem* created_expected_bookmark_item()
{
  QStandardItem* expected_item=new QStandardItem();
  expected_item->setToolTip("http://www.url.com");
  expected_item->setData("bookmarktitle", BookmarkRoles::Displayrole);
  expected_item->setData(false, BookmarkRoles::IsFolderRole);
  expected_item->setData("mocked_getCustomOrThemeIconPath", Qt::UserRole);
  expected_item->setData(int(BookmarkSource::Konqueror), BookmarkRoles::SourceRole);
  return expected_item;
}

QStandardItem* created_expected_title()
{
  QStandardItem* expected_item=new QStandardItem();
  expected_item->setData("bookmarktitle", Qt::DisplayRole);
  return expected_item;
}
QStandardItem* created_expected_metdata()  {
    QStandardItem* expected_item=new QStandardItem();

  expected_item->setData("mocked_getCustomOrThemeIconPath", Qt::UserRole);
  return expected_item;

  }

QStandardItem* created_expected_icon()
{

  QStandardItem* expected_item=new QStandardItem();
  expected_item->setData("mocked_getCustomOrThemeIconPath", Qt::UserRole);
  return expected_item;
}

QStandardItem* created_expected_empty_folder()
{
  QStandardItem* expected_item=new QStandardItem();
  expected_item->setData(true, BookmarkRoles::IsFolderRole);
  expected_item->setData("TVs",Qt::DisplayRole);
  return expected_item;
}


void XbelReaderTest::test_read_xbel_bookmark() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<bookmark href="http://www.url.com">
<title>bookmarktitle</title>
<info>
    <metadata owner="medata_owner">
      <bookmark:icon name ="icon name"/>
    </metadata>
</info>
</bookmark>)");

  fixture_test_xbel(xml_stream, created_expected_bookmark_item, "<bookmark>");
}

void XbelReaderTest::test_empty_folder() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<folder folded="no">
   <title>TVs</title>
  </folder>)");

  fixture_test_xbel(xml_stream, created_expected_empty_folder, "Empty Folder");
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

//   MockEnvironmentThemeFacade facade{};
//   XbelReader xbel_reader{BookmarkSource::Konqueror,facade};

//   QStandardItem expected_item{};
//   expected_item.setText("TVs");
//   expected_item.setData("mocked_getCustomOrThemeIconPath", Qt::UserRole);





//   fixture_test_xbel(xml_stream, expected_item, "Folder");
//   // QVERIFY2(parent_item.data(BookmarkRoles::IsFolderRole).toBool() == true, "BookmarkRoles::IsFolderRole does not match");
//   // QVERIFY2(parent_item.text() == "TVs", "Title is wrong");
//   // // QVERIFY2(parent_item.hasChildren() == true, "Did not read children element");
//   // QVERIFY2(parent_item.rowCount() > 0, "Did not read children element");
// }

void XbelReaderTest::test_read_xbel_icon() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<bookmark:icon name="www"/>)");

  fixture_test_xbel(xml_stream, created_expected_icon, "<bookmark:icon name>");
}

void XbelReaderTest::test_read_xbel_title() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<title>bookmarktitle</title>)");

  fixture_test_xbel(xml_stream, created_expected_title, "<title>");
}

void XbelReaderTest::test_read_xbel_metadata() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<metadata owner="http://freedesktop.org">
  <bookmark:icon name="bookmark_folder"/>
  </metadata>)");
  fixture_test_xbel(xml_stream, created_expected_metdata, "<metadata>");
}

void XbelReaderTest::fixture_test_xbel(QXmlStreamReader& xml_stream,
                                       std::function<QStandardItem*()> expecatance_builder,
                                       const QString& message) {
  QStandardItem parent;
  MockEnvironmentThemeFacade facade{};
  XbelReader xbel_reader{BookmarkSource::Konqueror, facade};
  xbel_reader.readXbelElement(xml_stream, parent);

  QStandardItem* expected = expecatance_builder();


  ASSERT_EQ(parent.text(), expected->text(), message + ": text does not match");
  ASSERT_EQ(parent.data(BookmarkRoles::IsFolderRole).toBool(), expected->data(BookmarkRoles::IsFolderRole).toBool(),
            message + ": isFolder does not match");
  ASSERT_EQ(parent.toolTip(), expected->toolTip(), message + ": tooltip does not match");
  ASSERT_EQ(parent.data(Qt::UserRole), expected->data(Qt::UserRole), message + ": UserRole does not match");
  ASSERT_EQ(parent.data(BookmarkRoles::SourceRole).toInt(), expected->data(BookmarkRoles::SourceRole).toInt(),
            message + ": SourceRole does not match");
  ASSERT_EQ(parent.data(BookmarkRoles::Displayrole).toString(), expected->data(BookmarkRoles::Displayrole).toString(),
            message + ": Displayrole does not match");
  ASSERT_EQ(parent.data(BookmarkRoles::Iconpathrole).toString(), expected->data(BookmarkRoles::Iconpathrole).toString(),
            message + ": Iconpathrole does not match");

  delete (expected);
}

QTEST_GUILESS_MAIN(XbelReaderTest)
#include "moc_xbel_reader_test.cpp"
