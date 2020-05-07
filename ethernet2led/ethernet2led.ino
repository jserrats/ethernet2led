#include <UIPEthernet.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_LEDS 74
#define BRIGHTNESS 20
#define BUFFER_LEN NUM_LEDS*4

EthernetUDP udp;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB);
byte packetBuffer[BUFFER_LEN];

void setup() {
  uint8_t mac[6] = {0x7e, 0x1e, 0xc0, 0xba, 0x55, 0x02};
  Ethernet.begin(mac);
  int success = udp.begin(1234);
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
 }

void loop() {
  while (true) {
    int packetSize = udp.parsePacket();
    if (packetSize) {

      int len = udp.read(packetBuffer, BUFFER_LEN);
      if(len ==1 && packetBuffer[0]==255){
        break;
      }
      for (int i = 0; i < len; i += 4) {
        strip.setPixelColor(packetBuffer[i], strip.Color(packetBuffer[i + 1], packetBuffer[i + 2], packetBuffer[i + 3]));
      }
      strip.show();
    }
  }
  for (int i = 0; i < NUM_LEDS; i ++) {
        strip.setPixelColor(i, strip.Color(0,0,0));
      }
  strip.show();
  udp.stop();
  udp.begin(1234);
}

