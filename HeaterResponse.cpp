#include "HeaterResponse.hpp"

///////////////////////////////////////////////////////////////////////////////
const HeaterResponse HeaterResponse::fromType(ResponseType t, double value)
{
    switch (t) {
        case Status:        return HeaterResponse("Status",                 "",     value, 1);
        case TempHeatsink:  return HeaterResponse("Heatsink Temperature",   "°C",   value, 2);
        case TempSens1:     return HeaterResponse("Sensor 1 Temperature",   "°C",   value, 2);
        case TempSens2:     return HeaterResponse("Sensor 2 Temperature",   "°C",   value, 2);
        case SetTemp:       return HeaterResponse("Target Temperature",     "°C",   value, 2);
        case Fan:           return HeaterResponse("Fan Speed",              "RPM",  value, 2);
        case Voltage:       return HeaterResponse("Voltage",                "V",    value, 2);
        case Current:       return HeaterResponse("Current",                "A",    value, 2);
        case None:          return HeaterResponse("None",                   "",     0, 0);
        //default:
            // TODO: throw Error
    }
}
///////////////////////////////////////////////////////////////////////////////
