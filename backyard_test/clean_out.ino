/*
The purpose of this function is to:
1. flush condensation
2. any lingering vapor from the previous sampling attempt
3. 15 minutes is based on lab protocol w/ dry-air
*/

void CleanOut()
{
  OpenLog.println("Starting cleaning protocol at: ");
  RecordTime();
  delay(1000);

  // step 1: relays on
  relayON();
  OpenLog.println ("Relay On");
  delay(20000); //give everything 20 seconds to turn on

  // step 2: valco valve to position #1 (jumper loop)
  valcoHM();
  OpenLog.println ("Valco in position 1");
  delay(5000);

  //open the manifold sample bypass loop
  digitalWrite(ProbeBypass, LOW); //Low OPENS the valve

  //delay 15 minutes, 900 seconds
  delay(900000);

  //write to SD card
  OpenLog.print("Finished cleaning protocol at:");
  RecordTime();
  delay(15);
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void ShutDown ()
{  
  //Make sure the valco is 'safe'
  valcoHM ();
  delay(3000);

  //Cut off air flow to the system
  digitalWrite(ProbeBypass, LOW);
  delay(200);

  //Turn off the MFC and valco valve
  relayOFF ();

  OpenLog.println("Sampling protocol is over, shutting down");
  RecordTime();
}
