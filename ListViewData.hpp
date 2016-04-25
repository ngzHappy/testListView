/*hpp*/
#if !defined(__PRIVATE__DATA__LISTVIEW_0___0x00)
#define __PRIVATE__DATA__LISTVIEW_0___0x00() 1

#include <QtWidgets/QStyledItemDelegate>
#include <functional>
#include <memory>

/*zone_namespace_begin*/
class ListView;
namespace zone_data{

typedef ::ListView ListViewType;
class ListViewItemDeletegate:public QStyledItemDelegate{
    Q_OBJECT
    ListViewType * super;
public:
    ListViewItemDeletegate(ListViewType *);
    ~ListViewItemDeletegate();
};

class ListView  {
public:
    ListView();
    ~ListView();

    ListViewItemDeletegate * delegate=nullptr;
    std::shared_ptr<std::function<QWidget*(QWidget*,QModelIndex)>> createWidgetFunction;
};

}

/*zone_namespace_end*/

#endif


