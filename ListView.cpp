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
#include <QPaintEvent>
#include <QTimer>
/*zone_namespace_begin*/

namespace {
/*此类型仅仅用于测试*/
namespace zone_data_private{
class TestWidget :
    public QWidget,
    public AbstractItemWidget{
    QString text_;
    std::uint32_t draw_index_=0;
public:
    TestWidget(QWidget *p):QWidget(p) { 
        //setAutoFillBackground(true);
    }

    void aboutToDelete() override { 
        setVisible(false); text_.clear();
    }

    virtual void paint(
        const QStyleOptionViewItem &option,
        const QModelIndex & index) override{
        if (isPaintOptionChanged(option,index)) {
            if (option.rect!=lastStyleOptionViewItem_.rect) {
                updateEditorGeometry(option,index);
            }
            else {
                auto var_draw_key=++draw_index_;
                QTimer::singleShot(5,this,[var_draw_key,this]() {
                    if (var_draw_key==draw_index_) { this->update(); }
                });
            }
            index_=index;
            lastStyleOptionViewItem_=option;
        }
    }

    virtual void setEditorData(const QModelIndex &index) override {
        index_=index;
        if (index.isValid()) {
            text_=index.data(Qt::DisplayRole).value<QString>();
        }
        else {text_="";}
        update();
    }

    virtual void setModelData(QAbstractItemModel * ,const QModelIndex &index) override {
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
        update();
    }

    virtual bool isPaintOptionChanged(
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override{
        if (index_!=index) { return true; }
        if (option.state!=lastStyleOptionViewItem_.state) { return true; }
        if (option.rect!=lastStyleOptionViewItem_.rect) { return true; }
        return false;
    }

    void renderToImage(QImage & argImage) {

        auto var_size=lastStyleOptionViewItem_.rect.size();
        
        QImage varImage(var_size,QImage::Format_RGBA8888);
        QPainter painter(&varImage);
        varImage.fill(QColor(0,0,0,0));

        painter.setRenderHint(QPainter::HighQualityAntialiasing);
        painter.setRenderHint(QPainter::TextAntialiasing);

        QColor brushColor=QColor(210,212,210);
        if (lastStyleOptionViewItem_.state&QStyle::State_MouseOver) {
            painter.setBrush(brushColor);
        }
        else {
            brushColor=QColor(127,127,127,127);
            painter.setBrush(brushColor);
        }

        constexpr const static double spaceing=0;
        if (lastStyleOptionViewItem_.state&QStyle::State_Selected) {
            painter.setPen(QPen(QColor(2,2,2,230),6));
            
            painter.drawRect(
                QRect(spaceing,spaceing,
                lastStyleOptionViewItem_.rect.width()-2*spaceing,
                lastStyleOptionViewItem_.rect.height()-2*spaceing));

        }
        else {
            painter.setPen(QPen(brushColor,0));
            painter.fillRect(
                QRect(spaceing,spaceing,
                lastStyleOptionViewItem_.rect.width()-2*spaceing,
                lastStyleOptionViewItem_.rect.height()-2*spaceing),
                brushColor);
        }

        painter.setPen(QPen(QColor(0,0,0),1));
        painter.setBrush(QColor(0,0,0));
        painter.drawText(10,20,text_);

        argImage=std::move(varImage);
    }

    virtual void paintEvent(QPaintEvent*)override {
        this->setGeometry(lastStyleOptionViewItem_.rect);
        QImage about_to_draw_;
        renderToImage(about_to_draw_);
        QPainter painter(this);
        painter.drawImage(0,0,about_to_draw_);
    }

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
        painter->fillRect(option.rect,QColor(0,0,0,0));
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
    auto var_rect_view_=arg_this->visibleRegion().boundingRect();
    auto &varAllItems=var_this_data->allOpenedItems;
    std::map<QModelIndex,zone_data::ListViewData::Item> var_in_view;
    for (auto & i:varAllItems) {
        auto var_this_rect_=arg_this->visualRect(i.first);
        if (var_this_rect_.intersects(var_rect_view_)) {
            var_in_view.insert(i);
        }
        else {
            i.second->aboutToDelete();
            arg_this->closePersistentEditor(i.first);
        }
    }
    varAllItems=std::move(var_in_view);
    //qDebug()<<"item in view"<<varAllItems.size();
}

/********************************zone_function********************************/
}

ListView::ListView()  {
    zone_private_function::construct(this);
    setSpacing(0);
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
    QListView::paintEvent(e);
    paintGC();
}

void ListView::setModel(QAbstractItemModel *arg_model){
    if(arg_model==QListView::model()){
        return;
    }
    setUpdatesEnabled(false);
    viewport()->setUpdatesEnabled(false);
    closeAllItem();
    QListView::setModel(arg_model);
    viewport()->setUpdatesEnabled(true);
    setUpdatesEnabled(true);
    viewport()->update();
    update();
}

/*zone_namespace_end*/


