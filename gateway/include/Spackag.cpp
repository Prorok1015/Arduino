#pragma once

#ifndef SPACKAG_CPP
#define SPACKAG_CPP

//#include <dht11.h>
#include "MYDHT.h"

class Spackag
{
    public:
        Spackag(){};
        void Begin(int mac){ Serial.println("BEGIN_PACKAG");Serial.println("MAC");Serial.println(mac);};
        void End(){ Serial.println("END_PACKAG");};
        void PrintData(DHTDATA data);
        void PrintError(char* error) { Serial.println("ERROR"); Serial.println(error);}
        void PrintMACNODE(byte macnode){ Serial.println("MACNODE"); Serial.println(macnode);}
};

void Spackag::PrintData(DHTDATA data)
{
    Serial.println("TEMP");
    Serial.println(data.temperature);
    Serial.println("HUM");
    Serial.println(data.humidity);

}

#endif