
#include <WiFiClientSecure.h>
#include "esphome.h"
using namespace esphome;

// ESPHOME free SMS notifier component
class FreeSMS : public Component, public switch_::Switch {
 public:
 
  FreeSMS(const String &user, const String &pass, const String &msg){
    //Build url
    _url = "/sendmsg?user="+user+"&pass="+pass+"&msg="+msg;
  }
  
  void setup() override{
  }
  
  void write_state(bool state) override {
    if(state)
    {
      const char* fingerprint = "3B 5C 64 35 F5 28 BF 1C FA 96 DC E7 65 B1 E1 B3 2E 84 35 77";
      const char* host = "smsapi.free-mobile.fr";
      WiFiClientSecure client;
      
      if (!client.connect(host, 443)) {
         ESP_LOGW("FreeSMS", "connection failed");
      }
      
      if (!client.verify(fingerprint, host)){
        ESP_LOGW("FreeSMS", "certificate doesn't match");
      }
      
      client.print(String("GET ") + _url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");
      
      if (!client.connected()){
        ESP_LOGW("FreeSMS", "connection error");
      }
      
    }
    publish_state(false);
  }

private:
  String _url;
};
