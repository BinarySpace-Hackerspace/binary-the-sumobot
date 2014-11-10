// variable to hold sensor values
int IR1 = 0;
int IR1Mapped = 0;
int IR2 = 0;
int IR2Mapped = 0;
int IR3 = 0;
int IR3Mapped = 0;
int IR4 = 0;
int IR4Mapped = 0;

//variables when manual calibration
//above 50 for black; below 50 for white
int IR1Low = 800;
int IR2Low = 800;
int IR3Low = 800;
int IR4Low = 800;
int IR1High = 1000;
int IR2High = 1000;
int IR3High = 1000;
int IR4High = 1000;

// variable to calibrate low values
/*
int IR1Low = 1023;
int IR2Low = 1023;
int IR3Low = 1023;
int IR4Low = 1023;
// variable to calibrate high values
int IR1High = 0;
int IR2High = 0;
int IR3High = 0;
int IR4High = 0;
*/

const int IR1Pin = A0;
const int IR2Pin = A1;
const int IR3Pin = A4;
const int IR4Pin = A5;

void setup() 
{
  Serial.begin(115200);
  pinMode(IR1Pin, INPUT);
  pinMode(IR2Pin, INPUT);
  pinMode(IR3Pin, INPUT);
  pinMode(IR4Pin, INPUT);
  
  /*
  // calibrate for the first five seconds after program runs
  while (millis() < 5000) 
  {
    // record the maximum sensor value
    IR1 = analogRead(IR1Pin);
    if (IR1 > IR1High) 
    {
      IR1High = IR1;
    }
    // record the minimum sensor value
    if (IR1 < IR1Low) 
    {
      IR1Low = IR1;
    }
    // record the maximum sensor value
    IR2 = analogRead(IR2Pin);
    if (IR2 > IR2High) 
    {
      IR2High = IR2;
    }
    // record the minimum sensor value
    if (IR2 < IR2Low) 
    {
      IR2Low = IR2;
    }
    // record the maximum sensor value
    IR3 = analogRead(IR3Pin);
    if (IR3 > IR3High) 
    {
      IR3High = IR3;
    }
    // record the minimum sensor value
    if (IR3 < IR3Low) 
    {
      IR3Low = IR3;
    }
    // record the maximum sensor value
    IR4 = analogRead(IR4Pin);
    if (IR4 > IR4High) 
    {
      IR4High = IR4;
    }
    // record the minimum sensor value
    if (IR4 < IR4Low) 
    {
      IR4Low = IR4;
    }
  }
  */
}

void loop() {
  //read the input from IR's and store it in a variable
  IR1 = analogRead(IR1Pin);
  IR2 = analogRead(IR2Pin);
  IR3 = analogRead(IR3Pin);
  IR4 = analogRead(IR4Pin);

  // map the sensor values to a wide range of pitches
  IR1Mapped = map(IR1, IR1Low, IR1High, 0, 100);
  IR1Mapped = constrain(IR1Mapped, 0, 100);
  IR2Mapped = map(IR2, IR2Low, IR2High, 0, 100);
  IR2Mapped = constrain(IR2Mapped, 0, 100);
  IR3Mapped = map(IR3, IR3Low, IR3High, 0, 100);
  IR3Mapped = constrain(IR3Mapped, 0, 100);
  IR4Mapped = map(IR4, IR4Low, IR4High, 0, 100);
  IR4Mapped = constrain(IR4Mapped, 0, 100);

  Serial.print("Sensor 1\t");
  Serial.print(IR1Mapped);
  Serial.print("\tSensor 2\t");
  Serial.print(IR2Mapped);
  Serial.print("\tSensor 3\t");
  Serial.print(IR3Mapped);
  Serial.print("\tSensor 4\t");
  Serial.println(IR4Mapped);
  
  delay(1000);
}

