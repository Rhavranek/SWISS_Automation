v/*
This is the March 30, 2022 version of the automation code for the Soil Water Isotope Stroage System.

Updates:
1.
3.
4.
*/

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// ---- RTC LIBRARIES & GLOBALS -----
#include <SPI.h>
#include <SparkFunDS3234RTC.h>
#define PRINT_USA_DATE
#define DS13074_CS_PIN 53 // DeadOn RTC Chip-select pin

// --- OpenLog LIBRARIES & GLOBALS----
#include <SoftwareSerial.h>
SoftwareSerial OpenLog(0,12); // 0 = Soft RX pin (not used, if in the future I want to listen to the datalogger, then change), 12 = Soft TX pin
  //Connect RXI of OpenLog to pin 12 on Arduino
// Power relay global
int relay = 13;

// SMC manifold globals
int Probe25 = 11;
int Probe50 = 10;
int Probe75 = 9;
int ProbeBypass = 8;

//counter setups
int FlaskNumber = 2; // this is the number of the port you want to START ON
int SampleDay = 0; // sampling will start three days from when this is plugged in.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= SETUP LOOP -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void setup()
{
  // ------Universal setup ------
  Serial.begin(9600); // use serial monitor to view outputs

  // ----- OpenLog Setup -----
  OpenLog.begin(9600);

  //------ RTC setup -------
  SPI.setDataMode(SPI_MODE3); //I don't know why mode 3, but it makes it work
  rtc.begin(DS13074_CS_PIN);
  rtc.autoTime(); // uses the compiler's time, and is in 24 hour mode
  rtc.update();

  //rtc.enableAlarmInterrupt(); // I don't think I actually need this line b/c I don't use the interupt
  rtc.setAlarm2(0); // (<minute>, <hour>, <date>, <day/date>), This sets off an alarm at the top of the hour

  // ----- Valco setup -----
  Serial1.begin(9600); // communication on secondary serial port to talk to valco valve

  // ----- Relay setup -----
  pinMode(relay, OUTPUT);

  // ----- manifold setup ------
  pinMode(Probe25, OUTPUT);
  pinMode(Probe50, OUTPUT);
  pinMode(Probe75, OUTPUT);
  pinMode(ProbeBypass, OUTPUT);

  digitalWrite(Probe25, HIGH); //High is closed
  digitalWrite(Probe50, HIGH); //High is closed
  digitalWrite(Probe75, HIGH); //High is closed
  digitalWrite(ProbeBypass, HIGH); //High is closed
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void loop()
{
  if(rtc.alarm2())
    {
      ++ SampleDay; // depends on not losing power the entire month (BOLD)
      delay(20);
      rtc.setAlarm2(0); ///(<minute>, <hour>, <date>, <day/date>),
      delay(20);
    }

    if(SampleDay == 5) // This is so that I only take a sample every 5 hours.
    {
      CleanOut();

      Sample25();
      Sample50();
      Sample75();

      CleanOut();
      ShutDown();

      SampleDay = 0; // reset the sample day
    }
  }



}
