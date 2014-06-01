#include "Heater.hpp"

///////////////////////////////////////////////////////////////////////////////
Heater::Heater(QObject* parent)
 : QObject(parent), is_connected(false)
{
}
///////////////////////////////////////////////////////////////////////////////
bool Heater::serialConnect(const QSerialPortInfo& port)
{
    if (this->isConnected())
        return false;

    serial.setPort(port);

    if (!serial.open(QIODevice::ReadWrite)) {
        emit serial_error(tr("connecting"), serial.errorString());
        return false;
    }

    if (!setSerialSettings()) {
        emit serial_error(tr("connecting"), serial.errorString());
        return false;
    }

    is_connected = true;
    emit heater_connected(serial);

    qDebug() << "heater connected to" << serial.portName();

    return true;
}
///////////////////////////////////////////////////////////////////////////////
bool Heater::setSerialSettings()
{
    return serial.setBaudRate(115200)
        && serial.setDataBits(QSerialPort::Data8)
        && serial.setParity(QSerialPort::NoParity)
        && serial.setStopBits(QSerialPort::OneStop)
        && serial.setFlowControl(QSerialPort::NoFlowControl);
}
///////////////////////////////////////////////////////////////////////////////
void Heater::serialDisconnect()
{
    if (this->isConnected()) {
        serial.close();
        is_connected = false;

        emit heater_disconnected();

        qDebug() << "heater disconnected";
    }
}
///////////////////////////////////////////////////////////////////////////////
