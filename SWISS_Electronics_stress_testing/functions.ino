
// -=-=-=-=- RELAY FUNCTIONS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void relayON () {
  digitalWrite(relay,HIGH);
  Serial.println("Relay ON");
}

void relayOFF () {
  digitalWrite(relay,LOW); //mimics turning off an on for now
  Serial.println("Relay OFF");
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


// -=-=-=-=- VALCO FUNCTIONS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void valcoUP (){
  Serial1.print("CW"); // there needs to be a line ending if this is to work on its own (serial.println), but this is designed to 
}

void valcoDOWN (){
  Serial1.print("CC");
}

void valcoHM (){
  Serial1.println("CW1"); //there is another valco command ("HM"), but that takes the fastest route to HM, and I just want to go one way
}

// ----- Print valco position to the serial monitor --------
void CheckValcoValve(void){
  Serial1.println("CP");
  delay(2000);
  
  String msg = String("");  //get
  
  if(Serial1.available() > 0)
  {
    while(Serial1.available() > 0)
    {
      msg += char(Serial1.read());
      delay(10); 
     }
    Serial.print("FromValco,");
    Serial.println(msg);
  }
}

// ------ Save valco position to the OpenLog ------ 
void RecordValcoPosition(void) {
  Serial1.println("CP");
  delay(1000);
  
  String msg = String("");  //get
  
  if(Serial1.available() > 0)
  {
    while(Serial1.available() > 0)
    {
      msg += char(Serial1.read());
      delay(10); 
     }
    OpenLog.print("The valco valve's current postion (CP) is: ");
    OpenLog.println(msg);
  }
}  

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// -=-=-=-=- RTC FUNCTIONS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// ---- Record time to the OpenLog -------
void RecordTime(void)
{
  rtc.update(); //read the register all at once
  
  //Date
  OpenLog.print("Today's date is: ");
  OpenLog.println(String(rtc.month()) + "/" +   // Print month
                  String(rtc.date()) + "/" +
                  String (rtc.year())
                );
  
  //Time
  OpenLog.print("The time is: ");
  OpenLog.print(String(rtc.hour()) + ":");
  
  if (rtc.minute() < 10)
    OpenLog.print('0'); // Print leading '0' for minute
  OpenLog.print(String(rtc.minute()) + ":"); // Print minute
  
  if (rtc.second() < 10)
    OpenLog.print('0'); // Print leading '0' for second
  OpenLog.println(String(rtc.second())); // Print second
}


//// ------ PRINT TIME FUNCTION ---------
void printTime(void)  // e.g. 7:32:16 | Monday October 31, 2016
{
  Serial.print(String(rtc.hour()) + ":"); // Print hour
  if (rtc.minute() < 10)
    Serial.print('0'); // Print leading '0' for minute
  Serial.print(String(rtc.minute()) + ":"); // Print minute
  if (rtc.second() < 10)
    Serial.print('0'); // Print leading '0' for second
  Serial.print(String(rtc.second())); // Print second

  Serial.print(" | ");

    // Few options for printing the day, pick one:
    Serial.print(rtc.dayStr()); // Print day string
    //Serial.print(rtc.dayC()); // Print day character
    //Serial.print(rtc.day()); // Print day integer (1-7, Sun-Sat)
    Serial.print(" - ");
  #ifdef PRINT_USA_DATE
    Serial.print(String(rtc.month()) + "/" +   // Print month
                   String(rtc.date()) + "/");  // Print date
  #else
    Serial.print(String(rtc.date()) + "/" +    // (or) print date
                   String(rtc.month()) + "/"); // Print month
  #endif
    Serial.println(String(rtc.year()));        // Print year
}  
  
////------- COUNT SECONDS FUNCTION ----------------   

void countSeconds(void)
{
  static int8_t lastSecond = -1;
// Call rtc.update() to update all rtc.seconds(), rtc.minutes(),
// etc. return functions.
  rtc.update();
  if (rtc.second() != lastSecond) // If the second has changed
  {
    printTime(); // Print the new time
    lastSecond = rtc.second(); // Update lastSecond value
  }   
}  