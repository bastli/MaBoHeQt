#include "Heater.hpp"

///////////////////////////////////////////////////////////////////////////////
Heater::Heater(QObject* parent)
 : QObject(parent), is_connected(false)
{
    connect(&serial, SIGNAL(readyRead()), this, SLOT(readData()));
}
///////////////////////////////////////////////////////////////////////////////
Heater::~Heater()
{
    if (isConnected())
        serialDisconnect();

}
///////////////////////////////////////////////////////////////////////////////
bool Heater::serialConnect(const QSerialPortInfo& port, bool emit_errors)
{
    if (this->isConnected())
        return false;

    serial.setPort(port);

    if (!serial.open(QIODevice::ReadWrite)) {
        if (emit_errors)
            emit serial_error(tr("connecting"), serial.errorString());
        return false;
    }

    if (!setSerialSettings()) {
        if (emit_errors)
            emit serial_error(tr("connecting"), serial.errorString());
        return false;
    }

    // TODO: test connection here

    is_connected = true;
    connect(&serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
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
bool Heater::serialAutoconnect()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    foreach(const QSerialPortInfo port, ports) {
        if (this->serialConnect(port))
            return true;
    }

    emit serial_error(tr("autoconnecting"), tr("No MakerBot Heater found. Tried %1 devices.").arg(ports.count()));

    return false;
}
///////////////////////////////////////////////////////////////////////////////
void Heater::serialDisconnect()
{
    if (this->isConnected()) {
        serial.close();
        is_connected = false;

        disconnect(&serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
        emit heater_disconnected();

        qDebug() << "heater disconnected";
    }
}
///////////////////////////////////////////////////////////////////////////////
const HeaterResponse Heater::sendCommand(const HeaterCommand& cmd)
{
    serial.write(cmd.getSerial());
    QByteArray response = serial.read(cmd.response_length);
}
///////////////////////////////////////////////////////////////////////////////
void Heater::readData()
{
    received_data.append(serial.readAll());
}
///////////////////////////////////////////////////////////////////////////////
void Heater::handleError(QSerialPort::SerialPortError error)
{
    emit serial_error(tr("general serial error"), error.errorString());
}
///////////////////////////////////////////////////////////////////////////////
