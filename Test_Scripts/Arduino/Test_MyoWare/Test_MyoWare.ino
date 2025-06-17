const int EnvPin = A0;  // Pinul de semnal envelopat al senzorului MyoWare conectat la A0
const int RawPin = A1; // Pinul de semnal brut al senzorului MyoWare conectat la A1
const int RectPin = A2; // Pinul de semnal rectificat al senzorului MyoWare conectat la A2

int env_sensorValue = 0;       // Variabilă pentru a stoca citirea senzorului pe pinul Env
int raw_sensorValue = 0;       // Variabilă pentru a stoca citirea senzorului pe pinul RAW
int rect_sensorValue = 0;       // Variabilă pentru a stoca citirea senzorului pe pinul Env

void setup() {
    Serial.begin(115200);  // Inițierea comunicației seriale
}

void loop() {
    env_sensorValue = analogRead(EnvPin);  // Citirea semnalului analogic
    raw_sensorValue = analogRead(RawPin);  
    rect_sensorValue = analogRead(RectPin);  

    //Serial.print("\nValoare senzor MyoWare: \nEnv: ");
    Serial.print("\n");
    Serial.print(env_sensorValue);          // Afișarea valorii în Monitorul Serial
    //Serial.print("; RAW: ");
    Serial.print("\t");
    Serial.print(raw_sensorValue);          // Afișarea valorii în Monitorul Serial
    //Serial.print("; Rect: ");
    Serial.print("\t");
    Serial.print(rect_sensorValue);          // Afișarea valorii în Monitorul Serial

    delay(100);  // Întârziere scurtă pentru a preveni suprasolicitarea ieșirii seriale
}
