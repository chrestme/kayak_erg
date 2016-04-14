const int hallPin = A7;
const int ledPin = GREEN_LED;

int hallState = 0;
int lastHallState = 0;

unsigned long last_time = 0;
//unsigned long cur_time, delta_time;
float rpms = 0;
long i = 0;

float getRPMs(unsigned long cur_time){
  unsigned long delta_time = cur_time - last_time;
  last_time = cur_time;
  float cur_rpms = 60.0 / (float)(delta_time / 1000.0) / 3.0;
  return cur_rpms;
}

void getHallState(){
  wakeup();
  unsigned long cur_time = millis();
  hallState = digitalRead(hallPin);
  if(hallState == HIGH) {
    digitalWrite(ledPin, LOW);
    //Serial.print("Interrupt! Hall HIGH");
  }
  else {
    digitalWrite(ledPin, HIGH);
    //Serial.print("Interrupt! Hall LOW");
    rpms = getRPMs(cur_time);
    //Serial.print("RPMS: ");
    //Serial.println(cur_rpms);
  }
  i = 0;
}


void setup()
{
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(hallPin, INPUT_PULLUP);
  Serial.begin(9600);
  digitalWrite(ledPin, LOW);
  attachInterrupt(hallPin, getHallState, CHANGE);
}

void loop()
{
  // put your main code here, to run repeatedly:
  //for (int i=0; i < 3000; i++)
  if (i == 300){
    i=0;
    Serial.println("Suspending...");
    suspend();
  }
  if (i % 10 == 0){
    //Serial.println("ping\n");
  }
  Serial.print("RPMS: ");
  Serial.println(rpms);
  sleep(10);
  i++;
  
}
