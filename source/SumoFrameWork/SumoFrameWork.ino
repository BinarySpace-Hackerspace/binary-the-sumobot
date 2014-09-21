// sumoFramework

int led = 13;

// sonar
int sonarTrig = 13;
int sonarEcho = 12;

// right motor
int motor1_1 = 5;
int motor1_2 = 3;

// left motor
int motor2_1 = 9;
int motor2_2 = 10;

// the setup routine runs once when you press reset:
void setup() {                
  pinMode(led, OUTPUT);

  pinMode(sonarTrig, OUTPUT);
  pinMode(sonarEcho, INPUT);

  pinMode(motor1_1, OUTPUT);
  pinMode(motor1_2, OUTPUT);
  pinMode(motor2_1, OUTPUT);
  pinMode(motor2_2, OUTPUT);  

  //analogWrite( motor1_1, 100 );
  //analogWrite( motor2_1, 100 );  

  Serial.begin(9600);
 // delay(5000);
  Serial.println( "Hello World" );
}

long ping()
{
  long duration, distance;
  digitalWrite(sonarTrig, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(sonarTrig, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(sonarTrig, LOW);
  duration = pulseIn(sonarEcho, HIGH);
  distance = (duration/2) / 29.1;  

  return distance;
}

void forward( int spd )
{
  analogWrite( motor1_1, spd);
  analogWrite( motor1_2, 0 );
  analogWrite( motor2_1, spd);
  analogWrite( motor2_2, 0 );
}

void brake()
{
  analogWrite( motor1_1, 255);
  analogWrite( motor1_2, 255);
  analogWrite( motor2_1, 255);
  analogWrite( motor2_2, 255);
}

void turnleft(int spd)
{
  analogWrite( motor1_1, spd);
  analogWrite( motor1_2, 0 );
  analogWrite( motor2_1, 0);
  analogWrite( motor2_2, spd );
}

long dist = 0;

void loop() 
{
  long distance = ping();
  
  if ( distance < 200 )
       dist = distance;

  if (dist >= 50)
  {
    forward(180);
  }
  
  if (dist < 50)
  {
    turnleft(180);
  }

}
