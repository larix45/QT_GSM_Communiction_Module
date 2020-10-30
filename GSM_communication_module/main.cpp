#include "mainwindow.h"

#include <QApplication>
#include <QSerialPort>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if(QCoreApplication::arguments().length() < 2)
    {
        w.show();
        return a.exec();
    }
    else
    {

        QSerialPort port;
        port.setPort(QSerialPortInfo::availablePorts().at(0));
        if(port.open(QIODevice::ReadWrite))
            qDebug() << "Device opened";
        else
            qDebug() << "Error opening device. Maybe you do not have acces to it.";



        char *buffer = new char[ QCoreApplication::arguments().at(1).length()];
        for(auto i = 0; i <  QCoreApplication::arguments().at(1).length(); i++)
            buffer[i] =   QCoreApplication::arguments().at(1).at(i).toLatin1();
        buffer[ QCoreApplication::arguments().at(1).length()] = '\r';
        buffer[ QCoreApplication::arguments().at(1).length()+1] = '\0'; //FOR QDEBUG OUTPUT ONLY
        port.write(buffer,  QCoreApplication::arguments().at(1).length()+1);
        port.waitForBytesWritten(600);
        port.waitForReadyRead(1000);

        const QByteArray data = port.readAll();
        qDebug() << "Q: " << buffer;
        qDebug() << "ANS: " << data;


        port.close();
    }
    return 0;
}
