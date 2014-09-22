#include <NewPing.h>
// Use this code to test your motor with the Arduino board:

// if you need PWM, just use the PWM outputs on the Arduino
// and instead of digitalWrite, you should use the analogWrite command

// --------------------------------------------------------------------------- Motors
int Dist_Counter = 0;
int Dist_Average[] = {0, 0, 0, 0, 0, 0};
int Distance = 0;
int motor_left[] = {4, 3};
int motor_right[] = {5, 6};

int motor1enable = 10;
int motor2enable = 11;


// --------------------------------------------------------------------------- Sonar
#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// --------------------------------------------------------------------------- Deff

const int buttonStart = 2;
bool Start = false;
int buttonState = 0;



int L1_SensorPin = A0;    // select the input pin for the potentiometer
int L1_SensorValue = 0;  // variable to store the value coming from the sensor
int L2_SensorPin = A0;    // select the input pin for the potentiometer
int L2_SensorValue = 0;  // variable to store the value coming from the sensor
int L3_SensorPin = A0;    // select the input pin for the potentiometer
int L3_SensorValue = 0;  // variable to store the value coming from the sensor
int L4_SensorPin = A0;    // select the input pin for the potentiometer
int L4_SensorValue = 0;  // variable to store the value coming from the sensor

int Value_Dark = 1000;
int Value_Light = 590;
int Light_Freshold = 795;



// --------------------------------------------------------------------------- Setup
void setup() {
  //Serial.begin(115200);

  // Setup motors
  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }

}

// --------------------------------------------------------------------------- Loop
void loop() {


  buttonState = digitalRead(buttonStart);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH && Start == false) {
    Start = true;
  }

  //if (buttonState == HIGH && Start == true) {
  // Start = false;
  // }

 // if (Start == true) { // IF START START
    L1_SensorValue = analogRead(L1_SensorPin);
    L2_SensorValue = analogRead(L2_SensorPin);
    L3_SensorValue = analogRead(L3_SensorPin);
    L4_SensorValue = analogRead(L4_SensorPin);

   Border_Check();


    Detect();
   
   
   //setMotor1Left(500, true);
   
//   setMotor2Right(500, false);
   
///delay(1000);
 //setMotor2Right(0, false);
//delay(1000);
 // } // IF START END

}

// --------------------------------------------------------------------------- Drive & Functions

void setMotor1Left(int speed, boolean reverse)
{
  analogWrite(motor1enable, speed);
  digitalWrite(motor_left[0], ! reverse);
  digitalWrite(motor_left[1], reverse);
}

void setMotor2Right(int speed, boolean reverse)
{
  analogWrite(motor2enable, speed);
  digitalWrite(motor_right[0], ! reverse);
  digitalWrite(motor_right[1], reverse);
}


void Detect() {

  delay(20);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).

  int Dist = uS / US_ROUNDTRIP_CM;


  if (Dist_Counter <= 5)
  {
    Dist_Average[Dist_Counter] = Dist;

  } else
  {
    Dist_Counter = -1;
  }

  Dist_Counter += 1;

  int sum = 0;

  for (int i = 0; i < 5; i++)
  {
    sum += Dist_Average[i];
  }

  Distance = sum / 5;

  //Serial.print("Ping: ");
  //Serial.print(Dist); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  //Serial.println("cm");


  if (Distance < 50) {
   
   setMotor1Left(500, true);
   
   setMotor2Right(500, true);
    //Serial.println("FWD");
  }
  else {
    turn_left();
  }

}

void Border_Check_Light() {

  if (  L1_SensorValue < Light_Freshold)
  {


  }

  if (  L2_SensorValue < Light_Freshold)
  {


  }

  if (  L3_SensorValue < Light_Freshold)
  {


  }
  if (  L4_SensorValue < Light_Freshold)
  {


  }





}


void Border_Check_Dark() {

  if (  L1_SensorValue > Light_Freshold)
  {


  }

  if (  L2_SensorValue > Light_Freshold)
  {


  }

  if (  L3_SensorValue > Light_Freshold)
  {


  }
  if (  L4_SensorValue > Light_Freshold)
  {


  }





}


void motor_stop() {
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
  //delay(25);
}

