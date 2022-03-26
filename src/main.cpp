#include <Arduino.h>
#include <DHTesp.h>
#include <SSD1306.h>

DHTesp              dht;
SSD1306             display(0x3c, 4, 5, GEOMETRY_128_32);
int                 interval = 2000;
unsigned long       lastDHTReadMillis = 0;
float               humidity = 0;
float               temperature = 0;

void setup() {
    Serial.begin(115200);
    dht.setup(14, DHTesp::DHT22); // Connect DHT sensor to GPIO 14
    delay(1000);
    Serial.println(); Serial.println("Humidity (%)\tTemperature (C)");
    
}

void readDHT22() {
    unsigned long currentMillis = millis();

    if(currentMillis - lastDHTReadMillis >= interval) {
        lastDHTReadMillis = currentMillis;
        humidity = dht.getHumidity();              // Read humidity (percent)
        temperature = dht.getTemperature();        // Read temperature as Fahrenheit
    }
}
void loop() {
    readDHT22();
    Serial.printf("%.1f\t %.1f\n", temperature, humidity);
    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, String(temperature));
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 16, String(humidity));
    display.display();
    delay(1000);
}
