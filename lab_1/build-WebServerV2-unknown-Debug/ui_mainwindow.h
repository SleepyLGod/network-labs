/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextBrowser *output;
    QLabel *label;
    QTextEdit *ip;
    QLabel *ip_label;
    QLabel *port_label;
    QLabel *base_path_label;
    QTextEdit *port;
    QTextEdit *path;
    QPushButton *run;
    QPushButton *stop;
    QPushButton *reset;
    QTextEdit *thread_limit;
    QLabel *thread_limit_logo;
    QLabel *label_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(807, 606);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        output = new QTextBrowser(centralwidget);
        output->setObjectName(QStringLiteral("output"));
        output->setGeometry(QRect(60, 100, 701, 211));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(390, 70, 31, 18));
        label->setAlignment(Qt::AlignCenter);
        ip = new QTextEdit(centralwidget);
        ip->setObjectName(QStringLiteral("ip"));
        ip->setGeometry(QRect(250, 350, 321, 21));
        ip_label = new QLabel(centralwidget);
        ip_label->setObjectName(QStringLiteral("ip_label"));
        ip_label->setGeometry(QRect(200, 350, 31, 18));
        ip_label->setAlignment(Qt::AlignCenter);
        port_label = new QLabel(centralwidget);
        port_label->setObjectName(QStringLiteral("port_label"));
        port_label->setGeometry(QRect(200, 400, 31, 18));
        port_label->setAlignment(Qt::AlignCenter);
        base_path_label = new QLabel(centralwidget);
        base_path_label->setObjectName(QStringLiteral("base_path_label"));
        base_path_label->setGeometry(QRect(160, 450, 81, 18));
        base_path_label->setAlignment(Qt::AlignCenter);
        port = new QTextEdit(centralwidget);
        port->setObjectName(QStringLiteral("port"));
        port->setGeometry(QRect(250, 400, 321, 21));
        path = new QTextEdit(centralwidget);
        path->setObjectName(QStringLiteral("path"));
        path->setGeometry(QRect(250, 450, 321, 21));
        run = new QPushButton(centralwidget);
        run->setObjectName(QStringLiteral("run"));
        run->setGeometry(QRect(230, 540, 96, 34));
        run->setStyleSheet(QStringLiteral("background-color: rgb(170, 0, 255);"));
        run->setFlat(false);
        stop = new QPushButton(centralwidget);
        stop->setObjectName(QStringLiteral("stop"));
        stop->setGeometry(QRect(360, 540, 96, 34));
        reset = new QPushButton(centralwidget);
        reset->setObjectName(QStringLiteral("reset"));
        reset->setGeometry(QRect(490, 540, 96, 34));
        thread_limit = new QTextEdit(centralwidget);
        thread_limit->setObjectName(QStringLiteral("thread_limit"));
        thread_limit->setGeometry(QRect(250, 500, 261, 21));
        thread_limit_logo = new QLabel(centralwidget);
        thread_limit_logo->setObjectName(QStringLiteral("thread_limit_logo"));
        thread_limit_logo->setGeometry(QRect(150, 500, 81, 18));
        thread_limit_logo->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(530, 500, 58, 18));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Log", Q_NULLPTR));
        ip_label->setText(QApplication::translate("MainWindow", "ip", Q_NULLPTR));
        port_label->setText(QApplication::translate("MainWindow", "port", Q_NULLPTR));
        base_path_label->setText(QApplication::translate("MainWindow", "base path", Q_NULLPTR));
        run->setText(QApplication::translate("MainWindow", "Run", Q_NULLPTR));
        stop->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
        reset->setText(QApplication::translate("MainWindow", "Reset", Q_NULLPTR));
        thread_limit_logo->setText(QApplication::translate("MainWindow", "max threads", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "( 1 - 30 )", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
