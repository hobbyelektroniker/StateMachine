/***********************************
 * State machine 9, Vers. 1.0 
 * Automatische Schaltung mit verschiedenen Schaltzeiten 
 * Schaltet Zuständ rot - rot/gelb - grün - gelb - rot
 * Taste1: gelb blinken, Taste2: normal
 * Optimierte Version
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
const int Z_GELB_BLINK = 5;

// Variablen für Ereignisse
bool e_taste1;
bool e_taste2;
bool e_takt;

// Variablen für Zustände
int zustand;

void neuer_zustand(int z_neu) {
  if (zustand == Z_GELB_BLINK && z_neu == Z_GELB_BLINK) {
    digitalWrite(PIN_LED_GELB,!digitalRead(PIN_LED_GELB)); // blinken
    e_taste1 = false;
  } else {
    digitalWrite(PIN_LED_GRUEN,(z_neu == Z_GRUEN));
    digitalWrite(PIN_LED_GELB,(z_neu == Z_GELB || z_neu == Z_ROT_GELB));
    digitalWrite(PIN_LED_ROT,(z_neu == Z_ROT || z_neu == Z_ROT_GELB));
    e_taste2 = false;
  }
  zustand = z_neu;
  e_takt = false;
}

void takt() {
  static unsigned long start= 0;
  int zeit;
  switch (zustand) {
    case Z_ROT: zeit = 5000; break;
    case Z_GRUEN: zeit = 2000; break;
    default: zeit = 1000;
  }
  if (start+zeit < millis()) {
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
  if (e_taste1) neuer_zustand(Z_GELB_BLINK); // Start Blink-Modus
  if (e_takt) { // Die Aktion hängt vom aktuellen Zustand ab
    switch(zustand) {
      case Z_KEINE: neuer_zustand(Z_ROT); break;
      case Z_ROT: neuer_zustand(Z_ROT_GELB); break;
      case Z_ROT_GELB: neuer_zustand(Z_GRUEN); break;
      case Z_GRUEN: neuer_zustand(Z_GELB); break;
      case Z_GELB: neuer_zustand(Z_ROT); break;
      case Z_GELB_BLINK: neuer_zustand(Z_GELB_BLINK); break;
    }
  }
  if (e_taste2) neuer_zustand(Z_ROT); // Blinkmodus beenden
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
