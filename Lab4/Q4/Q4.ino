 /*************************************************************************
 *                                                                        *
 * File: Q4.ino                                                           *
 *                                                                        *
 * Author: AG                                                             *
 *                                                                        *
 * Date: 01-24-2025                                                       *
 *                                                                        *
 * Description: Fan Controller                                            *
 *                                                                        *
 *                                                                        *
 *************************************************************************/
#include <Adafruit_GFX.h>      // Graphics library for OLED
#include <Adafruit_SSD1306.h>  // OLED driver library

// Define sensor and control pins
#define TEMP_SENSOR_PIN A0     // Temperature sensor analog input pin
#define BUTTON1_PIN 2          // Button to toggle fan ON/OFF
#define BUTTON2_PIN 3          // Button to adjust sensitivity level
#define LED_PIN 9              // PWM output (Fan simulation via LED)

// OLED Display setup
#define SCREEN_WIDTH 128       // OLED screen width in pixels
#define SCREEN_HEIGHT 64       // OLED screen height in pixels
#define OLED_RESET -1          // Reset pin (not used in this setup)

// Create an instance of the SSD1306 OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define PWM settings
const int PWM_FREQ = 250;      // 250Hz PWM frequency for fan speed control

// Sensitivity level (default: High)
int sensitivityLevel = 1;      // Levels: 1 (High), 2 (Medium), 3 (Low)

// Fan state (ON/OFF)
bool fanOn = false;

// Sensitivity Scaling Factors (Lower value = Slower Fan Response)
const float sensitivityScale[3] = {1.0, 0.6, 0.3}; // Adjust scaling for better control

// Debounce variables for button presses
unsigned long lastButton1Press = 0;
unsigned long lastButton2Press = 0;
const int debounceDelay = 200; // 200ms debounce delay

void setup() {
    Serial.begin(115200);  // Initialize serial communication for debugging

    // Set button pins as inputs
    pinMode(BUTTON1_PIN, INPUT);
    pinMode(BUTTON2_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT); // LED simulating fan speed via PWM

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
    unsigned long currentTime = millis();  // Get current time for debouncing

    // Read button states (active LOW due to INPUT_PULLUP configuration)
    int button1State = digitalRead(BUTTON1_PIN);
    int button2State = digitalRead(BUTTON2_PIN);

    // Toggle fan ON/OFF with Button 1 (debounced)
    if (button1State == HIGH && (currentTime - lastButton1Press) > debounceDelay) {
        fanOn = !fanOn;  // Toggle fan state
        Serial.println(fanOn ? "Fan ON" : "Fan OFF");  // Debugging output
        lastButton1Press = currentTime;  // Update last button press time
    }

    // Cycle through sensitivity levels with Button 2 (debounced)
    if (button2State == HIGH && (currentTime - lastButton2Press) > debounceDelay) {
        sensitivityLevel = (sensitivityLevel % 3) + 1;  // Cycles 1 → 2 → 3 → 1 ...
        Serial.print("Sensitivity: "); Serial.println(sensitivityLevel);  // Debugging output
        lastButton2Press = currentTime;  // Update last button press time
    }

    // Read temperature sensor and average over 100 samples for stability
    float tempSum = 0;
    for (int i = 0; i < 100; i++) {
        tempSum += analogRead(TEMP_SENSOR_PIN);  // Read temperature sensor value
        delay(5);  // Short delay to stabilize readings
    }
    float avgTemp = (tempSum / 100) * (5.0 / 1023.0) * 100; // Convert raw reading to temperature (°C)

    // Calculate fan speed based on temperature and sensitivity level
    int fanSpeed = 0;
    if (fanOn) {
        // Map temperature to PWM range (20°C = min speed, 40°C = max speed)
        float tempBasedSpeed = map(avgTemp, 20, 40, 0, 255);
        tempBasedSpeed = constrain(tempBasedSpeed, 0, 255);  // Ensure valid PWM range

        // Apply sensitivity factor (scale speed before final PWM value)
        fanSpeed = tempBasedSpeed * sensitivityScale[sensitivityLevel - 1];
        fanSpeed = constrain(fanSpeed, 0, 255);  // Ensure within PWM range
    }
    
    analogWrite(LED_PIN, fanSpeed);  // Set PWM value for LED (simulating fan speed)

    // Display system status on OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Temp: "); display.print(avgTemp); display.println(" C");
    display.print("Fan: "); display.println(fanOn ? "ON" : "OFF");
    display.print("Speed: "); display.println(fanSpeed);
    display.print("Sensitivity: "); display.println(sensitivityLevel);
    display.display();

    delay(100);  // Short delay for better responsiveness
}
