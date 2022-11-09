#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include "../include/http_server.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->server = new http_server();
    update_text();
    // 输出
    QTextBrowser * output = this->findChild<QTextBrowser *>(QString("output"));
    server->output = output;
    QPushButton * run_button = this->findChild<QPushButton *>(QString("run"));
    QPushButton * stop_button = this->findChild<QPushButton *>(QString("stop"));
    QPushButton * restart_button = this->findChild<QPushButton *>(QString("reset"));
    connect(run_button, &QPushButton::clicked, this, &MainWindow::start_wraper);
    connect(stop_button, &QPushButton::clicked, this, &MainWindow::stop_wrapper);
    connect(restart_button, &QPushButton::clicked, this, &MainWindow::restart_wrapper);
    stop_button->setEnabled(false);
    restart_button->setEnabled(false);
}

void MainWindow::start_wraper() {
    update_text();
    QPushButton * run_button = this->findChild<QPushButton *>(QString("run"));
    QPushButton * stop_button = this->findChild<QPushButton *>(QString("stop"));
    QPushButton * restart_button = this->findChild<QPushButton *>(QString("reset"));
    restart_button->setEnabled(true);
    run_button->setEnabled(false);
    stop_button->setEnabled(true);
    QTextBrowser * output = this->findChild<QTextBrowser *>(QString("output"));
    server->moveToThread(&workerThread);
    server->start();
    connect(server, SIGNAL(print_message(QString)), output, SLOT(setText(QString)));
    server->print("* Server Started\n");
}

void MainWindow::stop_wrapper() {
    QPushButton * run_button = this->findChild<QPushButton *>(QString("run"));
    QPushButton * stop_button = this->findChild<QPushButton *>(QString("stop"));
    run_button->setEnabled(true);
    stop_button->setEnabled(false);
    server->stop();
    server->quit();
//    workerThread.quit();
}

void MainWindow::restart_wrapper() {
    string ip = string(this->findChild<QTextEdit *>(QString("ip"))->toPlainText().toUtf8().constData());
    string port = string(this->findChild<QTextEdit *>(QString("port"))->toPlainText().toUtf8().constData());
    string path = string(this->findChild<QTextEdit *>(QString("path"))->toPlainText().toUtf8().constData());
    string thread_limit = string(this->findChild<QTextEdit *>(QString("thread_limit"))->toPlainText().toUtf8().constData());
    cout << "结果为" << ip << port << path << endl;
    if (!check_ip(ip)) {
        this->server->print("New Ip is illigal\n");
        return;
    }
    if (!check_path(path)) {
        this->server->print("New base path is illigal\n");
        return;
    }
    if (!check_port(port)) {
        this->server->print("New port is illigal\n");
        return;
    }
    if (!check_thread_limit(thread_limit)) {
        this->server->print("New thread limit is not in range 1-30");
    }
    server->set_all(ip, path, port, thread_limit);
    stop_wrapper();
    start_wraper();
    update_text();

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::update_text() {
    QTextEdit * ip = this->findChild<QTextEdit *>(QString("ip"));
    QTextEdit * port = this->findChild<QTextEdit *>(QString("port"));
    QTextEdit * path = this->findChild<QTextEdit *>(QString("path"));
    QTextEdit * thread_limit = this->findChild<QTextEdit *>(QString("thread_limit"));
    ip->setText(QString::fromStdString(server->get_ip_to_listen()));
    port->setText(QString::fromStdString(to_string(server->get_port())));
    path->setText(QString::fromStdString(server->get_base_path()));
    thread_limit->setText(QString::fromStdString(to_string(server->get_max_thread_num())));
}

