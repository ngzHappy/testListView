#include "MainWindow.hpp"
#include "CentralWidget.hpp"
#include <QtWidgets/QApplication>
#include <QtWidgets/qgraphicsview.h>
#include <QtWidgets/qgraphicsscene.h>
int main(int argc,char *argv[]) {
    QApplication app(argc,argv);

    /*Test 0*/
    MainWindow *window=new MainWindow;
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();

    /*Test 1*/
    QGraphicsView * view=new QGraphicsView;
    view->setScene(new QGraphicsScene(view));
    view->setAttribute(Qt::WA_DeleteOnClose);
    view->resize(500,600);
    view->scene()->addWidget(new CentralWidget);
    view->setFrameShape(QFrame::NoFrame);
    view->show();


    return app.exec();
}
