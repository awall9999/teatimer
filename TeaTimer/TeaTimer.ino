int LED[] = {2, 3, 4, 5, 6};
int SERVO = 7;
int ServoMin = 460;
int ServoMax = 2400;
int BUZZER = 8;
int ButtonSet = 10;
int ButtonStart = 11;
int SecTimer=0;
bool BlockA = false;
bool BlockB = false;
bool BlockC = false;
bool Position = false;


int LedDisplay=0;

void Output(int on){
for (int i = 0; i <= 4; i++) {
digitalWrite(LED[i],LOW);  
}
digitalWrite(LED[on-1],HIGH);
}

void Beep(int repeat, int a){
  for (int i = 1; i <= repeat; i++) {
     digitalWrite(BUZZER,HIGH);
     timer(a);
     digitalWrite(BUZZER,LOW);
     timer(a);
     }
}


void timerMicro(int value){
  unsigned long time_now = micros();
do {
  
    } while ((unsigned long)(micros() - time_now) < value);  
}

void timer(int value){
  unsigned long time_now = millis();
do {
    //if (digitalRead(ButtonStart) == HIGH && BlockC == false && BlockB == false ) {BlockC=true;LedDisplay=0;SecTimer=61;value=0;}
    } while ((unsigned long)(millis() - time_now) < value);  
}

void ServoPos(int value){
 digitalWrite(SERVO,HIGH);
  timerMicro(value);
 digitalWrite(SERVO,LOW);
  timerMicro(20000-value);
}
void TeaTimerGo(){
if (LedDisplay == 0 && Position == false){ServoPos(ServoMin);Position = true;return;}
if (LedDisplay == 0 && Position == true){ServoPos(ServoMax);Position = false;return;}
ServoPos(ServoMax);Position = false;
do{
for (SecTimer = 0; SecTimer <= 60; SecTimer++) {
  timer(1000);
  if (digitalRead(ButtonStart) == HIGH) {LedDisplay=0;SecTimer=61;}
  digitalWrite(LED[LedDisplay-1], !digitalRead(LED[LedDisplay-1]));
}
digitalWrite(LED[LedDisplay-1],LOW);                                                   
LedDisplay--;                                                   
}while(LedDisplay > 0);

ServoPos(ServoMin);Position = true;
LedDisplay=0;
timer(1000);
Beep(5,150);Beep(1,1000);

  
}

void setup() {

Serial.begin(9600);
for (int i = 0; i <= 4; i++) {
  pinMode(LED[i],OUTPUT); }
pinMode(BUZZER,OUTPUT); 
pinMode(SERVO,OUTPUT); 
pinMode(ButtonSet,INPUT); 
pinMode(ButtonStart,INPUT);
// Init Test Start//
  Beep(1,250);
  for (int i = 0; i <= 4; i++) {
    digitalWrite(LED[i],HIGH);
     timer(100);
    digitalWrite(LED[i],LOW);
     timer(100);
  }
  ServoPos(ServoMax);Position = false;
// Init Test End//




}




void loop() {

// Set TeaTimer
   //if (digitalRead(ButtonSet) == HIGH) digitalWrite(LED[0],HIGH); else digitalWrite(LED[0],LOW);
   //if (digitalRead(ButtonStart) == HIGH) digitalWrite(LED[1],HIGH); else digitalWrite(LED[1],LOW);
   if (digitalRead(ButtonSet) == HIGH && BlockA == false) {Beep(1,100);BlockA=true;}
   if (digitalRead(ButtonSet) == LOW && BlockA == true) {BlockA=false;LedDisplay++;if (LedDisplay > 5) {LedDisplay=1;};Output(LedDisplay);}

   if (digitalRead(ButtonStart) == HIGH && BlockB == false && BlockC ==false) {Beep(1,100);BlockB=true;}
   if (digitalRead(ButtonStart) == LOW && BlockB == true) {BlockB=false;TeaTimerGo();}

   
   


 

}
