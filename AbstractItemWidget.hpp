#ifndef ABSTRACTITEMWIDGET_HPP
#define ABSTRACTITEMWIDGET_HPP

#include <QtWidgets/QStyledItemDelegate>

class AbstractItemWidget {
protected:
    QStyleOptionViewItem lastStyleOptionViewItem_;
    QModelIndex index_;
public:
    AbstractItemWidget()=default;
    virtual ~AbstractItemWidget()=default;
    virtual void paint(const QStyleOptionViewItem &option,const QModelIndex &index)=0;
    virtual void setEditorData(const QModelIndex &index)=0;
    virtual void setModelData(QAbstractItemModel *model,const QModelIndex &index)=0;
    virtual QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index)=0;
    virtual void updateEditorGeometry(const QStyleOptionViewItem &option,const QModelIndex &index)=0;
    virtual bool isPaintOptionChanged(const QStyleOptionViewItem &,const QModelIndex &index)const=0;
    virtual QRect getRect()const=0;
};

#endif // ABSTRACTITEMWIDGET_HPP

