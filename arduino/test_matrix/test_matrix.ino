#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#define PIN 6
#define NUMPIXELS 256  // MATRIX
//#define NUMPIXELS 243.  // CALUGAS

#define FILA 16  // MATRIX
//#define FILA 9  // CALUGAS
#define DELAYVAL 500
#define OFFSET_H 3
#define OFFSET_V 3

//#define CALUGAS
#define MATRIX

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//SoftwareSerial RS485(11, 4); // RX, TX
int f0, f1, f2, f3, f4, f5, f6, f7, f8;
unsigned char frame[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#ifdef MATRIX
const uint16_t XYTable[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 64, 65, 66, 67, 68, 69, 70, 71,
  8, 9, 10, 11, 12, 13, 14, 15, 72, 73, 74, 75, 76, 77, 78, 79,
  16, 17, 18, 19, 20, 21, 22, 23, 80, 81, 82, 83, 84, 85, 86, 87,
  24, 25, 26, 27, 28, 29, 30, 31, 88, 89, 90, 91, 92, 93, 94, 95,
  32, 33, 34, 35, 36, 37, 38, 39, 96, 97, 98, 99, 100, 101, 102, 103,
  40, 41, 42, 43, 44, 45, 46, 47, 104, 105, 106, 107, 108, 109, 110, 111,
  48, 49, 50, 51, 52, 53, 54, 55, 112, 113, 114, 115, 116, 117, 118, 119,
  56, 57, 58, 59, 60, 61, 62, 63, 120, 121, 122, 123, 124, 125, 126, 127,
  128, 129, 130, 131, 132, 133, 134, 135, 192, 193, 194, 195, 196, 197, 198, 199,
  136, 137, 138, 139, 140, 141, 142, 143, 200, 201, 202, 203, 204, 205, 206, 207,
  144, 145, 146, 147, 148, 149, 150, 151, 208, 209, 210, 211, 212, 213, 214, 215,
  152, 153, 154, 155, 156, 157, 158, 159, 216, 217, 218, 219, 220, 221, 222, 223,
  160, 161, 162, 163, 164, 165, 166, 167, 224, 225, 226, 227, 228, 229, 230, 231,
  168, 169, 170, 171, 172, 173, 174, 175, 232, 233, 234, 235, 236, 237, 238, 239,
  176, 177, 178, 179, 180, 181, 182, 183, 240, 241, 242, 243, 244, 245, 246, 247,
  184, 185, 186, 187, 188, 189, 190, 191, 248, 249, 250, 251, 252, 253, 254, 255
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



/* 
    72, 71, 54, 53, 36, 35, 18, 17, 0,
    73, 70, 55, 52, 37, 34, 19, 16, 1,
    74, 69, 56, 51, 38, 33, 20, 15, 2,
    75, 68, 57, 50, 39, 32, 21, 14, 3,
    76, 67, 58, 49, 40, 31, 22, 13, 4,
    77, 66, 59, 48, 41, 30, 23, 12, 5,
    78, 65, 60, 47, 42, 29, 24, 11, 6,
    79, 64, 61, 46, 43, 28, 25, 10, 7,
    80, 63, 62, 45, 44, 27, 26, 9, 8,
    81, 98, 99, 116, 117, 134, 135, 152, 153,
    82, 97, 100, 115, 118, 133, 136, 151, 154,
    83, 96, 101, 114, 119, 132, 137, 150, 155,
    84, 95, 102, 113, 120, 131, 138, 149, 156, 
    85, 94, 103, 112, 121, 130, 139, 148, 157,
    86, 93, 104, 111, 122, 129, 140, 147, 158,
    87, 92, 105, 110, 123, 128, 141, 146, 159,
    88, 91, 106, 109, 124, 127, 142, 145, 160,
    89, 90, 107, 108, 125, 126, 143, 144, 161,
    234, 233, 216, 215, 198, 197, 180, 179, 162,
    235, 232, 217, 214, 199, 196, 181, 178, 163,
    236, 231, 218, 213, 200, 195, 182, 177, 164,
    237, 230, 219, 212, 201, 194, 183, 176, 165,
    238, 229, 220, 211, 202, 193, 184, 175, 166,
    239, 228, 221, 210, 203, 192, 185, 174, 167,
    240, 227, 222, 209, 204, 191, 186, 173, 168,
    241, 226, 223, 208, 205, 190, 187, 172, 169,
    242, 225, 224, 207, 206, 189, 188, 171, 170
  }; */



const uint8_t icolor[] = {
  0, 30, 40,
  0, 40, 0,
  40, 0, 10
};

const uint8_t ifondo[] = {
  0, 0, 0,
  20, 20, 20,
  100, 100, 100
};

void setup() {

  Serial1.begin(9600);
  pixels.begin();
  pixels.clear();
}

void loop() {
  //pixels.clear();

  if (Serial1.available()) {
    for (int i = 0; i < 9; i++) {
      frame[i] = Serial1.read();
    }


    // casilla (numero, cuadrado, color, fondo);
    //pixels.clear();
    //casilla(f1,0,0,0);


    //RS485.println(ficha_1);
  }

  //pixels.clear();

  if (frame[0] != f0) {

    if (frame[0] < 100) {
      casilla(frame[0], 0, 0, 0);
      f0 = frame[0];
    }
    if (frame[0] > 100) {
      casilla(frame[0] - 100, 0, 0, 0);
      f0 = frame[0];
    }
  }

  if (frame[1] != f1) {

    if (frame[1] < 100) {
      casilla(frame[1], 1, 0, 0);
      f1 = frame[1];
    }
    if (frame[1] > 100) {
      casilla(frame[1] - 100, 0, 0, 0);
      f1 = frame[1];
    }
  }

  if (frame[2] != f2) {

    if (frame[2] < 100) {
      casilla(frame[2], 2, 0, 0);
      f2 = frame[2];
    }
    if (frame[2] > 100) {
      casilla(frame[2] - 100, 0, 0, 0);
      f2 = frame[2];
    }
  }

  if (frame[3] != f3) {

    if (frame[3] < 100) {
      casilla(frame[3], 3, 0, 0);
      f3 = frame[0];
    }
    if (frame[3] > 100) {
      casilla(frame[3] - 100, 3, 0, 0);
      f3 = frame[3];
    }
  }

  if (frame[4] != f4) {

    if (frame[4] < 100) {
      casilla(frame[4], 4, 0, 0);
      f4 = frame[4];
    }
    if (frame[4] > 100) {
      casilla(frame[4] - 100, 4, 0, 0);
      f4 = frame[4];
    }
  }

  if (frame[5] != f5) {

    if (frame[5] < 100) {
      casilla(frame[5], 5, 0, 0);
      f5 = frame[5];
    }
    if (frame[5] > 100) {
      casilla(frame[5] - 100, 5, 0, 0);
      f5 = frame[5];
    }
  }

  if (frame[6] != f6) {

    if (frame[6] < 100) {
      casilla(frame[6], 6, 0, 0);
      f6 = frame[0];
    }
    if (frame[6] > 100) {
      casilla(frame[6] - 100, 6, 0, 0);
      f6 = frame[6];
    }
  }

  if (frame[7] != f7) {

    if (frame[7] < 100) {
      casilla(frame[7], 7, 0, 0);
      f7 = frame[7];
    }
    if (frame[7] > 100) {
      casilla(frame[7] - 100, 7, 0, 0);
      f7 = frame[7];
    }
  }

  if (frame[8] != f8) {

    if (frame[8] < 100) {
      casilla(frame[8], 8, 0, 0);
      f8 = frame[8];
    }
    if (frame[8] > 100) {
      casilla(frame[8] - 100, 8, 0, 0);
      f8 = frame[8];
    }
  }
















  pixels.show();
  // pixels.clear();
  // casilla (numero, cuadrado, color, fondo);
  //casilla(ficha_1,0,0,0);
  //casilla(ficha_2,1,1,0);
  /*casilla(3,2,2,0);
  casilla(4,3,0,0);
  casilla(5,4,0,0);
  casilla(6,5,0,0);
  casilla(7,6,0,0);
  casilla(8,7,0,0);
  casilla(9,8,0,0);*/

  //pixels.show();
  delay(DELAYVAL);
}

uint16_t XY(uint16_t x, uint16_t y) {
  uint16_t i = (y * FILA) + x;
  uint16_t j = XYTable[i];
  return j;
}
// casilla (numero, cuadrado, color, fondo);
void casilla(uint8_t n, uint8_t q, uint8_t c, uint8_t f) {

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
