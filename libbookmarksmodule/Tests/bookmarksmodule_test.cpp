#include <QtCore/QSharedPointer>
#include <bookmarkmodel.hpp>
#include <bookmarksmodule_test.h>
bookmarksmodule_test::bookmarksmodule_test(): QObject()
{
    
}
void bookmarksmodule_test::init()
{
//     m_model=QSharedPointer<Bookmarkmodel>(new Bookmarkmodel());
    Bookmarkmodel m_model;
    m_model.setPathForChromeBookamarks("fucl");
    // will be called before each testfunction is executed.
}
void bookmarksmodule_test::initTestCase()
{
    // will be called before the first testfunction is executed.
}
void bookmarksmodule_test::cleanup()
{
    // will be called after every testfunction.
}
void bookmarksmodule_test::cleanupTestCase()
{
    // will be called after the last testfunction was executed.
}

void bookmarksmodule_test::can_create_a_bookmark_model()
{
    
    
    QVERIFY2(true==false,"First test");
    
}


QTEST_MAIN(bookmarksmodule_test)
#include "moc_bookmarksmodule_test.cpp"
