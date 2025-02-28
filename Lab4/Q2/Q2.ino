 /*************************************************************************
 *                                                                        *
 * File: Q2.ino                                                           *
 *                                                                        *
 * Author: AG                                                             *
 *                                                                        *
 * Date: 01-24-2025                                                       *
 *                                                                        *
 * Description: Charge Controller                                         *
 *                                                                        *
 *                                                                        *
 *************************************************************************/
#include <Adafruit_GFX.h>      // Graphics library for OLED
#include <Adafruit_SSD1306.h>  // OLED driver library

#define CHARGE_THRESHOLD 4.2   // Full charge voltage for Li-ion battery
#define SCREEN_WIDTH 128       // OLED display width
#define SCREEN_HEIGHT 64       // OLED display height
#define OLED_RESET -1          // OLED reset pin (not used in this setup)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Analog input pins for voltage sensing
#define SOLAR_PIN A0          // Solar panel voltage sensor input
#define BATTERY_PIN A1        // Battery voltage sensor input

// Voltage thresholds
#define SOLAR_THRESHOLD 2.5   // Minimum voltage for solar charging

void setup() {
    Serial.begin(115200);  // Start serial communication at 115200 baud rate

    // Initialize OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));  // Display initialization error message
        for (;;);  // Halt execution if display fails
    }

    display.clearDisplay();   // Clear OLED screen
    display.setTextSize(1);   // Set text size to small
    display.setTextColor(WHITE);  // Set text color to white
}

void loop() {
    // Read voltages from solar panel and battery
    float solarVoltage = analogRead(SOLAR_PIN) * (5.0 / 1023.0);  // Convert analog value to voltage
    float batteryVoltage = analogRead(BATTERY_PIN) * (5.0 / 1023.0);

    display.clearDisplay();  // Clear previous display data
    display.setCursor(0, 0); // Set cursor to top-left

    // Display solar and battery voltage readings
    display.print("Solar: "); display.print(solarVoltage); display.println(" V");
    display.print("Battery: "); display.print(batteryVoltage); display.println(" V");

    // Determine power source and charging status
    if (solarVoltage > SOLAR_THRESHOLD) {  // Check if solar panel is generating sufficient power
        if (batteryVoltage < CHARGE_THRESHOLD) {  // Check if battery needs charging
            display.println("Charging Battery...");
        } else {
            display.println("Power Source: Solar");
        }
    } else {
        display.println("Power Source: Battery");
    }

    display.display();  // Update OLED display with new readings
    delay(2000);        // Wait 2 seconds before next update
}
