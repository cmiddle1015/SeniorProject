int A = 52; 
int B = 42; 
int out = 38; 

//22
//24
//8

//6
//7
//8

//52
//42
//38

int buttonStatus1 = 0; 
int buttonStatus2 = 0; 
int dOutStatus = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(out, OUTPUT);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
}

void loop() {
  delay(100);
  Serial.print("A : ");
  Serial.println(buttonStatus1);
  Serial.print("B : ");
  Serial.println(buttonStatus2);
  Serial.print("OUT : ");
  Serial.println(dOutStatus);
  
  buttonStatus1 = digitalRead(A);
  buttonStatus2 = digitalRead(B);
  if (buttonStatus1 == HIGH && buttonStatus2 == HIGH ) { 
      digitalWrite(out, HIGH);
    }
    else 
    {
      digitalWrite(out, LOW);
    }
}
