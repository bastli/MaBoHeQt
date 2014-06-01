#include "HeaterCommand.hpp"

///////////////////////////////////////////////////////////////////////////////
HeaterCommand::HeaterCommand(byte command, unsigned int response_length)
 : command_byte(command),
   response_length(response_length)
{
    memset(parameter, 0, sizeof(parameter));
}
///////////////////////////////////////////////////////////////////////////////
QByteArray HeaterCommand::getSerial()
{
    QByteArray data;

    data.append(0xFF); // start byte
    data.append(command_byte);
    data.append(parameter[0]);
    data.append(parameter[1]);

    return data;
}
///////////////////////////////////////////////////////////////////////////////
HeaterCommand HeaterCommand::parseResponse(const QByteArray& data)
{

}
///////////////////////////////////////////////////////////////////////////////
