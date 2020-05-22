#pragma once

#ifndef LIB_H
#define LIB_H

#include <dht11.h>
/*
class Packag
{
private:
    int MAC;
    unsigned char SIZE;
    int* data;
public:
    enum endsimbol { PACKAGEND, PACKAGENOTEND };
    Packag();
    byte SendMessage();
    Packag(int MAC, int* data, unsigned char SIZE, endsimbol ends);
    ~Packag();
};

Packag::Packag(){};

byte Packag::SendMessage()
{

    return 0;
}
Packag::Packag(int MAC, int* data, unsigned char SIZE, endsimbol ends)
{
    this->MAC = MAC;
    this->SIZE = SIZE;
    this->data = new int[SIZE];
    for (unsigned char i = 0; i <= SIZE; ++i) this->data[i] = data[i];
}
*/

class DHTDATA
{
    public:
        byte MAC_NODE;
        float temperature, humidity;
        DHTDATA(){};
        DHTDATA(int temp, int humi){ this->temperature = temp; this->humidity = humi;};
};

class Data
{
    private:
        dht11* DHT;
        unsigned char PIN;
        bool valid = false;
    public:
        bool is_valid() { return this->valid; };
        Data(unsigned char DHTPIN);
        bool TakeData();
        DHTDATA getData();
        
};

Data::Data(unsigned char DHTPIN){
    this->DHT = new dht11();
    this->PIN = DHTPIN;
}

DHTDATA Data::getData()
{
    DHTDATA dht(this->DHT->temperature, this->DHT->humidity);
    return dht;
}

bool Data::TakeData()
{   
    char result = this->DHT->read(this->PIN);

    if (DHTLIB_OK == result)
    {
        this->valid = true;

    }else if(DHTLIB_ERROR_CHECKSUM == result || DHTLIB_ERROR_TIMEOUT == result)
    {
        this->valid = false;
        
    }
    return this->valid;
};
#endif