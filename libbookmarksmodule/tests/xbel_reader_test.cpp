#include <libbookmarksmodule/data_types.h>
#include <libbookmarksmodule/xbel_reader.h>
#include <mocks.h>
#include <xbel_reader_test.h>

#include <QDebug>
#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItemModel>
#include <QtTest/QtTest>


void affect_expected_bookmark_item(QStandardItem* item)
{
  QStandardItem* bookmark=new QStandardItem();
  bookmark->setToolTip("http://www.url.com");
  bookmark->setData("bookmarktitle", BookmarkRoles::Displayrole);
  bookmark->setData(false, BookmarkRoles::IsFolderRole);
  bookmark->setData("mocked_getCustomOrThemeIconPath", Qt::UserRole);
  bookmark->setData(int(BookmarkSource::Konqueror), BookmarkRoles::SourceRole);
  item->appendRow(bookmark);
}

void affect_expected_bookmark_item_two(QStandardItem* item)
{
  QStandardItem* bookmark=new QStandardItem();
  bookmark->setToolTip("http://www.url.com");
  bookmark->setData("bookmark2", BookmarkRoles::Displayrole);
  bookmark->setData(false, BookmarkRoles::IsFolderRole);
  bookmark->setData("mocked_getCustomOrThemeIconPath", Qt::UserRole);
  bookmark->setData(int(BookmarkSource::Konqueror), BookmarkRoles::SourceRole);
  item->appendRow(bookmark);
}

void affect_expected_title(QStandardItem* item)
{
  item->setData("bookmarktitle", Qt::DisplayRole);
}
void affect_expected_metdata(QStandardItem* item)  {
  item->setData("mocked_getCustomOrThemeIconPath", Qt::UserRole);
}

void affect_expected_icon(QStandardItem* item)
{
  item->setData("mocked_getCustomOrThemeIconPath", Qt::UserRole);
}

void affect_expected_empty_folder(QStandardItem* item)
{
  QStandardItem* folder_item=new QStandardItem();
  folder_item->setData(true, BookmarkRoles::IsFolderRole);
  folder_item->setData("TVs",Qt::DisplayRole);

  // item->appendRow(folder_item);
  item->setChild(item->rowCount(),0,folder_item);
  QVERIFY(item->hasChildren());
  QVERIFY(!item->child(0)->hasChildren());
}

void affect_expected_folder_with_one_bookmark(QStandardItem* item)
{
  item->setData(true, BookmarkRoles::IsFolderRole);
  item->setData("TVs",Qt::DisplayRole);

  affect_expected_bookmark_item(item);
}


void affect_expected_folder_with_two_bookmark(QStandardItem* item)
{
  item->setData(true, BookmarkRoles::IsFolderRole);
  item->setData("TVs",Qt::DisplayRole);

  affect_expected_bookmark_item(item);
  affect_expected_bookmark_item_two(item);
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

  fixture_test_xbel(xml_stream, affect_expected_bookmark_item, "<bookmark>");
}

void XbelReaderTest::test_empty_folder() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<folder folded="no">
   <title>TVs</title>
  </folder>)");

  fixture_test_xbel(xml_stream, affect_expected_empty_folder, "Empty Folder");
}

// void XbelReaderTest::test_folder_with_one_bookmark()
// {
//   QXmlStreamReader xml_stream;
//   xml_stream.addData(R"(<folder folded="no">
//    <title>TVs</title>
//    <bookmark href="http://www.url.com">
// <title>bookmarktitle</title>
// <info>
//     <metadata owner="medata_owner">
//       <bookmark:icon name ="icon name"/>
//     </metadata>
// </info>
// </bookmark>
//   </folder>)");
//   fixture_test_xbel(xml_stream,affect_expected_folder_with_one_bookmark,"Folder with one bookmark");
// }

// void XbelReaderTest::test_folder_with_two_bookmark()
// {
//   QXmlStreamReader xml_stream;
//   xml_stream.addData(R"(<folder folded="no">
//    <title>TVs</title>
//    <bookmark href="http://www.url.com">
// <title>bookmarktitle</title>
// <info>
//     <metadata owner="medata_owner">
//       <bookmark:icon name ="icon name"/>
//     </metadata>
// </info>
// </bookmark>
// <bookmark href="http://www.url.com">
// <title>bookmark2</title>
// <info>
//     <metadata owner="medata_owner">
//       <bookmark:icon name ="icon name"/>
//     </metadata>
// </info>
// </bookmark>
//   </folder>)");
//   fixture_test_xbel(xml_stream,affect_expected_folder_with_two_bookmark,"Folder with one bookmark");
// }

void XbelReaderTest::test_read_xbel_icon() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<bookmark:icon name="www"/>)");

  fixture_test_xbel(xml_stream, affect_expected_icon, "<bookmark:icon name>");
}

void XbelReaderTest::test_read_xbel_title() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<title>bookmarktitle</title>)");

  fixture_test_xbel(xml_stream, affect_expected_title, "<title>");
}

void XbelReaderTest::test_read_xbel_metadata() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<metadata owner="http://freedesktop.org">
  <bookmark:icon name="bookmark_folder"/>
  </metadata>)");
  fixture_test_xbel(xml_stream, affect_expected_metdata, "<metadata>");
}

void XbelReaderTest::fixture_test_xbel(QXmlStreamReader& xml_stream,
                                       std::function<void(QStandardItem*)> expected_builder,
                                       const QString& message) {
  QStandardItem* parent=new QStandardItem();
  MockEnvironmentThemeFacade facade{};
  XbelReader xbel_reader{BookmarkSource::Konqueror, facade};
  xbel_reader.readXbelElement(xml_stream, parent);

  QStandardItem* expected= new QStandardItem();
  expected_builder(expected);
  qDebug()<<"children --- "<<expected->hasChildren();
  qDebug()<<"exped "<<expected;

  assert_equal(parent, expected, message);
}

QTEST_GUILESS_MAIN(XbelReaderTest)
#include "moc_xbel_reader_test.cpp"
