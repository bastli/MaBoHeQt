#ifndef HEATER_HPP
#define HEATER_HPP

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>
#include <QDebug>

#include "HeaterCommand.hpp"
#include "HeaterResponse.hpp"

Q_DECLARE_METATYPE(QSerialPortInfo)

class Heater : public QObject
{
    Q_OBJECT

public:
    Heater(QObject* parent = NULL);
    ~Heater();

    bool serialConnect(const QSerialPortInfo& port, bool emit_errors = true);
    bool serialAutoconnect();
    void serialDisconnect();

    inline bool isConnected() const { return this->is_connected; }

    const HeaterResponse sendCommand(const HeaterCommand& cmd);

signals:
    void heater_connected(const QSerialPort& port);
    void heater_disconnected();

    void serial_error(const QString& category, const QString& message);

    void heater_got_value(const HeaterResponse& value);

private slots:
    void readData();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort serial;
    bool is_connected;

    QByteArray received_data;

    bool setSerialSettings();
};

#endif // HEATER_HPP
