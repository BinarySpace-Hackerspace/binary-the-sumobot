#include <NewPing.h>
// Use this code to test your motor with the Arduino board:

// if you need PWM, just use the PWM outputs on the Arduino
// and instead of digitalWrite, you should use the analogWrite command

// --------------------------------------------------------------------------- Motors
int Dist_Counter = 0;
int Dist_Average[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Distance = 0;
int motor_left[] = {4, 3};
int motor_right[] = {5, 6};

int motor1enable = 10;
int motor2enable = 11;

int DistanceDetect = 15;

int enableLightOutput = 1;

int enableUSB = 0;
// --------------------------------------------------------------------------- Sonar
#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// --------------------------------------------------------------------------- Deff

const int buttonStart = 2;
bool Start = false;
int buttonState = 0;



int FL_SensorPin = A1;    // select the input pin for the potentiometer
int FL_SensorValue = 0;  // variable to store the value coming from the sensor
int FR_SensorPin = A0;    // select the input pin for the potentiometer
int FR_SensorValue = 0;  // variable to store the value coming from the sensor
int BL_SensorPin = A3;    // select the input pin for the potentiometer
int BL_SensorValue = 0;  // variable to store the value coming from the sensor
int BR_SensorPin = A2;    // select the input pin for the potentiometer
int BR_SensorValue = 0;  // variable to store the value coming from the sensor

int Value_Dark = 1000;
int Value_Light = 590;
//int Light_Freshold = 795;

int Light_Freshold_Front = 600;

int Light_Freshold_Back = 700;



// --------------------------------------------------------------------------- Setup
void setup() {
  Serial.begin(115200);

  // Setup motors
  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
delay(5000);
}

// --------------------------------------------------------------------------- Loop
void loop() {


//  motortest();
  
  
  buttonState = digitalRead(buttonStart);









  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH && Start == false) {
    Start = true;
  }

  //if (buttonState == HIGH && Start == true) {
  //  Start = false;
 // }

//  if (Start == true) { // IF START START
    FL_SensorValue = analogRead(FL_SensorPin);
    FR_SensorValue = analogRead(FR_SensorPin);
    BL_SensorValue = analogRead(BL_SensorPin);
    BR_SensorValue = analogRead(BR_SensorPin);

    if (enableLightOutput == 1) {
      Serial.print("FL:");
      Serial.println(FL_SensorValue);
      Serial.print("FR:");
      Serial.println(FR_SensorValue);
      Serial.print("BL:");
      Serial.println(BL_SensorValue);
      Serial.print("BR:");
      Serial.println(BR_SensorValue);
     
//delay(500);
   }
    Border_Check_Light();



 // } // IF START END

}

// --------------------------------------------------------------------------- Drive & Functions

void motortest()
{
  int i = 80;
 for (i = 80; i < 150; i++) {
   
     
  setMotor1Left(i, true);
  
  Serial.println(i);
   delay(2000);
   
 }

}


void setMotor1Left(int speed, boolean reverse)
{
  if (enableUSB == 1){
  speed = speed + 50;
  }
  analogWrite(motor1enable, speed + 420);
  digitalWrite(motor_left[0], ! reverse);
  digitalWrite(motor_left[1], reverse);
}

void setMotor2Right(int speed, boolean reverse)
{
    if (enableUSB == 1){
  speed = speed +50;
  }
  analogWrite(motor2enable, speed + 420);
  digitalWrite(motor_right[0], ! reverse);
  digitalWrite(motor_right[1], reverse);
}


void Detect() {

  delay(20);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).

  int Dist = uS / US_ROUNDTRIP_CM;

Serial.print("Ping: ");
  Serial.print(Dist); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");
  
  
  if (Dist_Counter < 9)
  {
    Dist_Average[Dist_Counter] = Dist;

  } else
  {
    Dist_Counter = -1;
  }

  Dist_Counter += 1;

  int sum = 0;

  for (int i = 0; i < 9; i++)
  {
    sum += Dist_Average[i];
  }

  Distance = sum / 9;

  


  if (Distance < DistanceDetect) {

    setMotor1Left(10, true);

    setMotor2Right(10, true);
    delay(15);
    //Serial.println("FWD");
  }
  else {
    setMotor1Left(-10, true);
    setMotor2Right(-10, false);
  }

}

void Border_Check_Light() {

  if (  FL_SensorValue <= Light_Freshold_Front)
  {

    setMotor1Left(2, false);
    setMotor2Right(1, false);
    delay(5);

  }

  else if (  FR_SensorValue <= Light_Freshold_Front)
  {
    setMotor1Left(1, false);
    setMotor2Right(2, false);
delay(5);
  }

  else if (  BL_SensorValue <= Light_Freshold_Back)
  {

    setMotor1Left(2, true);
    setMotor2Right(1, true);
    delay(5);
  }
  else if (  BR_SensorValue <= Light_Freshold_Back)
  {

    setMotor1Left(1, true);
    setMotor2Right(2, true);
    delay(5);
  }
  else if (  FL_SensorValue=Light_Freshold_Front && FR_SensorValue <= Light_Freshold_Front)
  {

    setMotor1Left(20, false);
    setMotor2Right(20, false);
    delay(5);
  }
  else if (  BL_SensorValue <= Light_Freshold_Back && BR_SensorValue <= Light_Freshold_Back)
  {

    setMotor1Left(20, true);
    setMotor2Right(20, true);
    delay(5);
  }




  else
  {

    Detect();


  }






}

void outputtoS(String text)
{
Serial.println(text);
}

//void Border_Check_Dark() {
//
//  if (  L1_SensorValue > Light_Freshold)
//  {
//
//
//  }
//
//  if (  L2_SensorValue > Light_Freshold)
//  {
//
//
//  }
//
//  if (  L3_SensorValue > Light_Freshold)
//  {
//
//
//  }
//  if (  L4_SensorValue > Light_Freshold)
//  {
//
//
//  }
//
//
//
//
//
//}


void motor_stop() {
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
  //delay(25);
}

