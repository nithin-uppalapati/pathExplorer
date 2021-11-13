//------------------

// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;
//float dat[] = { 375.7286254732264, 86.69880772051638, 391.28761799985443, 87.6447543230885, 362.00138121283464 };
//float dat[] = {311.0064308016797, -89.58790836505419, 367.03405836516043, -86.72006661866685, 324.8153321504389, -88.2925926437025, 199.00753754569197, 344.13858974056325, 194.00257730246784};
//float dat[] ={ 285.08595195133705, -140.29600054676277, 345.3071096864356, 146.56338019592275, 295.06101064017264 };

//float dat[] = {408.9254210733297, 90.20027691266343, 411.3635861376162, 83.8145997630149, 394.2892339387421, 90, 389.1015291668744};
//float dat2[] = {408.9254210733297, -90.20027691266343, 411.3635861376162, -83.8145997630149, 394.2892339387421, -90, 389.1015291668744};

float dat[] = {300,90,300,90,300,90,300};
//float dat2[] = {0,180,0};
float dat3[] = {300,-90,300,-90,300,-90,300};


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
  
  int i=0;
  for(i=0; i<7 ; i++) {
    if (i%2 == 0){
      strainght_line(dat[i]);
      
    }
    if (i%2 == 1) {
      turn_angle(dat[i]);
    }
  }
  delay(5000);
  
  turn_angle(180);

  delay(5000);
  
  for(i=0; i<7 ; i++) {
    if (i%2 == 0){
      strainght_line(dat3[i]);
    }
    if (i%2 == 1) {
      turn_angle(dat3[i]);
    }
  }

delay(1000000);
  
//  directionControl();
//  delay(1000);

//  spin();
//  delay(15000);
  
//  speedControl();
//  delay(1000);
}


void strainght_line(float line){
  analogWrite(enA, 200);
  analogWrite(enB, 200);
//  150 is very low
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(line*10);
  
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void turn_angle(float angl){
  analogWrite(enA, 200);
  analogWrite(enB, 200);

  if (angl>0) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2300*angl/360.0);
  }
  
  if (angl<0) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2300*angl*(-1)/360.0);
  }
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
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
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


//
void spin() {
    // Motors run in opposite directions
  analogWrite(enA, 190);
  analogWrite(enB, 190);

// counter clk wise  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(5000);
//  2300 --> 1 rotation

  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(3000);

  analogWrite(enA, 190);
  analogWrite(enB, 190);

//  clk wise
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(5000);
  
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(3000);

}

// Nithin
