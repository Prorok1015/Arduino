#include <Arduino.h>    // стандартная библиотека Ардуино
#include <SPI.h>        // библиотека для работы с SPI 
#include <nRF24L01.h>   // библиотека для работы с радиомодулем NRF24
#include "RF24.h"       // библиотека с настройками модуля NRF24
#include "MYDHT.h"        // собственная библиотека для более простой работы с температурным датчиком DHT11
#include "Spackag.cpp"  // собственая библиотека для отправки данных на компьютер

RF24 radio(9,10); // создание объекта радиомодуля
Spackag print;    // создание объекта для отправки данных на компьютер

int MAC = 1000;// уникальный номер шлюза
byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"};  //возможные номера труб

void setup(){
  Serial.begin(9600);           //открываем порт для связи с ПК
 radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0,15);     //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах

  radio.openReadingPipe(1,address[0]);      //хотим слушать трубу 0
  radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_1MBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!
  // ВНИМАНИЕ!!! enableAckPayload НЕ РАБОТАЕТ НА СКОРОСТИ 250 kbps!
  
  radio.powerUp(); //начать работу
  radio.startListening();  //начинаем слушать эфир, мы приёмный модуль
}

void loop(void) {
  DHTDATA data;     // создаем объект "данные"  
                    // и указывазываем что началась передача пакета данных на компьютер
  
  while ( radio.available())                      // слушаем эфир
  {
    print.Begin(MAC);                             // отправляем уникальный адрес шлюза                       
    radio.read( &data, sizeof(DHTDATA) );         // чиатем входящий сигнал
    print.PrintData(data);                        // отправляем данные
    print.PrintMACNODE(data.MAC_NODE);            // отправлем мак адрес узла отправившего данные
    print.End();                                  // отсылаем флаг конца пакета данных на компьютер    
  }          
}