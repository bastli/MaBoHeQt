#ifndef HEATERCOMMAND_HPP
#define HEATERCOMMAND_HPP

#include <QByteArray>

typedef unsigned char byte;

struct HeaterCommand
{
private:
    HeaterCommand(byte command, unsigned int response_length);

public:
    inline static const HeaterCommand CMD_getStatus()         { return HeaterCommand(0x00, 1); }
    inline static const HeaterCommand CMD_MagicByte()         { return HeaterCommand(0x01, 1); }
    inline static const HeaterCommand CMD_getTempHeatsink()   { return HeaterCommand(0x02, 2); }
    inline static const HeaterCommand CMD_getTempSens1()      { return HeaterCommand(0x03, 2); }
    inline static const HeaterCommand CMD_getTempSens2()      { return HeaterCommand(0x04, 2); }
    // TODO: fill in rest

    byte command_byte;
    byte parameter[2];

    int response_length;

    QByteArray getSerial();

    static HeaterCommand parseResponse(const QByteArray& data);
};

#endif // HEATERCOMMAND_HPP
