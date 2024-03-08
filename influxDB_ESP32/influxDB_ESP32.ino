/*
 * Projet : Connexion d'un ESP32 ou ESP8266 à InfluxDB
 * Description : Ce code utilise un ESP pour établir une connexion avec InfluxDB
 *               
 * Auteur : Richedor LALEYE (Adecola)
 * Date : 7 mars 2024
 * Version : 1
 * Licence : MIT
 */

#if defined(ESP32)
  #include <WiFiMulti.h>
  WiFiMulti wifiMulti;
  #define DEVICE "ESP32"
  #elif defined(ESP8266)
  #include <ESP8266WiFiMulti.h>
  ESP8266WiFiMulti wifiMulti;
  #define DEVICE "ESP8266"
  #endif
  
  #include <InfluxDbClient.h>
  #include <InfluxDbCloud.h>
  
  // WiFi AP SSID
  #define WIFI_SSID "GKA_WIFI_1"
  // WiFi password
  #define WIFI_PASSWORD "GreenKA2020"
  
  #define INFLUXDB_URL "https://us-east-1-1.aws.cloud2.influxdata.com"
  #define INFLUXDB_TOKEN "PUCbT1zgHeE5HjUs7vFs2bCMo9KduUl26emitlEL7ZOQbDjxOiJNykoZwIAL-JAZaeEuMUMs-37MvLfpLC9Byw=="
  #define INFLUXDB_ORG "24355fe20890a9f8"
  #define INFLUXDB_BUCKET "ESP32"
  
  // Time zone info
  #define TZ_INFO "UTC1"
  
  // Declare InfluxDB client instance with preconfigured InfluxCloud certificate
  InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
  
  // Declare Data point
  Point sensor("wifi_status");
  
  void setup() {
    Serial.begin(115200);
  
    // Setup wifi
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  
    Serial.print("Connecting to wifi");
    while (wifiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(100);
    }
    Serial.println();
  
    // Accurate time is necessary for certificate validation and writing in batches
    // We use the NTP servers in your area as provided by: https://www.pool.ntp.org/zone/
    // Syncing progress and the time will be printed to Serial.
    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
  
  
    // Check server connection
    if (client.validateConnection()) {
      Serial.print("Connected to InfluxDB: ");
      Serial.println(client.getServerUrl());
    } else {
      Serial.print("InfluxDB connection failed: ");
      Serial.println(client.getLastErrorMessage());
    }
  }
  void loop() {}
