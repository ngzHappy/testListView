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
    var_this_layout->setSpacing(0);
    auto var_button_0=new QPushButton;
    var_button_0->setMinimumHeight(32);
    var_button_layout->addWidget(var_button_0);
    auto var_button_1=new QPushButton;
    var_button_layout->addWidget(var_button_1);
    var_button_1->setMinimumHeight(32);
    ListView * var_list_view=new ListView;
    var_this_layout->addWidget(var_list_view);
    auto string_model=new QStringListModel({ "1","2","3",
        "11","12","13",
        "221","222","223",
        "3331","3332","3333",
        "44441","44442","44443",
        "555551","555552","555553",
        "6666661","6666662","6666663",
        "77777771","77777772","77777773", });
    var_list_view->setModel(string_model);
    var_list_view->setSelectionMode(
        QAbstractItemView::SelectionMode::ExtendedSelection);
    this->resize(600,700);
    setAutoFillBackground(true);
}

CentralWidget::~CentralWidget(){

}

