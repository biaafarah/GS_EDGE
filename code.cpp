#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include "EspMQTTClient.h"
#include "ArduinoJson.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define LED_PIN 14
#define SENSOR_PIN 27
#define BUZZER_PIN 26

#define DHT_PIN 27
#define DHT_SENSOR_TYPE DHT22
DHT dhtSensor(DHT_PIN, DHT_SENSOR_TYPE);

const float LIMITE_UMIDADE_LED = 20.0;
const float LIMITE_UMIDADE_BUZZER = 50.0;
bool buzzerLigado = false;

EspMQTTClient client{
  "Wokwi-GUEST",  // SSID do WiFi
  "",              // Senha do WiFi
  "mqtt.tago.io",  // Endereço do servidor MQTT
  "Default",       // Usuário
  "73b9d3ad-30af-4221-8a70-fe4873727717",  // Token do device
  "Device #1",           // Nome do device
  1883             // Porta de comunicação
};

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }

  dhtSensor.begin();
  oled.setCursor(0, 0);

  Serial.println("Conectando WiFi");
  while (!client.isWifiConnected()) {
    Serial.print('.');
    client.loop();
    delay(1000);
  }
  Serial.println("WiFi Conectado");

  Serial.println("Conectando com Servidor MQTT");
  while (!client.isMqttConnected()) {
    Serial.print('.');
    client.loop();
    delay(1000);
  }
  Serial.println("MQTT Conectado");
}

void onConnectionEstablished()
{}
char bufferJson[100];

void loop() {
  int temp = dhtSensor.readTemperature();
  int humidity = dhtSensor.readHumidity();

  Serial.println("Temp: " + String(temp) + "°C");
  Serial.println("Humidity: " + String(humidity) + "%");
  Serial.println("---");

  oled.clearDisplay();

  oled.setTextSize(1);         // set text size
  oled.setTextColor(WHITE);    // set text color
  oled.setCursor(0, 10);       // set position to display
  oled.println("Temp: " + String(temp) + "C"); // set text

  oled.setTextSize(1);         // set text size
  oled.setTextColor(WHITE);    // set text color
  oled.setCursor(0, 20);       // set position to display
  oled.println("Humidity: " + String(humidity) + "%"); // set text

  oled.display();

  if (humidity > LIMITE_UMIDADE_BUZZER && !buzzerLigado) {
    tone(BUZZER_PIN, 1000);  // turn on
    buzzerLigado = true;
  } else if (humidity <= LIMITE_UMIDADE_BUZZER && buzzerLigado) {
    tone(BUZZER_PIN, 0);  // turn on
    buzzerLigado = false;
  }

  if (humidity < LIMITE_UMIDADE_LED) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  StaticJsonDocument<300> doc;
  doc["variable"] = "Temperatura";
  doc["value"] = temp;
  serializeJson(doc, bufferJson);
  client.publish("topicoEngSoft", bufferJson);
  client.loop();

  doc["variable"] = "Humidade";
  doc["value"] = humidity;
  serializeJson(doc, bufferJson);
  client.publish("YOUR_TOPIC", bufferJson);
  client.loop();

  delay(2000);

}
