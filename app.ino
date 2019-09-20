#include "secret.h"
#include <Adafruit_NeoPixel.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// For WifiManager
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#define PIXEL_PIN      3

#define NUMPIXELS      12

char auth[] = BLYNK_AUTH;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXEL_PIN);
WiFiManager wifiManager;


String wifiName = WiFi.SSID();
String wifiPass = WiFi.psk();


void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  wifiManager.autoConnect("Lamp-WiFi");

  Blynk.begin(auth, wifiName.c_str(), wifiPass.c_str());
  Blynk.syncVirtual(V5);
}

void loop() {
  Blynk.run();
}

//-------------------------------------------------------------------------------

BLYNK_WRITE(V0){
  changeColor(param[0].asInt(), param[1].asInt(), param[2].asInt());
//   colorFade(param[0].asInt(), param[1].asInt(), param[2].asInt(), 20);
}

void changeColor(uint8_t r, uint8_t g, uint8_t b){
  uint32_t color = pixels.Color(r, g, b);
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}

// Fades evenly from one color to another. 
// The parameter `wait` is the delay before applying each incremental color update between starting color and end.
void colorFade(uint8_t r, uint8_t g, uint8_t b, uint8_t wait){

  bool changing = false;
  uint8_t curr_r, curr_g, curr_b;

  uint32_t curr_col = pixels.getPixelColor(1);
  curr_b = curr_col & 0xFF; curr_g = (curr_col >> 8) & 0xFF; curr_r = (curr_col >> 16) & 0xFF;  // separate into RGB components

  while ((curr_r != r) || (curr_g != g) || (curr_b != b)){  // while the curr color is not yet the target color
    for(uint16_t i = 0; i < pixels.numPixels(); i++) {

      uint32_t curr_col = pixels.getPixelColor(i);

      curr_b = curr_col & 0xFF; curr_g = (curr_col >> 8) & 0xFF; curr_r = (curr_col >> 16) & 0xFF;
      
      if (curr_r < r) curr_r++; else if (curr_r > r) curr_r--;  // increment or decrement the old color values
      if (curr_g < g) curr_g++; else if (curr_g > g) curr_g--;
      if (curr_b < b) curr_b++; else if (curr_b > b) curr_b--;

      pixels.setPixelColor(i, curr_r, curr_g, curr_b);  // set the color
    }
    delay(wait);
    pixels.show();
  }
}