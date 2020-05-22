#pragma once

#ifndef LIB_H
#define LIB_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
  
#define DHTTYPE    DHT11 

class DHTDATA
{
    public:
        byte MAC_NODE;
        float temperature, humidity;
        DHTDATA(){};
        DHTDATA(float temp, float humi){ this->temperature = temp; this->humidity = humi;};
};

class Data
{
    private:
        DHT_Unified* DHT;
        bool valid = false;
        sensors_event_t t_event;
        sensors_event_t h_event;
    public:
        int time(){ return 0;/*DHT->min_delay / 1000;*/}
        bool is_valid() { return this->valid; };
        Data(unsigned char DHTPIN);
        bool TakeData();
        DHTDATA getData();
        
};

Data::Data(unsigned char DHTPIN){
    this->DHT = new DHT_Unified(DHTPIN, DHTTYPE);
    DHT->begin();
}

DHTDATA Data::getData()
{
    DHTDATA data(t_event.temperature, h_event.relative_humidity);
    return data;
}

bool Data::TakeData()
{   
    
    DHT->temperature().getEvent(&t_event);
    DHT->humidity().getEvent(&h_event);
    
    if (!(isnan(t_event.temperature) || isnan(h_event.relative_humidity)))
    {
        this->valid = true;

    }else
    {
        this->valid = false;
    }
    return this->valid;
};

#endif