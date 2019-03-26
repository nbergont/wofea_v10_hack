#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "esphome.h"
using namespace esphome;

const uint8_t _fingerprint[20] = {0x3B, 0x5C, 0x64, 0x35, 0xF5, 0x28, 0xBF, 0x1C, 0xFA, 0x96, 0xDC, 0xE7, 0x65, 0xB1, 0xE1, 0xB3, 0x2E, 0x84, 0x35, 0x77};

// namespace is called 'switch_' because 'switch' is a reserved keyword
class FreeSMS : public Component, public switch_::Switch {
 public:
 
  FreeSMS(const String &user, const String &pass, const String &msg){
	  //Build url
    _url = "https://smsapi.free-mobile.fr/sendmsg?user="+user+"&pass="+pass+"&msg="+msg;
  }
  
  void setup() override{
  }
  
  void write_state(bool state) override {
    if(state)
    {
      HTTPClient https;
      if(https.begin(_url, _fingerprint))
      {
        int httpCode = https.GET();
        if (httpCode < 0) {
          ESP_LOGW("FreeSMS", "HTTPS ERROR : %d", httpCode);
        }
        https.end();
      }
    }
    publish_state(false);
  }

private:
  String _url;
};
