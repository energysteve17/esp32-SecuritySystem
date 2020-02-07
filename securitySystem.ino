
/*************************************************************************************************
* 
* STEAM Security System                                               by Steven P. Hinkel
* 
* This program is designed for tutorial / learning purposes.  This secuirty system is a 
* good proxy to demonstrate inputs and outputs.  We will be using a reed switch as our 
* primary input.  For an output, we will be using both an LED and a Piezo Buzzer.
* 
* 
* sph Pinout
* ------------
* REED     ESP32 
* wire1    GND
* wire2    GPIO23  NOTE:use internal pullup, no resistor required.
* 
* BUZZER   ESP32
* RED      GPIO19
* Black    GND
* 
* 
* Change Log:
* -------------
* 1.0 Original version created  
*   
*   
*************************************************************************************************/


//------------------------------------
// Global variables
boolean bDebug = false;
boolean bIntruderDetected = false;

// Sensor's declarations / pinout
const int CONST_iBuzzerPin = 19;
const int CONST_iReedSwitchPin = 23;
const int CONST_iLEDPin = 2;
//const int CONST_iLEDPin = 21;

// Timeslice variables to avoid blocking delays.
unsigned long lOneDayInterval = 0;        // interval how often to send email alerts, limited to daily.
unsigned long lLastReadSensor = 0;        // millis tiimer to read water level every minute;
unsigned long lReadSensorInterval = 0;    // millis tiimer to read water level every minute, but allow first time thru;


//----------------------------------------
//Functions

void fPrintMessage(String sMsg) {

  // print function that will only display when the bDebug variable is set to true;  this is good
  // to turn on while learning, and then set to false when promoted to production.

  if (bDebug) {
     Serial.print("\n");
     Serial.print(sMsg);  
  }
  return;
}


void fToggleLED(int iOnOff) {

  // turn on an LED as a proxy for testing outputs.  the hiletGo ESP32's onboard led = GPIO2.

  if (iOnOff == 1) {
     digitalWrite(CONST_iLEDPin, HIGH);   // turn the LED on (HIGH is the voltage level)
     //Serial.print("\nturning ON LED.");
  } else {
     digitalWrite(CONST_iLEDPin, LOW);    // turn the LED off by making the voltage LOW
  }

  return;
}



void fPlayAlertBeep() {

  // pulse buzzer for a beeping sound pattern uppon startup, wifi failure, etc.
  // play with the delay values to produce various tunes.

  for (int iCtr= 0; iCtr < 3; iCtr++) {
     fToggleBuzzer(1);            
     delay(200);
     fToggleBuzzer(0);            
     delay(70);
  }

  return;
}



void fToggleBuzzer(int iOnOff) {

  // this function toggles a buzzer to serve as a local alert.

  //pinMode(CONST_iBuzzerPin, OUTPUT);
  if (iOnOff == 1) {
     digitalWrite(CONST_iBuzzerPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
     digitalWrite(CONST_iBuzzerPin, LOW);    // turn the LED off by making the voltage LOW
  }

  return;
}



int fReadSensor() {

  // This function reads the reed switch sensor.  Result will equal 0 if door closed and 1 when door open.

  int iSensorValue = digitalRead(CONST_iReedSwitchPin);
  fPrintMessage("Sensor Value=" + String(iSensorValue));

  return iSensorValue;
}



void setup() {

  // This function is called automatically upon powering up.  Here we tell the ESP32 what we
  // have attached to each physical pin.

  Serial.begin(115200);
  Serial.print("\nStart of securitySystem tutorial.");
  fPrintMessage("\nThis is how i am configured:");
  fPrintMessage("   my reed switch is attached to GND an GPIO=" + String(CONST_iReedSwitchPin));
  fPrintMessage("   my piezo buzzer is attached to GND an GPIO=" + String(CONST_iBuzzerPin));
  fPrintMessage("   my LED is attached to GND an GPIO=" + String(CONST_iLEDPin));

  pinMode(CONST_iReedSwitchPin, INPUT_PULLUP);      // reed switch
  pinMode(CONST_iBuzzerPin, OUTPUT);                // piezo buzzer
  pinMode(CONST_iLEDPin, OUTPUT);                   // external or onboard LED

  //analogReadResolution(12);                       // esp32's 12-bit resolution.
  fPlayAlertBeep();

  fToggleBuzzer(0);
  fToggleLED(0);

  return;
}



void loop() {

  // This function is automaticaly called after the setup function.  It will perpetually repeat.

  int iSensor = 0;

  // read sensor every second.  if-millis is like a delay, but does not halt all processing.
  unsigned long lCurrentMilliSeconds = millis();
  if (lCurrentMilliSeconds - lLastReadSensor >= lReadSensorInterval) {
     lLastReadSensor = lCurrentMilliSeconds;  // keep b4 calc function to accound for the 100 seconds of calculating.
     iSensor = fReadSensor();
     lReadSensorInterval = 500;               // 1/2 of a second.  
  }

  if (iSensor == 1) {                         // The reed switch is reporting the door is OPEN
     bIntruderDetected = true;
     fToggleBuzzer(1);
     fToggleLED(1);
     // add send eMail / TXT here?
     Serial.print("\nIntruder alert.");
     delay(3000);                             // Typically an alarm drop will run several/many minutes.
  } else {                         
     if (bIntruderDetected) {
        fToggleBuzzer(0);
        fToggleLED(0);
     }
     bIntruderDetected = false;
  }


}