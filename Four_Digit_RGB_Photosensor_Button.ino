//Some code for an Arduino Uno to exercise a four digit 7 segment LED display, a three color LED, 
//and take some inputs from a photo diode and a couple buttons.
//
//Spaghetti code by Douglas L. Van Bossuyt.  Heavily borrowed elements from the Elegoo Super Starter Kit and 
//elsewhere online as I needed to figure things out.

#include <Bounce2.h>

/*
int latch=9;  //74HC595  pin 9 STCP
int clock=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS

const int DIGIT_1 = 7;
const int DIGIT_2 = 4;
const int DIGIT_3 = 12;
const int DIGIT_4 = 11;


*/
const int BUTTON_1 = 2;
const int BUTTON_2 = 3;



// Instantiate a Bounce object
Bounce debouncer1 = Bounce(); 

// Instantiate another Bounce object
Bounce debouncer2 = Bounce(); 



/*
int lightPin = 0;



unsigned char table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};

*/

const int BLUE = A1;
const int GREEN = 5;
const int RED = 6;

// Modifiable variables here:
int DelayInterval = 10;
int blinkDelay = 500;
unsigned long debounceDelay = 500;

/*
// Defined variables here:
int Button_Read_1 = 0;
int Button_Read_2 = 0;
int photoDiode = 0;
int blinkCounter = 0;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
*/

/*
int lastButton_1State = 1;
int lastButton_2State = 1;
int Button_1_Raw_State = 1;
int Button_2_Raw_State = 1;
int Count_Button_1 = 0;

*/
// playing around variables


unsigned long currentTime = 0;
int Program = 0;
byte Debounce = 100;
volatile unsigned long Button1 = 0;   

byte lastBlink = 0;


void setup() {
/*  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
  
  pinMode(DIGIT_1,OUTPUT);
  pinMode(DIGIT_2,OUTPUT);
  pinMode(DIGIT_3,OUTPUT);
  pinMode(DIGIT_4,OUTPUT);
  */

  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  
  //pinMode(BUTTON_1, INPUT_PULLUP);
  //pinMode(BUTTON_2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON_1), debounce_3, CHANGE);
 
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

/*
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
*/
void BLINK_ON(){  
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
  lastBlink = 0;
}

void BLINK_OFF(){
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  lastBlink = 1;
}

/*
int Buttons_Read(){
   Button_1_Raw_State = digitalRead(BUTTON_1);
   Button_2_Raw_State = digitalRead(BUTTON_2);
   if (Button_1_Raw_State == 0 && lastButton_1State == 1 && lastDebounceTime1 == 0){
    lastDebounceTime1 = millis();
    }
   if (Button_2_Raw_State == 0 && lastButton_2State == 1 && lastDebounceTime2 == 0){
    lastDebounceTime2 = millis();
   }
   if ((millis() - lastDebounceTime1) > debounceDelay && Button_1_Raw_State == 0){
      lastButton_1State = 0; 
      lastDebounceTime1 = 0;
   }
   if ((millis() - lastDebounceTime2) > debounceDelay && Button_2_Raw_State == 0){
      lastButton_2State = 0;
      lastDebounceTime2 = 0;
   }


  if (lastButton_1State == 0){
    
    ++Count_Button_1;
    lastButton_1State = 1;
    lastButton_2State = 1;
    ReadOut(0,0,0,Count_Button_1);
  }
  if (lastButton_2State == 0 && Count_Button_1 != 0){
    lastButton_1State = 1;
    lastButton_2State = 1;
    lastDebounceTime1 = 0;
    lastDebounceTime2 = 0;
    ReadOut(0,0,0,0);
    return Count_Button_1;
  }

  else if (Count_Button_1 == 0){
     ReadOut(0,0,0,0);
     return 0;
  }
  else {
    return 0;
  }
}
*/

void debounce_3(){
  Button1++;
}

/*
byte debounce_2(){

  static unsigned long FirstPressTimer;
  static unsigned long CurrentTime;
  static bool BeenPressed;

  CurrentTime = millis();

  Serial.println("debounce 2");

  Serial.print("FirstPressTimer == ");
  Serial.println(FirstPressTimer);
  Serial.print("CurrentTime == ");
  Serial.println(CurrentTime);
  Serial.print("BeenPressed == ");
  Serial.println(BeenPressed);
  
// first record when the button is pressed initially.  
// only record if enough time has passed since the last button press was sent.

  if (BeenPressed == 0) {
    FirstPressTimer = CurrentTime;
    BeenPressed = 1;
    Serial.println("First If");
  }

// then see if enough time has passed since the button was initially pressed.  but not too much time since the button has been pressed.
// pass that button has been pressed
// also record the time of when this was passed so we can check the next time to make sure enough time was passed.

  else if ((CurrentTime > (FirstPressTimer + Debounce)) && (BeenPressed == 1) ) { // (CurrentTime < ((WhenPassed + Debounce) * 3))) {
    Button1++;
    BeenPressed = 0;
    Serial.println("Second If");
  }
  else {
    Serial.println("else");
  }

}




//
//



/*

int debounce(){
  bool Button1CurrentState = digitalRead(BUTTON_1);

  static bool LastButton1State = HIGH;
  static unsigned long Button1Timer = 0;
  static bool NotPassedYet1 = true;
  static unsigned long iterations = 0;
  static unsigned long iterationsButtonHeld = 0;
  static float RatioButtonHeld = 0.75;

  Serial.println("debounce");

  Serial.print("Button1CurrentState == ");
  Serial.println(Button1CurrentState);
  Serial.print("LastButton1State == ");
  Serial.println(LastButton1State);
  Serial.print("NotPassedYet1 == ");
  Serial.println(NotPassedYet1);
  Serial.print("Current Time == ");
  Serial.println(currentTime);
  Serial.print("Button1Timer == ");
  Serial.println(Button1Timer);
  Serial.print("iterations == ");
  Serial.println(iterations);
  Serial.print("iterationsButtonHeld == ");
  Serial.println(iterationsButtonHeld);

  iterations++;
  
  if (Button1CurrentState == LOW && LastButton1State == HIGH && NotPassedYet1 == true){ 
    // only start counting the debounce if the current button state is pressed, the last button state was not pressed, and we haven't passed a value back yet.
    LastButton1State = LOW;
    Button1Timer = currentTime;
    iterations = 1;
    iterationsButtonHeld = 1;
    Serial.println("first if statement");
  }
  
  if (Button1CurrentState == LOW && LastButton1State == LOW && (currentTime - Button1Timer) > Debounce && NotPassedYet1 == true && (iterationsButtonHeld >= (iterations * RatioButtonHeld + 1)) &&  iterationsButtonHeld <= iterations){ 
    // only allows the knowledge that the button has been pressed to leave if we haven't passed it yet and we've held the button long enough.  Also verifies we've been holding the button and not cheating.
    LastButton1State = HIGH;
    NotPassedYet1 == false;
    Button1Timer = currentTime;
    return LOW;
    Serial.println("second if statement");
  }
  
  if (Button1CurrentState == HIGH && LastButton1State == HIGH && (currentTime - Button1Timer) >= Debounce && NotPassedYet1 == false){ 
    // resets everything after waiting for no debounce from letting off the button
    NotPassedYet1 == true;
    iterations = 0;
    iterationsButtonHeld = 0;
    LastButton1State == HIGH;
    Serial.println("third if statement");
    return HIGH;
  }

  if (Button1CurrentState == LOW && LastButton1State == LOW) {
    // incriment the button held iterations
    iterationsButtonHeld++;
    Serial.println("increment iterationsButtonHeld");
  }

  if (iterationsButtonHeld < (iterations * RatioButtonHeld + 1)) {
    // resets everything because the button wasn't held long enough over the debounce duration
    NotPassedYet1 == true;
    iterations = 0;
    iterationsButtonHeld = 0;
    LastButton1State == HIGH;
    Serial.println("reset because button wasn't held long enough");
    return 2;
  }
  
  return 3;
}


*/



//
//








void loop() {
  Program = 9;
  currentTime = millis();

  static unsigned long timer = millis();
  static bool looper = 0;
  static bool looper2 = 0;
  
  static unsigned long Button1Presses = 0;
  static unsigned long LastTime = 0;


  // Update the Bounce instances :
  debouncer1.update();
  debouncer2.update();

  // Get the updated value :
  int value1 = debouncer1.read();
  int value2 = debouncer2.read();


  if(Program == 9){
    if ( value1 == LOW || value2 == LOW ) {
       BLINK_ON();     
    }
    else {
       BLINK_OFF();      
    }
  }

  if(Program == 2){


    if (Button1Presses < Button1) {
      if (lastBlink == 0 && ((LastTime + Debounce) < currentTime)) {
        BLINK_OFF();
        LastTime = currentTime;
      }
      else if (lastBlink == 1 && ((LastTime + Debounce) < currentTime)) {
        BLINK_ON();
        LastTime = currentTime;
      }
      else {
        Serial.println("ERROR IN BUTTON INPUT 1");
      }
      Button1Presses++;
    }
    else if (Button1Presses == Button1){
      if (lastBlink == 0 && ((LastTime + blinkDelay) < currentTime)) {
        BLINK_OFF();
        LastTime = currentTime;
      }
      else if (lastBlink == 1 && ((LastTime + blinkDelay) < currentTime)) {
        BLINK_ON();
        LastTime = currentTime;
      }
      else {
        Serial.println("ERROR IN BUTTON INPUT 2");
      }
    }
    else {
      Serial.println("ERROR IN PROGRAM 2");
    }
    
    Serial.print("Button1Presses == ");
    Serial.println(Button1Presses);
    Serial.print("Button1 == ");
    Serial.println(Button1);  
  }
/*
  if(Program == 1){

    
    byte Button1Status = debounce();
    Serial.print("button 1 status == ");
    Serial.println(Button1Status);
    if(Button1Status == LOW && looper == 0 && looper2 == 1){
      BLINK_ON();
      looper = 1;
      timer = currentTime;
    }
    if(Button1Status == LOW && looper == 1 && (currentTime - timer) > (blinkDelay*2)){
      BLINK_OFF();
      looper = 0;
      looper2 = 0;
      timer = currentTime;
    }
    if(looper2 == 0 && (currentTime - timer) > (blinkDelay*2)){
      looper2 = 1;
    }
  }
  
  if(Program == 0){
    if ((currentTime - timer) < blinkDelay && looper == 0){
      BLINK_ON();
      if (looper == 0){
        looper = 1;
        timer = currentTime;
      }
    }
    if ((timer + blinkDelay) <= currentTime && looper == 1 && looper2 == 0){
      BLINK_OFF();
      looper2 = 1;
    }
    if (currentTime > (blinkDelay * 2 + timer)){
      looper = 0;
      looper2 = 0;
      timer = currentTime;
    }
    /*(delay (200);
    Serial.println("end of program 0");
    Serial.print("currentTime == ");
    Serial.println(currentTime);
    Serial.print("timer == ");
    Serial.println(timer);
    Serial.print("blinkDelay == ");
    Serial.println(blinkDelay);
    Serial.print("looper == ");
    Serial.println(looper);
    
    // Program = Buttons_Read();

      if (Program != 0){
      Count_Button_1 = 0;
      lastButton_1State = 1;
      lastButton_2State = 1;
      lastDebounceTime1 = 0;
      lastDebounceTime2 = 0;
      ReadOut(0,0,0,Program);
   

  }
/*
  
  /*
  else if(Program == 1){
      BLINK_OFF();
      int time_since_button_press = millis();
  while(Program == 1){
    for(int Fourth = 0; Fourth < 10; Fourth ++){
      for(int Third = 0; Third < 10; Third ++){
        for(int Second = 0; Second < 10; Second ++){
          for(int First = 0; First < 10; First ++){ 
            for(int i = 0; i < DelayInterval; i ++){
              ReadOut(First,Second,Third,Fourth);
                if ((digitalRead(BUTTON_1) == 0 || digitalRead(BUTTON_2) == 0) && (time_since_button_press + 500) < millis()) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  lastButton_1State = 1;
                  lastButton_2State = 1;
                  lastDebounceTime1 = 0;
                  lastDebounceTime2 = 0;
                  break;
                }
            }
            if (Program == 0) { // exit out of for loop
             break;
            }
          }
          if (Program == 0) { // exit out of for loop
           break;
          }
        }
        if (Program == 0) { // exit out of for loop
         break;
        }
      }
      if (Program == 0) { // exit out of for loop
       break;
      }
    }
    if (Program == 0) { // exit out of for loop
     break;
    }
   }
   Program = 0;
   ReadOut(0,0,0,0);
  }

  else if (Program == 2){
      BLINK_OFF();
      int time_since_button_press = millis();
   while(Program == 2){
    int redValue = 0;
    int greenValue = 0;
    int blueValue = 0;

    for(redValue = 0; redValue < 254; redValue++){
      RGB(redValue,greenValue,blueValue,DelayInterval);
                if ((digitalRead(BUTTON_1) == 0 || digitalRead(BUTTON_2) == 0) && (time_since_button_press + 500) < millis()) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  lastButton_1State = 1;
                  lastButton_2State = 1;
                  lastDebounceTime1 = 0;
                  lastDebounceTime2 = 0;
                  break;
                }
    }

    for(greenValue = 0; greenValue < 254; greenValue++){
      RGB(redValue,greenValue,blueValue,DelayInterval);
                if ((digitalRead(BUTTON_1) == 0 || digitalRead(BUTTON_2) == 0) && (time_since_button_press + 500) < millis()) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  lastButton_1State = 1;
                  lastButton_2State = 1;
                  lastDebounceTime1 = 0;
                  lastDebounceTime2 = 0;
                  break;
                }
    }

    for(blueValue = 0; blueValue < 254; blueValue++){
      RGB(redValue,greenValue,blueValue,DelayInterval); 
                if ((digitalRead(BUTTON_1) == 0 || digitalRead(BUTTON_2) == 0) && (time_since_button_press + 500) < millis()) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  lastButton_1State = 1;
                  lastButton_2State = 1;
                  lastDebounceTime1 = 0;
                  lastDebounceTime2 = 0;
                  break;
                }    
    }

        for(redValue; redValue > 0; redValue--){
      RGB(redValue,greenValue,blueValue,DelayInterval);
                if ((digitalRead(BUTTON_1) == 0 || digitalRead(BUTTON_2) == 0) && (time_since_button_press + 500) < millis()) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  lastButton_1State = 1;
                  lastButton_2State = 1;
                  lastDebounceTime1 = 0;
                  lastDebounceTime2 = 0;
                  break;
                }
    }

    for(greenValue; greenValue > 0; greenValue--){
      RGB(redValue,greenValue,blueValue,DelayInterval);
                if ((digitalRead(BUTTON_1) == 0 || digitalRead(BUTTON_2) == 0) && (time_since_button_press + 500) < millis()) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  lastButton_1State = 1;
                  lastButton_2State = 1;
                  lastDebounceTime1 = 0;
                  lastDebounceTime2 = 0;
                  break;
                }
    }

    for(blueValue; blueValue > 0; blueValue--){
      RGB(redValue,greenValue,blueValue,DelayInterval); 
                if ((digitalRead(BUTTON_1) == 0 || digitalRead(BUTTON_2) == 0) && (time_since_button_press + 500) < millis()) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  lastButton_1State = 1;
                  lastButton_2State = 1;
                  lastDebounceTime1 = 0;
                  lastDebounceTime2 = 0;
                  break;
                } 
    }

   }
  }

  else if (Program == 3){
    int time_since_button_press = millis();
    BLINK_OFF();
    int First = 0;
    int Second = 0;
    int Third = 0;
    int Fourth = 0;
   while(Program == 3){ 
    int reading  = analogRead(lightPin);
    First = (reading%10);
    Second = ((reading/10)%10);
    Third = ((reading/100)%10);
    Fourth = (reading/1000);
     
    ReadOut(First,Second,Third,Fourth); 
                if ((digitalRead(BUTTON_1) == 0 || digitalRead(BUTTON_2) == 0) && (time_since_button_press + 500) < millis()) { // exit out of for loop
                  ReadOut(0,0,0,0);
                  Program = 0;
                  lastButton_1State = 1;
                  lastButton_2State = 1;
                  lastDebounceTime1 = 0;
                  lastDebounceTime2 = 0;
                  break;
                }
   }
   Program = 0;
  }

  else {
    Serial.println("Error in program selection");
    Program = 0;
    ReadOut(0,0,0,0);
  }
  */
}
