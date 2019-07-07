//Warning: the code is using millis(), and will freak-out after 49 days running non-stop
//do not use beyond that time.
//TODO: write a statment that fixes the "millis() 49-days bug"

//Version: 07.07.2019 7:58 AM
//(date is better for me than random numbers..)

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String menu[] = { "0" , "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9" };
String inString = "";    // string to hold input
int i = 0;

const int buttonPin = 7;    // the number of the pushbutton pin
int buttonState;

///cursor-mode///
//////////////////////////////////////
unsigned long cursorTime = 0;
int cursorPeriod = 100;
bool cursorON = false;
//////////////////////////////////////

//////////////////////////////////////
unsigned long previousTime = 0;
int period = 50;
bool flag = false;
//////////////////////////////////////

///////////////////////////////////////
unsigned long previousWaitTime = 0;
int wait_time = 1000;
bool wait_flag = false;
int charmove = 0;
///////////////////////////////////////

void setup()
{
  //Serial for position debug, not required.
  //Serial.begin(115200);
  pinMode(buttonPin, INPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("1-Button Keypad");

}

void loop()
{
  
  buttonState = digitalRead(buttonPin);

  ////////////////////////////////////////////////////////////////////////////
  //  first part of device's number select is below
  ////////////////////////////////////////////////////////////////////////////
  //  TODO: make a timer that set the curser to next row, after 1 sec,
  //        but timer reset if we press the button again within that time
  ////////////////////////////////////////////////////////////////////////////

  unsigned long currentTime = millis();
  
  ///cursor-mode///
  if (currentTime - cursorTime > cursorPeriod)
  {
    cursorTime = currentTime;
    if (cursorON == false){
      //turn cursor sign on
      cursorON = true;
      lcd.setCursor(charmove, 1);
        lcd.cursor();
    } else {
      //turn cursor sign off
      cursorON = false;
        lcd.noCursor();
    }
  }
      

  if (buttonState == HIGH) {
    previousTime = currentTime;
    flag = true;
    
    //position-debug:
    //Serial.println(currentTime);
    //Serial.print("       ");
    //Serial.println(charmove);
    //Serial.print("       ");
    //Serial.print(wait_flag);
    
  }
  
  if ((currentTime - previousTime > period) && (flag == true)) {
    flag = false;
    previousTime = currentTime;
    lcd.setCursor(charmove, 1);
    
    inString = menu[i];

    if ((inString.toInt()) >= 9) {
      i = 0;
    }
    else
    {
      i++;
    }
    lcd.print(inString);
    
    ///////////////////////////////
    previousWaitTime = currentTime;
    wait_flag = true;
    ///////////////////////////////    
  }

      if ((currentTime - previousWaitTime > wait_time) && (wait_flag == true)) {
      wait_flag = false;
      previousWaitTime = currentTime;
        
        i = 0;
        if (charmove >= 6){
          charmove = 0;
        } else {
      charmove++;
        }
	  //lcd.setCursor(charmove, 1);
    }

}