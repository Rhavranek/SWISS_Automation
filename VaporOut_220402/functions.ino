void relayON () {
  digitalWrite(relay,HIGH);
  Serial.println("Relay ON");
}

void relayOFF () {
  digitalWrite(relay,LOW); //mimics turning off an on for now
  Serial.println("Relay OFF");
}

//=-=-=-=-=-=-=----=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void valcoUP (){
  Serial1.print("CW"); // there needs to be a line ending if this is to work on its own (serial.println), but this is designed to
}

void valcoDOWN (){
  Serial1.print("CC");
}

void valcoHM (){
  Serial1.println("CW1"); //there is another valco command ("HM"), but that takes the fastest route to HM, and I just want to go one way
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

// ------ Save valco position to the OpenLog ------
void PrintValcoPosition(void) {
  Serial.println("Hello - trying to talk to valco");
  Serial1.println("CP");
  delay(3000);

  String msg = String("");  //get

  if(Serial1.available() > 0)
  {
    while(Serial1.available() > 0)
    {
      msg += char(Serial1.read());
      delay(1000);
     }
    Serial.print("The valco valve's current postion (CP) is: ");
    Serial.println(msg);
  }
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

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

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-

void CleanTubes() {

  OpenLog.println("Starting cleaning protocol at: ");
  RecordTime();
  delay(1000);

  // step 1: relays on
  relayON();
  OpenLog.println ("Relay On");
  delay(20000); //give everything 20 seconds to turn on
  Serial.println("Relay On");

  // step 2: valco valve to position #1 (jumper loop)
  valcoHM();
  OpenLog.println ("Valco in position 1");

  delay(300000); //flush for five minutes

  relayOFF();
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void DeadEndPull() {
  valcoDOWN();
  Serial1.println (FlaskNumber);

  //log info
  OpenLog.println("Starting Dead-End pull on Flask number");
  OpenLog.println(FlaskNumber);
  RecordValcoPosition();
  delay(15);

  OpenLog.println("The time this flask started is:");
  RecordTime();
  delay(15);

  delay(420000); //measure for 7 minutes
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void CarrierGasPush(){
  //log info

  OpenLog.println("Starting Carrier Gas push on Flask number");
  OpenLog.println(FlaskNumber);
  RecordValcoPosition();
  delay(15);

  OpenLog.println("The time I started doing a carrier gas push at is:");
  RecordTime();
  delay(15);

  relayON();

  delay(300000); //flush for 5 more minutes 

  --FlaskNumber; //set the FlaskNumber for the next cycle 
  delay(20);
}
