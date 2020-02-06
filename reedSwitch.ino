
const int iSensor = 23;

void setup() {
   Serial.begin(115200);
   Serial.print("\nStart of reed switch test");
   pinMode(iSensor, INPUT_PULLUP);      // Rain sensor
}

void loop() {
   int sensorValue = digitalRead(iSensor);
   if (sensorValue == 0) Serial.print("\nIntruder alert.");
}