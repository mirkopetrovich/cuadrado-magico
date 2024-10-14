int X = 720;
int Y = 900;
void setup() {
  size(820,1000);
}
void draw() {
  background(235);
  translate (50,50);
  noStroke();
  fill(35,76,173);
  triangle(X,Y,X/2,Y,X/2,Y-(X/2)/2);
  fill(210,80,59);
  triangle(0,Y-X/2,X/2,Y-X/2,X/2,Y-((X/2)/2));
  int in2Y = Y-(X/2);
  fill(35,76,173);
  triangle(0,in2Y, 0,mouseY,(in2Y-mouseY)/2,mouseY);
  fill(210,80,59);
  triangle((in2Y-mouseY)/2,mouseY,(in2Y-mouseY),mouseY,(in2Y-mouseY),mouseY-(in2Y-mouseY));
  int in3X = (in2Y-mouseY);
  int in3Y = (mouseY-(in2Y-mouseY));
  int fin3X = (X+in3X)/2;
  int ancho3 =fin3X-in3X;
  int fin3Y = in3Y+(ancho3/2);
  fill(35,76,173);
  triangle(in3X,in3Y,fin3X,in3Y,fin3X,fin3Y);
  fill(210,80,59);
  triangle(fin3X,fin3Y,fin3X,fin3Y+(ancho3/2),X,fin3Y+(ancho3/2));
  int in4Y = fin3Y+(ancho3/2);
  int alto4 =in2Y-in4Y;
  int base4 =X-(alto4/4);
  fill(35,76,173);
  triangle(X,in4Y,X,in4Y+(alto4/2),base4,in4Y+(alto4/2));
  fill(210,80,59);
  triangle(base4,in4Y+(alto4/2),X-(alto4/2),in4Y+(alto4/2),X-(alto4/2),in4Y+(alto4));
  int in5X = X-(alto4/2);
  int in5Y = in4Y+alto4;
  int base5 = (in5X-in3X)/2;
  fill(35,76,173);
  triangle(in5X,in5Y, in5X-base5,in5Y,in5X-base5,in5Y-base5/2);
  fill(210,80,59);
  triangle(in5X-base5,in5Y-base5/2,in5X-base5,in5Y-base5,in3X,in5Y-base5);
  int in6Y = in5Y-base5;
  int altura6 = in6Y-in4Y;
  fill(35,76,173);
  triangle(in3X,in6Y, in3X, in6Y-altura6/2, in3X+altura6/4,in6Y-altura6/2);
  fill(210,80,59);
  triangle(in3X+altura6/4,in6Y-altura6/2,in3X+altura6/2,in6Y-altura6/2,in3X+altura6/2,in4Y);
  int in7X = in3X+altura6/2;
  int base7 = (in5X-in7X)/2;
  fill(35,76,173);
  triangle(in7X,in4Y,in7X+base7,in4Y,in7X+base7,in4Y+base7/2);
  fill(210,80,59);
  triangle(in7X+base7,in4Y+base7/2,in7X+base7,in4Y+base7,in5X,in4Y+base7);
}
  
