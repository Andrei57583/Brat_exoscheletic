const int INA = 13;
const int INB = 12;
const int PWM = 11;

const int sensorPin = A1;  // MyoWare signal pin connected to A0
int sensorValue = 0;       // Variable to store sensor reading

bool flag_ridicat = false;

int angle = 0;

void setup() {
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(PWM, OUTPUT);

  

  Serial.begin(9600);

}

void loop() {
    
  sensorValue = analogRead(sensorPin);  // Read the analog signal
  Serial.print("MyoWare Sensor Value: ");
  Serial.println(sensorValue);          // Print the value to Serial Monitor
  delay(100);  // Short delay to prevent overwhelming serial output

  if (sensorValue >= 500 && flag_ridicat == false) 
  {
    ridicare_mana();
    stop_motor();
    flag_ridicat = !flag_ridicat;
    delay(3000);

  } else if (sensorValue <= 500 && flag_ridicat == true) {
    coborare_mana();
    stop_motor();
    flag_ridicat = !flag_ridicat;
    delay(3000);
  } 
  
}


void ridicare_mana() {

  Serial.println("Se ridica mana!");
  Serial.println(flag_ridicat);

  digitalWrite(INA, HIGH);  // direcție înainte
  digitalWrite(INB, LOW);

  while(angle < 90)
  { 
    Serial.println("Unghi: ");
    Serial.print(angle);
    analogWrite(PWM, 240);
    delay(500);
    angle++;
  }
  
}

void coborare_mana() {

  Serial.println("Se coboara mana!");
  Serial.println(flag_ridicat);

  digitalWrite(INA, LOW);  // direcție înapoi
  digitalWrite(INB, HIGH);

  while(angle > 0)
  {
    Serial.println("Unghi: ");
    Serial.print(angle);
    analogWrite(PWM, 240);
    delay(500);
    angle--;
  }
  
}

void stop_motor() {

  Serial.println("Se opreste mana!");

  analogWrite(PWM, 0);
}