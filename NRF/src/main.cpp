#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include "RF24.h"
#include "MYDHT.h"
#include "Spackag.cpp"

#define DHTPIN 7 //определяем пин по которому будем считывать данные с датчика 
RF24 radio(9,10);//создаем объект радиомодуля
Data dht(DHTPIN);//создаем объект датчика температуры и влажности
byte MAC = 4;    //устанавливаем уникальный мак адресс устройства
byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"};// номера труб
void setup(){
  Serial.begin(9600);           //открываем порт для связи с ПК
  radio.begin();                //активировать модуль
  radio.setAutoAck(1);          //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0,15);       //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();     //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах
  radio.openWritingPipe(address[0]);    //отправляем по трубе 0, открываем канал для передачи данных
  radio.setChannel(0x60);               //выбираем канал (в котором нет шумов)
  radio.setPALevel (RF24_PA_MAX);       //уровень мощности передатчика. 
  radio.setDataRate (RF24_1MBPS);       //скорость обмена. 
  radio.powerUp();                      //начать работу
  radio.stopListening();                //не слушаем радиоэфир, мы передатчик
}

void loop(void) 
{
  if (dht.TakeData())                     // пробуем взять данные с датчика 
  {
    DHTDATA data = dht.getData();         // выгружаем данные в объект DHTDATA
    data.MAC_NODE = MAC;                  // записываем уникальный адрес узла*/
    radio.write(&data,sizeof(DHTDATA));  // отправляем данные на шлюз
  }
  delay(4000);// ждем время
}