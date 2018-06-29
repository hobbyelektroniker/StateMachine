/***********************************
 * State machine 1, Vers. 1.0 
 * Einfache Schaltung mit Taster
 * Keine state machine!
 * Der Hobbyelektroniker, 12.06.2018
 ***********************************/

// Pin - Definitionen
const int PIN_LED_GRUEN = 12;
const int PIN_LED_GELB = 11;
const int PIN_LED_ROT = 10;

const int PIN_TASTE1 = 7;
const int PIN_TASTE2 = 6;

  

void setup() {
  // Pin's vorbereiten
  pinMode(PIN_LED_GRUEN,OUTPUT);
  pinMode(PIN_LED_GELB,OUTPUT);
  pinMode(PIN_LED_ROT,OUTPUT);

  pinMode(PIN_TASTE1,INPUT_PULLUP);
  pinMode(PIN_TASTE2,INPUT_PULLUP);

  // Ausganszustand herstellen
  digitalWrite(PIN_LED_GRUEN,LOW);
  digitalWrite(PIN_LED_GELB,LOW);
  digitalWrite(PIN_LED_ROT,LOW);

}

void loop() {
  if (digitalRead(PIN_TASTE1) == LOW) {
    digitalWrite(PIN_LED_GRUEN,HIGH);
  } else {
    digitalWrite(PIN_LED_GRUEN,LOW);
  }
  if (digitalRead(PIN_TASTE2) == LOW) {
    digitalWrite(PIN_LED_ROT,HIGH);
  } else {
    digitalWrite(PIN_LED_ROT,LOW);
  }


}
