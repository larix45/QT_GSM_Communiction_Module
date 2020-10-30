#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    port = new QSerialPort;
    const auto port_info = QSerialPortInfo::availablePorts();
    for(auto i = 0; i < port_info.length(); i++)
        qDebug() << port_info.at(i).portName();

    if(port_info.length() >= 1)
        port->setPort(port_info.at(0));
    else
        qDebug() << "No devices available";
    port->setReadBufferSize(64);


    settingsWindow = new Settings(this);
    QObject::connect(settingsWindow, &Settings::send_data, this, &MainWindow::data_change_from_settings);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString message = ui->textBrowser->toPlainText();
    if(port->open(QIODevice::ReadWrite))
        qDebug() << "Device opened";
    else
        qDebug() << "Error opening device. Maybe you do not have acces to it.";



    char *buffer = new char[ui->lineEdit->text().length()];
    for(auto i = 0; i < ui->lineEdit->text().length(); i++)
        buffer[i] =  ui->lineEdit->text().at(i).toLatin1();
    buffer[ui->lineEdit->text().length()] = '\r';
    buffer[ui->lineEdit->text().length()+1] = '\0'; //FOR QDEBUG OUTPUT ONLY
    //qDebug() << "BUFFER: " << buffer;
    port->write(buffer, ui->lineEdit->text().length()+1);
    port->waitForBytesWritten(300);
    port->waitForReadyRead(400);
    message += '\n';
    message += buffer;
    const QByteArray data = port->readAll();
    message += data;


    port->close();
  //  qDebug() << "Device closed!";
    message += '\n';

    ui->textBrowser->setText(message);
}
void MainWindow::data_change_from_settings(QSerialPortInfo port_data, QSerialPort::FlowControl flow_contol)
{
    port->setPort(port_data);
    port->setFlowControl(flow_contol);
}
void MainWindow::on_toolButton_clicked()
{
    qDebug() << QCoreApplication::arguments().at(1);
    settingsWindow->show();
}
