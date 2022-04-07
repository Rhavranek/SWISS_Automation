void ShutDown () {
  Serial.println("About to shut down womp womp");
  //Make sure the valco is 'safe'
  valcoHM ();
  delay(3000);
  
  //Cut off air flow to the system
  digitalWrite(ProbeBypass, HIGH);
  delay(200);
  
  //Turn off the MFC and valco valve
  relayOFF ();
  
  OpenLog.println("Sampling protocol is over, shutting down");
  RecordTime();

}