#include "mbed.h"
#include "ESP8266Interface.h"
#include "string"


// Library to use https://github.com/ARMmbed/mbed-mqtt
#include <MQTTClientMbedOs.h>


using namespace MQTT;

class PubSubClient
{
    private:
    ESP8266Interface *esp;
    SocketAddress deviceIP;
    SocketAddress MQTTBroker;    
    TCPSocket *socket;
    MQTTClient *client;
    MQTT::Message msg;
    MQTTPacket_connectData data;
    
    //Subscriptions
    /*
    static int hs_count;
    static char hs[10][40];    //Topics
    static Callback< void(string)> cbs[10]; //Callbacks
    static int topicNr;
    */
    public:
    void init();
    PubSubClient(Callback< void()> func);
    PubSubClient();
    bool connect(char* clientName);
    int publish(const char* topic, const char* buf);
    int publish(const char* topic, const char* buf, MQTT::QoS qos);
    int publish(const char* topic, const char* buf, MQTT::QoS qos, bool retain);
    int subscribe(const char* topicFilter, MQTT::QoS qos, MQTTClient::messageHandler mh);
    //int subscribe(const char* topic,Callback< void(string)> func);
    //static void subscribeCallback(MessageData& mymessage);
    //static void loop();
    int yield(unsigned long timeout_ms = 1000L);
    int loop(unsigned long timeout_ms = 1000L);
    string gibPayload(MessageData& mymessage);
};