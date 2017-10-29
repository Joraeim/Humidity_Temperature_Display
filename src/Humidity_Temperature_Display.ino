/*
 * Project Humidity_Temperature_Display
 * Description:
 * Author:
 * Date:
 */
#include "Adafruit_Si7021.h"
#include "Sparkfun_S7S.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();
Sparkfun_S7S display = Sparkfun_S7S();

int LED = D7;
// setup() runs once, when the device is first turned on.
void setup() {

  sensor.begin();
  display.begin();
  display.WriteValue(0xFFFF);
  pinMode(LED, OUTPUT);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

  float humidity = sensor.readHumidity();
  float temperature = sensor.readTemperature('F');
  // The core of your code will likely live here.
  //Particle.printf("Humidity: %s, Temperature: %s\n", humidity, temperature);
  bool success = true;
  success &= Particle.publish("H", String::format("%.2f",humidity), 1);
  success &= Particle.publish("T", String::format("%.2f",temperature), 1);
  if(!success) {
    toggleLED(5);
    delay(2000);
    //display.WriteValue("FAIL");
  }
  //display.WriteValue("H");
  //delay(500);
  display.WriteValue(humidity);
  delay(1000);

  //display.WriteValue("T");
  //delay(500);
  display.WriteValue(temperature);
  delay(1000);

  toggleLED(1);
  //delay(10000);
}

void toggleLED(int count)
{
  for(int i = 0; i < count; i++)
  {
    digitalWrite(LED, !digitalRead(D7));
    delay(250);
  }
  return;
}
