// Parameters
String _measurementId;
int _deviceId;
String _dateTime;
float _distanceToSurface;
float _formerDistanceToSurface;
float _waterheight;
double _flowSpeed;
bool _flood;


// Arduino setup
int flowPin = 2;    //This is the input pin on the Arduino
volatile int count; //This integer needs to be set as volatile to ensure it updates correctly during the interrupt process.
//int timeDelay = 5000;


// To run once:
void setup() {
  pinMode(flowPin, INPUT);            //Sets the pin as an input
  attachInterrupt(0, Flow, RISING);   //Configures interrupt 0 (pin 2 on the Arduino Uno) to run the function "Flow"
  Serial.begin(9600);                 //Start Serial
}


// To run repeatedly
void loop() 
{
  delay(5000);
  GetFlowSpeed();
  GetWaterheight(); 
  // Prints to display the values (CRTL+SHIF+'M')
  count = 0;
  Serial.println("Current flow speed: ");
  Serial.println(_flowSpeed);           
  Serial.println("Current height: ");
  Serial.println(_waterheight);
}


// To calculate the current waterheight
int GetWaterheight()
{
  _waterheight = random(100,200);
  return _waterheight;
}


// To measure the current flowspeed
double GetFlowSpeed()
{
  // Calculate/convert datat to L per minture
  _flowSpeed = (count * 2.25);         
  _flowSpeed = _flowSpeed * 60;         
  _flowSpeed = _flowSpeed / 1000;     
  //_flowSpeed = 111;  
  return _flowSpeed; 
}


void Flow()
{
   count++; //Every time this function is called, increment "count" by 1
}


// To check or there is a flood at this moment
void CalculateFlood()
{
  // als het gemiddelde van de vorige en de huidige meting hoger is dan de hoogte van X, dan is het een overstroming 
}
