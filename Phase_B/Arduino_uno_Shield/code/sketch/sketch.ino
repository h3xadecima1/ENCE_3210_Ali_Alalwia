/************************************************************************* 
*                                                                        * 
* File: sketch.ino                                                       *
*                                                                        * 
* Author: AG                                                             *
*                                                                        * 
* Date: 01-24-2025                                                       *
*                                                                        * 
* Description: SOS Morse Code using Led .                                * 
*                                                                        * 
*************************************************************************/ 
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#define ONE_WIRE_BUS 2                // DS18B20 data wire is connected to input 2
#define OLED_RESET 4                  // Adafruit needs this but we don't use for I2C
#define TEMP_UNIT 8                   // Temprature Unit change pin attached to ISR botton 1
#define RESET 10                      // System reset pin attaced to ISR button 2
#define resetPin 12                   // Arduing reset pin
static volatile bool gCF = true;      // a boolean variable used to set the temprature units
Adafruit_MPU6050 mpu;                 // Adafruit MPU module 
DeviceAddress thermometerAddress;     // custom array type to hold 64 bit device address
Adafruit_SSD1306 display(OLED_RESET); // create a display instance
OneWire oneWire(ONE_WIRE_BUS);        // create a oneWire instance to communicate with temperature IC
DallasTemperature tempSensor(&oneWire);  // pass the oneWire reference to Dallas Temperature

void setup()   {

  Serial.begin(9600);
  digitalWrite(resetPin, HIGH); //Pin 12 is connected to the reset pin in the arduino board
  pinMode(resetPin, OUTPUT);
  pinMode(TEMP_UNIT, INPUT);  
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
  // attach an interrupt to the run button  that will run only if the button is pressed
  attachInterrupt(digitalPinToInterrupt(RESET), isr_button2, CHANGE);

  }
  tempSensor.setResolution(thermometerAddress, 11);      // set the temperature resolution (9-12)
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);
}


void loop() {
  if(digitalRead(TEMP_UNIT) == HIGH)
  {
      gCF = !gCF;
  }
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  if (a.acceleration.x >= 1)
  {
    display.setRotation(2);
  }
  else if(a.acceleration.x <= -1)
  {
    display.setRotation(0);
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

// interrupt runs only if the run button was pressed 
void isr_button2()
{
  // sets the reset pin to low resulting in reseting the arduino board 
  digitalWrite(resetPin, LOW);
}