/************************************************************************* 
*                                                                        * 
* File: sketch.ino                                                       *
*                                                                        * 
* Author: AG                                                             *
*                                                                        * 
* Date: 02-17-2025                                                       *
*                                                                        * 
* Description: Thermometer  .                                            * 
*                                                                        * 
*************************************************************************/ 
#include "images.h"
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#define ONE_WIRE_BUS 7                 // DS18B20 data wire is connected to input 2
#define OLED_RESET 2                   // Adafruit needs this but we don't use for I2C
#define TEMP_UNIT 4                    // Temprature Unit change pin attached to ISR botton 1
#define RESET 5                        // System reset pin attaced to ISR button 2
#define resetPin 12                    // Arduing reset pin
#define LOCK 3
#define LED_pin 9
#define LED_SW 6
static volatile bool gCF = false;       // a boolean variable used to set the temprature units
static volatile bool gLock = false;
static volatile bool gLed = false;
Adafruit_MPU6050 mpu;                  // Adafruit MPU module 
DeviceAddress thermometerAddress;      // custom array type to hold 64 bit device address
Adafruit_SSD1306 display(OLED_RESET);  // create a display instance
OneWire oneWire(ONE_WIRE_BUS);         // create a oneWire instance to communicate with temperature IC
DallasTemperature tempSensor(&oneWire);  // pass the oneWire reference to Dallas Temperature

void setup()   {
  Serial.begin(9600);
  pinMode(LED_pin, OUTPUT);
  pinMode(LED_SW, INPUT);
  pinMode(TEMP_UNIT, INPUT);
  pinMode(LOCK, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C address of the display
  display.clearDisplay();                     // clear the display buffer
  display.display();                          // update display

  Serial.println("DS18B20 Temperature IC Test");
  Serial.println("Locating devices...");
  tempSensor.begin();                         // initialize the temp sensor

  
  if (!tempSensor.getAddress(thermometerAddress, 0))
    Serial.println("Unable to find Device.");
  else {
    Serial.print("Device 0 Address: ");
    printAddress(thermometerAddress);
    Serial.println();
  }

  tempSensor.setResolution(thermometerAddress, 11);      // set the temperature resolution (9-12)
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);

  // attach an interrupt to the run button  that will run only if the button is pressed
  // attachInterrupt(digitalPinToInterrupt(LOCK), isr_button1, FALLING);
  // attachInterrupt(digitalPinToInterrupt(TEMP_UNIT), isr_button2, FALLING);


}


void loop() {
  if(digitalRead(LOCK) == HIGH)
  {
    gLed = !gLed;
  }
  if(digitalRead(LOCK) == HIGH)
  {
    gLock = !gLock;
  }
  if(digitalRead(TEMP_UNIT) == HIGH)
  {
      gCF = !gCF;
  }
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  if (a.acceleration.x >= 1)
  {
    display.setRotation(0);
  }
  else if(a.acceleration.x <= -1)
  {
    display.setRotation(2);
  }
  tempSensor.requestTemperatures();                      // request temperature sample from sensor on the one wire bus
  displayTemp(tempSensor.getTempC(thermometerAddress));  // show temperature on OLED display

  delay(500);                                            // update readings every half a second
}

void displayTemp(float temperatureReading) {             // temperature comes in as a float with 2 decimal places

  // set up OLED text size and print the temperature data
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Temp:");

  if(gLock == true)
  {
    display.clearDisplay();
    display.drawBitmap(0, 0, images[0], 128, 32, WHITE);
    display.display();
  }
  else if( gLock == true)
  {
    display.print(temperatureReading, 1);  // rounded to 1 decimal place
    display.print((char)247);              // degree symbol
    display.println("C");
  }


  if(gCF == false)
  {
    // show temperature °C
  display.print(temperatureReading, 1);  // rounded to 1 decimal place
  display.print((char)247);              // degree symbol
  display.println("C");
  }  

  else if (gCF == true)
  {
    // show temperature °F
  display.print(DallasTemperature::toFahrenheit(temperatureReading), 1); // rounded to 1 decimal place
  display.print((char)247);                                              // degree symbol
  display.println("F");
  }
  display.display();                    // update the OLED display with all the new text

  if(gLed == true)
  {
    digitalWrite(LED_pin, HIGH);
  }
  else if(gLed == false)
  {
    digitalWrite(LED_pin, LOW);
  }

}

// print device address from the address array
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// // interrupt runs only if the run button was pressed 
// void isr_button1()
// {
//   gLock = !gLock;
// }
// void isr_button2()
// {
//   gCF = !gCF;
// }