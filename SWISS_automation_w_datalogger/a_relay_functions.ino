void relayON () {
  digitalWrite(relay,HIGH);
  Serial.println("Relay ON");
}

void relayOFF () {
  digitalWrite(relay,LOW); //mimics turning off an on for now
  Serial.println("Relay OFF");
}