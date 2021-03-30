// Tea Timer
// V1.1
// (c) Alain MAUER
// www.alainsprojects.com



int LED[] = {2, 3, 4, 5, 6};
int SERVO = 7;
int ServoMin = 460;  // adapt this value if needed
int ServoMax = 2400; // adapt this value if needed
int BUZZER = 8;
int ButtonSet = 10;
int ButtonStart = 11;
int SecTimer=0;
bool BlockA = false;
bool BlockB = false;
bool BlockC = false;
bool Position = false;
int LedDisplay=0;

void ClearLed(){        // all LED's off
  for (int i = 0; i <= 4; i++) {
      digitalWrite(LED[i],LOW);
       }
}
void Output(int on){        // Next Led On
for (int i = 0; i <= 4; i++) {
digitalWrite(LED[i],LOW);  
}
digitalWrite(LED[on-1],HIGH);
}

void Beep(int repeat, int a){       // Buzzer activate repeat,time
  for (int i = 1; i <= repeat; i++) {
     digitalWrite(BUZZER,HIGH);
     timer(a);
     digitalWrite(BUZZER,LOW);
     timer(a);
     }
}


void timerMicro(int value){                 //Timer in micros
  unsigned long time_now = micros();
do {
  
    } while ((unsigned long)(micros() - time_now) < value);  
}

void timer(int value){                      //Timer in millis
  unsigned long time_now = millis();
do {
    
    } while ((unsigned long)(millis() - time_now) < value);  
}

void ServoPos(int value){             // Servo funktion to create the correct impulse ServoPos(variable)
 digitalWrite(SERVO,HIGH);
  timerMicro(value);
 digitalWrite(SERVO,LOW);
  timerMicro(20000-value);
}
void TeaTimerGo(){          // Timer funktion
if (LedDisplay == 0 && Position == false){ServoPos(ServoMin);Position = true;return;} // When nothing set, move the motor up
if (LedDisplay == 0 && Position == true){ServoPos(ServoMax);Position = false;return;} // When nothing set, move the motor down
ServoPos(ServoMax);Position = false;   // Motor Down
do{
for (SecTimer = 0; SecTimer <= 60; SecTimer++) {         // led x 60 sec (1-5min)
  timer(1000);                                           // 1 sec delay 
  if (digitalRead(ButtonStart) == HIGH) {LedDisplay=0;SecTimer=61;} // Check if Stop Button pushed
  digitalWrite(LED[LedDisplay-1], !digitalRead(LED[LedDisplay-1])); // toggle LED each second
}
digitalWrite(LED[LedDisplay-1],LOW);                                                   
LedDisplay--;    
digitalWrite(LED[LedDisplay-1],HIGH);                                         
}while(LedDisplay > 0);

ServoPos(ServoMin);Position = true;
LedDisplay=0;
ClearLed();
timer(1000);
Beep(3,150);Beep(1,1000);

  
}

void setup() {

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
   
   if (digitalRead(ButtonSet) == HIGH && BlockA == false) {Beep(1,100);BlockA=true;}
   if (digitalRead(ButtonSet) == LOW && BlockA == true) {BlockA=false;LedDisplay++;if (LedDisplay > 5) {LedDisplay=1;};Output(LedDisplay);}

   if (digitalRead(ButtonStart) == HIGH && BlockB == false && BlockC ==false) {Beep(1,100);BlockB=true;}
   if (digitalRead(ButtonStart) == LOW && BlockB == true) {BlockB=false;TeaTimerGo();}

}
