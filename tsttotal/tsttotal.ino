#include <movingAvg.h> // https://github.com/JChristensen/movingAvg
movingAvg distance(3);  // Define the moving average object

// Parameters
int _measurementId;
int _deviceId;
float _distanceToSurface;
double _flowSpeed;
boolean _flood;


// Arduino setup
long duration;
int setTimeDelay = 5000; // To set intervalduration
const int flowPin = 2;   
const int trigPin = 8;
const int echoPin = 9;
volatile int count; // This integer needs to be set as volatile to ensure it updates correctly during the interrupt process.


// To run once:
void setup() 
{
  pinMode(flowPin, INPUT); // Sets the pin as an input
  attachInterrupt(0, Flow, RISING); // Configures interrupt 0 (pin 2 on the Arduino Uno) to run the function "Flow"
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
  distance.begin();       
}


// To run repeatedly
void loop() 
{
  delay(setTimeDelay); // Delay between repeating the process for 5 sec

  GetFlowSpeed();
  GetWaterheight(); 
  CalculateFlood();
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


// Calculate the current distance between sensors in centimeter
void GetWaterheight()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  _distanceToSurface = duration * 0.034 / 2; // Calculating the distance
  
  return _distanceToSurface;
}


// Measure the current flowspeed in ml/minute
void GetFlowSpeed()
{
  _flowSpeed = (count * 2.25);         
  _flowSpeed = _flowSpeed * 60;         
  _flowSpeed = _flowSpeed / 1000;   
      
  return _flowSpeed; 
}


// Check or there is a flood at this moment
void CalculateFlood()
{
  float avg = distance.reading(_distanceToSurface);
   Serial.println("TTTT"); // Print the moving average
  Serial.println(avg); // Print the moving average
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

// Every time this function is called, increment "count" by 1
void Flow()
{
   count++; 
}
