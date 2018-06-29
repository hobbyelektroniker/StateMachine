/***********************************
 * State machine 6, Vers. 1.0 
 * Automatische Schaltung 
 * Schaltet Zuständ rot - rot/gelb - grün - gelb - rot
 * Der Hobbyelektroniker, 12.06.2018
 ***********************************/

// Pin - Definitionen
const int PIN_LED_GRUEN = 12;
const int PIN_LED_GELB = 11;
const int PIN_LED_ROT = 10;

const int PIN_TASTE1 = 7;
const int PIN_TASTE2 = 6;

// Zustände
const int Z_KEINE = 0;
const int Z_ROT = 1;
const int Z_GELB = 2;
const int Z_GRUEN = 3;
const int Z_ROT_GELB = 4;


// Variablen für Ereignisse
bool e_taste1;
bool e_taste2;
bool e_takt;

// Variablen für Zustände
int zustand;

void keine() {
  digitalWrite(PIN_LED_GRUEN,LOW);
  digitalWrite(PIN_LED_GELB,LOW);
  digitalWrite(PIN_LED_ROT,LOW);
  zustand = Z_KEINE;
  e_taste1 = false;
  e_taste2 = false;
}

void rot() {
  Serial.println("rot");
  digitalWrite(PIN_LED_GRUEN,LOW);
  digitalWrite(PIN_LED_GELB,LOW);
  digitalWrite(PIN_LED_ROT,HIGH);
  zustand = Z_ROT;
  e_taste1 = false;
  e_takt = false;
}

void gruen() {
  Serial.println("gruen");
  digitalWrite(PIN_LED_GRUEN,HIGH);
  digitalWrite(PIN_LED_GELB,LOW);
  digitalWrite(PIN_LED_ROT,LOW);
  zustand = Z_GRUEN;
  e_taste1 = false;
  e_takt = false;
}

void gelb() {
  digitalWrite(PIN_LED_GRUEN,LOW);
  digitalWrite(PIN_LED_GELB,HIGH);
  digitalWrite(PIN_LED_ROT,LOW);
  zustand = Z_GELB;
  e_taste1 = false;
  e_takt = false;
}

void rot_gelb() {
  digitalWrite(PIN_LED_GRUEN,LOW);
  digitalWrite(PIN_LED_GELB,HIGH);
  digitalWrite(PIN_LED_ROT,HIGH);
  zustand = Z_ROT_GELB;
  e_taste1 = false;
  e_takt = false;
}

void takt() {
  static unsigned long start= 0;
  if (start+1000 < millis()) {
    e_takt = true;
    start = millis();
  }
}

void ereignisse() {
  if (digitalRead(PIN_TASTE1) == LOW) {
    e_taste1 = true;
    delay(300); 
  }
  if (digitalRead(PIN_TASTE2) == LOW) {
    e_taste2 = true;
    delay(300); 
  }
  takt();
}

void verarbeitung() {
  if (e_taste2) keine(); // Taste 2 schaltet sofort aus
  if (e_taste1 || e_takt) { // Die Aktion hängt vom aktuellen Zustand ab
    switch(zustand) {
      case Z_KEINE: rot(); break;
      case Z_ROT: rot_gelb(); break;
      case Z_ROT_GELB: gruen(); break;
      case Z_GRUEN: gelb(); break;
      case Z_GELB: rot(); break;
    }
  }
}


void setup() {
  // Pin's vorbereiten
  pinMode(PIN_LED_GRUEN,OUTPUT);
  pinMode(PIN_LED_GELB,OUTPUT);
  pinMode(PIN_LED_ROT,OUTPUT);

  pinMode(PIN_TASTE1,INPUT_PULLUP);
  pinMode(PIN_TASTE2,INPUT_PULLUP);

  // Ausgangszustand herstellen
  digitalWrite(PIN_LED_GRUEN,LOW);
  digitalWrite(PIN_LED_GELB,LOW);
  digitalWrite(PIN_LED_ROT,LOW);
  zustand = Z_KEINE;
  e_taste1 = false;
  e_taste2 = false;
  e_takt = false;
}

void loop() {
  ereignisse();
  verarbeitung();
}
