/*
  2017-07-31 jjh
  VitconMQTTItem.cpp

  VitconMQTTItem.h 주석 참조
*/

#include "VitconMQTTItem.h"
#include <stdlib.h>

using namespace vitcon;

MQTTItem::MQTTItem()
{
  MQTTItem("");
}

MQTTItem::MQTTItem(const char* topic)
{
  for (int i = 0; i < TOPICLEN; i++)
  {
    mTopic[i] = topic[i];
    if (topic[i] == '\0')
      break;
  }
}

void MQTTItem::Set(const char* data)
{
  for (int i = 0; i < DATALEN; i++)
  {
    mData[i] = data[i];
    if (data[i] == '\0')
      break;
  }
}

void MQTTItem::Set(int data)
{
  char buf[12];
  itoa(data, buf, 10);

  for (int i = 0; i < DATALEN; i++)
  {
    mData[i] = buf[i];
    if (buf[i] == '\0')
      break;
  }
}

void MQTTItem::Set(double data)
{
  char buf[10];
  dtostrf(data, 4, 2, buf);

  for (int i = 0; i < DATALEN; i++)
  {
    mData[i] = buf[i];
    if (buf[i] == '\0')
      break;
  }
}

char* MQTTItem::GetData()
{
  return mData;
}

char* MQTTItem::GetTopic()
{
  return mTopic;
}

