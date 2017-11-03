/*
  2017-07-31 jjh
  VitconMQTTComm.cpp

  VitconMQTTComm.h 주석 참조
*/
#include "VitconMQTTComm.h"
#include "Arduino.h"

using namespace vitcon;

MQTTComm::MQTTComm(HardwareSerial *serial, MQTTItem **items, int itemcount)
{
  mSerial = serial;
  mItems = items;
  mItemCount = itemcount;
  mInterval = 500;
}

void MQTTComm::Init()
{
  mSerial->begin(250000);
  mSerial->setTimeout(100);
}

void MQTTComm::Run()
{
  SendData();
  int c;
  if ( ( c = mSerial->read()) != -1)  ReceiveData(c);
}

void MQTTComm::SendData()
{
  unsigned long curr = millis();

  if (curr - mTimer >= mInterval)
  {
    String str = "";
    uint16_t len = 0;

    for (int i = 0; i < mItemCount; i++)
    {
      const char* topic = mItems[i]->GetTopic();
      const char* data = mItems[i]->GetData();

      if(strlen(data) == 0 ) continue;

	  len += strlen(topic);
	  len ++;
	  len += strlen(data);
	  if ( i + 1 < mItemCount ) len++;
    }

    mSerial->write(STX);
	mSerial->write((byte*)&len, sizeof(uint16_t));

	for (int i = 0; i < mItemCount; i++)
    {
      const char* topic = mItems[i]->GetTopic();
      const char* data = mItems[i]->GetData();

      if(strlen(data) == 0 ) continue;

	  mSerial->print(topic);
	  mSerial->write((char)DATASEP);
	  mSerial->print(data);

	  if ( i + 1 < mItemCount )	  mSerial->write((char)TOPICSEP);
	  
    }

    mSerial->write(ETX);

    mTimer = curr;
  }
}

void MQTTComm::ReceiveData(int c)
{
  if (c == STX)
  {
    uint16_t len;
    mSerial->readBytes((byte*)&len, 2);
    
    char input[len + 1];
    byte n = mSerial->readBytes(input, len);
    input[n] = 0;

    byte etx;
    mSerial->readBytes(&etx, 1);

    

    if ( len != n ) return;
    if(  etx != ETX ) return;    
    char* separator = strchr(input, DATASEP);
    if ( separator != 0)
    {
      *separator = 0;
      const char* topic = input;
      ++separator;
      const char* data = separator;
      callback(topic, data);
    }
  }
}

void MQTTComm::SetInterval(unsigned long ms)
{
  if (ms < 200)
    mInterval = 200;
  else
    mInterval = ms;
}

void MQTTComm::SetSubscribe(void (* func)(const char* topic, const char* data))
{
  mFunc = func;
}

void MQTTComm::callback(const char* topic, const char* data)
{
  if (mFunc != 0) mFunc(topic, data);
}


