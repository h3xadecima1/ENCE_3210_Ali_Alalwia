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
#include "images.h"  //images library
#include <Wire.h>    //Wire library to control the thermometer
#include <OneWire.h> // OneWire library to control the thermometer
#include <DallasTemperature.h> //Dallas Library to be used with the thermometer
#include <Adafruit_SSD1306.h>  //Adafruit library to control the Display
#include <Adafruit_MPU6050.h>  // Adafruit library to control the gyro sensor
#include <Adafruit_Sensor.h>   // Adafruit library to control the gyro sensor
#define OLED 2 // screen on / off button 
#define LOCK 3 // lock button
#define TEMP_UNIT 4  // unit change button                    
#define CAL 5  //calibration button                       
#define LED_SW 6 //led swtich to turn the led on and off 
#define ONE_WIRE_BUS 7  //thermometer bus pin                 
#define LED_pin 9    // led pin
#define DISPLAY 11   // value to be used with Adafruit display library for 
static volatile bool gCF = false;       // a boolean variable used to set the temprature units
static volatile bool gLock = false;     // a boolean variable used to Lock and unlock buttons
static volatile bool gLed = false;      // a boolean variable used to turn the led on and off
static volatile bool gCal = false;      // a boolean variable used to calibrate the thermometer
static volatile bool gONOFF = false;    // a boolean variable used to turn the screen on and off
static volatile bool gNo_lock = false;  // a boolean variable used to check if the lock is on or off
Adafruit_MPU6050 mpu;                  // Adafruit MPU module 
DeviceAddress thermometerAddress;      // custom array type to hold 64 bit device address
Adafruit_SSD1306 display(DISPLAY);        // create a display instance
OneWire oneWire(ONE_WIRE_BUS);         // create a oneWire instance to communicate with temperature IC
DallasTemperature tempSensor(&oneWire);  // pass the oneWire reference to Dallas Temperature

void setup()   {
  Serial.begin(9600);    // starts serial protocol
  pinMode(LED_pin, OUTPUT);  //enable Led pin
  pinMode(LED_SW, INPUT);    //enable led on/off button pin
  pinMode(TEMP_UNIT, INPUT); // enable temperatuer unit change button pin
  pinMode(LOCK, INPUT);    // enable the lock button pin
  pinMode(CAL, INPUT);     // enable the calibrtion pin
  pinMode(OLED, INPUT);    // enable screen on and off pin
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C address of the display
  display.clearDisplay();                     // clear the display buffer
  display.display();                          // update display

  Serial.println("DS18B20 Temperature IC Test");  // prints "DS18B20 Temperature IC Test" to the serial moniter
  Serial.println("Locating devices...");   // prints "Locating devices..."
  tempSensor.begin();    // initialize the temp sensor

  if (!tempSensor.getAddress(thermometerAddress, 0))  //checks if thermometer is connected or not
    Serial.println("Unable to find Device.");  // if the thermometer is not connected prints "Unable to find Device."
  else {
    Serial.print("Device 0 Address: "); // prints "Device 0 Address: "
    printAddress(thermometerAddress);   // prints the thermometer address
    Serial.println();   // prints an empty line
  }

  tempSensor.setResolution(thermometerAddress, 11); // set the temperature resolution (9-12)
  mpu.begin();   // initialize the gyro sensor
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);  // set mpu sensor Accelerometer Range
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);  // set mpu sensor gyro range
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); // sets mpu senor bandwidth
  delay(100);  // 0.1 seconds delay

}
void loop() {
  // Led on/off switch 
  if(digitalRead(LED_SW) == HIGH && gNo_lock == false)  // checks if the LED button is pressed  and if the lock button is engaged or not
  {
    gLed = !gLed;  // sets the led on/off condition to true if it was false or false if it was true 
    if(gLed == true) 
    {
      digitalWrite(LED_pin, HIGH);   // Sets the led Pin to High = LED ON
    }
    else if(gLed == false)
    {
      digitalWrite(LED_pin, LOW);  // Sets the led Pin to LOW = LED OFF
    }
  }
  // Unit C to F button
  if(digitalRead(TEMP_UNIT) == HIGH && gNo_lock == false) // checks if the Temprature unit switch button is pressed  and if the lock button is engaged or not
  {
      gCF = !gCF;  // sets the Units C/F condition to true if it was false or false if it was true
  }
  // calibration button
  if (digitalRead(CAL) == HIGH && gNo_lock == false) // checks if the Calibration button is pressed  and if the lock button is engaged or not
  {
    gCal = !gCal;  // sets the calibrtion condition to true if it was false or false if it was true
    if (gCal == true)
    {
      displayTemp(22.0);  // sets the temprature to 22C/71.6F as for 5 seconds to simulate calibration(give the thermometer time to read new temp)
      delay(5000);  // 5 seconds delay                                 
    }
  }
  // Screen on / off button
  if(digitalRead(OLED) == HIGH && gNo_lock == false) // checks if the Display on/off button is pressed  and if the lock button is engaged or not
  {
    gONOFF = !gONOFF;   // sets the Display on/off condition to true if it was false or false if it was true
    if(gONOFF == true)
    {
      display.ssd1306_command(SSD1306_DISPLAYOFF); // Turns the Display OFF if the ON/OFF button is pressed
    }
    else if(gONOFF == false)
    {
    display.ssd1306_command(SSD1306_DISPLAYON);  // Turns the Display ON if the ON/OFF button is pressed
    }
  }
  // Lock button
  if(digitalRead(LOCK) == HIGH )  // checkes if lock butto is pressed 
  {
    gLock = !gLock;   // sets the lock condition to true if it was false or false if it was true
    gNo_lock = !gNo_lock;   // sets the button lock to true if it was false or false if it was true to lock or unlock all the buttons
  }
  sensors_event_t a, g, temp;                            
  mpu.getEvent(&a, &g, &temp);  // reads Accelerometer acceleration, Gyro position  and temprature from memory address
  
  if (a.acceleration.x >= 1) // if the position is >  1 meaning the screen connsctors are up or angeled in that direction
  {
    display.setRotation(0);  // rotates thte display position upwards
  }
  else if(a.acceleration.x <= -1)  // if the position is <  -1 meaning the screen connsctors are upside down or angeled in that direction
  {
    display.setRotation(2);   // rotates thte display position upwards
  }
  tempSensor.requestTemperatures();    // request temperature sample from sensor on the one wire bus
  displayTemp(tempSensor.getTempC(thermometerAddress));  // show temperature on OLED display

  delay(500);      // update readings every half a second
}

void displayTemp(float temperatureReading) {  // temperature comes in as a float with 2 decimal places

  // set up OLED text size and print the temperature data
  display.clearDisplay();  //Clears the display
  display.setTextSize(2);  // sets text size to 2
  display.setTextColor(WHITE); // sets the text color to white
  display.setCursor(0, 0); // sets the curser position on the display 
  display.println("Temp:"); // Prints tbe word 'Temp' on the display 
  
  if(gLock == true)  // if lock button is on
  {
    display.drawBitmap(0, 0, images[0], 128, 32, WHITE);   // displays lock image on the screen
  }
  else if(gLock == false)  // if lock button is off                      
  {
    if(gCF == true)    //if Unit button was pressed
    {
      display.print(DallasTemperature::toFahrenheit(temperatureReading), 1); //converts the temp to Fahrenheit and prints the result on the display 
      display.print((char)247);    // degree symbol
      display.println("F");  //prints the letter 'F'
    }
    else if (gCF == false)
    {
      display.print(temperatureReading, 1); //prints the temperature in Celsius on the diplay 
      display.print((char)247);  // degree symbol
      display.println("C"); // prints the letter 'C'
    }
  }
  display.display(); // update the OLED display with all the new text
}

// print device address from the address array
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)  //increase i each loop by 1 until i = 7
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}