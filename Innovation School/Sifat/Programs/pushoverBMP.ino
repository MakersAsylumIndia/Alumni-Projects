#define USE_ARDUINO_INTERRUPTS false
#include <ESP8266WiFi.h>
#include <PulseSensorPlayground.h>
#include "Pushover.h"

Pushover po = Pushover("aw2yh5qgwcxj42cuc1dj2idnd7txpz", "u5dhgyf4xeq46ke4aa8dix14g89a38", UNSAFE);

PulseSensorPlayground pulseSensor;

const char ssid[] = "Samsung Note9";
const char password[] = "123456987";

const int PULSE_INPUT = A0;
const int THRESHOLD = 550;
byte samplesUntilReport;
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;

long prevMillisThingSpeak = 0;
int intervalThingSpeak = 10000;
int BPM = 0;


void setup() {
  Serial.begin(115200);  // Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }

  WiFi.mode(WIFI_STA);
  pulseSensor.analogInput(PULSE_INPUT);
  pulseSensor.setThreshold(THRESHOLD);
  samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;

  po.setDevice("Device1");
  po.setSound("bike");

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    //Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

}

void loop() {

  if (pulseSensor.sawNewSample()) {
    BPM = pulseSensor.getBeatsPerMinute();
    Serial.println(BPM);

    if (BPM < 100 && BPM > 90 && millis() - prevMillisThingSpeak > intervalThingSpeak) {

      po.setMessage("Alert");
      Serial.println(po.send());
      prevMillisThingSpeak = millis();

    }
  }
}
