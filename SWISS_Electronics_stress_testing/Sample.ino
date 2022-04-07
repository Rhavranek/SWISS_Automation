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


void Sample25(void)
{
  Serial.println("Starting Sample25");
  OpenLog.print("Starting 25 cm protocol at: ");
  RecordTime(); 
  delay (15);
  
  // step 1: relays on
    relayON(); 
    delay(20000);  // this needs to be long enough for everthing to turn on 
  
  // step 2: valco valve to position #1, sample probe open, flush the probe
    valcoHM();
    delay(1000);
    digitalWrite(ProbeBypass, HIGH); // say why
    delay(200); //Test that LOW is closed and not open
    digitalWrite(Probe25,LOW); 
    
    OpenLog.println("Flushing started at: ");
    RecordTime();
    delay(2000);
    
  
      //flush 300 seconds
      delay(300000);
  
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
        delay(2700000); //delays for 45 minutes 
        
        //advance flask number
        ++ FlaskNumber;
        valcoHM(); // step 4:back to safety!
      }; 
  
  
  
  delay(1000);
  digitalWrite(Probe25,HIGH); 
  digitalWrite(ProbeBypass, LOW);
}


void Sample50(void)
{
  Serial.println("Starting Sample50");
  OpenLog.print("Starting 50 cm protocol at: ");
  RecordTime(); 
  delay (15);
  
  // step 1: relays on
    relayON(); 
    delay(20000);  // this needs to be long enough for everthing to turn on 
  
  // step 2: valco valve to position #1, sample probe open, flush the probe
    valcoHM();
    delay(1000);
    digitalWrite(ProbeBypass, HIGH); // say why
    delay(200); //Test that LOW is closed and not open
    digitalWrite(Probe50,LOW); 
    
    OpenLog.println("Flushing started at: ");
    RecordTime();
    delay(2000);
    
  
      //flush 300 seconds
      delay(300000);
  
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
        delay(2700000); //delays for 45 minutes 
        
        //advance flask number
        ++ FlaskNumber;
        valcoHM(); // step 4:back to safety!
      }; 
  
  
  
  delay(1000);
  digitalWrite(Probe50,HIGH); 
  digitalWrite(ProbeBypass, LOW);
}

void Sample75(void)
{
  Serial.println("Starting Sample75");
  OpenLog.print("Starting 75 cm protocol at: ");
  RecordTime(); 
  delay (15);
  
  // step 1: relays on
    relayON(); 
    delay(20000);  // this needs to be long enough for everthing to turn on 
  
  // step 2: valco valve to position #1, sample probe open, flush the probe
    valcoHM();
    delay(1000);
    digitalWrite(ProbeBypass, HIGH); // say why
    delay(200); //Test that LOW is closed and not open
    digitalWrite(Probe75,LOW); 
    
    OpenLog.println("Flushing started at: ");
    RecordTime();
    delay(2000);
    
  
      //flush 300 seconds
      delay(300000);
  
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
        delay(2700000); //delays for 45 minutes 
        
        //advance flask number
        ++ FlaskNumber;
        valcoHM(); // step 4:back to safety!
      }; 
  
  
  
  delay(1000);
  digitalWrite(Probe75,HIGH); 
  digitalWrite(ProbeBypass, LOW);
}

void ShutDown () {
  
  //Make sure the valco is 'safe'
  valcoHM ();
  delay(3000);
  
  //Cut off air flow to the system
  digitalWrite(ProbeBypass, HIGH); //close the bypass valve 
  delay(200);
  
  //Turn off the MFC and valco valve
  relayOFF ();
  
  OpenLog.println("Sampling protocol is over, shutting down");
  RecordTime();
}