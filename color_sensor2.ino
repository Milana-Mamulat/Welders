const int Rmin = 70;
const int Gmin = 100;
const int Bmin = 100;
const int Ymin = 100;
int Color = 0;  //0-NONE 1-RED 2-BLUE 3-GREEN 4-YELLOW
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

int ColorNO(){
  int c = 0;
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  delay(70);
  
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  delay(70);
 
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  delay(70);
  if(blueFrequency < redFrequency && blueFrequency < greenFrequency && greenFrequency>Gmin){
      c=2;
    }
  else if(blueFrequency > redFrequency && blueFrequency > greenFrequency && blueFrequency>Bmin){
      c=4;
    }
  else if(greenFrequency < blueFrequency && greenFrequency < redFrequency && greenFrequency > Gmin){
      c=3;
    }
  else if(redFrequency*2 < blueFrequency && redFrequency*2 < greenFrequency){
      c=1;
    }
  else{
      c=0;
    } 
    return c; 
  }

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  Serial.begin(9600);
}

void loop() {
  Color = ColorNO();
  switch(Color){
    case 0:Serial.println("NONE");break;
    case 1:Serial.println("RED");break;
    case 2:Serial.println("BLUE");break;
    case 3:Serial.println("GREEN");break;
    case 4:Serial.println("YELLOW");break;
    default:
    Serial.println("NONE");
    }
  
}
