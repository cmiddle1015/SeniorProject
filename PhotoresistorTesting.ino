// THIS WORKS DON'T CHANGE IT
/* Photocell controlling lamp program */
// Constants
#define DELAY 500 // Delay between two measurements in ms
#define MIN_RAW 0 // Analog minimum value
#define MAX_RAW 500 // Analog maximum value
#define MIN_CMD 0 // Digital minimum value
#define MAX_CMD 255 // Digital maximum value

// Parameters
const int sensorPin = A0; // Pin connected to sensor
const int ledPin = 26; // Pin connected to sensor

//Variables
int sensorVal; // Analog value from the sensor
int cmd; //Led command value

//Main
void setup(void) {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}

void loop(void) {
  sensorVal = analogRead(sensorPin);
  //cmd=sensorToLed(sensorVal);
  //analogWrite(ledPin,cmd);
  delay(DELAY);
  Serial.print("Sensor : ");
  Serial.println(sensorVal);
  //Serial.print("Command : ");
  //Serial.println(cmd);

  if(sensorVal >= 200)
  {
    digitalWrite(ledPin, HIGH);
  } 
  else
  {
    digitalWrite(ledPin, LOW);
  }
}

//Functions
//int sensorToLed(int raw){
  // The LED shine when the room is dark
  //int val = map(sensorVal, 0, 500, 255, 0);
  //val=max(val,MIN_CMD);
  //val=min(val,MAX_CMD);
  //return val;
//}
