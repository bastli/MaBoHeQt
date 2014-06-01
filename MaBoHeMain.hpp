#ifndef MABOHEMAIN_HPP
#define MABOHEMAIN_HPP

#include <QMainWindow>
#include <QList>
#include <QMessageBox>
#include <QDebug>

#include "Heater.hpp"

namespace Ui {
class MaBoHeMain;
}

class MaBoHeMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit MaBoHeMain(QWidget *parent = 0);
    ~MaBoHeMain();

    void connectHeater(const QSerialPortInfo& port);


public slots:
    void scanForDevices();
    void connectButton();

    void heater_connected(const QSerialPort& port);
    void heater_disconnected();

    void serial_error(const QString& category, const QString& message);

    void update_heater_value(const HeaterResponse& value);

private:
    Ui::MaBoHeMain *ui;

    Heater heater;
};

#endif // MABOHEMAIN_HPP
