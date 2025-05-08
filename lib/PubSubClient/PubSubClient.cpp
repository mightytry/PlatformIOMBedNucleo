#include "PubSubClient.h"


void PubSubClient::init()
{
    DigitalOut ch_pd(MBED_CONF_APP_ESP_CH_PD_PIN);
    DigitalOut rst(MBED_CONF_APP_ESP_RST_PIN); 
    ch_pd=1;
    rst=0;
    HAL_Delay(100);
    rst=1;
    static TCPSocket socket1;
    socket=&socket1;
    Timer tim;
    
    static ESP8266Interface esp1(MBED_CONF_APP_ESP_TX_PIN, MBED_CONF_APP_ESP_RX_PIN);
    esp=&esp1;
    int ret = esp->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    static MQTTClient client1(&socket1);
    client=&client1;
    if(ret != 0)
    {
        printf("\nConnection error\n");
    }
    else
    {
        printf("\nConnection success\n");
    }
    esp->get_ip_address(&deviceIP);
    printf("IP via DHCP: %s\n", deviceIP.get_ip_address());
    if (MBED_CONF_APP_HOSTNAME==true)
        // Use with DNS
        {
        esp->gethostbyname(MBED_CONF_APP_MQTT_BROKER_HOSTNAME, &MQTTBroker);
        printf("\nMQTTBroker %s\n",MQTTBroker.get_ip_address());
        MQTTBroker.set_port(MBED_CONF_APP_MQTT_BROKER_PORT);
        }
    else
    // Use with IP
        //SocketAddress MQTTBroker(MBED_CONF_APP_MQTT_BROKER_IP, MBED_CONF_APP_MQTT_BROKER_PORT);
        {
        MQTTBroker.set_port(MBED_CONF_APP_MQTT_BROKER_PORT);
        MQTTBroker.set_ip_address(MBED_CONF_APP_MQTT_BROKER_IP);
        if (MQTTBroker.get_ip_version()== nsapi_version::NSAPI_IPv4) printf("IP-Version IPV4");
        }
    msg.qos = MQTT::QOS0;
    msg.retained = false;
    msg.dup = false;
    
    printf("\n socket open: %d\n",socket->open(esp));
    printf("\n socket connect: %d\n",socket->connect(MQTTBroker));
}

PubSubClient::PubSubClient()
{
    init();
}

bool PubSubClient::connect(char* clientName)
{
    int ret=0;
    data = MQTTPacket_connectData_initializer;  
        
    data.MQTTVersion = 4;
    char *id = clientName;//MBED_CONF_APP_MQTT_ID;
    
    data.clientID.cstring=id;
    
    printf("\n ID=%s\n",clientName);
    
    ret=client->connect(data);
    printf("\n client connect: %d\n",ret);
    
    return ret==0;
}

int PubSubClient::publish(const char* topic, const char* buf)
{
        msg.payload = (void*)buf;
        msg.qos=QOS0;
        msg.retained=false;
        msg.payloadlen = strlen(buf);
        int ret=client->publish(topic, msg);
        return ret;
}

int PubSubClient::publish(const char* topic, const char* buf, MQTT::QoS qos)
{
        msg.payload = (void*)buf;
        msg.qos=qos;
        msg.retained=false;
        msg.payloadlen = strlen(buf);
        int ret=client->publish(topic, msg);
        return ret;
}

int PubSubClient::publish(const char* topic, const char* buf, MQTT::QoS qos, bool retain)
{
        msg.payload = (void*)buf;
        msg.qos=qos;
        msg.retained=retain;
        msg.payloadlen = strlen(buf);
        int ret=client->publish(topic, msg);
        return ret;
}

int PubSubClient::subscribe(const char* topicFilter, MQTT::QoS qos, MQTTClient::messageHandler mh)
{
    int ret=client->subscribe(topicFilter, qos, mh);
    return ret;
}

int PubSubClient::yield(unsigned long timeout_ms)
{

 return client->yield(timeout_ms);
 
}

int PubSubClient::loop(unsigned long timeout_ms)
{

 return client->yield(timeout_ms);
 
}

string PubSubClient::gibPayload(MessageData& mymessage)
{
string ret;

    for (int i=0;i<(int)(mymessage.message.payloadlen);i++)
    {
        ret[i]=((char*)(mymessage.message.payload))[i];
    }
    return ret;  
}