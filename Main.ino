

//PR
bool ledIsOn = false; //tells Fred when light is on
const int readPRVal = A0; //resistance value measured from photoresistor
const int PROutput = 3; //will be the output of the light detection system
//TODO: make this call another function ^^^

int PRVal; //reads photoresistor raw value
int timerCount = 0; //for test timing using baude rate
int wallsHit = 0; //tells Fred how many walls he has encountered

/*
//ultrasonic
const int trigPin = 11;
const int echoPin = 12;
long duration;
int distance;
bool isAtWall = false;
*/

//limit switches
bool isAtWall = false;
int A = 22; 
int B = 24; 
int out = 8; 
int buttonStatus1 = 0; 
int buttonStatus2 = 0; 
int dOutStatus = 0;

void setup()
{
  Serial.begin(9600);
  
  //PR
  pinMode(PROutput, OUTPUT);
  
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

  /*
  //Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  */

  //limit switches
  pinMode(out, OUTPUT);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  
}

void loop()
{ 
  ledIsOn = checkLEDOn();
  if(ledIsOn)
  {
    while(true)
    {
      isAtWall = checkIsAtWall();
      if(isAtWall)
      {
        //increment wall count
        wallsHit++;
        if(wallsHit = 1)
        {
          leftTurnAction1();
        }
        else if(wallsHit = 2)
        {
          leftTurnAction2();
        }
        else if(wallsHit = 3)
        {
          leftTurnAction3();
        }
        
      }
      
      else
      {
        moveForward();
      }
    }
  } 
  }

//Functions:

//what to do when hit first wall
void leftTurnAction1()
{
  //stop
  fredStop();
  delay(1000);

  //back up some distance (test this)
  moveBackward();
  delay(1000);

  //turn 90 degrees left (CCW)
  turnLeft();
  delay(1000);

  //move forward until next wall is encountered
  moveForward();
}

//what to do when hit second wall
void leftTurnAction2()
{
  //stop
  fredStop();
  delay(1000);

  //back up some distance (test this)
  moveBackward();
  delay(1000);

  //turn 90 degrees left (CCW)
  turnLeft();
  delay(1000);

  //move forward until next wall is encountered
  moveForward();
}

//what to do when hit third wall
void leftTurnAction3()
{
  //stop
  fredStop();
  delay(1000);

  //back up some distance (test this)
  moveBackward();
  delay(1000);

  //turn 90 degrees left (CCW)
  turnLeft();
  delay(1000);

  //move forward until next wall is encountered
  fredStop();
}

//reads PR value. If above threshold, return true (sets value of "ledIsOn")
bool checkLEDOn()
{
  PRVal = analogRead(readPRVal);
  
  Serial.println(PRVal);

  if(PRVal >= 200)
  {
    digitalWrite(PROutput, HIGH);
    return true;
  }
  else
  {
    digitalWrite(PROutput, LOW);
    return false;
  }
}

//check if against wall w/ limit switches
bool checkIsAtWall()
{
  /*
  Serial.print("A : ");
  Serial.println(buttonStatus1);
  Serial.print("B : ");
  Serial.println(buttonStatus2);
  Serial.print("OUT : ");
  Serial.println(dOutStatus);
  */
  
  buttonStatus1 = digitalRead(A);
  buttonStatus2 = digitalRead(B);
  if (buttonStatus1 == HIGH && buttonStatus2 == HIGH ) { 
      digitalWrite(out, HIGH);
      return true;
    }
    else 
    {
      digitalWrite(out, LOW);
      return false;
    }
}

//start movement stuff
//no control for now. just have it move forward until something else happens
void moveForward()
{
    //set dir
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    
    analogWrite(enA, 1000);
    analogWrite(enB, 1000);
}

/*
//bool to tell system when Fred is close to a wall
//checks continuously with lidar (at baude rate)
//Executes some protocol when this happens, keeps track of how many walls Fred has encoutered
bool checkIsAtWall()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  //distance needs to be <= 5 to work
  if(distance <= 7) //is x distance from wall (test this number), then activate some protocol
  {
    //leftTurnAction();
    return true;
    leftTurnAction();
  }
  else
  {
    return false;
    moveForward();
  }
}
*/



//stop motors
void fredStop()
{
     //set dir
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    analogWrite(enA, 1000);
    analogWrite(enB, 1000);
}

//stop motors
void moveBackward()
{
  
    //set dir
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    analogWrite(enA, 1000);
    analogWrite(enB, 1000);
  
}

//turn right (CW looking down)
void turnRight()
{
    //set dir
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    analogWrite(enA, 1000);
    analogWrite(enB, 1000);
}

//turn left (CCW looking down)
void turnLeft()
{
    //set dir
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    
    analogWrite(enA, 1000);
    analogWrite(enB, 1000);
}
