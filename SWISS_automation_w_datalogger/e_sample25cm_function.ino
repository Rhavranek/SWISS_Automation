void Sample25(void)
{
  OpenLog.print("Starting 25 cm protocol at: ");
  RecordTime(); 
  delay (15);
  
  // step 1: relays on
    relayON(); 
    delay(20000);  // this needs to be long enough for everthing to turn on 
  
  // step 2: valco valve to position #1, sample probe open, flush the probe
    valcoHM();
    delay(1000);
    digitalWrite(ProbeBypass, HIGH); // this closes probe bypass 
    delay(200); //Test that LOW is closed and not open
    digitalWrite(Probe25, LOW); //this OPENS Probe 25
    
    OpenLog.println("Flushing started at: ");
    RecordTime();
    delay(2000);
    
  
      //flush for 10 minutes, 600 seconds
      delay(600000);
  
  // step 3: open the flask, and flush for 45 minutes
    if (FlaskNumber < 17)
      {
        //move the valco
        valcoUP();
        Serial1.println (FlaskNumber);
        
        //log info
        RecordTime();
        delay(15);
        
        OpenLog.print("Valco should be going to: ");
        OpenLog.println(FlaskNumber);
        delay(15);
        RecordValcoPosition();
        
        //wait
        delay(2700000); //delays for 45 minutes - the arduino can't do anything else in this time. Another way to do this would be to set an alarm 
        
        //advance flask number
        ++ FlaskNumber;
        valcoHM(); // step 4:back to safety!
      }; 
  
  
  
  delay(1000);
  digitalWrite(Probe25,HIGH); // close Probe 25 
  digitalWrite(ProbeBypass, LOW); //Having probe bypass open is the norm 
}