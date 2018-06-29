/***********************************
 * State machine 3, Vers. 1.0 
 * Einfache Schaltung mit Taster
 * State machine für Taster1, vereinfachte Version
 * Der Hobbyelektroniker, 12.06.2018
 ***********************************/

// Pin - Definitionen
const int PIN_LED_GRUEN = 12;
const int PIN_TASTE1 = 7;

void setup() {
  // Pin's vorbereiten
  pinMode(PIN_LED_GRUEN,OUTPUT);
  pinMode(PIN_TASTE1,INPUT_PULLUP);

  // Ausganszustand herstellen
  digitalWrite(PIN_LED_GRUEN,LOW);
}

void loop() {
  if (digitalRead(PIN_TASTE1) == LOW) {
    digitalWrite(PIN_LED_GRUEN,!digitalRead(PIN_LED_GRUEN));
    delay(300);
  }
}
