#ifndef ABSTRACTITEMWIDGET_HPP
#define ABSTRACTITEMWIDGET_HPP

#include <QtWidgets/QStyledItemDelegate>
#include <QtGui/qbrush.h>

class AbstractItemWidget {
protected:
    QStyleOptionViewItem lastStyleOptionViewItem_;
    QModelIndex index_;
    QColor backGroundColor_;
public:
    AbstractItemWidget() { backGroundColor_=QColor(0,0,0,0); };
    virtual ~AbstractItemWidget()=default;
    virtual void paint(const QStyleOptionViewItem &option,const QModelIndex &index)=0;
    virtual void setEditorData(const QModelIndex &index)=0;
    virtual void setModelData(QAbstractItemModel *model,const QModelIndex &index)=0;
    virtual QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index)=0;
    virtual void updateEditorGeometry(const QStyleOptionViewItem &option,const QModelIndex &index)=0;
    virtual bool isPaintOptionChanged(const QStyleOptionViewItem &,const QModelIndex &index)const=0;
    virtual void aboutToDelete()=0;
    virtual QRect geometry()const=0;
    QColor backgroundColor()const { return backGroundColor_; }
};

#endif // ABSTRACTITEMWIDGET_HPP

