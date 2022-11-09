#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <mutex>
#include <string>

#include "Request.h"
#include "utils.h"
#include "Fs.h"
#include "my_thread.h"
#include "http_server.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    http_server * server = nullptr;
    QThread workerThread;
    void start_wraper();
    void stop_wrapper();
    void restart_wrapper();
    void update_text();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
