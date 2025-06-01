const int INA = 13;
const int INB = 12;
const int PWM = 11;

void setup() {
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(PWM, OUTPUT);

  Serial.begin(9600);
  delay(1000);
  Serial.println("Test Driver Motor");

  digitalWrite(INA, HIGH);  // direcție înainte
  digitalWrite(INB, LOW);
}

void loop() {
  // Creștere treptată a vitezei
  for (int speed = 0; speed <= 255; speed += 10) {
    analogWrite(PWM, speed);
    Serial.print("Viteză PWM = ");
    Serial.println(speed);
    delay(300);
  }

  // Pauză cu motorul oprit
  analogWrite(PWM, 0);
  Serial.println("Oprit. Pauză 3 secunde...");
  delay(3000);

  // Schimbă direcția motorului
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);
  Serial.println("Schimb direcția.");

  for (int speed = 0; speed <= 255; speed += 10) {
    analogWrite(PWM, speed);
    Serial.print("Viteză PWM = ");
    Serial.println(speed);
    delay(300);
  }

  analogWrite(PWM, 0);
  Serial.println("Oprit. Pauză 3 secunde...");
  delay(3000);

  // Revine la direcția inițială
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);
}
