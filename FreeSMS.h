
#include "esphome.h"
using namespace esphome;

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

const uint8_t _fingerprint[20] = {0x5A, 0xCF, 0xFE, 0xF0, 0xF1, 0xA6, 0xF4, 0x5F, 0xD2, 0x11, 0x11, 0xC6, 0x1D, 0x2F, 0x0E, 0xBC, 0x39, 0x8D, 0x50, 0xE0};

// namespace is called 'switch_' because 'switch' is a reserved keyword
class FreeSMS : public Component, public switch_::Switch {
 public:
 
  FreeSMS(const String &user, const String &pass, const String &msg){
    _url = "https://smsapi.free-mobile.fr/sendmsg?user="+user+"&pass="+pass+"&msg="+msg;
  }
  
  void setup() override{
  }
  
  void write_state(bool state) override {
    if(state)
    {
      HTTPClient https;
      BearSSL::WiFiClientSecure client;
      
      client.setFingerprint(_fingerprint);
      if(https.begin(client, _url))
      {
        int httpCode = https.GET();
        if (httpCode < 0) {
          ESP_LOGW("FreeSMS", "HTTPS ERROR : %s", https.errorToString(httpCode).c_str());
        }
        https.end();
      }
    }
    publish_state(false);
  }

private:
  String _url;
};
