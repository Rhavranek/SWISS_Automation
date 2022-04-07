void CleanOut() 
{
  Serial.println("what up what up");
  OpenLog.println("Starting cleaning protocol at: ");
  RecordTime();
  delay(100);

  // step 1: relays on
  relayON();
  OpenLog.println ("Relay On");
  delay(20000);

  // step 2: valco valve to position #1 (jumper loop)
  valcoHM();
  //OpenLog.println ("Valco in position 1")
  delay(5000);

  //open the manifold sample bypass loop
  digitalWrite(ProbeBypass, LOW);

  //delay 3 seconds
  delay(3000);

  //write to SD card
  OpenLog.print("Finished cleaning protocol at:");
  RecordTime();
  delay(200);
}