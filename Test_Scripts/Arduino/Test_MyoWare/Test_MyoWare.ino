const int sensorPin = A1;  // MyoWare signal pin connected to A0
int sensorValue = 0;       // Variable to store sensor reading

void setup() {
    Serial.begin(115200);  // Start serial communication
}

void loop() {
    sensorValue = analogRead(sensorPin);  // Read the analog signal
    Serial.print("MyoWare Sensor Value: ");
    Serial.println(sensorValue);          // Print the value to Serial Monitor
    delay(100);  // Short delay to prevent overwhelming serial output
}
