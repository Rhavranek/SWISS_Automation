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