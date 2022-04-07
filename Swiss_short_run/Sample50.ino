void Sample50(void)
{
  Serial.println("Starting Sample50");
  OpenLog.print("Starting 50 cm protocol at: ");
  RecordTime(); 
  delay (15);
  
  // step 1: relays on
    relayON(); 
    delay(2000);
  
  // step 2: valco valve to position #1, sample probe open, flush the probe
    valcoHM();
    delay(1000);
    digitalWrite(ProbeBypass, HIGH);
    delay(200);
    digitalWrite(Probe50,LOW); 
    
    OpenLog.println("Flushing started at: ");
    RecordTime();
    delay(2000);
    
  
      //flush for 3 minutes
      delay(3000);
  
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
        delay(10000); //delays for 10 seconds  
        
        //advance flask number
        ++ FlaskNumber;
      }; 
  
  // step 4: back to safety!
  valcoHM();
  delay(1000);
  digitalWrite(Probe50,HIGH); 
  digitalWrite(ProbeBypass, LOW);
}


  