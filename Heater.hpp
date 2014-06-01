#ifndef HEATER_HPP
#define HEATER_HPP

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

Q_DECLARE_METATYPE(QSerialPortInfo)

class Heater : public QObject
{
    Q_OBJECT

public:
    Heater(QObject* parent = NULL);

    bool serialConnect(const QSerialPortInfo& port);
    void serialDisconnect();

    inline bool isConnected() const { return this->is_connected; }

signals:
    void heater_connected(const QSerialPort& port);
    void heater_disconnected();

    void serial_error(const QString& category, const QString& message);

private:
    QSerialPort serial;
    bool is_connected;

    bool setSerialSettings();
};

#endif // HEATER_HPP
