/*cpp*/
#undef MACRO_PROTECTED
#define MACRO_PROTECTED public
#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=_v_->data_
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=_v_->data_
#endif

#include <cstddef>
#include <QtGui/QPalette>
#include <QtGui/QPainter>
#include "ListView.hpp"
#include "ListViewData.hpp"
#include "ListViewPrivateFunction.hpp"
#include "AbstractItemWidget.hpp"
#include <QtCore/qdebug.h>
#include <stdexcept>

/*zone_namespace_begin*/

namespace {
/*此类型仅仅用于测试*/
namespace zone_data_private{
class TestWidget :
    public QWidget,
    public AbstractItemWidget{
public:
    TestWidget(QWidget *p):QWidget(p) {}

    virtual void paint(
        const QStyleOptionViewItem &option,
        const QModelIndex & index) override{
        if (isPaintOptionChanged(option,index)) {
            this->update();
            index_=index;
            lastStyleOptionViewItem_=option;
        }
    }

    virtual void setEditorData(const QModelIndex &index) override { 
        index_=index; 
        update();
    }

    virtual void setModelData(QAbstractItemModel *,const QModelIndex &index) override { 
        index_=index; 
    }

    virtual QSize sizeHint(const QStyleOptionViewItem &,const QModelIndex &) override {
        return QSize(64,64);
    }

    virtual void updateEditorGeometry(
        const QStyleOptionViewItem &option,
        const QModelIndex &index) override{
        lastStyleOptionViewItem_=option;
        index_=index;
        this->setGeometry(option.rect);
    }

    virtual bool isPaintOptionChanged(
        const QStyleOptionViewItem &option,const QModelIndex &index) const override{
        if (index_!=index) { return true; }
        if (option.rect!=lastStyleOptionViewItem_.rect) {return true;}
        if (option.state!=lastStyleOptionViewItem_.state) { return true; }
        return false;
    }

    virtual void paintEvent(QPaintEvent*)override {
        QPainter painter(this);
        if (lastStyleOptionViewItem_.state&QStyle::State_MouseOver) {
            painter.setBrush(QColor(255,255,255,200));
        }
        else{
            painter.setBrush(QColor(
                60+(rand()&127),
                60+(rand()&127),
                60+(rand()&127),
                200));
        }

        if (lastStyleOptionViewItem_.state&QStyle::State_Selected) {
            painter.setPen(QPen(QColor(2,2,2,230),6));
        }
        else {
            painter.setPen(QPen(Qt::transparent,0));
        }

        painter.drawRect(rect());
    }

    QRect getRect() const override { return QWidget::geometry(); }
};

}
}

namespace zone_data {
/********************************zone_data********************************/
ListViewData::ListViewData() {
    typedef std::shared_ptr<std::function<QWidget*(QWidget*,QModelIndex)>> _T_FunctionType;
    createWidgetFunction=_T_FunctionType(
                new std::function<QWidget*(QWidget*,QModelIndex)>(
                    [](QWidget*arg_p,QModelIndex){
                    QWidget * var_ans=new zone_data_private::TestWidget(arg_p);
                    return var_ans;
                }));
}


ListViewData::~ListViewData() {
}

ListViewItemDeletegate::ListViewItemDeletegate(ListViewType * arg_super)
    :QStyledItemDelegate(arg_super){
    super=arg_super;
}

ListViewItemDeletegate::~ListViewItemDeletegate(){

}

QWidget *ListViewItemDeletegate::createEditor(
        QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const try{
    auto & var_create_function= super->createFunction();
    if(var_create_function&&(*var_create_function)){
        auto * varAns=(*var_create_function)(parent,index);
        zone_this_data(super);
        var_this_data->allOpenedItems.insert(
        {index,ListViewData::Item(varAns)});
        return varAns;
    }
    return QStyledItemDelegate::createEditor(parent,option,index);
}
catch (decltype(nullptr)) {
    qDebug()<<"???"<<__LINE__<<__FILE__<<__func__;
    throw std::logic_error("ListViewItemDeletegate::createEditor");
}

void ListViewItemDeletegate::paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const {
    zone_this_data(super);
    auto varPos=var_this_data->allOpenedItems.find(index);
    if (varPos!=var_this_data->allOpenedItems.end()) {
        return varPos->second->paint(option,index);
    }
    else {
        return super->openPersistentEditor(index);
    }
    return QStyledItemDelegate::paint(
        painter,option,index);
}

void ListViewItemDeletegate::setEditorData(
        QWidget *editor,
        const QModelIndex &index) const {
    zone_this_data(super);
    auto varPos=var_this_data->allOpenedItems.find(index);
    if (varPos!=var_this_data->allOpenedItems.end()) {
        return varPos->second->setEditorData(index);
    }
    return QStyledItemDelegate::setEditorData(editor,index);
}

void ListViewItemDeletegate::setModelData(
        QWidget *editor,
        QAbstractItemModel *model,
        const QModelIndex &index) const {
    zone_this_data(super);
    auto varPos=var_this_data->allOpenedItems.find(index);
    if (varPos!=var_this_data->allOpenedItems.end()) {
        return varPos->second->setModelData(model,index);
    }
    return QStyledItemDelegate::setModelData(editor,model,index);
}

QSize ListViewItemDeletegate::sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const {
    zone_this_data(super);
    auto var_pos=var_this_data->allOpenedItems.find(index);
    if(var_pos!=var_this_data->allOpenedItems.end()){
        return var_pos->second->sizeHint(option,index);
    }
    return QSize(64,64);
}

void ListViewItemDeletegate::updateEditorGeometry(
        QWidget *editor,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const {
    auto * varItemWidget=dynamic_cast<AbstractItemWidget *>(editor);
    if (varItemWidget) {
        return varItemWidget->updateEditorGeometry(option,index);
    }
    return QStyledItemDelegate::updateEditorGeometry(
        editor,option,index);
}

ListViewData::Item::Item(QWidget *var_i) { 
    itemWidget_=dynamic_cast<AbstractItemWidget *>(var_i);
    if (nullptr==itemWidget_) { throw nullptr; }
}
ListViewData::Item::~Item() {}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/
void construct(ListView*arg_this){
    arg_this->data_=new zone_data::ListViewData;
    zone_this_data(arg_this);
    var_this_data->delegate=new zone_data::ListViewItemDeletegate(arg_this);
    arg_this->setItemDelegate(var_this_data->delegate);
}
void destruct(ListView*arg_this){
    delete arg_this->data_;
}

void close_all_item(ListView*arg_this) {
    zone_this_data(arg_this);
    auto &varAllItems=var_this_data->allOpenedItems;
    for (const auto & i:varAllItems) {
        arg_this->closePersistentEditor(i.first);
    }
    varAllItems.clear();
}

void paintGC(ListView*arg_this) {
    zone_this_data(arg_this);
    auto * varViewPort= arg_this->viewport();
    if (varViewPort==nullptr) { varViewPort=arg_this; }
    auto var_rect_view_=varViewPort->geometry();
    auto &varAllItems=var_this_data->allOpenedItems;
    std::map<QModelIndex,zone_data::ListViewData::Item> var_in_view;
    for (const auto & i:varAllItems) {
        auto var_this_rect_=i.second->getRect();
        if (var_this_rect_.intersects(var_rect_view_)) {
            var_in_view.insert(i);
        }
        else {
            arg_this->closePersistentEditor(i.first);
            //qDebug()<<"close"<<i.first;
        }
    }
    varAllItems=std::move(var_in_view);
    //qDebug()<<"all items size:"<<varAllItems.size();
}

/********************************zone_function********************************/
}

ListView::ListView()  {
    zone_private_function::construct(this);
}

ListView::~ListView() {
    zone_private_function::destruct(this);
}

const ListView::CreateFunction & ListView::getCreateFunction() const{
    zone_const_this_data(this);
    return var_this_data->createWidgetFunction;
}

template<typename _t_CREATEFUNCTION_t__>
void ListView::_p_setCreateFunction(_t_CREATEFUNCTION_t__ &&_createFunction_){
    zone_this_data(this);
    var_this_data->createWidgetFunction=std::forward<_t_CREATEFUNCTION_t__>(_createFunction_);
    closeAllItem();
}

void ListView::setCreateFunction(const CreateFunction&_createFunction_){
    _p_setCreateFunction(_createFunction_);
}

void ListView::setCreateFunction(CreateFunction&&_createFunction_){
    _p_setCreateFunction(std::move(_createFunction_));
}

void ListView::closeAllItem(){
    zone_private_function::close_all_item(this);
}

void ListView::paintGC() {
    zone_private_function::paintGC(this);
}

void ListView::paintEvent(QPaintEvent* e) {
    paintGC();
    QListView::paintEvent(e);
}

/*zone_namespace_end*/


