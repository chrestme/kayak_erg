#include "TM1637.h"

/* Macro Define */
#define CLK               9                  /* 4-digital display clock pin */
#define DIO               10                 /* 4-digiral display data pin */
 
/* Global Varibles */
TM1637 tm1637(CLK, DIO);                  /* 4-digital display object */

// constants won't change. They're used here to 
// set pin numbers:
const int hallPin = A7;     // the number of the pushbutton pin
const int ledPin =  GREEN_LED;      // the number of the LED pin

// variables will change:
int hallState = 0;         // variable for reading the pushbutton status
int lastHallState = 0;

unsigned long time = 0;
unsigned long cur_time, delta_time;
float rpms;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(hallPin, INPUT_PULLUP);     
  Serial.begin(9600);
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL); 
}

void loop(){
  // read the state of the pushbutton value:
  hallState = digitalRead(hallPin);

  if (hallState != lastHallState) {

    if (hallState == HIGH) {     
      // turn LED on:    
      digitalWrite(ledPin, LOW);
      //tm1637.display(0,0);
      //tm1637.display(1,0);
      //tm1637.display(2,0);
      //tm1637.display(3,0);
    } 
    else {
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      Serial.print("RPMs: ");
    
      //This needs to go into a callback
      cur_time = millis();
      delta_time = cur_time - time;
      time = cur_time;
      rpms = 60.0 / (float)(delta_time / 1000.0);   
      Serial.println(rpms);
      int rpm_int;
      //int rpm_array[4];
      rpm_int = rpms;
      
      for(int i=3; i >= 0; i--){
        //int rpm_array[i] = rpm_int % 10;
        tm1637.display(i,rpm_int % 10);
        rpm_int /= 10;
      }
    }
  }
  lastHallState = hallState;
}
