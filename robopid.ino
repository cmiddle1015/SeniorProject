//motors
//motor A
#define enA 9
#define in1 28
#define in2 30

//motor B
#define enB 10
#define in3 32
#define in4 34

//ultrasonic
int trigPinLeft = 2;
int echoPinLeft = 12;
int trigPinRight = 4;
int echoPinRight = 13;

long durationLeft;
long durationRight;
int distanceLeft;
int distanceRight;

//Time control
float time, timePrev;
float period = 50; //dt

//Gains
float kp = 5;
float ki = 0;
float kd = 10;
float setpoint_d_r = 21.5;
float setpoint_d_l = 21.5;

float error_r, prev_error_r, error_l, prev_error_l;
float PID_p_r, PID_i_r, PID_d_r, PID_total_r;
float PID_p_l, PID_i_l, PID_d_l, PID_total_l;

float thedistance_r = 0;
float thedistance_l = 0;

void setup() {
  
  Serial.begin(9600);

    //motors
  //motor A
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  //motor B
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //if input 1 = LOW and 2 = HIGH, then forward
  //Opposite is backwards
  //if both HIGH or LOW, stop
  //Default is stopped
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);

  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  
}

void loop() {
  
time = millis();

//l
if (time+period>=timePrev)
{
    thedistance_l = checkLeft();   // figure this out as well (thedistance(); here actually)
    error_l = setpoint_d_l - thedistance_l;
    PID_p_l = kp * error_l;
    float difference_l = error_l - prev_error_l;     
    PID_d_l = kd*((error_l - prev_error_l)/period);
    PID_total_l = PID_p_l + PID_i_l + PID_d_l;  
    PID_total_l = map(PID_total_l, 20, 23, 400, 350); // map this to PWM value instead of angle    = dist to pwm
    //what I mean is, map the max total distance - size of robot (based on the game walls, cm) to PWM value (0 to 1023) using the above function (map())
    PID_total_l = constrain(PID_total_l,350,400);

}
//r
if (time+period>=timePrev)
{
    thedistance_r = checkRight();   
    error_r = setpoint_d_r - thedistance_r;   
    PID_p_r = kp * error_r;
    float difference_r = error_r - prev_error_r;     
    PID_d_r = kd*((error_r - prev_error_r)/period);
    PID_total_r = PID_p_r + PID_i_r + PID_d_r;  
    PID_total_r = map(PID_total_r, 20, 23, 400, 350); //cm to pwm value
    //This ^^^ will return a PWM value (type case to int btw). Just give that to your analogWrite for motor pwm and that's it :)
    PID_total_r = constrain(PID_total_r,350,400);

}
moveForward(PID_total_l, PID_total_r);
timePrev = time;

}

float checkLeft()
{
    // Clears the trigPin
  digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLeft, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationLeft = pulseIn(echoPinLeft, HIGH);
  // Calculating distance
  distanceLeft = durationLeft * 0.034 / 2;

  Serial.print("Left Distance,");
  Serial.print(distanceLeft);
  return distanceLeft;
}

float checkRight()
{
  
    // Clears the trigPin
  digitalWrite(trigPinRight, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRight, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationRight = pulseIn(echoPinRight, HIGH);
  // Calculating distance
  distanceRight = durationRight * 0.034 / 2;

  Serial.print(",Right Distance,");
  Serial.print(distanceRight);
  return distanceRight;
}

void moveForward(float theLeftPWM, float theRightPWM)
{
    //set dir
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    analogWrite(enA, theLeftPWM);
    analogWrite(enB, theRightPWM);

    //Serial.print("Left PWM,");
    //Serial.println(theLeftPWM);
    //Serial.print("Right PWM,");
    //Serial.println(theRightPWM);
    Serial.println("");
}
