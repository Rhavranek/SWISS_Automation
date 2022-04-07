int FlaskNumber = 16; // this is the number of the port you want to START ON

void setup() {
  Serial.begin(9600);

   // ----- Valco setup -----
  Serial1.begin(9600); // communication on secondary serial port to talk to valco valve
  Serial.println("trying to talk to valco");
  PrintValcoPosition();

}

void loop() {
  ++FlaskNumber;
  delay(10);
  Serial.println("valcoUP");
  Serial.println(FlaskNumber);
  delay(500);

  valcoUP();
  Serial1.println(FlaskNumber);
  delay(10000);


  --FlaskNumber;
  --FlaskNumber;
  delay(10);
  Serial.println("valcoDOWN");
  Serial.println(FlaskNumber);
  delay(500);


  valcoDOWN();
  Serial1.println(FlaskNumber);
  delay(10000);

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

// ------ Save valco position to the monitor ------
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