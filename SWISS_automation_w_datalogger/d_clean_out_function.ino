void CleanOut() 
{
  OpenLog.println("Starting cleaning protocol at: ");
  RecordTime();
  delay(1000);

  // step 1: relays on
  relayON();
  //OpenLog.println ("Relay On")
  delay(20000); // give everything 20 seconds to turn on

  // step 2: valco valve to position #1 (jumper loop)
  valcoHM();
  //OpenLog.println ("Valco in position 1")
  delay(5000);

  //open the manifold sample bypass loop
  digitalWrite(ProbeBypass, LOW); //Low OPENS the valve 

  //delay 5 minutes, 300 seconds
  delay(300000);

  //write to SD card
  OpenLog.print("Finished cleaning protocol at:");
  RecordTime();
  delay(15);
}
