//////////
//Warning: the code is using millis(), and will freak-out after 49 days running non-stop
//do not use beyond that time.
//////////////////////////////
//TODO: write a statment that fixes the "millis() 49-days bug"
//////////////////////////////
//
//Version: 07.07.2019 12:23 PM (cursor-position edition)
//edit: i removed the "String menu[]" because it is really not required for counting from 0 to 9, 
//i replaced it with much simpler "int i" .
////

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int i = 0;

const int buttonPin = 7;    // the number of the pushbutton pin
int buttonState;

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
  pinMode(buttonPin, INPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("1-Button Keypad");
  
  //cursor-position
  lcd.setCursor(0, 1);
  lcd.cursor();
  //
}

void loop()
{
  
  buttonState = digitalRead(buttonPin);

  ////////////////////////////////////////////////////////////////////////////
  //  first part of device's number select is below
  ////////////////////////////////////////////////////////////////////////////

  unsigned long currentTime = millis();
       
  if (buttonState == HIGH) {
    previousTime = currentTime;
    
    //program write down to memory the time we pressed						  
    //the button, and save it under previousTime					  
    //(currentTime is the millis() timer)
    
    flag = true;
    
    //i puted flag here so the code wont turn on automaticlly.
    //otherwise it will run all the time. a safe and simple way to make it run once, 
    //is to make the flag go 'True' on button state 'HIGH', 
    //and then in the other function we set it back to 'False'.	 
    
  }
  
  if ((currentTime - previousTime > period) && (flag == true)) {
      
  //currentTime is millis(); and its subtracted  
  //from the last time we pressed the button (previousTime)
  //then we compare it to period which is our delay (50 milisecends)
  //if it is bigger than our delay time (in other word, if it passed that delay time), 
  //and the flag (from button press) is ture, the function below will start.
  //in the function we reset the flag and the time so we can use the function again.	  
    
    flag = false;
    previousTime = currentTime;
    lcd.setCursor(charmove, 1);
    
    if (i >= 9) {
    //this is a reset function to reset the string back to zero
    //it is enabled once the number past number 9	    
      i = 0;
    }
    else
    {
      i++;
    }
    //cursor-position off before print.
    lcd.noCursor();
    //
    lcd.print(i);
    
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
        //cursor-position on after movement.
     	lcd.setCursor(charmove, 1);
        lcd.cursor();
        //
    }

}


// some of my own philosophy here:
// "You can communicate with everything in this world,
// either if its human or non-human, animal or machine.
// the key patience and tolerance..."
// - I.W.
