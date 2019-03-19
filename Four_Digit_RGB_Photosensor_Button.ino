//Some code for an Arduino Uno to exercise a four digit 7 segment LED display, a three color LED, 
//and take some inputs from a photo diode and a couple buttons.
//
//Spaghetti code by Douglas L. Van Bossuyt.  Heavily borrowed elements from the Elegoo Super Starter Kit and 
//elsewhere online as I needed to figure things out.

#include <Bounce2.h>


int latch=9;  //74HC595  pin 9 STCP
int clock=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS

const int DIGIT_1 = 7;
const int DIGIT_2 = 4;
const int DIGIT_3 = 12;
const int DIGIT_4 = 11;

const int BUTTON_1 = 2;
const int BUTTON_2 = 3;



// Instantiate a Bounce object
Bounce debouncer1 = Bounce(); 

// Instantiate another Bounce object
Bounce debouncer2 = Bounce(); 




int lightPin = 0;



unsigned char table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};



const int BLUE = A1;
const int GREEN = 5;
const int RED = 6;

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
  
  pinMode(DIGIT_1,OUTPUT);
  pinMode(DIGIT_2,OUTPUT);
  pinMode(DIGIT_3,OUTPUT);
  pinMode(DIGIT_4,OUTPUT);
  

  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  

 
  Serial.begin(9600);


  // Setup the first button with an internal pull-up :
  pinMode(BUTTON_1,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer1.attach(BUTTON_1);
  debouncer1.interval(5); // interval in ms
  
   // Setup the second button with an internal pull-up :
  pinMode(BUTTON_2,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer2.attach(BUTTON_2);
  debouncer2.interval(5); // interval in ms

  
}


void Display(int Digit, unsigned char num)
{

  digitalWrite(DIGIT_1,HIGH);
  digitalWrite(DIGIT_2,HIGH);
  digitalWrite(DIGIT_3,HIGH);
  digitalWrite(DIGIT_4,HIGH);
  
  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,table[num]);
  digitalWrite(latch,HIGH);

  
  if (Digit == 1){
    digitalWrite(DIGIT_1,LOW);
    delay(1);
  }
  else if (Digit == 2){
    digitalWrite(DIGIT_2,LOW);
    delay(1);
  }
  else if (Digit == 3){
    digitalWrite(DIGIT_3,LOW);
    delay(1);
  }
  else if (Digit == 4){
    digitalWrite(DIGIT_4,LOW);
    delay(1);
  }
  else {
    Serial.print("Error in writing digit. Variable Digit is: ");
    Serial.println(Digit);
  }
}

void Display2(int One, int Two, int Three, int Four, unsigned char num){
  
}

void ReadOut(int One, int Two, int Three, int Four){
  Display(1,One);
  Display(2,Two);
  Display(3,Three);
  Display(4,Four);
}

void RGB(int red, int green, int blue, int DELAY){
    analogWrite(RED, red);
    analogWrite(GREEN, green);   
    analogWrite(BLUE, blue);
    delay(DELAY);
}

void BLINK_ON(){  
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
}

void BLINK_OFF(){
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
}







void loop() {

  static int Program;
  static int DelayInterval = 500;
  static int fadeDelay = 50;
  static int buttonHold = 1000;
  static unsigned long Timer = 0;
  static int buttonCount = 0;
  static unsigned long buttonTimer = 0;
  static int countDelay = 10;
 
  // Update the Bounce instances :
  debouncer1.update();
  debouncer2.update();

  // Get the updated value :
  int value1 = debouncer1.read();
  int value2 = debouncer2.read();

  int currentTime = millis();

  if(Program == 0){
    if((currentTime < (DelayInterval + Timer)) && digitalRead(RED) == LOW){
      BLINK_ON();
      Timer = currentTime;
    }
    else if((currentTime >= (DelayInterval + Timer)) && (currentTime < ((DelayInterval * 2) + Timer))){
      BLINK_OFF();
    }
    else if(currentTime >= ((DelayInterval * 2) + Timer)){
      Timer = currentTime;
    }
    else{
      //Serial.println("Error in timer");
    }


    if (value2 == HIGH && buttonCount != 0){
      Program = buttonCount;
      Serial.print("buttonCount == ");
      Serial.println(buttonCount);
      buttonCount = 0;
      Serial.print("Program == ");
      Serial.println(Program);
    }
    else if (value2 == HIGH && buttonCount == 0){
      
    }
    else if (value2 == LOW){
      if (value1 == LOW && (currentTime > buttonTimer + buttonHold)){
        buttonCount++;
        buttonTimer = currentTime;
      }
    }
    else{
      Serial.println("Error in counting buttons");
    }

    
  }

  else if(Program == 1){
    if (value1 == LOW) {
       BLINK_ON();     
    }
    else {
       BLINK_OFF();      
    }
    if (value2 == LOW){
      Program = 0;
    }
  }

  else if(Program == 2){
      BLINK_OFF();
    for(int Fourth = 0; Fourth < 10; Fourth ++){
      for(int Third = 0; Third < 10; Third ++){
        for(int Second = 0; Second < 10; Second ++){
          for(int First = 0; First < 10; First ++){ 
            for(int i = 0; i < countDelay; i ++){
              ReadOut(First,Second,Third,Fourth);
                if (digitalRead(BUTTON_2) == LOW) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 10;
                  Fourth = 10;
                  Third = 10;
                  Second = 10;
                  First = 10;
                }
            }
          }
  
        }
      }
    }
   Program = 0;
   ReadOut(0,0,0,0);
  }

  else if (Program == 3){
      BLINK_OFF();
    int redValue = 0;
    int greenValue = 0;
    int blueValue = 0;

    for(redValue = 0; redValue < 254; redValue++){
      RGB(redValue,greenValue,blueValue,fadeDelay);
                if (digitalRead(BUTTON_2) == LOW) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  redValue = 254;
                  blueValue = 254;
                  greenValue = 254;
                }
    }

    for(greenValue = 0; greenValue < 254; greenValue++){
      RGB(redValue,greenValue,blueValue,fadeDelay);
                if (digitalRead(BUTTON_2) == LOW) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  redValue = 254;
                  blueValue = 254;
                  greenValue = 254;
                }
    }

    for(blueValue = 0; blueValue < 254; blueValue++){
      RGB(redValue,greenValue,blueValue,fadeDelay); 
                if (digitalRead(BUTTON_2) == LOW) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  redValue = 254;
                  blueValue = 254;
                  greenValue = 254;
                }    
    }

        for(redValue; redValue > 0; redValue--){
      RGB(redValue,greenValue,blueValue,fadeDelay);
                if (digitalRead(BUTTON_2) == LOW) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  redValue = 0;
                  blueValue = 0;
                  greenValue = 0;
                }
    }

    for(greenValue; greenValue > 0; greenValue--){
      RGB(redValue,greenValue,blueValue,fadeDelay);
                if (digitalRead(BUTTON_2) == LOW) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                   redValue = 0;
                  blueValue = 0;
                  greenValue = 0;
                }
    }

    for(blueValue; blueValue > 0; blueValue--){
      RGB(redValue,greenValue,blueValue,fadeDelay); 
                if (digitalRead(BUTTON_2) == LOW) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  redValue = 0;
                  blueValue = 0;
                  greenValue = 0;
                } 
    }

  
  }

  else if (Program == 4){
    BLINK_OFF();
    int First = 0;
    int Second = 0;
    int Third = 0;
    int Fourth = 0;
    int reading  = analogRead(lightPin);
    First = (reading%10);
    Second = ((reading/10)%10);
    Third = ((reading/100)%10);
    Fourth = (reading/1000);
     
    ReadOut(First,Second,Third,Fourth); 
                if (digitalRead(BUTTON_2) == LOW) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                }
  }

  else {
    Serial.println("Error in program selection");
    Program = 0;
    ReadOut(0,0,0,0);
  }
}
