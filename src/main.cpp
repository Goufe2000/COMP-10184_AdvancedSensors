// ******************************************************************
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program
// COMP-10184
// Mohawk College

// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the  DS18B20 is connected to
const int oneWireBus = D3;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

DeviceAddress sensor;

void setup()
{
  DS18B20.getAddress(sensor, 0);
  // configure the USB serial monitor
  Serial.begin(115200);

  // Start the DS18B20 sensor
  DS18B20.begin();
  Serial.println("\nTemperature Application");
  if (DS18B20.getAddress(sensor, 0)){
    Serial.print("Found DS18B20 sensor with address: ");

  for (int i = 0; i < 8; i++)
  {
    Serial.print(sensor[i], HEX);
  }
}
  if (!DS18B20.getAddress(sensor, 0))
    Serial.println("\nNo DS18B20 temperature sensors are installed!");
}

void loop()
{
  float fTemp;
  // ask DS18B20 for the current temperature
  DS18B20.requestTemperatures();

  // fetch the temperature.  We only have 1 sensor, so the index is 0.
  fTemp = DS18B20.getTempCByIndex(0);
  if (DS18B20.getAddress(sensor, 0))
  {
    // print the temp to the USB serial monitor
    String TemperatureValue;

    if (fTemp <= 10)
    {
      TemperatureValue = "Too Cold!";
    }

    else if (fTemp < 15)
    {
      TemperatureValue = "Cool";
    }

    else if (fTemp < 25)
    {
      TemperatureValue = "Perfect";
    }

    else if (fTemp < 30)
    {
      TemperatureValue = "Warm";
    }

    else if (fTemp < 35)
    {
      TemperatureValue = "Hot";
    }

    else if (fTemp >= 35)
    {
      TemperatureValue = "Too Hot!";
    }
    Serial.println("\nCurrent Temperature is: " + String(fTemp) + " or " + (TemperatureValue));
    // wait 5s (5000ms) before doing this again
    delay(5000);
  }
}