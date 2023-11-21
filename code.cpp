// Incluindo as bibliotecas necessárias
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "ArduinoJson.h"
#include "EspMQTTClient.h"
#include "DHTesp.h"

// Configuração do pino do sensor DHT22
const int DHT_PIN = 15; // Pino ao qual o sensor DHT22 está conectado
DHTesp dhtSensor; // Instância do sensor DHT22

// Configuração do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço do display, número de colunas e linhas

// Configuração do MQTT
EspMQTTClient client{
  "Wokwi-GUEST",   // SSID do WiFi
  "",               // Senha do WiFi
  "mqtt.tago.io",   // Endereço do servidor MQTT
  "Default",        // Usuário
  "70de94f2-1cfb-4f85-b94b-7dee0b6ef274", // Token do dispositivo
  "esp",            // Nome do dispositivo
  1883              // Porta de comunicação
};

void setup() {
  // Inicialização do Display LCD
  lcd.init();
  lcd.backlight();

  // Inicialização do sensor DHT22
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  // Inicialização da comunicação serial
  Serial.begin(9600);
  Serial.println("Conectando WiFi");

  // Loop até conectar ao WiFi
  while (!client.isWifiConnected()) {
    Serial.print('.');
    client.loop();
    delay(1000);
  }
  Serial.println("WiFi Conectado");
  Serial.println("Conectando com Servidor MQTT");

  // Loop até conectar ao servidor MQTT
  while (!client.isMqttConnected()) {
    Serial.print('.');
    client.loop();
    delay(1000);
  }
  Serial.println("MQTT Conectado");
}

// Callback da EspMQTTClient
void onConnectionEstablished() {
  // Opcional: ação quando a conexão é estabelecida
}

char bufferJson[100];

void loop() {
  // Leitura de temperatura e umidade do sensor DHT22
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  // Exibição no Serial Monitor
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("---");

  // Exibição no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(data.temperature, 2) + "C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: " + String(data.humidity, 1) + "%");

  // Aguarda por uma nova leitura do sensor (taxa de amostragem do DHT22 de ~0.5Hz)
  delay(2000);

  // Envia para o servidor MQTT
  StaticJsonDocument<300> documentoJson;
  documentoJson["temperature"] = data.temperature;
  documentoJson["humidity"] = data.humidity;
  char bufferJson[100];
  serializeJson(documentoJson, bufferJson);
  client.publish("topicoTDSPI", bufferJson);
  delay(2000);
  client.loop();
}

