#include <AccelStepper.h>
char buffer[16];  //maximum expected length
int len = 0;
int valueMovement;
int valueSpeed;
int valueAcceleration;
int pos = 0;
char receivedCommand;

// dir and pulse pin declaration for all stepper motors

// stepper_1
#define STEP_PIN_MOTOR_1 2
#define DIR_PIN_MOTOR_1 3

// stepper_2
#define STEP_PIN_MOTOR_2 4
#define DIR_PIN_MOTOR_2 5

// stepper_3
#define STEP_PIN_MOTOR_3 6
#define DIR_PIN_MOTOR_3 7

// stepper_4
#define STEP_PIN_MOTOR_4 8
#define DIR_PIN_MOTOR_4 9

// interface 1 = AccelStepper::FULL4WIRE
#define INTERFACE 1


// stepper_1
AccelStepper stepper1(INTERFACE, STEP_PIN_MOTOR_1, DIR_PIN_MOTOR_1);

// stepper_2
AccelStepper stepper2(INTERFACE, STEP_PIN_MOTOR_2, DIR_PIN_MOTOR_2);

// stepper_3
AccelStepper stepper3(INTERFACE, STEP_PIN_MOTOR_3, DIR_PIN_MOTOR_3);

// stepper_3
AccelStepper stepper4(INTERFACE, STEP_PIN_MOTOR_4, DIR_PIN_MOTOR_4);






void setup() {
  Serial.begin(115200);
  //pinMode(limitSw_1, INPUT);  //lim1
}
void loop() {
  //Serial.write('CHECK');
  //int limSw1 = digitalRead(limitSw_1);

  /**
  if(limSw1 == LOW){
    //stepper2.setCurrentPosition(0); // reset position
    Serial.println("STOP "); //print action 
    stepper2.stop(); //stop motor
    stepper2.disableOutputs(); //disable power
  }
  **/




  
  
  int posStepper_1 = {stepper1.currentPosition()};
  int posStepper_2 = {stepper2.currentPosition()};
  int posStepper_3 = {stepper3.currentPosition()};
  int posStepper_4  = {stepper4.currentPosition()};

  String posValues = String(posStepper_1) + ' ' + String(posStepper_2) + ' ' + String(posStepper_3) + ' ' + String(posStepper_4);
  Serial.print(posValues);
  Serial.print('\n');
  

  if (Serial.available() > 0) {
    int incomingByte = Serial.read();
    buffer[len++] = incomingByte;
    //
    // check for overflow
    //
    if (len >= 16) {
      // overflow, resetting
      len = 0;
    }
    //
    // check for newline (end of message)
    //
    if (incomingByte == '\n') {

      int n = sscanf(buffer, "%c %d %d %d", &receivedCommand, &valueMovement, &valueSpeed, &valueAcceleration);
      if (n == 4) {
        // valid message received, use values here..
        /**
        if(valueMovement < 1000){
          Serial.print(valueMovement);
        }
        **/
        
      } else {
        // parsing error, reject
        Serial.print("Rejected");
      }
      len = 0;  // reset buffer counter
    }
  }

  // Returning all stepper motors to homing position
  if(receivedCommand == 'h'){ 
    // stepper_1
    stepper1.setMaxSpeed(75);
    stepper1.setAcceleration(50);
    stepper1.runToNewPosition(0);

    // stepper_2
    stepper2.setMaxSpeed(75);
    stepper2.setAcceleration(50);
    stepper2.runToNewPosition(0);

    // stepper_3
    stepper3.setMaxSpeed(75);
    stepper3.setAcceleration(50);
    stepper3.runToNewPosition(0);

    // stepper_4
    stepper4.setMaxSpeed(75);
    stepper4.setAcceleration(50);
    stepper4.runToNewPosition(0);
  }

  if(valueMovement <= 1300){
    //movement of stepper1
    if(receivedCommand == 'o' && stepper1.distanceToGo() == 0){
      stepper1.setMaxSpeed(valueSpeed);
      stepper1.setAcceleration(valueAcceleration);
      stepper1.moveTo(valueMovement);
    }
    stepper1.run();

  //movement of stepper2
    if(receivedCommand == 'o' && stepper2.distanceToGo() == 0){
      stepper2.setMaxSpeed(valueSpeed);
      stepper2.setAcceleration(valueAcceleration);
      stepper2.moveTo(valueMovement);
    }
    stepper2.run();

  //movement of stepper2
    if(receivedCommand == 'o' && stepper3.distanceToGo() == 0){
      stepper3.setMaxSpeed(valueSpeed);
      stepper3.setAcceleration(valueAcceleration);
      stepper3.moveTo(valueMovement);
    }
    stepper3.run();

  //movement of stepper2
    if(receivedCommand == 'o' && stepper4.distanceToGo() == 0){
      stepper4.setMaxSpeed(valueSpeed);
      stepper4.setAcceleration(valueAcceleration);
      stepper4.moveTo(valueMovement);
    }
    stepper4.run();
  }
  
}