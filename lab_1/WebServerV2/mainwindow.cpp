#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->server = new HttpServer();

    UpdateText();

    // 输出
    QTextBrowser * output = this->findChild<QTextBrowser *>(QString("output"));
    server->output = output;
    QPushButton * run_button = this->findChild<QPushButton *>(QString("run"));
    QPushButton * stop_button = this->findChild<QPushButton *>(QString("stop"));
    QPushButton * restart_button = this->findChild<QPushButton *>(QString("reset"));
    connect(run_button, &QPushButton::clicked, this, &MainWindow::StartWraper);
    connect(stop_button, &QPushButton::clicked, this, &MainWindow::StopWrapper);
    connect(restart_button, &QPushButton::clicked, this, &MainWindow::RestartWrapper);
    stop_button->setEnabled(false);
    restart_button->setEnabled(false);
}

void MainWindow::StartWraper() {
    UpdateText();
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
    server->Print("* Server Started\n");
}

void MainWindow::StopWrapper() {
    QPushButton * run_button = this->findChild<QPushButton *>(QString("run"));
    QPushButton * stop_button = this->findChild<QPushButton *>(QString("stop"));
    run_button->setEnabled(true);
    stop_button->setEnabled(false);
    server->Stop();
    server->quit();
//    workerThread.quit();
}

void MainWindow::RestartWrapper() {
    std::string ip = std::string(this->findChild<QTextEdit *>(QString("ip"))->toPlainText().toUtf8().constData());
    std::string port = std::string(this->findChild<QTextEdit *>(QString("port"))->toPlainText().toUtf8().constData());
    std::string path = std::string(this->findChild<QTextEdit *>(QString("path"))->toPlainText().toUtf8().constData());
    std::string thread_limit = std::string(this->findChild<QTextEdit *>(QString("thread_limit"))->toPlainText().toUtf8().constData());

    std::cout << "结果为" << ip << ":" << port << path << std::endl;
    if (!CheckIp(ip)) {
        this->server->Print("New Ip is illigal\n");
        return;
    } else {
        this->server->Print("New Ip is OK\n");
    }
    if (!CheckPath(path)) {
        this->server->Print("New base path is illigal\n");
        return;
    } else {
        this->server->Print("New base path is OK\n");
    }
    if (!CheckPort(port)) {
        this->server->Print("New port is illigal\n");
        return;
    } else {
        this->server->Print("New port is OK\n");
    }
    if (!CheckThreadLimit(thread_limit))
        this->server->Print("New thread limit is not in range 1-30");
    server->set_all(ip, path, port, thread_limit);
    StopWrapper();
    StartWraper();
    UpdateText();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::UpdateText() {
    QTextEdit * ip = this->findChild<QTextEdit *>(QString("ip"));
    QTextEdit * port = this->findChild<QTextEdit *>(QString("port"));
    QTextEdit * path = this->findChild<QTextEdit *>(QString("path"));
    QTextEdit * thread_limit = this->findChild<QTextEdit *>(QString("thread_limit"));
    ip->setText(QString::fromStdString(server->get_ip_to_listen()));
    port->setText(QString::fromStdString(std::to_string(server->get_port())));
    path->setText(QString::fromStdString(server->get_base_path()));
    thread_limit->setText(QString::fromStdString(std::to_string(server->get_max_thread_num())));
}

