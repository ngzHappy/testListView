/*hpp*/
#if !defined(__LISTVIEW_0___HPP_0x00_)
#define __LISTVIEW_0___HPP_0x00_() 1

#include <QtWidgets/QListView>
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

namespace zone_data{
class ListView;
}

class ListView :public QListView{
    Q_OBJECT
    macro_no_copy(ListView);
MACRO_PROTECTED:
    zone_data::ListView * data_=nullptr;
public:

    ListView();
    ~ListView();

};

/*zone_namespace_end*/

#endif


