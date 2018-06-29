/***********************************
 * State machine 2, Vers. 1.0 
 * Einfache Schaltung mit Taster
 * State machine für Taster1
 * Der Hobbyelektroniker, 12.06.2018
 ***********************************/

// Pin - Definitionen
const int PIN_LED_GRUEN = 12;
const int PIN_LED_GELB = 11;
const int PIN_LED_ROT = 10;

const int PIN_TASTE1 = 7;
const int PIN_TASTE2 = 6;

int z_gruen; // Zustand der grünen Led (HIGH, LOW) 

void setup() {
  // Pin's vorbereiten
  pinMode(PIN_LED_GRUEN,OUTPUT);
  pinMode(PIN_LED_GELB,OUTPUT);
  pinMode(PIN_LED_ROT,OUTPUT);

  pinMode(PIN_TASTE1,INPUT_PULLUP);
  pinMode(PIN_TASTE2,INPUT_PULLUP);

  // Ausganszustand herstellen
  digitalWrite(PIN_LED_GRUEN,LOW);
  z_gruen = LOW;
  digitalWrite(PIN_LED_GELB,LOW);
  digitalWrite(PIN_LED_ROT,LOW);

}

void loop() {
  if (digitalRead(PIN_TASTE1) == LOW) {
    if (z_gruen == LOW) z_gruen = HIGH; else z_gruen = LOW;
    digitalWrite(PIN_LED_GRUEN,z_gruen);
    delay(300);
  }
  if (digitalRead(PIN_TASTE2) == LOW) {
    digitalWrite(PIN_LED_ROT,HIGH);
  } else {
    digitalWrite(PIN_LED_ROT,LOW);
  }


}
