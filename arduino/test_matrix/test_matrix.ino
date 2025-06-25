#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#define PIN 6
//#define NUMPIXELS 256 // MATRIX
#define NUMPIXELS 243  // CALUGAS
//#define NUMPIXELS 64 // MATRIX SIMPLE

//#define FILA 16 // MATRIX
#define FILA 9  // CALUGAS
//#define FILA 8
#define DELAYVAL 100
#define OFFSET_H 3
#define OFFSET_V 3

#define CALUGAS
//#define MATRIX

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
int f0, f1, f2, f3, f4, f5, f6, f7, f8;
int frame[] = {0,0,0,0,0,0,0,0,0};

#ifdef MATRIX
const uint16_t XYTable[] = {
  0, 1, 2, 3, 4, 5, 6, 7,
  8, 9, 10, 11, 12, 13, 14, 15,
  16, 17, 18, 19, 20, 21, 22, 23,
  24, 25, 26, 27, 28, 29, 30, 31,
  32, 33, 34, 35, 36, 37, 38, 39,
  40, 41, 42, 43, 44, 45, 46, 47,
  48, 49, 50, 51, 52, 53, 54, 55,
  56, 57, 58, 59, 60, 61, 62, 63
};
#endif

#ifdef CALUGAS
const uint16_t XYTable[] = {
  24, 23, 18, 17, 12, 11, 6, 5, 0,
  25, 22, 19, 16, 13, 10, 7, 4, 1,
  26, 21, 20, 15, 14, 9, 8, 3, 2,
  27, 32, 33, 38, 39, 44, 45, 50, 51,
  28, 31, 34, 37, 40, 43, 46, 49, 52,
  29, 30, 35, 36, 41, 42, 47, 48, 53,
  78, 77, 72, 71, 66, 65, 60, 59, 54,
  79, 76, 73, 70, 67, 64, 61, 58, 55,
  80, 75, 74, 69, 68, 63, 62, 57, 56
};
#endif

const uint8_t icolor[] = {
  0, 255, 255,
  0, 40, 0,
  40, 0, 10
};

const uint8_t ifondo[] = {
  255, 255, 255,
  20, 20, 20,
  100, 100, 100
};


/////////////////////////////////////////////////////////////////////DECLARACIONES
String inputString = "";
bool stringComplete = false;

void setup() {
  Serial.begin(250000);
  Serial1.begin(250000);
  pixels.begin();
  pixels.clear();
  inputString.reserve(200);

}
/////////////////////////////////////////////////////////////////////////////////////SERIAL
void serialEvent1() {
  while (Serial1.available()) {
    int intint = Serial1.read();
    if ((intint >= 48) && (intint <= 57)) {
      inputString += intint-57;
      //Serial.println(intint-48);
    }
    if (intint < 14) {
      stringComplete = true;
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////RELLENAR
void rellenar_frame() {
  for (int x = 0; x < 9; x++) {
      frame[x] = inputString[2 * x + 1];
      Serial.print(frame[x]);
  }
  Serial.println("");
}




///////////////////////////////////////////////////////////////////////////////////////////////////LOOP
void loop() {
  /////////////////////////////////////////////////////////////////////////////////////STRING COMPLETE
  if (stringComplete) {
    Serial.println(inputString.length());
    if (inputString.length() == 18) {
      Serial.println(inputString);
      rellenar_frame();
    }
    inputString = "";
    stringComplete = false;
  }

  //////////////////////////////////////////////////////////////////////////////////DIBUJAR
  pixels.clear();
  for(int x=0; x<9; x++){
    casilla(frame[x], x, 0, 0);
  }
  pixels.show();
  //delay(DELAYVAL);
}




////////////////////////////////////////////////////////////////////////////////////////FUNCIONES
uint16_t XY(uint16_t x, uint16_t y) {
  uint16_t i = (y * FILA) + x;
  uint16_t j = XYTable[i];
  return j;
}
// casilla (numero, cuadrado, color, fondo); /////////////////////////////////////////CASILLA
void casilla(int n, uint8_t q, uint8_t c, uint8_t f) {

  uint8_t casilleros[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
  uint8_t of_h = (q % 3) * 3;
  uint8_t of_v = floor(q / 3) * 3;
  uint8_t r = icolor[3 * c];
  uint8_t g = icolor[3 * c + 1];
  uint8_t b = icolor[3 * c + 2];
  uint8_t r_ = ifondo[3 * f];
  uint8_t g_ = ifondo[3 * f + 1];
  uint8_t b_ = ifondo[3 * f + 2];

  urnShuffle(casilleros);

  for (int i = 0; i < 9; i++) {
    uint8_t h = i % 3;
    uint8_t v = floor(i / 3);

#ifdef MATRIX
    if (casilleros[i] < n) pixels.setPixelColor(XY(h + of_h, v + of_v), pixels.Color(r, g, b));
    else pixels.setPixelColor(XY(h + of_h, v + of_v), pixels.Color(r_, g_, b_));
#endif

#ifdef CALUGAS
    if (casilleros[i] < n) {
      pixels.setPixelColor(XY(h + of_h, v + of_v) * 3, pixels.Color(r, g, b));
      pixels.setPixelColor(XY(h + of_h, v + of_v) * 3 + 1, pixels.Color(r, g, b));
      pixels.setPixelColor(XY(h + of_h, v + of_v) * 3 + 2, pixels.Color(r, g, b));
    } else {
      pixels.setPixelColor(XY(h + of_h, v + of_v) * 3, pixels.Color(r_, g_, b_));
      pixels.setPixelColor(XY(h + of_h, v + of_v) * 3 + 1, pixels.Color(r_, g_, b_));
      pixels.setPixelColor(XY(h + of_h, v + of_v) * 3 + 2, pixels.Color(r_, g_, b_));
    }
#endif
  }
}


// Fisher-Yates shuffle
void urnShuffle(uint8_t arr[]) {
  // Seed the random number generator
  randomSeed(analogRead(0));  // Use an unconnected analog pin to generate entropy for seeding

  for (int i = 8; i > 0; i--) {
    // Get a random index from 0 to i
    int j = random(0, i + 1);

    // Swap the elements at index i and j
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}
