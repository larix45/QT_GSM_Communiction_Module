#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QWindow>
#include <QLabel>
#include <QCoreApplication>
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_toolButton_clicked();
    void data_change_from_settings(QSerialPortInfo port_data, QSerialPort::FlowControl flow_contol);

private:

    Ui::MainWindow *ui;
    QSerialPort *port;
    Settings *settingsWindow;





};
#endif // MAINWINDOW_H
