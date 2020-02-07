
const int iSensor = 23;
boolean bIntruderDetected = false;

void setup() {
  Serial.begin(115200);
  Serial.print("\nStart of reed switch test");
  pinMode(iSensor, INPUT_PULLUP);      // Reed Switch
}

void loop() {
  int sensorValue = digitalRead(iSensor);
  if (sensorValue == 1) {
     bIntruderDetected = true;
     Serial.print("\nIntruder alert.");

  } else {
     if (bIntruderDetected) Serial.print("\nThe door is closed.");
     bIntruderDetected = false;
  }
  delay(500);
}
