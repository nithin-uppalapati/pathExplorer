//------------------
#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;


SoftwareSerial blu(12,11); // TX,RX

//--------

// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

// ultrasonic
const int TriggerPin = 13;      //Trig pin - 8 / 12
const int EchoPin = 10;          //Echo pin - 9 / 11

//others - debug
int ld =2;
//

//float dat[] = { 375.7286254732264, 86.69880772051638, 391.28761799985443, 87.6447543230885, 362.00138121283464 };
float dat[] = {300,30,300,-30,300};

char main_message;
char incomingByte;

int draw[100];
int speed_val = 180;

// FLAGS:-----------
bool obstcl = true;
bool man_ctrl = false;
bool draw_ctrl = false;
//------------------

void setup() {
  Serial.begin(9600); blu.begin(9600);
  
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
  Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
  delay(500);
  }
  
//  mpu.calibrateGyro();
  mpu.setThreshold(3);
  
  pinMode(enA, OUTPUT); pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);
  
  pinMode(TriggerPin,OUTPUT); pinMode(EchoPin,INPUT);      
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, LOW);
  
  delay(5000);
}

void loop() {

String message;
if(blu.available()> 0){ 
  message = blu.readString();
  }

//if (blu.available() > 0) {
//  main_message = blu.read();
//  Serial.print("main message: ");Serial.println(main_message);
//}
//-----

if(message[0] == 'S'){
  String spd = message.substring(1);
    Serial.print("spd: ");Serial.println(spd);
    speed_val = spd.toInt();
}


man_ctrl = (message[0] == 'M');
if(message[0] == 'M'){
  Serial.print("man_ctrl: ");Serial.println(man_ctrl);
  manual_control(man_ctrl);
}


draw_ctrl = (message[0] == 'P');
if(message[0] == 'P'){
  Serial.print("draw_ctrl: ");Serial.println(draw_ctrl);
  path_calctor(draw_ctrl);
}


if ((message[0] == 'Q')){
  master_stop();
}

//  speedControl();
//  delay(1000);
//Serial.println("end of loop");
}

void path_executor(int i, int draw){
  Serial.println("Inside path_executor() function");
//  for (int k=0; k<cnt; k++){
//    Serial.print("draw[");Serial.print(k);Serial.print("] : ");Serial.println(draw[k]);
//  }

//  for(int i=0; i<cnt ; i++) {
    if (i%2 == 0){
      strainght_line(draw);//[i]
      Serial.print("Executed Straight Line no. :");Serial.println(i/2);
    }
    delay(500);
    if (i%2 == 1) {
      turn_angle(draw);//[i]
      Serial.print("Executed Angle no. :");Serial.println(1+i/2);
    }
    delay(500);
//  }
  
}

void path_calctor(bool draw_ctrl){ // this is pending
  if(draw_ctrl){
//    Serial.print("draw_ctrl in path_calctor: ");Serial.println(draw_ctrl);
  }
int cntr=0;

while(draw_ctrl){
  String message_p;
//  Serial.println("in While loop (in path_cal)");
  if(blu.available()> 0){ 
//    Serial.println("in if cond (in path_cal) loop");
    message_p = blu.readString();
    Serial.print("Bluetooth Input Data: ");Serial.println(message_p);
    if(message_p[0] != 'P'){
      master_stop();
      break;
    }
    String z = message_p.substring(1);
//    Serial.print("z: ");Serial.println(z);
    int y = z.toInt();
//    Serial.print("draw[");Serial.print(cntr);Serial.print("]: ");Serial.println(y);
//    draw[cntr] = y;
    check_obstacle();
    if(obstcl){
      path_executor(cntr, y);
      blu.println(cntr);
    }
    if(!obstcl){ 
      Serial.println("Obstacle Detected!! and sent message back to the APP");
      int zz = -1;
      blu.println(zz);
      break;
     }
    cntr+=1;
  }
}
//if(draw_ctrl){
//  path_executor(cntr, draw);
//}
}

void manual_control(bool man_ctrl){
  if(man_ctrl){
    Serial.println("in manual_control function");
  }
while(man_ctrl){
  String message_m;
  if(blu.available()> 0){ 
    message_m = blu.readString();
    if(message_m[0] == 'Q'){
      master_stop();
      break;
    }
    incomingByte = message_m[1];
//    check_obstacle();
  }
  check_obstacle();
  if (!obstcl){
Serial.println("Obstacle Detected!!"); 
  }
    if(incomingByte == 'F' && obstcl){
      analogWrite(enA, speed_val);analogWrite(enB, speed_val);
      digitalWrite(in1, LOW);digitalWrite(in2, HIGH);digitalWrite(in3, LOW);digitalWrite(in4, HIGH);
//      Serial.println("FORWARD");
    }
    if(incomingByte == 'R'){
      analogWrite(enA, speed_val);analogWrite(enB, speed_val);
      digitalWrite(in1, LOW); digitalWrite(in2, HIGH); digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
//      Serial.println("RIGHT");
    }
    if(incomingByte == 'L'){
      analogWrite(enA, speed_val);analogWrite(enB, speed_val);
      digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
//      Serial.println("LEFT");
    }
    if(incomingByte == 'B'){
      analogWrite(enA, speed_val);analogWrite(enB, speed_val);
      digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
//      Serial.println("BACK");
    }
    if(incomingByte == 'C'){
    master_stop();
//    Serial.println("STOP");
    }
}
}

void check_obstacle(){
//  Serial.println("in check_obstacle function ");
  long sonic_dist = 0;
  for(int i=0;i<2;i++){
  digitalWrite(TriggerPin, LOW);  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH); delayMicroseconds(10);digitalWrite(TriggerPin, LOW);          
  sonic_dist += ((pulseIn(EchoPin,HIGH) /2.9) / 20); 
  }
 sonic_dist = sonic_dist/2.0;   // can remove this division and make change to below inequality
//Serial.print("Free Range (cms.): ");Serial.println(sonic_dist);
if(sonic_dist<10){
  digitalWrite(ld,HIGH);
  master_stop();
  obstcl = false;
}
else{
  digitalWrite(ld,LOW);
  obstcl = true;
}
}

void master_stop(){
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    digitalWrite(in1, LOW); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, LOW);
//    
}
//void move_car(int spd, bool a, bool b, bool c, bool d){
//  
//}

void strainght_line(float line){   /* line == distance length in meters */
  check_obstacle();
  if(obstcl){
  Serial.println("in strainght_line");
  analogWrite(enA, speed_val);
  analogWrite(enB, speed_val);
  check_obstacle();
//  150 is very low
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  delay(line*10);
  
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  }
}

void turn_angle(float angl){
//  counter clk wise yaw will decrease

  Serial.println("in turn_angle");

  float ref_yaw = 0;
  bool turn_flag = true;
  
  timer = millis();
  Vector norm = mpu.readNormalizeGyro();
//  roll = roll + norm.XAxis * timeStep;
//yaw = yaw + norm.ZAxis * timeStep; original equations

  yaw = yaw + norm.XAxis * timeStep;          // changed from Z to X
  ref_yaw = yaw;
  delay((timeStep*1000) - (millis() - timer));
  
  analogWrite(enA, speed_val);
  analogWrite(enB, speed_val);
  check_obstacle();
  if (angl>0 && obstcl) {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH); digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  Serial.println("in angl>0");
//  delay(1800*angl/360.0);
  }
  
  if (angl<0 && obstcl) {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  Serial.println("in angl<0");
//  delay(1900*angl*(-1)/360.0);
  }
  
//  Serial.println("before while loop");

  while(turn_flag && obstcl) {
//      Serial.println("in while loop");
      
      timer = millis();
      Vector norm = mpu.readNormalizeGyro();    // see if you can globally declare it
      yaw = yaw + norm.XAxis * timeStep;          // changed from Z to X
      delay((timeStep*1000) - (millis() - timer));
//      Serial.print("ref_yaw : ");Serial.print(ref_yaw);Serial.print("    ");
      Serial.print("yaw : "); Serial.println(yaw);
      
      if ( abs(ref_yaw - yaw) > abs(angl) ) {
      Serial.print("Angle to be turned: "); Serial.println(abs(ref_yaw - yaw));
      turn_flag = false;
      Serial.print("Angle Turned Successfully!");
      analogWrite(enA, 0);
      analogWrite(enB, 0);
      break;
    }
  }
}


void batter_indic(){
  analogWrite(enA, 0);
  analogWrite(enB, 0);
   
  float old_meas, new_meas, percent;
  int sensorValue, i;
  
  old_meas =0;
  
  for (i=0; i<200; i++){
    sensorValue = analogRead(A0);
    new_meas = sensorValue * (5.0 / 1023.0);
    old_meas+= new_meas;
  }
  old_meas = old_meas/200.0;
  //Serial.println(old_meas/200.0,3);
  delay(50);
  
  if (old_meas>=3.6){
    percent = 40 + ((old_meas - 3.6)/(0.525) ) * 60.0; // (4.125 - 3.6)
    return percent;
  }
  else if (old_meas>=3.5){
    percent = 20 + ((old_meas - 3.5)/(0.1) ) * 20.0; // (4.125 - 3.6)
    return percent;
  }
  else if (old_meas<3.5){
    percent = ((old_meas - 3)/(0.5) ) * 20.0; // (4.125 - 3.6)
    return percent;
  }

}




// Nithin ----- END OF CODE



// Below code is for reference / rough

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
