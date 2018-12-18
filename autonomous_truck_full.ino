//FULL CODE FOR SEMI AUTONOMOUS TRUCK V.1

//Library for using the Ultrasonic Sensor
#include <NewPing.h>

//Global variables for motor driver
int leftMotorForward = 5;
int leftMotorBack = 10;
int rightMotorForward = 6;
int rightMotorBack = 9;

//Global variables for line sensor
int lineSensor1 = 0;
int lineSensor2 = 0;
int lineSensor3 = 0;
int lineSensor4 = 0;

//Define pins used for echo and trigger and the max distance for the Ultrasonic Sensor
#define trig_pin 12
#define echo_pin 11
#define maximum_distance 500

//New Ping library sensor function constructor
NewPing sonar(trig_pin, echo_pin, maximum_distance);

//Setup function only runs once
//We setup our output and input pins here
void setup() {
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBack, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBack, OUTPUT);

  pinMode(lineSensor1, INPUT);
  pinMode(lineSensor2, INPUT);
  pinMode(lineSensor3, INPUT);
  pinMode(lineSensor4, INPUT);
}

//Loop function runs continuously and runs our program
void loop() {

  //Local variable for calling and receiving the result from the sonar ping function
  int distance = sonar.ping_in();

  //Read the Line Sensors, if HIGH (BLACK Line) or LOW (WHITE area)
  lineSensor1 = digitalRead(1);
  lineSensor2 = digitalRead(2);
  lineSensor3 = digitalRead(3);
  lineSensor4 = digitalRead(4);

  //STOP truck if the distance is greater than 5in. and less than or equal to 10in.
  if((distance > 5) && (distance <= 10)){

    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBack, HIGH);
    digitalWrite(rightMotorBack, HIGH);
  }

  //TURN truck LEFT if line sensor 1 or 2 see black line and sensors 3 and 4 don't
  else if((lineSensor1 == HIGH || lineSensor2 == HIGH) && (lineSensor3 == LOW && lineSensor4 == LOW)){

    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBack, HIGH);
    digitalWrite(rightMotorBack, LOW);
  }

  //TURN truck RIGHT if line sensor 3 or 4 see black line and sensors 1 and 2 don't
  else if ((lineSensor1 == LOW && lineSensor2 == LOW) && (lineSensor3 == HIGH || lineSensor4 == HIGH)){

    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBack, LOW);
    digitalWrite(rightMotorBack, HIGH);
    digitalWrite(rightMotorForward, LOW);
  }

  //STOP truck if all line sensors see black line
  else if (lineSensor1 == HIGH && lineSensor2 == HIGH && lineSensor3 == HIGH && lineSensor4 == HIGH){

    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBack, HIGH);
    digitalWrite(rightMotorBack, HIGH);
    digitalWrite(rightMotorForward, HIGH);
  }

  //GO FORWARD if the above conditions are not true
  else{

    //if((lineSensor4 == LOW && lineSensor3 == HIGH) || (lineSensor2 == HIGH && lineSensor1 == LOW))

    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBack, LOW);
    digitalWrite(leftMotorBack, LOW);
  }
}
