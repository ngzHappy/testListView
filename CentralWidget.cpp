#include "CentralWidget.hpp"
#include "ListView.hpp"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtCore/QStringListModel>

CentralWidget::CentralWidget(){
    QHBoxLayout * var_button_layout=new QHBoxLayout;
    QVBoxLayout * var_this_layout=new QVBoxLayout;
    this->setLayout(var_this_layout);
    var_this_layout->addLayout(var_button_layout);
    var_button_layout->addWidget(new QPushButton);
    var_button_layout->addWidget(new QPushButton);
    ListView * var_list_view=new ListView;
    var_this_layout->addWidget(var_list_view);
    var_list_view->setModel(new QStringListModel({"1","2","3",
                                                 "1","2","3",
                                                 "1","2","3",
                                                 "1","2","3",
                                                 "1","2","3",
                                                 "1","2","3",
                                                 "1","2","3",
                                                 "1","2","3",}));
    var_list_view->setSelectionMode(
        QAbstractItemView::SelectionMode::ExtendedSelection);
}

CentralWidget::~CentralWidget(){

}

