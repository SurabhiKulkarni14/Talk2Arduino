#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2     
#define DHTTYPE DHT11   
int L1 = 13;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(L1, OUTPUT);
  dht.begin();
}

String vdit_voice;

void loop() {
  if (Serial.available() > 0) {
    vdit_voice = Serial.readStringUntil('\n');
    vdit_voice.trim();  // Clean whitespace/newlines
    Serial.println("Received: " + vdit_voice);
  }

  if (vdit_voice == "light on") {
    digitalWrite(L1, HIGH);
  } else if (vdit_voice == "light off") {
    digitalWrite(L1, LOW);
  } else if (vdit_voice == "what about the temperature") {
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temp) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" *C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
}
