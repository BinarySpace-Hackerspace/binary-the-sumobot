#define echoPin 4 // Echo Pin Input
#define trigPin 5 // Trigger Pin Output
int debugLED = 13;

void setup() {
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(debugLED, OUTPUT);
}

void loop() 
{
  echo();
}

void echo()
{
  int maximumRange = 60; // Maximum range needed
  int minimumRange = 0; // Minimum range needed
  long duration, distance; // Duration used to calculate distance
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration) / 58.2;
  
  if (distance >= maximumRange || distance <= minimumRange)
  {
     Serial.println("Reading...");
     digitalWrite (debugLED, LOW);
  }
  else
  {
  Serial.print(distance);
  Serial.println(" cm");
  digitalWrite (debugLED, HIGH);
  }
  delay(50);
}
