#include <TFT.h>  
#include <SPI.h>
#include <Wire.h>

#define dc   8
#define rst  9
#define cs   10

TFT TFTscreen = TFT(cs, dc, rst);

char s1[4];
char s2[4];
char s3[4];

void setup() {

   Wire.begin();

  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.setTextSize(4);
  

}

void loop() {



  byte receivedData[] = { 5, 0, 0 };

  Wire.requestFrom(8, 3);

  int index_1 = 0;
  while (Wire.available() && index_1 < 3) {
    receivedData[index_1++] = Wire.read();
  }

String valor_1 = String(receivedData[0]);
String valor_2 = String(receivedData[1]);
String valor_3 = String(receivedData[2]);

  TFTscreen.stroke(0,0,0);  
  TFTscreen.text(s1, 70, 10);
  TFTscreen.text(s2, 70, 50);
  TFTscreen.text(s3, 70, 90);

valor_1.toCharArray(s1, 4);
valor_2.toCharArray(s2, 4);
valor_3.toCharArray(s3, 4);


TFTscreen.stroke(255, 255, 255);
  
  TFTscreen.text(s1, 70, 10);
  TFTscreen.text(s2, 70, 50);
  TFTscreen.text(s3, 70, 90);
  delay(100);

}

