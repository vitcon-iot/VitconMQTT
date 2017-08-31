/*
	2017-07-31 jjh
	VitconMQTTItem.h

 2017-07-31 v1.0.0

*/
#ifndef _VITCONMQTTITEM_H_
#define _VITCONMQTTITEM_H_

#define TOPICLEN 100
#define DATALEN 200

namespace vitcon
{
  class MQTTItem
  {
    public:
      MQTTItem();
      MQTTItem(const char* topic);
  
      void Set(const char* data);
      void Set(int data);
      void Set(double data);

      char* GetTopic();
      char* GetData();
  
    private:
      char mTopic[TOPICLEN];
      char mData[DATALEN];
  };
}

#endif /* EOF */
