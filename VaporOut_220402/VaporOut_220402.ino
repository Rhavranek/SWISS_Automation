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

//counter setups
int FlaskNumber = 16; // this is the number of the port you want to START ON
int SampleDay = 0; // sampling will start three days from when this is plugged in.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void setup()
{
  // ------Universal setup ------
  Serial.begin(9600); // use serial monitor to view outputs
  Serial.println("Code Started");

  // ----- OpenLog Setup -----
  OpenLog.begin(9600);

  //------ RTC setup -------
  SPI.setDataMode(SPI_MODE3); //I don't know why mode 3, but it makes it work
  rtc.begin(DS13074_CS_PIN);
  rtc.autoTime(); // uses the compiler's time, and is in 24 hour mode
  rtc.update();

  // ----- Valco setup -----
  Serial1.begin(9600); // communication on secondary serial port to talk to valco valve
  Serial.println("trying to talk to valco");
  PrintValcoPosition();

  // ----- Relay setup -----
  pinMode(relay, OUTPUT);

}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void loop() {
  if (FlaskNumber >1){
    Serial.println("CleanTubes started");
    CleanTubes();
    Serial.println("CleanTubes ended");
    delay(500);
    Serial.println("DeadEndPull started");        
    DeadEndPull();
    Serial.println("DeadEndPull ended");
    delay(500);
    Serial.println("CarrierGasPush started");
    CarrierGasPush();
    Serial.println("CarrierGasPush ended");
  }
}


