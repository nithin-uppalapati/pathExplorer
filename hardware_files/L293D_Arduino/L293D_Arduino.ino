////L293D
////Motor A
//const int motorPin1  = 5;  // Pin 14 of L293
//const int motorPin2  = 6;  // Pin 10 of L293
////Motor B
//const int motorPin3  = 10; // Pin  7 of L293
//const int motorPin4  = 9;  // Pin  2 of L293
//
////This will run only one time.
//void setup() {
//
//  //Set pins as outputs
//  pinMode(motorPin1, OUTPUT);
//  pinMode(motorPin2, OUTPUT);
//  pinMode(motorPin3, OUTPUT);
//  pinMode(motorPin4, OUTPUT);
//
//  //Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4
//
//  //This code  will turn Motor A clockwise for 2 sec.
//  //    digitalWrite(motorPin1, HIGH);
//  //    digitalWrite(motorPin2, LOW);
//  //    digitalWrite(motorPin3, LOW);
//  //    digitalWrite(motorPin4, LOW);
//  //    delay(1000);
//  //    //This code will turn Motor A counter-clockwise for 2 sec.
//  //    digitalWrite(motorPin1, LOW);
//  //    digitalWrite(motorPin2, HIGH);
//  //    digitalWrite(motorPin3, LOW);
//  //    digitalWrite(motorPin4, LOW);
//  //    delay(1000);
//  //
//  //    //This code will turn Motor B clockwise for 2 sec.
//  //    digitalWrite(motorPin1, LOW);
//  //    digitalWrite(motorPin2, LOW);
//  //    digitalWrite(motorPin3, HIGH);
//  //    digitalWrite(motorPin4, LOW);
//  //    delay(1000);
//  //    //This code will turn Motor B counter-clockwise for 2 sec.
//  //    digitalWrite(motorPin1, LOW);
//  //    digitalWrite(motorPin2, LOW);
//  //    digitalWrite(motorPin3, LOW);
//  //    digitalWrite(motorPin4, HIGH);
//  //    delay(1000);
//  //
//  //    //And this code will stop motors
//  //    digitalWrite(motorPin1, LOW);
//  //    digitalWrite(motorPin2, LOW);
//  //    digitalWrite(motorPin3, LOW);
//  //    digitalWrite(motorPin4, LOW);
//  //
//}
//
//
//void loop() {
//  digitalWrite(motorPin1, HIGH);
//  digitalWrite(motorPin2, LOW);
//  digitalWrite(motorPin3, LOW);
//  digitalWrite(motorPin4, LOW);
//  delay(1000);
//  //This code will turn Motor A counter-clockwise for 2 sec.
//  digitalWrite(motorPin1, LOW);
//  digitalWrite(motorPin2, HIGH);
//  digitalWrite(motorPin3, LOW);
//  digitalWrite(motorPin4, LOW);
//  delay(1000);
//
//  //This code will turn Motor B clockwise for 2 sec.
//  digitalWrite(motorPin1, LOW);
//  digitalWrite(motorPin2, LOW);
//  digitalWrite(motorPin3, HIGH);
//  digitalWrite(motorPin4, LOW);
//  delay(1000);
//  //This code will turn Motor B counter-clockwise for 2 sec.
//  digitalWrite(motorPin1, LOW);
//  digitalWrite(motorPin2, LOW);
//  digitalWrite(motorPin3, LOW);
//  digitalWrite(motorPin4, HIGH);
//  delay(1000);
//
//  //And this code will stop motors
//  digitalWrite(motorPin1, LOW);
//  digitalWrite(motorPin2, LOW);
//  digitalWrite(motorPin3, LOW);
//  digitalWrite(motorPin4, LOW);
//
//
//}





//------------------

// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  directionControl();
  delay(1000);
  spin();
  delay(1000);
//  speedControl();
//  delay(1000);
}

// This function lets you control spinning direction of motors
void directionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2000);
  
  // Now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);
  
  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// This function lets you control speed of the motors
void speedControl() {
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  // Accelerate from zero to maximum speed
  for (int i = 50; i < 256; i++) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  
  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 50; --i) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  
  // Now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void spin() {
    // Motors run in opposite directions
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2000);
}
// Nithin
