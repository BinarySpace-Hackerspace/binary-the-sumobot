#define echoPin 4 // Echo Pin Input
#define trigPin 5 // Trigger Pin Output

#define motor1pole1 2 
#define motor1pole2 3
#define motor2pole1 7
#define motor2pole2 8

// map L293d motor enable pins to Arduino pins
#define enablePin1 9
#define enablePin2 10

#define M1_MAX_SPEED 100
#define M2_MAX_SPEED 100

#define motordelay 30
#define debugmotorsec 100

int mspeed = 160;  // pick a starting speed up to 255
int previousDistance;
int i;
int j;

void setup() {
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // set mapped L293D motor1 and motor 2 enable pins on Arduino to output (to turn on/off motor1 and motor2 via L293D)
  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);

  // set mapped motor poles to Arduino pins (via L293D)
  pinMode( motor1pole1 , OUTPUT);
  pinMode( motor1pole2, OUTPUT);
  pinMode( motor2pole1, OUTPUT);
  pinMode( motor2pole2 , OUTPUT);
  motorspeed(0, 0);
}

void loop() 
{
  echo();
  motorspeed(mspeed, mspeed);
}

void echo()
{
  //int maximumRange = 60; // Maximum range needed
  int minimumRange = 30; // Minimum range needed
  long duration, distance; // Duration used to calculate distance
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration) / 58.2;
  Serial.print ("Distance\t");
  Serial.println (distance);
  
    if (distance <= minimumRange)
    {
      if (previousDistance > distance)
      {     
        i = random (1, 3);
        Serial.println (i);
        if (i == 1)
        {
          j = 2;
        }
        if (i == 2)
        {
          j = 1;
        }
      }
      motorforward(i);
      motorback(j);
      delay(debugmotorsec);
    }
      else
      {
        motorforward(1);
        motorforward(2);
        delay(debugmotorsec);
      }
    //delay(50);
    previousDistance = distance;
}

// MOTOR FUNCTIONS

void motorstop(int motornum){
  delay(motordelay);
  if (motornum == 1) {
    digitalWrite(motor1pole1, LOW);
    digitalWrite(motor1pole2, LOW);
  }
  else if (motornum == 2) {

    digitalWrite(motor2pole1, LOW);
    digitalWrite(motor2pole2, LOW);
  }
  delay(motordelay);
}

void motorforward(int motornum){
  if (motornum == 1) {
    digitalWrite(motor1pole1, HIGH);
    digitalWrite(motor1pole2, LOW);
  }
  else if (motornum == 2) {

    digitalWrite(motor2pole1, LOW);
    digitalWrite(motor2pole2, HIGH);
  }
  delay(motordelay);
}

void motorback(int motornum){
  if (motornum == 1) {
    digitalWrite(motor1pole1, LOW);
    digitalWrite(motor1pole2, HIGH);
  } 
  else if (motornum == 2) {
    digitalWrite(motor2pole1, HIGH);
    digitalWrite(motor2pole2, LOW);
  }
  delay(motordelay);
}

void motorspeed(int motor1speed, int motor2speed) {
  if (motor1speed > M1_MAX_SPEED ) motor1speed = M1_MAX_SPEED; // limit top speed
  if (motor2speed > M2_MAX_SPEED ) motor2speed = M2_MAX_SPEED; // limit top speed
  if (motor1speed < 0) motor1speed = 0; // keep motor above 0
  if (motor2speed < 0) motor2speed = 0; // keep motor speed above 0
  analogWrite(enablePin1, motor1speed);
  analogWrite(enablePin2, motor2speed);
}
