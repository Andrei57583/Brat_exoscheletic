const int potPin = A0;  // Pinul unde este conectat potențiometrul
int potValue = 0;       // Variabilă pentru valoarea citită
float angle = 0;        // Variabilă pentru unghiul calculat

void setup() {
    Serial.begin(9600);  // Inițializează comunicația serială
}

void loop() {
    potValue = analogRead(potPin);  // Citește valoarea de la potențiometru
    angle = map(potValue, 0, 1023, 0, 300);  // Convertim valoarea într-unghi între 0° și 300°
    
    Serial.print("Valoare pot: ");
    Serial.print(potValue);
    Serial.print(" | Unghi: ");
    Serial.print(angle);
    Serial.println("°");

    delay(100);  // Mică întârziere pentru stabilizare
}
