#include <Joystick.h>
#include <Encoder.h>

//The following command simply states what is included in the joystick we're making. We state how many buttons it has and check boxes for including axis, etc.
//It is part of the joystick library. We just write stuf, the library does all the woodoo magic. 

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 
7, //Buttons, will be 7 when encoders are active
0, //Hat switches
false,false,false,    //No X, Y or Z axis
false,false,false,    //No Rx, Ry or Rz axis
false,false,          //No rudder, no throttle
false,false,false);   //No accelerator, brake or steering axis

//Now declaring all the pins
int push = 2;
int d = 3;
int c = 4;
int b = 5;
int a = 6;
int encA = 7; // use this for encoder
int encB = 8; // use this for encoder
long oldPosition  = 0; // use this for encoder position

Encoder myEnc(encA, encB); // Inicialize Encoder Rotary

void setup() {
    
//Setting up all button pins to digital inputs with pullup resistors, so that these pins are HIGH by default, and will go LOW if button is pressed, since the pin then will be direcly connected to ground. 
    pinMode(push,INPUT_PULLUP);
    pinMode(d,INPUT_PULLUP);
    pinMode(c,INPUT_PULLUP);
    pinMode(b,INPUT_PULLUP);
    pinMode(a,INPUT_PULLUP);
    
    Joystick.begin(); //Activating joystick library
    
}

void loop() {
        
//Reading the buttons
  int aButton = digitalRead(a);
  int bButton = digitalRead(b);
  int cButton = digitalRead(c);
  int dButton = digitalRead(d);
  int pushButton = digitalRead(push);
  
//Button logics and communicating to Joystick library

  if (aButton == LOW) { //Check if button is LOW
    Joystick.pressButton(0); //If true, joystick library tells computer that button is pressed
  } else {Joystick.releaseButton(0);} //If false, but button is not pressed
  
  if (bButton == LOW) {
    Joystick.pressButton(1); 
  } else {Joystick.releaseButton(1);} 
  
  if (cButton == LOW) {
    Joystick.pressButton(2); 
  } else {Joystick.releaseButton(2);} 
  
  if (dButton == LOW) {
    Joystick.pressButton(3); 
  } else {Joystick.releaseButton(3);} 
  
  if (pushButton == LOW && aButton == HIGH && bButton == HIGH && cButton == HIGH && dButton == HIGH) { //If pushButton is LOW, and none of the other buttons are low, it is a true activation. In any other case this button is not presed
    Joystick.pressButton(4); 
  } else {Joystick.releaseButton(4);} 

  
 long newPosition = myEnc.read(); // read de actual position of Rotary
 
  if (newPosition != oldPosition) { // if the position change, action to Joystick
    
    if ((oldPosition > newPosition) && (digitalRead(encB) == 1)) { // only if the Rotary is rotated to left
      Joystick.pressButton(6);
      delay(50);
      Joystick.releaseButton(6);
    }
    
    if ((oldPosition < newPosition) && (digitalRead(encA) == 1)) { // only if the Rotary is rotated to right
      Joystick.pressButton(5);
      delay(50);
      Joystick.releaseButton(5);
    }

    oldPosition = newPosition; // update the last position to new position for next rotate of Rotary
  }
  
}
