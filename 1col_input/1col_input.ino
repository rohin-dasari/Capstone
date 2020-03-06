#include <SoftwareSerial.h>

SoftwareSerial blue(5, 6);
int row1_in = A5;
int row2_in = A3;
int row3_in = A2;
int row4_in = A0;

float row1_out = 0;
float row2_out = 0;
float row3_out = 0;
float row4_out = 0;

 /*
  * Column 1 --> Digital Pin 10
  * Column 2 --> Digital Pin 11
  * Column 3 --> Digital Pin 12
  * Column 4 --> Digital Pin 13
  */
int columnPin = 10;

const int ncols = 4;
const int nrows = 4;
int colPins[ncols] = {10, 11, 12, 13};
int rowInput[nrows] = {A5, A3, A2, A0};


unsigned long timerStart = 0;
unsigned long waitPeriod = 1000;
unsigned long currentTime = 0;

void setup() {
  Serial.begin(9600);
  blue.begin(9600);
  for (int i = 0; i < ncols; i++){
    pinMode(colPins[0], OUTPUT);
  }
  timerStart = millis();
  digitalWrite(columnPin, HIGH);

}

void loop() {
  
//  int data[ncols][nrows];
//  for (int i = 0; i < ncols; i++){
//    digitalWrite(colPins[i], HIGH);
//    for (int j = 0; j < nrows; j++){
//      if (pauseStatus && ((millis()-pauseStart) >= pauseLen)){
//        data[i][j] = analogRead(rowInput[j]);
//      }
//      Serial.print((String)data[i][j] + " ");
//    }
//    Serial.println();
//    digitalWrite(colPins[i], LOW);
//  }

  
//  Serial.println(data[1][1]);
  volatile int data[ncols][nrows];
  for (int i = 0; i < ncols; i++){
    currentTime = millis();
    if (currentTime - timerStart < waitPeriod){
      digitalWrite(colPins[i], HIGH);
      for (int j = 0; j < nrows; j++){
        data[i][j] = analogRead(rowInput[j]);
//        Serial.print((String)data[i][j] + " ");
      }
//      Serial.print("|");
    }
    else{
//      Serial.println();
      timerStart = millis();
    }
  }

  for (int i = 0; i < ncols; i ++){
    for (int j = 0; j < nrows; j++){
      Serial.print((String)data[i][j] + " ");
      blue.print((String)data[i][j] + " ");
    }
    Serial.print("|");
    blue.print("|");
  }
  Serial.println();
  blue.print("\n");

  


  
//  int data[nrows];

//  for (int i = 0; i < nrows; i++){
//    data[i] = analogRead(rowInput[i]);
//    row1_out = analogRead(rowInput[0]);
//    row2_out = analogRead(rowInput[1]);
//    row3_out = analogRead(rowInput[2]);
//    row4_out = analogRead(rowInput[3]);
  

//  for (int i = 0; i < nrows; i++){
//    Serial.print((String)data[i] + " ");
//  }
//  Serial.println();  
//  if (row1_out != 0 || row2_out != 0 || row3_out != 0 || row4_out != 0){
//    Serial.print((String)row1_out + " ");
//    Serial.print((String)row2_out + " ");
//    Serial.print((String)row3_out + " ");
//    Serial.print((String)row4_out + " ");
//    Serial.println();
//  }

}
