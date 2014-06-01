#ifndef HEATERRESPONSE_HPP
#define HEATERRESPONSE_HPP

#include <QDateTime>

struct HeaterResponse
{
private:
    HeaterResponse(const QString& name, const QString& unit, double value, QDateTime time, int length)
     : name(name), unit(unit), value(value), time(time), length(length) {}

    HeaterResponse(const QString& name, const QString& unit, double value, int length)
     : name(name), unit(unit), value(value), time(QDateTime::currentDateTime()), length(length) {}

public:
    QString name, unit;

    enum ResponseType {
        Status,
        MagicByte,
        TempHeatsink,
        TempSens1,
        TempSens2,
        SetTemp,
        Fan,
        Voltage,
        Current,
        None,
    } type;

    double value;
    QDateTime time;

    int length;

    static const HeaterResponse fromType(ResponseType t, double value);
};

#endif // HEATERRESPONSE_HPP
