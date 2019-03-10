//Some code for an Arduino Uno to exercise a four digit 7 segment LED display, a three color LED, 
//and take some inputs from a photo diode and a couple buttons.
//
//Spaghetti code by Douglas L. Van Bossuyt.  Heavily borrowed elements from the Elegoo Super Starter Kit and 
//elsewhere online as I needed to figure things out.

int latch=9;  //74HC595  pin 9 STCP
int clock=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS

const int DIGIT_1 = 7;
const int DIGIT_2 = 4;
const int DIGIT_3 = 12;
const int DIGIT_4 = 11;

const int BLUE = A1;
const int GREEN = 5;
const int RED = 6;

const int BUTTON_1 = 2;
const int BUTTON_2 = 3;

int lightPin = 0;



unsigned char table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};

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
  
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  
  Serial.begin(9600);

}


// Modifiable variables here:
int DelayInterval = 10;
int blinkDelay = 50;
unsigned long debounceDelay = 500;

// Defined variables here:
int Button_Read_1 = 0;
int Button_Read_2 = 0;
int Program = 0;
int photoDiode = 0;
int blinkCounter = 0;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;


int lastButton_1State = 1;
int lastButton_2State = 1;
int Button_1_Raw_State = 1;
int Button_2_Raw_State = 1;
int Count_Button_1 = 0;

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
  return;
}

void BLINK_OFF(){
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  return;
}


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




void loop() {
  if(Program == 0){
    if (blinkCounter <= 1){
      BLINK_ON();
    }
    if (blinkCounter = blinkDelay){
      BLINK_OFF();
    }
    if (blinkCounter > (blinkDelay * 2)){
      blinkCounter = 0;
    }
    
    blinkCounter++;
    
    Program = Buttons_Read();
    
    if (Program != 0){
      Count_Button_1 = 0;
      lastButton_1State = 1;
      lastButton_2State = 1;
      lastDebounceTime1 = 0;
      lastDebounceTime2 = 0;
      ReadOut(0,0,0,Program);
   
    }
  }
  
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
}