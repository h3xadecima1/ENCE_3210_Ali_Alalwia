 /**********************************************************************
 *                                                                     
 * File: sketch_jan17d.ino                                          
 *                                                                     
 * Author: AG                        
 *                                                                     
 * Date: 01-17-2025      
 *
 * Description: calculate global integer array 𝑦[𝑛] = 2 ∗ 𝑥[𝑛] − 𝑥[𝑛 − 1]
 *              using ISR. 
 *
 **********************************************************************/
#define isrButton 3   // Button Pin definitions

// Define global arrays
volatile int gX[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Initial array values
volatile int gY[10] = {0}; // Result array

void setup() {
  // Set up the button pin as input with pull-up resistor
  pinMode(isrButton, INPUT);

  // Attach the interrupt to the button pin
  attachInterrupt(digitalPinToInterrupt(isrButton), calculateY, CHANGE);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Print the array y for debugging
  Serial.println("Array y values:");
  for (int i = 0; i < 10; i++) {
    Serial.print("y[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(gY[i]);
  }
  delay(1000); // Update every second
}

// Interrupt Service Routine (ISR) to calculate y
void calculateY() {
  // Calculate y[n] = 2 * x[n] - x[n-1]
  noInterrupts(); // Disable interrupts during critical section
  gY[0] = 2 * gX[0]; // Special case for n = 0
  for (int n = 1; n < 10; n++) {
    gY[n] = 2 * gX[n] - gX[n - 1];
  }
  interrupts(); // Re-enable interrupts
}
