/*hpp*/
#if !defined(__PRIVATE__DATA__LISTVIEW_0___0x00)
#define __PRIVATE__DATA__LISTVIEW_0___0x00() 1

#include <QtWidgets/QStyledItemDelegate>
#include <functional>
#include <memory>
#include <map>
#include <list>
#include <QtWidgets/qwidget.h>
#include <QtCore/qpointer.h>
#include "AbstractItemWidget.hpp"

/*zone_namespace_begin*/
class ListView;
namespace zone_data {

class ListViewItemDeletegate :public QStyledItemDelegate {
    Q_OBJECT

private:
    typedef ListView ListViewType;
    ListViewType * super;
public:
    ListViewItemDeletegate(ListView *);
    ~ListViewItemDeletegate();


    virtual QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    virtual void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor,const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index) const override;

};

class ListViewData {
public:
    ListViewData();
    ~ListViewData();

    class Item {
        AbstractItemWidget * itemWidget_;
    public:
        Item(QWidget *);
        ~Item();

        AbstractItemWidget & operator*() { return *itemWidget_; }
        const AbstractItemWidget & operator*()const { return *itemWidget_; }

        AbstractItemWidget * operator->() { return itemWidget_; }
        const AbstractItemWidget * operator->()const { return itemWidget_; }

    };

    ListViewItemDeletegate * delegate=nullptr;
    std::shared_ptr<std::function<QWidget*(QWidget*,QModelIndex)>> createWidgetFunction;
    std::map<QModelIndex,Item> allOpenedItems;
    std::uint32_t paintGC_Count=0;

};

}

/*zone_namespace_end*/

#endif


