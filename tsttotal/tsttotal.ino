// Parameters
int _measurementId;
int _deviceId;
String _dateTime;
float _distanceToSurface;
float _formerDistanceToSurface;
double _flowSpeed;
boolean _flood = false;
long duration;
int timeDelay = 5000; // to set interval

// Arduino setup
const int flowPin = 2;   
const int trigPin = 8;
const int echoPin = 9;
volatile int count; //This integer needs to be set as volatile to ensure it updates correctly during the interrupt process.

// To run once:
void setup() 
{
  pinMode(flowPin, INPUT);            //Sets the pin as an input
  attachInterrupt(0, Flow, RISING);   //Configures interrupt 0 (pin 2 on the Arduino Uno) to run the function "Flow"
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Inp
  Serial.begin(9600);                 //Start Serial
}

// To run repeatedly
void loop() 
{
  delay(5000);

  GetFlowSpeed();
  GetWaterheight(); 
  CalculateFlood(_distanceToSurface);
  count = 0;   

  // Print in serial monitor
  Serial.println();
  Serial.print("flowSpeed: ");           
  Serial.println(_flowSpeed); 
  Serial.print("distance: ");          
  Serial.println(_distanceToSurface);
  Serial.print("flood: ");
  Serial.println(_flood);
}

// To calculate the current waterheight
void GetWaterheight()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  _distanceToSurface = duration * 0.034 / 2;
  return _distanceToSurface;
}


// To measure the current flowspeed
void GetFlowSpeed()
{
  _flowSpeed = (count * 2.25);         
  _flowSpeed = _flowSpeed * 60;         
  _flowSpeed = _flowSpeed / 1000;       
  return _flowSpeed; 
}

// To check or there is a flood at this moment
void CalculateFlood(float currentHeight)
{
  // lijst bouwen met daarin max 3 elementen, hierop gemiddelde berekene
  // en deze de uitslag van de bool laten bepalen. 
  float avg = currentHeight;

  if(avg<5)
  {
    _flood = true;
  }
  else
  {
    _flood = false;
  }
  return _flood;
}


void Flow()
{
   count++; //Every time this function is called, increment "count" by 1
}f
