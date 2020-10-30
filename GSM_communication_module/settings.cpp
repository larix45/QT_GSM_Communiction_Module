#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    for(auto i = 0; i < QSerialPortInfo::availablePorts().length(); i++)
        ui->comboBox->addItem(QSerialPortInfo::availablePorts().at(0).portName(),i);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_buttonBox_accepted()
{
    QSerialPort::FlowControl active_flow_contol;
    switch(ui->comboBox_2->currentIndex())
    {
    case 0:
        active_flow_contol = QSerialPort::FlowControl::NoFlowControl;
        qDebug() << "no flow control";
        break;
    case 1:
        active_flow_contol = QSerialPort::FlowControl::HardwareControl;
        qDebug() << "hw control";
        break;
    case 2:
        active_flow_contol = QSerialPort::FlowControl::SoftwareControl;
        qDebug() << "sw contol";
        break;
    }


    emit send_data(QSerialPortInfo::availablePorts().at(ui->comboBox->currentIndex()), active_flow_contol);
}

void Settings::on_buttonBox_rejected()
{
    this->hide();
}

void Settings::on_comboBox_currentIndexChanged(int index)
{
    ui->textBrowser->setText("Port name:" + QSerialPortInfo::availablePorts().at(index).portName() + "\nDescription:" + QSerialPortInfo::availablePorts().at(index).description() + "\nManufacturer:" + QSerialPortInfo::availablePorts().at(index).manufacturer() +"\nProduct ID:" + QSerialPortInfo::availablePorts().at(index).productIdentifier());
}
