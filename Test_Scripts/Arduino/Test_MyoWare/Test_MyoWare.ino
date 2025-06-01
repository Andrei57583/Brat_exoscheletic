const int sensorPin = A1;  // Pinul de semnal al senzorului MyoWare conectat la A1
int sensorValue = 0;       // Variabilă pentru a stoca citirea senzorului

void setup() {
    Serial.begin(115200);  // Inițierea comunicației seriale
}

void loop() {
    sensorValue = analogRead(sensorPin);  // Citirea semnalului analogic
    Serial.print("Valoare senzor MyoWare: ");
    Serial.println(sensorValue);          // Afișarea valorii în Monitorul Serial
    delay(100);  // Întârziere scurtă pentru a preveni suprasolicitarea ieșirii seriale
}
