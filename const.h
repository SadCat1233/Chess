struct Point{
  int x, y;
  Point(int x_, int y_){
    x = x_;
    y = y_;
  }
};


int SENSORS_INVERTING = 1;

byte M1_D = 10;
byte M1_S = 11;
byte M1_MAX_PIN = 13;
byte M1_MIN_PIN = 12;


byte M2_D = 9;
byte M2_S  = 3;
byte M2_MAX_PIN = 8;
byte M2_MIN_PIN = 2;


bool MAG = false;
int SPT = 10000;
int INP_K = 100;
float Y_K = 1239 / 11;
float X_K = 974 / 9;

Point BOARD_CORNER(1, 1);
int SQUARE_SIZE = 35;
