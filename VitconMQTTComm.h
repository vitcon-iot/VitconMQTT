/*
  2017-07-31 jjh
  VitconMQTTComm.h

  ESP-12S 모듈에 통신 데이터를 전송하는 모듈이다.

  2017-07-31 v1.0.0
*/

#ifndef _VITCONMQTTCOMM_H_
#define _VITCONMQTTCOMM_H_

#include "VitconMQTTitem.h"
#include "HardwareSerial.h"

#define STX 0x02
#define ETX 0x03

#define DATASEP 0xF0
#define TOPICSEP 0xF1

namespace vitcon
{
  class MQTTComm
  {
    public:
      MQTTComm(HardwareSerial *serial, MQTTItem **items, int itemcount);
  
      void Init();
      void Run();
  
      void SetInterval(unsigned long ms);
      void SetSubscribe(void (* func)(const char* topic, const char* data));
  
    private:
      HardwareSerial *mSerial;
  
      MQTTItem **mItems;
      int mItemCount;
  
      unsigned long mInterval;
      unsigned long mTimer;
  
      void (* mFunc)(const char* topic, const char* data);
  
      void SendData();
      void ReceiveData(int c);
      void callback(const char* topic, const char* data);
  };
}

#endif /* EOF */
