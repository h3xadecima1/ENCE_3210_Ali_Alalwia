#include <Adafruit_GFX.h>      // Graphics library for OLED
#include <Adafruit_SSD1306.h>  // OLED driver library

// Define charge threshold for Li-ion battery
#define CHARGE_THRESHOLD 4.2   // Full charge voltage (4.2V)

// Define OLED display parameters
#define SCREEN_WIDTH 128       // OLED display width in pixels
#define SCREEN_HEIGHT 64       // OLED display height in pixels
#define OLED_RESET -1          // Reset pin (not used in this setup)

// Create an instance of the SSD1306 OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define analog input pins for voltage sensing
#define SOLAR_PIN A0          // Analog pin connected to solar panel voltage sensor
#define BATTERY_PIN A1        // Analog pin connected to battery voltage sensor

// Define voltage threshold for solar panel operation
#define SOLAR_THRESHOLD 2.5   // Minimum voltage required for solar charging

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
    // Read voltages from the solar panel and battery
    float solarVoltage = analogRead(SOLAR_PIN) * (5.0 / 1023.0);  // Convert analog reading to voltage
    float batteryVoltage = analogRead(BATTERY_PIN) * (5.0 / 1023.0);

    display.clearDisplay();  // Clear previous display data
    display.setCursor(0, 0); // Set cursor position at the top-left of the screen

    // Display solar and battery voltage readings on OLED
    display.print("Solar: "); display.print(solarVoltage); display.println(" V");
    display.print("Battery: "); display.print(batteryVoltage); display.println(" V");

    // Determine the power source and charging status
    if (solarVoltage > SOLAR_THRESHOLD) {  // Check if solar panel is generating sufficient power
        if (batteryVoltage < CHARGE_THRESHOLD) {  // Check if battery needs charging
            display.println("Charging Battery...");  // Display charging status
        } else {
            display.println("Power Source: Solar");  // Display power source as solar
        }
    } else {
        display.println("Power Source: Battery");  // Display power source as battery
    }

    display.display();  // Update OLED display with new readings
    delay(2000);        // Wait for 2 seconds before next update
}
