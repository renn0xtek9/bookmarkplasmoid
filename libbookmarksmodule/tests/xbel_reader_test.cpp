#include <libbookmarksmodule/data_types.h>
#include <libbookmarksmodule/xbel_reader.h>
#include <mocks.h>
#include <xbel_reader_test.h>

#include <QtCore/QXmlStreamReader>
#include <QtGui/QStandardItemModel>
#include <QtTest/QtTest>


void affect_expected_bookmark_item(QStandardItem* item)
{
  QStandardItem* bookmark=new QStandardItem();
  bookmark->setToolTip("http://www.url.com");
  bookmark->setData("bookmark 1", BookmarkRoles::Displayrole);
  bookmark->setData(false, BookmarkRoles::IsFolderRole);
  bookmark->setData("mocked_getCustomOrThemeIconPath", Qt::UserRole);
  bookmark->setData(int(BookmarkSource::Konqueror), BookmarkRoles::SourceRole);
  item->appendRow(bookmark);
}

void affect_expected_bookmark_item_two(QStandardItem* item)
{
  QStandardItem* bookmark=new QStandardItem();
  bookmark->setToolTip("http://www.url.com");
  bookmark->setData("bookmark 2", BookmarkRoles::Displayrole);
  bookmark->setData(false, BookmarkRoles::IsFolderRole);
  bookmark->setData("mocked_getCustomOrThemeIconPath", Qt::UserRole);
  bookmark->setData(int(BookmarkSource::Konqueror), BookmarkRoles::SourceRole);
  item->appendRow(bookmark);
}

void affect_expected_title(QStandardItem* item)
{
  item->setData("bookmark 1", Qt::DisplayRole);
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
  folder_item->setData("Folder One",Qt::DisplayRole);

  item->setChild(item->rowCount(),0,folder_item);
  QVERIFY(item->hasChildren());
  QVERIFY(!item->child(0)->hasChildren());
}

void affect_expected_folder_with_one_bookmark(QStandardItem* item)
{
  QStandardItem* folder_item=new QStandardItem();
  folder_item->setData(true, BookmarkRoles::IsFolderRole);
  folder_item->setData("Folder One",Qt::DisplayRole);

  item->setChild(item->rowCount(),0,folder_item);
  QVERIFY(item->hasChildren());
  QVERIFY(!item->child(0)->hasChildren());

  affect_expected_bookmark_item(folder_item);
  QVERIFY(item->child(0)->hasChildren());
}


void affect_expected_folder_with_two_bookmark(QStandardItem* item)
{
  QStandardItem* folder_item=new QStandardItem();
  folder_item->setData(true, BookmarkRoles::IsFolderRole);
  folder_item->setData("Folder One",Qt::DisplayRole);

  item->setChild(item->rowCount(),0,folder_item);
  QVERIFY(item->hasChildren());
  QVERIFY(!item->child(0)->hasChildren());

  affect_expected_bookmark_item(folder_item);
  QVERIFY(item->child(0)->hasChildren());
  affect_expected_bookmark_item_two(folder_item);
}

void affect_expected_second_empty_folder(QStandardItem* item)
{
  QStandardItem* folder_item2=new QStandardItem();
  folder_item2->setData(true, BookmarkRoles::IsFolderRole);
  folder_item2->setData("Folder Two",Qt::DisplayRole);

  item->setChild(item->rowCount(),0,folder_item2);
  QVERIFY(!item->child(1)->hasChildren());
}

void affect_expected_two_folder_side_by_side(QStandardItem* item)
{
  affect_expected_empty_folder(item);
  affect_expected_second_empty_folder(item);
}

void affect_expected_nested_folder(QStandardItem* item)
{
  QStandardItem* folder_item=new QStandardItem();
  folder_item->setData(true, BookmarkRoles::IsFolderRole);
  folder_item->setData("Folder One",Qt::DisplayRole);

  item->setChild(item->rowCount(),0,folder_item);
  QVERIFY(item->hasChildren());

  QStandardItem* folder_item2=new QStandardItem();
  folder_item2->setData(true, BookmarkRoles::IsFolderRole);
  folder_item2->setData("Folder Nested",Qt::DisplayRole);

  folder_item->setChild(folder_item->rowCount(),0,folder_item2);
  QVERIFY(item->child(0)->hasChildren());
}

void affect_expected_nested_folder_and_side_by_side(QStandardItem* item)
{
  affect_expected_nested_folder(item);
  affect_expected_second_empty_folder(item);
}

void XbelReaderTest::test_read_xbel_bookmark() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<bookmark href="http://www.url.com">
<title>bookmark 1</title>
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
   <title>Folder One</title>
  </folder>)");

  fixture_test_xbel(xml_stream, affect_expected_empty_folder, "Empty Folder");
}

void XbelReaderTest::test_folder_with_one_bookmark()
{
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<folder folded="no">
   <title>Folder One</title>
   <bookmark href="http://www.url.com">
<title>bookmark 1</title>
<info>
    <metadata owner="medata_owner">
      <bookmark:icon name ="icon name"/>
    </metadata>
</info>
</bookmark>
  </folder>)");
  fixture_test_xbel(xml_stream,affect_expected_folder_with_one_bookmark,"Folder with one bookmark");
}

void XbelReaderTest::test_folder_with_two_bookmark()
{
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<folder folded="no">
   <title>Folder One</title>
   <bookmark href="http://www.url.com">
<title>bookmark 1</title>
<info>
    <metadata owner="medata_owner">
      <bookmark:icon name ="icon name"/>
    </metadata>
</info>
</bookmark>
<bookmark href="http://www.url.com">
<title>bookmark 2</title>
<info>
    <metadata owner="medata_owner">
      <bookmark:icon name ="icon name"/>
    </metadata>
</info>
</bookmark>
  </folder>)");
  fixture_test_xbel(xml_stream,affect_expected_folder_with_two_bookmark,"Folder with one bookmark");
}

void XbelReaderTest::test_read_xbel_icon() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<bookmark:icon name="www"/>)");

  fixture_test_xbel(xml_stream, affect_expected_icon, "<bookmark:icon name>");
}

void XbelReaderTest::test_read_xbel_title() {
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<title>bookmark 1</title>)");

  fixture_test_xbel(xml_stream, affect_expected_title, "<title>");
}

void XbelReaderTest::test_two_folder_side_by_side()
{
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<folder folded="no">
   <title>Folder One</title>
  </folder>
  <folder folded="no">
   <title>Folder Two</title>
  </folder>)");
  fixture_test_xbel(xml_stream,affect_expected_two_folder_side_by_side,"Two folder side by side");
}

void XbelReaderTest::test_nested_folder()
{
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<folder folded="no">
   <title>Folder One</title>
    <folder folded="no">
    <title>Folder Nested</title>
    </folder>
  </folder>)");
  fixture_test_xbel(xml_stream,affect_expected_nested_folder,"Nested folder");
}

void XbelReaderTest::test_nested_folder_and_side_by_side()
{
  QXmlStreamReader xml_stream;
  xml_stream.addData(R"(<folder folded="no">
   <title>Folder One</title>
    <folder folded="no">
    <title>Folder Nested</title>
    </folder>
  </folder>
  <folder folded="no">
   <title>Folder Two</title>
  </folder>)");
  fixture_test_xbel(xml_stream,affect_expected_nested_folder_and_side_by_side,"Nested folder and side by side");
}

void XbelReaderTest::fixture_test_xbel(QXmlStreamReader& xml_stream,
                                       std::function<void(QStandardItem*)> expected_builder,
                                       const QString& message) {
  QStandardItem* parent=new QStandardItem();
  MockEnvironmentThemeFacade facade{};
  XbelReader xbel_reader{BookmarkSource::Konqueror, facade};
  xbel_reader.read(xml_stream, parent);

  QStandardItem* expected= new QStandardItem();
  expected_builder(expected);

  assert_equal(parent, expected, message);
}

QTEST_GUILESS_MAIN(XbelReaderTest)
#include "moc_xbel_reader_test.cpp"
