/*hpp*/
#if !defined(__LISTVIEW_0___HPP_0x00_)
#define __LISTVIEW_0___HPP_0x00_() 1

#include <QtWidgets/QListView>
#include <functional>
#include <memory>

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#if !defined(macro_no_copy)
#define macro_no_copy(_t_class_name_) public:_t_class_name_(const _t_class_name_ &)=delete; \
_t_class_name_(_t_class_name_ &&)=delete; \
_t_class_name_&operator=(const _t_class_name_ &)=delete; \
_t_class_name_&operator=(_t_class_name_ &&)=delete
#endif

/*zone_namespace_begin*/

namespace zone_data {
class ListViewData;
}

class ListView :public QListView {
    Q_OBJECT
    macro_no_copy(ListView);
MACRO_PROTECTED:
    zone_data::ListViewData * data_=nullptr;
public:
    typedef std::shared_ptr<std::function<QWidget*(QWidget*,QModelIndex)>> CreateFunction;
public:

    ListView(QWidget * /*parent*/=nullptr);
    ~ListView();
public:

    void setCreateFunction(const CreateFunction& /*createFunction*/);
    void setCreateFunction(CreateFunction&& /*createFunction*/);
    const CreateFunction & getCreateFunction() const;
    const CreateFunction & createFunction() const { return getCreateFunction(); }

    void closeAllItem();
    void setModel(QAbstractItemModel *model)override;

private:
    template<typename _t_CREATEFUNCTION_t__>
    void _p_setCreateFunction(_t_CREATEFUNCTION_t__ && /*createFunction*/);
protected:
    void paintGC();
    void paintEvent(QPaintEvent*)override;

};

/*zone_namespace_end*/

#endif


