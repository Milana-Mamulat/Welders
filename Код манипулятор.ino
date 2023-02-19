 include <Servo.h>
#define TIME_STEP 15

#define TIME_CADR 25

byte portServo[5]={5,6,3,9,10};
Servo M[5];
byte posAct[5] = { 0, 110, 0, 50, 110 };

byte posNew[5];

byte posHome[5]   = {0, 120, 20, 150, 150};
byte posWhite[5]  = {40, 80, 40, 150, 150};
byte posBlack[5]  = {40, 150, 15, 150, 150};
byte posRed[5]    = {65, 50, 15, 150, 150};
byte posBlue[5]   = {65, 70, 35, 150, 150};

// (0 - 180) 
// (20 - 180)
// (0 - 50)
// (0 - 100)
// (0 - 76)

void copyPos(byte oldPos[],byte newPos[]){
  for( byte i=0; i<5; i++) {
    newPos[i] = oldPos[i];
  }}

void setPos() {
  for( byte i=0; i<5; i++) {
    M[i].write( posAct[i] );
  }
}

void setPosNew(byte newPos[]) {
  
  for( byte i=0; i<5; i++) {
    posAct[i] = newPos[i];
    M[i].write( posAct[i] );
  }
}

void info() {
  for( byte i=0; i<5; i++) {
    Serial2.println( "Motor[ " + String( i ) + " ]: " + String(posAct[i]));
  }
}
void multiplyPos(byte anime[], byte num, int time) {
  for( byte i=0; i<num; i++) {
    setPosNew( anime[i] );
    delay(time);
  }
}

byte maxAngle(byte posStart[], byte posFinish[]) {
  byte maxStep = 1;
  int posStep;
  
  for( byte i=0; i<5; i++) {
    posStep = (posFinish[i] - posStart[i]);
    if( posStep < 0) posStep = -posStep;
    if( maxStep < posStep ) maxStep = posStep;
  }
  return maxStep;
}

void playPos(byte posS[], byte posFinish[], int time_pos) {
  float posStep[5];
  byte posTmp[5];
  byte posStart[5];

  copyPos( posS, posStart);
  
  byte numStep = maxAngle(posStart, posFinish);
  
  for( byte i=0; i<5; i++) {
    posStep[i] = (posFinish[i] - posStart[i])/ (float)numStep;
  }
  
  for(int j=0; j<numStep; j++) {
    for(int i=0; i<5; i++) {
      posTmp[i] = posStart[i] + j*posStep[i];
    }
    setPosNew( posTmp);
    delay(time_pos);
  }
  setPosNew( posFinish);
}
void setup() 
{
    Serial2.begin(115200);
    for(int i=0;i<5;i++){
      M[i].attach(portServo[i]);
      }
  copyPos( posAct, posNew);
  Serial2.println("Enter command: ");
}

void loop() 
{
  if (Serial2.available() >= 4 ) 
  {
    char bufC = Serial2.read();
    char n1, n2, n3;
    switch (bufC) 
    {     
      case 'A':
      n1 = Serial2.read();
      n2 = Serial2.read();
      n3 = Serial2.read();
      copyPos( posAct, posNew);
        posNew[0]= (n1 - '0')*100 + (n2 - '0')*10 + (n3 - '0');
      break; 
      case 'B':
        n1 = Serial2.read();
        n2 = Serial2.read();
        n3 = Serial2.read();  
        copyPos( posAct, posNew);
        posNew[1]= (n1 - '0')*100 + (n2 - '0')*10 + (n3 - '0');
        break;
      case 'C':
        n1 = Serial2.read();
        n2 = Serial2.read();
        n3 = Serial2.read();      
        copyPos( posAct, posNew);
        posNew[2]= (n1 - '0')*100 + (n2 - '0')*10 + (n3 - '0');
        break; 
      case 'D': 
        n1 = Serial2.read();
        n2 = Serial2.read();
        n3 = Serial2.read();
        copyPos( posAct, posNew);
        posNew[3]= (n1 - '0')*100 + (n2 - '0')*10 + (n3 - '0');
        break; 
      case 'E': 
        n1 = Serial2.read();
        n2 = Serial2.read();
        n3 = Serial2.read();      
        copyPos( posAct, posNew);
        posNew[4]= (n1 - '0')*100 + (n2 - '0')*10 + (n3 - '0');
        break; 
      case 'P': 
        n1 = Serial2.read();
        n2 = Serial2.read();
        n3 = Serial2.read(); 
        if( n1 == 'H') copyPos( posHome, posNew );
        if( n1 == 'W') copyPos( posWhite, posNew);
        if( n1 == 'B' && n2 == 'L' && n3 == 'K') copyPos( posBlack, posNew);
        if( n1 == 'R') copyPos( posRed, posNew);
        if( n1 == 'B' && n2 == 'L' && n3 == 'U') copyPos( posBlue, posNew);
        break; 
      case 'I':
        info(); 
        break;      
    default: 
      Serial2.println('?');
    }
  }
  delay(TIME_CADR);
 
  playPos(posAct,posNew,TIME_STEP);
}
