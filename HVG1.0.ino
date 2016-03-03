//---------------------------------------------------Variables for Computer Interface

//Flags
boolean TempBlock1C = false;
boolean TempBlock2C = false;
boolean ChangeFlagC = false;

boolean SmoothFlagC = false;
boolean rampUpInProgC = false;

boolean frequencychangeC = false;
boolean changetozerofreqC = false;
boolean changefromzerofreqC = false;
boolean voltagechangeC = false;

boolean FirstLoopFlagC = false;
boolean RampFlagC = false;
boolean FirstLoopFlag2C = false;

boolean SmoothFlag2C = false;
boolean rampDownInProgC = false;

boolean SmoothRampFlagC = false;

boolean FirstLoopFlag = false;
boolean FirstLoopFlag2 = false;
boolean TempBlock1 = false;
boolean TempBlock2 = false;
boolean RampFlag = false;
boolean ChangeFlag = false;

//Ramping Counter
int rampUpInProgCounterC;
int rampupcounterC;
int rampdowncounterC;
int rampupcounter3C;
int voltagerampcounterC;
int rampDownInProgCounterC;
int SmoothCounterRampC;
int smoothrampdowncounterC;

//Signal Counter
int SmoothCounterC;
int LCDrealtimeCounterC;
int FirstLoopCounterC;
int FirstLoopCounter2C;
int SmoothCounter2C;
int LCDCounter2C;

//value storage
float aimfrequencyC;
float aimvoltageC;
float aimrealvoltageC;

int lastsign;

//-------------------- function generation --------------
//sin
int sinvoltageout;
int lastsinvoltageout;

//square
int squarevoltageout;
int lastsquarevoltageout;

//triangle
int triangvoltageout;
int lasttriangvoltageout;



//Serial Communication-----------------------------------------------------------------

int separator1;
int separator2;
int separator3;
int separator4;
int separator5;
int separator6;
int separator7;
int space;

int v1;
int v2;
int v3;
int f1;
int f2;
int f3;

//---------------------------------------------------Variables for Standard Interface
//ramping counter
int rampUpInProgCounter;
int rampDownInProgCounter;
int rampupcounterR;
int rampupcounter3R;
int rampdowncounterR;
int voltagerampcounterR;
int SmoothCounterRampR;
int smoothrampdowncounterR;
int SmoothCounterR;
int SmoothCounter2R;

//signal counter
int FirstLoopCounterR;
int FirstLoopCounter2R;
int ModeCounter;
int ModeCounter2;
int LCDCounter;
int LCDCounter2;
int LCDCounterR;
int LCDCounter2R;
int LCDrealtimeCounterR;

//signal flags
boolean rampUpInProg = false;
boolean rampDownInProg = false;
boolean ChangeFlagR = false;
boolean FirstLoopFlagR = false;
boolean FirstLoopFlag2R = false;
boolean RampFlagR = false;
boolean TempBlock1R = false;
boolean TempBlock2R = false;
boolean SmoothRampFlagR = false;
boolean SmoothFlagR = false;
boolean SmoothFlag2R = false;

boolean frequencychange = false;
boolean changetozerofreq = false;
boolean changefromzerofreq = false;
boolean voltagechange = false;

//value storage
float voltageR;
float frequencyR;
int realvoltageR;
int voltageoutR;

float lastvoltageR;
float lastfrequencyR;
int lastrealvoltageR;
int lastvoltageoutR;

float aimvoltage;
float aimfrequency;
float aimrealvoltage;

//button variables
int buttonStateR;
int lastButtonStateR;
boolean currentButtonStateR = false; 

//Potentiometer
int sensorValue1;
int sensorValue2;
int sensorValue3;
int sensorValue4;

//Potentiometer smoothing
int average1;
int average2;
int average3;
int average4;

//voltage
int Value1;
int Value2;
int Value3;

//Parameters
float voltage;
float frequency;
int realvoltage;
int voltageout;

float lastvoltage;
float lastfrequency;
int lastrealvoltage;
int lastvoltageout;



//-----------------------------------------------------------------------------
//------------------- JavaSideCommunication ---------------------------

float voltageCom;
float frequencyCom;

int wave;
int sign;

//------------------------------- Display ----------------------------------------------

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
int Contrast = 30; 

//time
float t;

//Test LED
int outputPin_led = 10;

//Button
int  buttonPin = 7;
int buttonState;
int lastButtonState;
boolean currentButtonState = false; 

//button - mode selection
int currButState;
unsigned long PrevMillis = 0;
const unsigned long IntervalMs = 25;
byte longButPressCountMax = 80;    // 80 * 25 = 2000 ms---------------------
byte longButPressCount = 0;
byte prevButState = HIGH;      
boolean mode = false;

// called when button is kept pressed for more than 2 seconds---------------
void longButPress() {
mode = !mode;
  }
// called when key goes from not pressed to pressed-------------------------
void ButPress() {
    longButPressCount = 0;
}

// called when key goes from pressed to not pressed--------------------------
void ButRelease() {
    if (longButPressCount >= longButPressCountMax) {
        longButPress();
    }
}

//-----------------------------------------------------------------------------

void setup()
{
 Serial.begin(9600);

  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
    

  //LED
  pinMode(outputPin_led, OUTPUT);

  //LCD
  pinMode(9, OUTPUT); 
  analogWrite(6, Contrast); 
  lcd.begin(16, 2);
 
}

void loop(){ 
    
    t = millis() / 1000.0;

//mode button management---------------------------------------------------------------

if (millis() - PrevMillis >= IntervalMs) {
        PrevMillis = millis();
       
       // byte currButState = digitalRead(buttonPin);
        currButState = digitalRead(buttonPin);
       
        if ((prevButState == 0) && (currButState == 1)) {
            ButPress();
        }
        else if ((prevButState == 1) && (currButState == 0)){ 
            ButRelease();
        }
        else if (currButState == 1) {
            longButPressCount++;
        }
       
        prevButState = currButState;
}

//---------------------mode 1 - Standard Interface ------------------------------------------
//mode selection first loop---------------------------------------------------------
if (mode == false){
  
ModeCounter = 0;
if (ModeCounter2 == 0) {
        currentButtonStateR = false;
        lastfrequencyR = 0; 
        frequencyR = 0;
        lastvoltageR = 0;
        voltageR = 0;
        lastrealvoltageR = 0; 
        realvoltageR = 0;
        
}

//reseting counter----------------------------------------------------------------
if (ModeCounter2 >= 3000){
ModeCounter2 = 1;
}
ModeCounter2++;

//read Potentiometers when no voltage setting is in progress----------------------
if (rampUpInProg == false && rampDownInProg == false){
 
  sensorValue1 = analogRead(A0);
  sensorValue2 = analogRead(A1);
  sensorValue3 = analogRead(A2);
  sensorValue4 = analogRead(A3);


  average1 = ( average1 * 9 + sensorValue1 ) / 10;
  average2 = ( average2 * 9 + sensorValue2 ) / 10;
  average3 = ( average3 * 9 + sensorValue3 ) / 10;
  average4 = ( average4 * 9 + sensorValue4 ) / 10; 
  
  Value1 = map(average1, 0, 1023, 0, 6);
  Value2 = map(average2, 0, 1023, 0, 10);
  Value3 = map(average3, 0, 1023, 0, 10);
  frequencyR = map(average4, 1023, 0, -8, 1000);
  frequencyR = frequencyR / 100; // frequencyR = frequencyR / 100.00;

  
  voltageR = Value1 / 1.0 + Value2 / 10.0 + Value3 / 100.0;

  if (voltageR > 5) {
    voltageR = 5.00;
  }

  realvoltageR = (voltageR * 255) / 5;

}
//calculate wave values----------------------------------------------------------------------
  SinBuildingR();
  LastSinBuildingR();


   //voltage on/off - button action------------------------------------------------------------
if (TempBlock1R == false && TempBlock2R == false && ChangeFlagR == false){

  buttonStateR = digitalRead(buttonPin);
}

  if (buttonStateR != lastButtonStateR) {

    if (buttonStateR == HIGH) {
      currentButtonStateR = !currentButtonStateR;
    }
  }
  lastButtonStateR = buttonStateR;

//on-----------------------------------------------------------------------------------------
  if (currentButtonStateR == true) {
if (LCDCounterR == 0) {
    
  digitalWrite(9, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltageR)+ + " " + "(Sin)" + "   ");
  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequencyR)+ " " + "(ON)" + "   ");

}
if (LCDCounterR >= 3000){
LCDCounterR = 1;
}
 LCDCounterR++;
    actionR();
    SmoothCounter2R = 0;
    LCDCounter2R = 0;

    
  }

//off-------------------------------------------------------------------------------------
  if (currentButtonStateR == false  ) {
   if (LCDCounter2R == 0) {
    
  digitalWrite(9, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltageR)+ + " " + "(Sin)" + "   ");
  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequencyR)+ " " + "(OFF)" + "   ");

}
if (LCDCounter2R >= 3000){
LCDCounter2R = 1;
}
 LCDCounter2R++; 
    noactionR();
    SmoothCounterR = 0;
     LCDCounterR = 0;
  }
}



//--------------------------------- mode 2 - Computer Interface--------------------------------
if(mode == true){

  ModeCounter2 = 0;
//firsttime in loop - reset values-----------------------------------------------------
if (ModeCounter == 0) {
        currentButtonState = false;
        lastfrequency = 0; 
        frequency = 0;
        lastvoltage = 0;
        voltage = 0;
        lastrealvoltage = 0; 
        realvoltage = 0;
        sign = 0;
        lastsign = 0;
}
if (ModeCounter >= 3000){
ModeCounter = 1;
}
ModeCounter++;

// if no voltaeg setting is in progress - read serial data----------------------
if (rampUpInProgC == false && rampDownInProgC == false){
 //ReadSerial-------------------------------------------------------------------
ReadInput();  
}

//data check and storage------------------------------------------------------
if (voltageCom >= 0.00 && voltageCom <= 5.00 && frequencyCom >= 0.00 && frequencyCom <= 10.00 && wave <= 3 ){

  sign = wave;
  voltage = voltageCom;
  frequency = frequencyCom;
  realvoltage = (voltage * 255) / 5;
}
//wave valiue calculation-------------------------------------------------------
    SinBuilding();
    LastSinBuilding();
    SquareBuilding();
    LastSquareBuilding();
    TriangleBuilding();
    LastTriangleBuilding();
    
//voltage on/off - button action------------------------------------------------
if (TempBlock1C == false && TempBlock2C == false && ChangeFlagC == false){

  buttonState = digitalRead(buttonPin);}

 //wave form sign send from JavaSide---------------------------------------------
 if (sign == 0){
 voltageout = sinvoltageout;
 lastvoltageout = lastsinvoltageout;
 }
 
 if (sign == 1){
 voltageout = triangvoltageout;
lastvoltageout = lasttriangvoltageout;
 }
 
 if (sign == 2){
  voltageout = squarevoltageout;
 lastvoltageout = lastsquarevoltageout;
 
 }

  if (buttonState != lastButtonState) {

    if (buttonState == HIGH) {
      currentButtonState = !currentButtonState;
    }
  }
  lastButtonState = buttonState;

 //----------------- output ON -----------------------------------
  if (currentButtonState == true) {
      if (LCDCounter == 0) {
    
 if (sign == 0){
digitalWrite(9, HIGH);

 lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltage) + " (Sin)" + "   ");


  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequency) + " (ON)" + "   ");
}

  if (sign == 1){
digitalWrite(9, HIGH);

 lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltage)+ " (Tri)" + "   ");


  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequency)+ " (ON)" + "   ");

  }
  
  if (sign == 2){
digitalWrite(9, HIGH);

 lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltage)+ " (Sqr)"  + "   ");


  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequency)+ " (ON)" + "   ");
  }

}
if (LCDCounter >= 3000){
LCDCounter = 1;
}
 LCDCounter++; 
          
             action();
             SmoothCounter2C = 0;
    }
  
//----------------- output OFF -----------------------------------
  if (currentButtonState == false  ) {
if (LCDCounter2C == 0) {
    
  if (sign == 0){
digitalWrite(9, HIGH);

 lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltage) + " (Sin)" + "   ");


  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequency) + " (OFF)" + "   ");
}

  if (sign == 1){
digitalWrite(9, HIGH);

 lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltage)+ " (Tri)" + "   ");


  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequency)+ " (OFF)" + "   ");

  }
  
  if (sign == 2){
digitalWrite(9, HIGH);

 lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltage)+ " (Sqr)"  + "   ");


  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequency)+ " (OFF)" + "   ");
  }

}
if (LCDCounter2C >= 3000){
LCDCounter2R = 1;
}
    LCDCounter2C++;
             noaction();
             LCDCounter = 0;
             SmoothCounterC = 0;
      }

}
}

//-----------------------------------------------------------------------------
//------------------------------ Standard Interface -----------------------------------------------
//-----------------------------------------------------------------------------
void actionR() {
//First Loop--------------------------------------------------------------
    if (SmoothCounterR == 0) {
      SmoothFlagR = true;
      TempBlock1R = true;
    }
if (SmoothCounterR >= 3000){
SmoothCounterR = 1;
}
    SmoothCounterR++;

    if (SmoothFlagR == true){

 //---------------- transition ----------------------------------------------
 
      if (voltageoutR != 0 && frequencyR != 0){
      PORTA = 0;
      analogWrite(outputPin_led, 0);
      }

if  (voltageoutR == 0 && frequencyR != 0){
      lastfrequencyR = frequencyR;
      SmoothFlagR = false;
      TempBlock1R = false;
      }

//--------------frequency 0 - ramp up------------------------------------------
if (frequencyR == 0 || rampUpInProg == true){

//first time in here set rampUpInProg = true;
if (rampUpInProgCounter == 0){
  rampUpInProg = true;
  }
  rampUpInProgCounter++;

    
    if (voltageoutR <= rampupcounterR) {
        rampupcounterR = 0;
        SmoothFlagR = false;
        TempBlock1R = false;
        lastfrequencyR = frequencyR;
        lastvoltageR = voltageR;
        lastrealvoltageR = realvoltageR;
        rampUpInProg = false;
        rampUpInProgCounter = 0;

      } else {
        rampupcounterR++;
        PORTA = rampupcounterR;
        analogWrite(outputPin_led, rampupcounterR);
      }
    }
  }

 //---------- continuos output ----------------------------------------------
    if (SmoothFlagR == false){

  //------ Checking Potentiometers -------------------------------------------
  if (voltageR != lastvoltageR || frequencyR != lastfrequencyR) {
    ChangeFlagR = true;
  }

  //------------------ no Change--------------------------------------------------------
  if (ChangeFlagR == false) {

    PORTA = voltageoutR;
    
    lastfrequencyR = frequencyR;
    lastvoltageR = voltageR;
    lastrealvoltageR = realvoltageR;
    analogWrite(outputPin_led, voltageoutR);
  
    if (LCDrealtimeCounterR == 0) {
    //if first loop
  digitalWrite(9, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltageR)+ + " " + "(Sin)" + "   ");
  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequencyR)+ " " + "(ON)" + "   ");

}
if (LCDrealtimeCounterR >= 3000){
LCDrealtimeCounterR = 1;
}
 LCDrealtimeCounterR++;

  }

  //------ Change -------------------------------------------
  //------ cases -------------------------------------------
  if (ChangeFlagR == true) {
    LCDrealtimeCounterR = 0;
  }
  if (ChangeFlagR == true && frequencychange == false && changetozerofreq == false && changefromzerofreq == false && voltagechange == false && rampUpInProg == false) {  
    //------ frequency change ------------------------------------
    if (lastfrequencyR != 0 && frequencyR != 0 ) {


      frequencychange = true;

    }

    //------ lastfrequency not 0 - changing to frequency 0 --------------------
    if (lastfrequencyR != 0 && frequencyR == 0) {

      changetozerofreq = true;

      aimfrequency = frequencyR;
      aimvoltage = voltageR;
      aimrealvoltage = realvoltageR;

    }

    //------- lastfrequency is 0 changing to frequency not 0-------------------
    if (lastfrequencyR == 0 && frequencyR != 0) {

      changefromzerofreq = true;


    }
    //------ voltagechange on frequency 0 -------------------------------------
    if (lastfrequencyR == 0 && frequencyR == 0) {

      voltagechange = true;

    }

  }
//----------------- Case handling --------------------------------------------

  //------ frequency change (both frequencies not 0) ------------------------------------
  if (frequencychange == true) {
    PORTA = lastvoltageoutR;
    analogWrite(outputPin_led, lastvoltageoutR);

    if (lastvoltageoutR == 0 && frequencyR == 0) {
      frequencychange = false;
    }
    if (frequency > 1.00){
      if (lastvoltageoutR == 0 && voltageoutR == 0) {
    
      ChangeFlagR = false;
      frequencychange = false;
      lastfrequencyR = frequencyR;
      lastvoltageR = voltageR;
      lastrealvoltageR = realvoltageR;
      }
      }
    if (frequency < 1.00){
    if (lastvoltageoutR < 50 && voltageoutR < 50) {
      ChangeFlagR = false;
      frequencychange = false;
      lastfrequencyR = frequencyR;
      lastvoltageR = voltageR;
      lastrealvoltageR = realvoltageR;
    }
  }
  }

  //------- lastfrequency not 0 - changing to frequency 0 -------------------
  if ( changetozerofreq == true) {
    if (rampupcounterR == 0) {
      PORTA = lastvoltageoutR;
      analogWrite(outputPin_led, lastvoltageoutR);
       
    }
    if (lastvoltageoutR == 0 && rampupcounterR == 0 ) {
      rampupcounterR++;
    }
    if (rampupcounterR != 0) {
      if (realvoltageR <= rampupcounterR) {
        rampupcounterR = 0;
        ChangeFlagR = false;
        changetozerofreq = false;
        lastfrequencyR = aimfrequency;
        lastvoltageR = aimvoltage;
        lastrealvoltageR = aimrealvoltage;

      } else {
        rampupcounterR++;
        PORTA = rampupcounterR;
        analogWrite(outputPin_led, rampupcounterR);
        
      }
    }

  }

  //------- lastfrequency is 0 changing to frequency not 0 -------------------
  if (changefromzerofreq == true) {
    if (FirstLoopCounterR == 0) {
      FirstLoopFlagR = true;
    }

    FirstLoopCounterR++;

    if (FirstLoopFlagR == true) {
      rampdowncounterR = realvoltageR;
      FirstLoopFlagR = false;
    }

    if (rampdowncounterR > 0 && RampFlagR == false) {
      rampdowncounterR--;
      PORTA = rampdowncounterR;
      analogWrite(outputPin_led, rampdowncounterR);
      
    }

    if (rampdowncounterR == 0 && voltageoutR != 0 && frequencyR != 0 && RampFlagR == false) {
      PORTA = rampdowncounterR;
      analogWrite(outputPin_led, rampdowncounterR);
      
    }
       //additional safety in case the user switches back to frequency 0 while transition to wave output is in progress--------------
    if (RampFlagR == true) {
      frequencyR = 0;
    }
    if (rampdowncounterR == 0 && frequencyR == 0) {
      rampupcounter3R++;
      RampFlagR = true;
    }
    if (rampupcounter3R != 0) {
      if (realvoltageR <= rampupcounter3R) {
        rampupcounter3R = 0;
        ChangeFlagR = false;
        FirstLoopCounterR = 0;
        rampdowncounterR = 0;
        changefromzerofreq = false;
        lastfrequencyR = frequencyR;
        lastvoltageR = voltageR;
        lastrealvoltageR = realvoltageR;
        RampFlagR = false;

      } else {
        rampupcounter3R++;
        PORTA = rampupcounter3R;
        analogWrite(outputPin_led, rampupcounter3R);
        
      }
    }

    if (rampdowncounterR == 0 && voltageoutR == 0 && RampFlagR == false) {
      ChangeFlagR = false;
      FirstLoopCounterR = 0;
      rampdowncounterR = 0;
      changefromzerofreq = false;
      lastfrequencyR = frequencyR;
      lastvoltageR = voltageR;
      lastrealvoltageR = realvoltageR;

    }
  }


  //--------------- changing voltage when frequency is 0 ----------------------------------
  if (voltagechange == true) {
    /
    if (FirstLoopCounter2R == 0) {
      FirstLoopFlag2R = true;
    }

    FirstLoopCounter2R++;

    if (FirstLoopFlag2R == true) {
      voltagerampcounterR = lastrealvoltageR;
      FirstLoopFlag2R = false;
    }
//ramp down to new voltage;
    if (voltagerampcounterR > voltageoutR) {
      voltagerampcounterR--;
      PORTA = voltagerampcounterR;
      analogWrite(outputPin_led, voltagerampcounterR);
      
    }
//ramp up to new voltage;
    if (voltagerampcounterR < voltageoutR) {
      voltagerampcounterR++;
      PORTA = voltagerampcounterR;
      analogWrite(outputPin_led, voltagerampcounterR);
    }

    if (voltagerampcounterR == voltageoutR) {
      FirstLoopCounter2R = 0;
      voltagerampcounterR = 0;
      ChangeFlagR = false;
      voltagechange = false;
      lastfrequencyR = frequencyR;
      lastvoltageR = voltageR;
      lastrealvoltageR = realvoltageR;

    }
  }

}
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
void noactionR() {

//------------------------- first loop------------------------------------
  SmoothCounterR = 0;

    if (SmoothCounter2R == 0) {
      SmoothFlag2R = true;
      TempBlock2R = true;
    }
if (SmoothCounter2R >= 3000){
SmoothCounter2R = 1;
}
    SmoothCounter2R++;

    if (SmoothFlag2R == true){
        //analogWrite(outputPin_led, 255);

//------------------------- output OFF on voltage 0-------------------------
      if (voltageoutR != 0 && frequencyR != 0){
      PORTA = lastvoltageoutR;
      analogWrite(outputPin_led, lastvoltageoutR);
      }
      if (voltageoutR == 0 && frequencyR != 0){
        SmoothFlag2R = false;
        TempBlock2R = false;
      }

//------------------------- frequency 0 - voltage ramp down ----------------------
      if (frequencyR == 0 || rampDownInProg == true) {

//first time in here set rampDownInProg = true;
if (rampDownInProgCounter == 0){
  rampDownInProg = true;
  }
  rampDownInProgCounter++;
            
            if (SmoothCounterRampR == 0) {
                  SmoothRampFlagR = true;
                }
            
                SmoothCounterRampR++;
            
                if (SmoothRampFlagR == true) {
                    smoothrampdowncounterR = voltageoutR;
                    SmoothRampFlagR = false;
                }
            
                    if (smoothrampdowncounterR > 0) {
                  smoothrampdowncounterR--;
                  PORTA = smoothrampdowncounterR;
                  analogWrite(outputPin_led, smoothrampdowncounterR);
                    }
            
                if (smoothrampdowncounterR == 0){
                    
                    SmoothFlag2R = false;
                    TempBlock2R = false;
                    SmoothCounterRampR = 0;
                    rampDownInProg = false;
                }
   }
      
      }

//---------------------------------- output switched off -------------------------------
      
      if (SmoothFlag2R == false){
       


  //turn output off (set it to 0 voltage)
  voltageoutR = 0;
  PORTA = voltageoutR;
      

  digitalWrite(9, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltageR)+ + " " + "(Sin)" + "   ");
  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequencyR)+ " " + "(OFF)" + "   ");

 analogWrite(outputPin_led, voltageoutR);


      }
}



//------------------------ wave form calculation -----------------------------------------------------
void SinBuildingR() {

  if (frequencyR == 0) {
    voltageoutR = realvoltageR;
  }
  else {
    voltageoutR = (realvoltageR + realvoltageR * sin( 2.0 * PI * frequencyR * t )) / 2;
  }

}

//-----------------------------------------------------------------------------
void LastSinBuildingR() {

  if (lastfrequencyR == 0) {
    lastvoltageoutR = lastrealvoltageR;
  }
  else {
    lastvoltageoutR = (lastrealvoltageR + lastrealvoltageR * sin( 2.0 * PI * lastfrequencyR * t )) / 2;
  }

}



//-----------------------------------------------------------------
//-----------------------------------------------------------------
void action() {
//First Loop-------------------------------------------------------
    if (SmoothCounterC == 0) {
      SmoothFlagC = true;
      TempBlock1C = true;
    }
if (SmoothCounterC >= 3000){
SmoothCounterC = 1;
}
    SmoothCounterC++;

    if (SmoothFlagC == true){

 //0 voltage into wave-----------------------------------------------
 
      if (voltageout != 0 && frequency != 0){
      PORTA = 0;
      analogWrite(outputPin_led, 0);
      }

if  (voltageout == 0 && frequency != 0){
      lastfrequency = frequency;
      SmoothFlagC = false;
      TempBlock1C = false;
      }

//frequency 0 - ramp -----------------------------------------------
if (frequency == 0 || rampUpInProgC == true){

//first time in here set rampUpInProg = true-------------------------
if (rampUpInProgCounterC == 0){
  rampUpInProgC = true;
  }
  rampUpInProgCounterC++;

    
    if (voltageout <= rampupcounterC) {
        rampupcounterC = 0;
        SmoothFlagC = false;
        TempBlock1C = false;
        lastfrequency = frequency;
        lastvoltage = voltage;
        lastrealvoltage = realvoltage;
        rampUpInProgC = false;
        rampUpInProgCounterC = 0;

      } else {
        rampupcounterC++;
        PORTA = rampupcounterC;
        analogWrite(outputPin_led, rampupcounterC);
      }
    }
  }

 //---------- continuos output --------------------------------
    if (SmoothFlagC == false){

  //------ Checking Potentiometers ------------------------------------
  if (voltage != lastvoltage || frequency != lastfrequency || sign != lastsign) {
    ChangeFlagC = true;
  }

  //---------------------------- no Change ---------------------------------------------
  if (ChangeFlagC == false) {

    PORTA = voltageout;
    
    lastfrequency = frequency;
    lastvoltage = voltage;
    lastrealvoltage = realvoltage;
    lastsign = sign;
    analogWrite(outputPin_led, voltageout);
  
    if (LCDrealtimeCounterC == 0) {
    //if first loop-----------------------------------------------------------
  if (sign == 0){
digitalWrite(9, HIGH);

 lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltage) + " (Sin)" + "   ");


  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequency) + " (ON)" + "   ");
}

  if (sign == 1){
digitalWrite(9, HIGH);

 lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltage)+ " (Tri)" + "   ");


  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequency)+ " (ON)" + "   ");

  }
  
  if (sign == 2){
digitalWrite(9, HIGH);

 lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltage)+ " (Sqr)"  + "   ");


  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequency)+ " (ON)" + "   ");
  }

}
if (LCDrealtimeCounterC >= 3000){
LCDrealtimeCounterC = 1;
}
 LCDrealtimeCounterC++;

  }

  //------ Change --------------------------------------------
  if (ChangeFlagC == true) {
    LCDrealtimeCounterC = 0;
  }
  //cases-----------------------------------------------------
  if (ChangeFlagC == true && frequencychangeC == false && changetozerofreqC == false && changefromzerofreqC == false && voltagechangeC == false && rampUpInProgC == false) {  
    
    //------ frequency change ------------------------------------
    if (lastfrequency != 0 && frequency != 0 ) {


      frequencychangeC = true;

    }

    //------ lastfrequency not 0 - changing to frequency 0 --------------
    if (lastfrequency != 0 && frequency == 0) {

      changetozerofreqC = true;

      aimfrequencyC = frequency;
      aimvoltageC = voltage;
      aimrealvoltageC = realvoltage;

    }

    //------- lastfrequency is 0 changing to frequency not 0 ---------------------
    if (lastfrequency == 0 && frequency != 0) {

      changefromzerofreqC = true;


    }
    //------ voltagechange on frequency 0 ---------------------------------------
    if (lastfrequency == 0 && frequency == 0) {

      voltagechangeC = true;

    }

  }
  
  //-------------------- case handling -----------------------------------------
  //-------------------- frequency change --------------------------------------
  
  if (frequencychangeC == true) {
    PORTA = lastvoltageout;
    analogWrite(outputPin_led, lastvoltageout);

    if (lastvoltageout == 0 && frequency == 0) {
      frequencychangeC = false;
    }
    if (lastvoltageout < 50  && voltageout < 50) { 
      ChangeFlagC = false;
      frequencychangeC = false;
      lastfrequency = frequency;
      lastvoltage = voltage;
      lastrealvoltage = realvoltage;
      lastsign = sign;
    }
  }


  //------- lastfrequency not 0 - changing to frequency 0 -------------------
  if ( changetozerofreqC == true) {
    if (rampupcounterC == 0) {
      PORTA = lastvoltageout;
      analogWrite(outputPin_led, lastvoltageout);
       
    }
    if (lastvoltageout == 0 && rampupcounterC == 0 ) {
      rampupcounterC++;
    }
    if (rampupcounterC != 0) {
      if (realvoltage <= rampupcounterC) {
        rampupcounterC = 0;
        ChangeFlagC = false;
        changetozerofreqC = false;
        lastfrequency = aimfrequencyC;
        lastvoltage = aimvoltageC;
        lastrealvoltage = aimrealvoltageC;
        lastsign = sign;

      } else {
        rampupcounterC++;
        PORTA = rampupcounterC;
        analogWrite(outputPin_led, rampupcounterC);
        
      }
    }

  }

  //------- lastfrequency is 0 changing to frequency not 0 -------------------
  if (changefromzerofreqC == true) {
    if (FirstLoopCounterC == 0) {
      FirstLoopFlagC = true;
    }

    FirstLoopCounterC++;

    if (FirstLoopFlagC == true) {
      rampdowncounterC = realvoltage;
      FirstLoopFlagC = false;
    }

//rampdown------------------------------------------------------------------
    if (rampdowncounterC > 0 && RampFlagC == false) {
      rampdowncounterC--;
      PORTA = rampdowncounterC;
      analogWrite(outputPin_led, rampdowncounterC);
      
    }

    if (rampdowncounterC == 0 && voltageout != 0 && frequency != 0 && RampFlagC == false) {
      PORTA = rampdowncounterC;
      analogWrite(outputPin_led, rampdowncounterC);
      
    }

    //additional safety in case the user switches back to frequency 0 while transition to wave output is in progress--------------
    if (RampFlagC == true) {
      frequency = 0;
    }
    if (rampdowncounterC == 0 && frequency == 0) {
      rampupcounter3C++;
      RampFlagC = true;
    }
    if (rampupcounter3C != 0) {
      if (realvoltage <= rampupcounter3C) {
        rampupcounter3C = 0;
        ChangeFlagC = false;
        FirstLoopCounterC = 0;
        rampdowncounterC = 0;
        changefromzerofreqC = false;
        lastfrequency = frequency;
        lastvoltage = voltage;
        lastrealvoltage = realvoltage;
        RampFlagC = false;
        lastsign = sign;

      } else {
        rampupcounter3C++;
        PORTA = rampupcounter3C;
        analogWrite(outputPin_led, rampupcounter3C);
        
      }
    }

    if (rampdowncounterC == 0 && voltageout == 0 && RampFlagC == false) {
      ChangeFlagC = false;
      FirstLoopCounterC = 0;
      rampdowncounterC = 0;
      changefromzerofreqC = false;
      lastfrequency = frequency;
      lastvoltage = voltage;
      lastrealvoltage = realvoltage;
      lastsign = sign;

    }
  }


  //--------------- changing voltage when frequency is 0 ----------------------------------
  if (voltagechangeC == true) {
    //ramp down to  lastvoltageout = 0;
    if (FirstLoopCounter2C == 0) {
      FirstLoopFlag2C = true;
    }

    FirstLoopCounter2C++;

    if (FirstLoopFlag2C == true) {
      voltagerampcounterC = lastrealvoltage;
      FirstLoopFlag2C = false;
    }

    if (voltagerampcounterC > voltageout) {
      voltagerampcounterC--;
      PORTA = voltagerampcounterC;
      analogWrite(outputPin_led, voltagerampcounterC);
      
    }

    if (voltagerampcounterC < voltageout) {
      voltagerampcounterC++;
      PORTA = voltagerampcounterC;
      analogWrite(outputPin_led, voltagerampcounterC);
    }

    if (voltagerampcounterC == voltageout) {
      FirstLoopCounter2C = 0;
      voltagerampcounterC = 0;
      ChangeFlagC = false;
      voltagechangeC = false;
      lastfrequency = frequency;
      lastvoltage = voltage;
      lastrealvoltage = realvoltage;
      lastsign = sign;

    }
  }

}
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void noaction() {
//------------------------- first loop-------------------
  SmoothCounterC = 0;

    if (SmoothCounter2C == 0) {
      SmoothFlag2C = true;
      TempBlock2C = true;
    }
if (SmoothCounter2C >= 3000){
SmoothCounter2C = 1;
}
    SmoothCounter2C++;

    if (SmoothFlag2C == true){

//------------------------- output OFF on voltage 0-------------------------
      if (voltageout != 0 && frequency != 0){

PORTA = voltageout;
analogWrite(outputPin_led, voltageout);
}
      
      if (voltageout == 0 && frequency != 0){
        SmoothFlag2C = false;
        TempBlock2C = false;
      }

//------------------------- frequency 0 - voltage ramp down ----------------------
      if (frequency == 0 || rampDownInProgC == true) {

//first time in here set rampDownInProg = true;
if (rampDownInProgCounterC == 0){
  rampDownInProgC = true;
  }
  rampDownInProgCounterC++;
            
            if (SmoothCounterRampC == 0) {
                  SmoothRampFlagC = true;
                }
            
                SmoothCounterRampC++;
            
                if (SmoothRampFlagC == true) {

                if (sign == 0){
                    smoothrampdowncounterC = sinvoltageout;}

                if (sign == 1){
                    smoothrampdowncounterC = triangvoltageout;}

                 if (sign == 2){
                    smoothrampdowncounterC = squarevoltageout;}
                    
                    SmoothRampFlagC = false;
                }
            
                    if (smoothrampdowncounterC > 0) {
                  smoothrampdowncounterC--;
                  PORTA = smoothrampdowncounterC;
                  analogWrite(outputPin_led, smoothrampdowncounterC);
                    }
            
                if (smoothrampdowncounterC == 0){
                    
                    SmoothFlag2C = false;
                    TempBlock2C = false;
                    SmoothCounterRampC = 0;
                    rampDownInProgC = false;
                }
   }
      
      }

//---------------------------------- output switched off -------------------------------
      
      if (SmoothFlag2C == false){

  //turn output off (set it to 0 voltage)
  voltageout = 0;
  PORTA = voltageout;
      

if (sign == 0){
digitalWrite(9, HIGH);

 lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltage) + " (Sin)" + "   ");


  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequency) + " (OFF)" + "   ");
}

  if (sign == 1){
digitalWrite(9, HIGH);

 lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltage)+ " (Tri)" + "   ");


  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequency)+ " (OFF)" + "   ");

  }
  
  if (sign == 2){
digitalWrite(9, HIGH);

 lcd.setCursor(0, 0);
  lcd.print("Volt "  + String(voltage)+ " (Sqr)"  + "   ");


  lcd.setCursor(0, 1);
  lcd.print("Freq "  + String(frequency)+ " (OFF)" + "   ");
  }
  
} 
 analogWrite(outputPin_led, voltageout);


      }




//-----------------------------------------------------------------------------------------------
//-------------------------------- Serial communication over usb-connection ---------------------------------------------------------------

void ReadInput() {  
 
while (Serial.available() >= 7 )
 {

    wave = Serial.read();
    v1 = Serial.read();
    v2 = Serial.read();
    v3 = Serial.read();
    f1 = Serial.read();
    f2 = Serial.read();
    f3 = Serial.read();
    Serial.flush();

voltageCom = v1 + v2/10.0 + v3/100.0;

frequencyCom = f1 + f2/10.0 + f3/100.0;

Serial.println(voltageCom); //sending back to java console
Serial.println(frequencyCom);

}
 }
 
//------------------------ wave form calculation -----------------------------------------------------
 //----------------------------------- SIN ------------------------------------------------------------
void SinBuilding() {

  if (frequency == 0) {
    sinvoltageout = realvoltage;
  }
  else {
    sinvoltageout = (realvoltage + realvoltage * sin( 2.0 * PI * frequency * t )) / 2;
  }

}

//-----------------------------------------------------------------------------------------------
void LastSinBuilding() {

  if (lastfrequency == 0) {
    lastsinvoltageout = lastrealvoltage;
  }
  else {
    lastsinvoltageout = (lastrealvoltage + lastrealvoltage * sin( 2.0 * PI * lastfrequency * t )) / 2;
  }

}


//-------------------------------------- SQUARE --------------------------------------------------------
void SquareBuilding(){

  if (frequency == 0) {
    squarevoltageout = realvoltage;
  }
  else {
 
  squarevoltageout = (realvoltage + realvoltage * sgn(sin(2*PI*t*frequency)))/2;
  
    }
  }

//----------------------------------------------------------------------------------------------
void LastSquareBuilding(){

  if (lastfrequency == 0) {
    lastsquarevoltageout = lastrealvoltage;
  }
  else {
  
  lastsquarevoltageout = (lastrealvoltage + lastrealvoltage * sgn(sin(2*PI*t*lastfrequency)))/2;
 
  
    }
  }

  

//----------------------------------------- TRIANGLE -----------------------------------------------------
void TriangleBuilding(){

  if (frequency == 0) {
    triangvoltageout = realvoltage;
  }
  else {

 triangvoltageout = (realvoltage + 2*realvoltage/PI * asin(sin(2.0*PI*t*frequency)))/2;
  
  
  }
}

//----------------------------------------------------------------------------------------------
void LastTriangleBuilding(){

  if (lastfrequency == 0) {
    lasttriangvoltageout = lastrealvoltage;
  }
  else {

lasttriangvoltageout = (lastrealvoltage + 2*lastrealvoltage/PI * asin(sin(2.0*PI*t*lastfrequency)))/2;
    
}
}


//-------------------------- signum function --------------------------------------------------------
static inline int8_t sgn(float val) {
 if (val < 0) return -1;
 if (val==0) return 0;
 return 1;
}


