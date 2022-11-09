#include "../include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    //窗口标题以及图标
    w.setWindowIcon(QIcon(":/home/dong/Git-repos/network-labs/lab_1/WebServerV1/res/img/github.jpg"));
    w.setWindowTitle("Dong's Web Server");
    w.show();
    return a.exec();
}

