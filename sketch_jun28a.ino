const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(9600);
  Serial.println("Reaktionsspiel startet...");
  randomSeed(analogRead(A0)); // Irgendwo unbenutzten analogen Pin lesen
}

void loop() {
  // Countdown: LEDs nacheinander an
  digitalWrite(led1, HIGH);
  delay(500);
  digitalWrite(led1, LOW);

  digitalWrite(led2, HIGH);
  delay(300);
  digitalWrite(led2, LOW);

  digitalWrite(led3, HIGH);
  delay(200);
  digitalWrite(led3, LOW);

  // Serielle Eingaben VOR der Reaktionsphase verwerfen
  while (Serial.available() > 0) {
    Serial.read();
  }
  
  // 🔄 Zufällige Wartezeit vor Start (zwischen 0,5 und 3 Sekunden)
  int waitTime = random(500, 3000);
  delay(waitTime);

  // Reaktionsphase: alle LEDs an
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  Serial.println("🚨 JETZT drücken! (Enter im Serial Monitor)");

  bool reacted = false;
  unsigned long startTime = millis();

  // 1 Sekunde Zeit zum Reagieren
  while (millis() - startTime < 1000) {
    if (Serial.available() > 0) {
      Serial.read();  // Eingabe abfangen (Enter)
      reacted = true;
      break;
    }
  }

  // Alle LEDs aus
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  delay(300); // kurze Pause

  // Ergebnis-Auswertung mit Blinkanzeige
  if (reacted) {
    Serial.println("gut");
    blinkLED(led1, 2, 200); // grün blinkt 2x
  } else {
    Serial.println("verkackt");
    blinkLED(led3, 2, 200); // rot blinkt 2x
  }

  delay(2000); // Pause vor nächster Runde
}

void blinkLED(int pin, int times, int duration) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(duration);
    digitalWrite(pin, LOW);
    delay(duration);
  }
}