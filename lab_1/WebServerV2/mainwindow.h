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
#include "server.h"
#include "utils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    HttpServer * server = nullptr;
    QThread workerThread;
    void StartWraper();
    void StopWrapper();
    void RestartWrapper();
    void UpdateText();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
