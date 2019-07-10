// one button password keypad
// made by id-ware/micromix.
// based on "keypad password" example by Andrew Mascolo.

//////////
//Warning: the code is using millis(), and will freak-out after 49 days running non-stop
//do not use beyond that time.
//////////////////////////////
//TODO: 1. write a statment that fixes the "millis() 49-days bug"
//      2. get rid of delay at password checks?
//////////////////////////////
//
//Version: 08.07.2019 11:46 AM (final)
//(date is better for me than random numbers..)
////
//-------------------------------------------------------------

//**un-comment the lines below for the display you use**
//----------------------// Normal-LCD //---------------------
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//-----------------------// I2C-LCD //-----------------------
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

////////////////////
#define Password_Lenght 6 // Give enough room for five chars + NULL char

char Data[Password_Lenght]; // 5 is the number of chars it can hold + the null char = 6
char Master[Password_Lenght] = "12345";
byte data_count = 0, master_count = 0;
//bool Pass_is_good;
//char customKey;
////////////////////

int single_digit = -1;

const int buttonPin = 7;    // the number of the pushbutton pin
int buttonState;
int maxlenght = 4;

unsigned long previousTime = 0;
int period = 50;
bool flag = false;

unsigned long previousWaitTime = 0;
int wait_time = 1000;
bool wait_flag = false;
int charmove = 0;

////////////
void setup()
{
  //Serial.begin(115200);  //used for debugging, not required
  pinMode(buttonPin, INPUT);

  //  **un-comment the lines below for the display you use**
  //----------------------// Normal-LCD //---------------------
  //lcd.begin(16, 2);
  //-----------------------// I2C-LCD //-----------------------
  lcd.init();
  lcd.backlight();    // turn on backlighting
  //
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

  unsigned long currentTime = millis();

  if (buttonState == HIGH) {
    previousTime = currentTime;
    flag = true;
  }

  if ((currentTime - previousTime > period) && (flag == true)) {

    flag = false;
    previousTime = currentTime;
    lcd.setCursor(charmove, 1);

    if (single_digit >= 9) {
      single_digit = 0;
    }
    else
    {
      single_digit++;
    }
    //cursor-position off before print.
    lcd.noCursor();
    //
    lcd.print(single_digit);

    ///////////////////////////////
    previousWaitTime = currentTime;
    wait_flag = true;
    ///////////////////////////////
  }

  if ((currentTime - previousWaitTime > wait_time) && (wait_flag == true)) {

    wait_flag = false;
    previousWaitTime = currentTime;

    /////////////////////
    // converting here the int value to char data type

    char buffer[1];  // inserting a new char buffer of the size of 1 for the converter
    sprintf(buffer, "%d", single_digit); //the converter itself
    // i is our char in the int format, and we convert it here to the char type
    //so we can save it as string and compere it in the end to the password we got stored in memory.

    // "/n" = newline
    // "%lu" = long
    // "%d" = int
    // "%06" before "lu" or "int" will result with ZERO padding
    // of the number, i.e.: 50 -> 000050

    Data[data_count] = buffer[0]; // store char into data array
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
    /////////////////////

    if (charmove >= maxlenght) {
      charmove = 0;
    } else {
      charmove++;
    }
    single_digit = -1;

    ///
    if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
    {
      delay(500); // NOT REQUIRED, JUST FOR COSMATICS
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Password is ");

      //Serial.println(Data);  //used for debugging, not required
      //Serial.println(Master);  //used for debugging, not required

      if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
        lcd.print("Good");
      else
        lcd.print("Bad");

      delay(1000);// added 1 second delay to make sure the password is completely shown on screen before it gets cleared.
      lcd.clear();
      clearData();
      //charmove = 0;
      //single_digit = 0;
      lcd.setCursor(0, 0);
      lcd.print("1-Button Keypad");
    }
    ///

    //cursor-position on after movement.
    lcd.setCursor(charmove, 1);
    lcd.cursor();
    //

  }

}

void clearData()
{
  while (data_count != 0)
  { // This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}
