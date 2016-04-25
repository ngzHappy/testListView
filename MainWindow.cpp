#include "MainWindow.hpp"
#include "CentralWidget.hpp"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    this->setCentralWidget(new CentralWidget);
    this->resize(600,768);
}

MainWindow::~MainWindow(){

}
