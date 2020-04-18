#ifndef BOOKMARKSMODULE_TEST_HPP
#define BOOKMARKSMODULE_TEST_HPP
#include <QtTest/QTest>
#include <QtCore/QSharedPointer>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QDebug>
#include <bookmarkmodel.hpp>


typedef QPair<int,QStringList> TreeElement;
typedef QList<TreeElement> TwoDimensionTree ;    

QDebug operator<< (QDebug d, const TwoDimensionTree &tree) {
    for (const auto& row:tree)
    {
        d<<"\n";
        for(int i=0;i<row.first;++i)
        {
            d<<"  ";
        }
        d<<row.second.at(0)<<" "<<row.second.at(1);
    }
    return d;
}
QDebug operator<< (QDebug d, const TreeElement& treelement)
{
    d<<" index"<<treelement.first <<" content: "<<treelement.second;
    return d;
}
char *toString(const TreeElement& treelement)
{
    QString content,index;
    for (int i=0;i<treelement.second.size();++i)
    {
        content+=treelement.second.at(i)+" ";
    }
    index.setNum(treelement.first);
    return QTest::toString(QString("index: ")+ index +QString(" content: ")+content);
}



class bookmarksmodule_test: public QObject 
{
    Q_OBJECT
public:
    bookmarksmodule_test();
private Q_SLOTS:
    // will be called before the first testfunction is executed.
    void initTestCase();
    // will be called after the last testfunction was executed.
    void cleanupTestCase();
    // will be called before each testfunction is executed.
    void init();
    // will be called after every testfunction.
    void cleanup();
    
    void path_are_set_correctly();
    
    void scan_complete_hierarchy_of_konqueror_model_bookmark();
    void scan_complete_hierarchy_of_okular_model_bookmark();
    void scan_complete_hierarchy_of_okular_model_bookmark_when_folded();
    void scan_complete_hierarchy_of_chrome_bookmark_model();
    
    void filters_folder_and_items();
    void filters_folder_and_items_when_filtering_items_only();
    
    void model_is_not_filter_when_searchfield_is_empty();
    
private:   
    QSharedPointer<Bookmarkmodel> m_model{};
    TwoDimensionTree get_tree_of_data_model(QModelIndex parent, int col_start=0);
    
    void load_model_with_konqueror_bookmarks();
    void load_model_with_okular_bookmarks();
    
};

#endif // BOOKMARKSMODULE_TEST_HPP
