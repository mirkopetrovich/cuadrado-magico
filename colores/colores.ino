#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels(27, 6, NEO_RBG + NEO_KHZ800);

unsigned char cinco[5];

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pixels.begin(); 
  pixels.clear();
  pixels.show();

}

void loop() {

  if (Serial.available() > 0) {
    Serial.readBytes(cinco,5);
  }

  int pixi = (cinco[0]<<8)+cinco[1];
  int rojo = cinco[2];
  int verde = cinco[3];
  int azul = cinco[4];

for (int i=0;i<3;i++) pixels.setPixelColor((pixi*3)+i, pixels.Color(rojo,verde,azul));
pixels.show();
}
