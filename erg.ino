const int hallPin = A7;
const int ledPin = GREEN_LED;

int hallState = 0;
int lastHallState = 0;

unsigned long time = 0;
unsigned long cur_time, delta_time;
float rpms;

float getRPMs(cur_time){
  delta_time = cur_time - time;
  time = cur_time;
  rpms = 60.0 / (float)(delta_time / 1000.0) / 3;
  return rpms;
}

void getHallState(){
  wakeup();
  hallState = digitalRead(hallPin);
  
}


void setup()
{
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(hallPin, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(hallPin, getHallState, CHANGING);
}

void loop()
{
  // put your main code here, to run repeatedly:
  for (int i=0; i < 3000; i++)
  {
    sleep(100);
  }
  suspend();
  
}
