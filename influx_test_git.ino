#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <InfluxDb.h>

#define INFLUXDB_HOST "192.168.1.1"   //Enter IP of device running Influx Database
#define WIFI_SSID "SSID"              //Enter SSID of your WIFI Access Point
#define WIFI_PASS "PASSWORD"          //Enter Password of your WIFI Access Point

ESP8266WiFiMulti WiFiMulti;
Influxdb influx(INFLUXDB_HOST);

void setup() {
  Serial.begin(9600);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WIFI");
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  influx.setDb("esp8266_test");

  Serial.println("Setup Complete.");
}

int loopCount = 0;

void loop() {
  loopCount++;

  InfluxData row("data");
  row.addTag("Device", "ESP8266");
  row.addTag("Sensor", "Temp");
  row.addTag("Unit", "Celsius");
  row.addValue("LoopCount", loopCount);
  row.addValue("RandomValue", random(10, 40));

  influx.write(row);
  delay(5000);
}
