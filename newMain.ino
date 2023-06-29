#include <HardwareSerial.h>
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

#define SPIWIFI       SPI  // The SPI port
#define SPIWIFI_SS    10   // Chip select pin
#define ESP32_RESETN  5    // Reset pin
#define SPIWIFI_ACK   7    // a.k.a BUSY or READY pin
#define ESP32_GPIO0   6

enum DataType {
  LIGHT_IN      = 0,
  LIGHT_OUT     = 1,
  TEMP          = 2,
  STATUS_LIGHT  = 3,
  STATUS_BLINDS = 4,
  OPEN_BLINDS   = 5
};

char ssid[] = SECRET_SSID;     // your network SSID
char pass[] = SECRET_PASS;     // your network password

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int port = 1883;

//topics to publish
const char topicpublishRL[] = "room_light";
const char topicpublishOL[] = "outside_light";
const char topicpublishTP[] = "temp";
const char topicpublishLS[] = "light_status";
const char topicpublishBS[] = "blinds_status";

//topics to subscribe
const char topicsubscribeLS[] = "light_status";
const char topicsubscribeBS[] = "blinds_status";

//interval for sending
const long interval = 10000;
unsigned char newBlinds = 0;
unsigned char newLight = 0;
unsigned long previousMillis = 0;
DataType data_type = LIGHT_IN; // Default data type

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for the serial port to connect. Needed for native USB port only
  }

  // Attempt to connect to WiFi network
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // Failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1)
      ;
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  //Subscribe to topics
  Serial.print("Subscribing to topic: ");
  Serial.println(topicsubscribeLS);
  Serial.println();
  mqttClient.subscribe(topicsubscribeLS);

  Serial.print("Subscribing to topic: ");
  Serial.println(topicsubscribeBS);
  Serial.println();
  mqttClient.subscribe(topicsubscribeBS);

  Serial.println();
}

void loop() {
  mqttClient.poll();

  // UART
  if (Serial.available()) {
    data_type = static_cast<DataType>(Serial.read());
  }

  // PUBLISHER
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time a message was sent
    previousMillis = currentMillis;

    switch (data_type) {
      case LIGHT_IN:
        mqttClient.beginMessage(topicpublishRL);
        mqttClient.print("");
        mqttClient.endMessage();
        break;

      case LIGHT_OUT:
        mqttClient.beginMessage(topicpublishOL);
        mqttClient.print("");
        mqttClient.endMessage();
        break;

      case TEMP:
        mqttClient.beginMessage(topicpublishTP);
        mqttClient.print("");
        mqttClient.endMessage();
        break;

      case STATUS_LIGHT:
        mqttClient.beginMessage(topicpublishLS);
        mqttClient.print("");
        mqttClient.endMessage();
        break;

      case STATUS_BLINDS:
        mqttClient.beginMessage(topicpublishBS);
        mqttClient.print("");
        mqttClient.endMessage();
        break;

      default:
        // Invalid data type
        break;
    }
  }
}

//Subscribe
void onMqttMessage(int messageSize) {
  //received message, print out the topic & contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  while (mqttClient.available()) {
    if (mqttClient.messageTopic() == topicsubscribeBS) {
      newBlinds = static_cast<unsigned char>(mqttClient.read());
    }
    if (mqttClient.messageTopic() == topicsubscribeLS) {
      newLight = static_cast<unsigned char>(mqttClient.read());
    }
  }
  Serial.println();
  Serial.println();
}
