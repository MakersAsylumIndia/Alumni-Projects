#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID       "the barsaati"
#define WLAN_PASS       "6@SiriFortRoad"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "pranavkumar"
#define AIO_KEY         "aio_NYVw24UBNeDxCv7znQsrQKI7RFxH"

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish sensor = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sense");

void MQTT_connect();

int ledPin = 12; // choose pin for the LED
int irPin = 13; // choose input pin (for Infrared sensor)
int irStatus; // variable for reading the pin status

void setup()
{
  Serial.begin(115200);
  delay(10);
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  Serial.println(F("project"));
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT); // declare LED as output
  pinMode(irPin, INPUT); // declare Infrared sensor as input
}

void loop() {
  MQTT_connect();

  Serial.print(F("\nSending distance val "));

  int irStatus = digitalRead(irPin);
  if (irStatus ==1){
  if (! sensor.publish(irStatus)) {
   Serial.println(F("Failed"));
   } else {
   Serial.println(F("OK!"));
   }
  } 
  


  delay(3000);
}

void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
