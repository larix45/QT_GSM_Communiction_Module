#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
signals:
    void send_data(QSerialPortInfo data, QSerialPort::FlowControl flow_contol);
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Settings *ui;

};

#endif // SETTINGS_H
