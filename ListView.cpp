/*cpp*/
#undef MACRO_PROTECTED
#define MACRO_PROTECTED public
#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=_v_->data_
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=_v_->data_
#endif

#include "ListView.hpp"
#include "ListViewData.hpp"
#include "ListViewPrivateFunction.hpp"

/*zone_namespace_begin*/

namespace zone_data {
/********************************zone_data********************************/
ListView::ListView() {
    typedef std::shared_ptr<std::function<QWidget*(QWidget*,QModelIndex)>> _T_FunctionType;
    createWidgetFunction=_T_FunctionType(
                new std::function<QWidget*(QWidget*,QModelIndex)>(
                    [](QWidget*arg_p,QModelIndex){
                    QWidget * var_ans=new QWidget(arg_p);
                    var_ans->palette();
                    return var_ans;
                }));
}


ListView::~ListView() {
}

ListViewItemDeletegate::ListViewItemDeletegate(ListViewType * arg_super)
    :QStyledItemDelegate(arg_super){
    super=arg_super;
}

ListViewItemDeletegate::~ListViewItemDeletegate(){

}

/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/
void construct(ListView*arg_this){
    arg_this->data_=new zone_data::ListView;
    zone_this_data(arg_this);
    var_this_data->delegate=new zone_data::ListViewItemDeletegate(arg_this);
    arg_this->setItemDelegate(var_this_data->delegate);
}
void destruct(ListView*arg_this){
    delete arg_this->data_;
}
/********************************zone_function********************************/
}

ListView::ListView()  {
    zone_private_function::construct(this);
}


ListView::~ListView() {
    zone_private_function::destruct(this);
}

/*zone_namespace_end*/


