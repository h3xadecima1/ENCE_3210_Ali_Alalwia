#define selectButton 9   // Button for selecting the operation
#define runButton 10     // Button for triggering the operation
#define redLed 11        // Red LED to indicate operation
#define greenLed 12      // Green LED to indicate operation
#define blueLed 13       // Blue LED to indicate operation

int gArr1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // First array
int gArr2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // Second array
int gResult[10] = {};  // Array to store results of operations
int gCounter = 0;       // Track number of button presses
int gButtonState = 0;   // Current state of the select button
int gLastButtonState = 0;  // Previous state of the select button

void setup() {
  Serial.begin(9600);
  pinMode(selectButton, INPUT);
  pinMode(runButton, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}

void loop() {
  // Check if the select button is pressed to change the operation
  gButtonState = digitalRead(selectButton);
  
  // Detect button press (LOW to HIGH transition for selectButton)
  if (gButtonState == HIGH && gLastButtonState == LOW) {
    delay(50);  // Debounce delay
    counter++;
    if (gCounter > 3) {
      gCounter = 1;  // Reset counter after 3 clicks
    }

    // Update the LEDs based on the counter (operation type)
    digitalWrite(redLed, (gCounter == 1) ? HIGH : LOW);
    digitalWrite(greenLed, (gCounter == 2) ? HIGH : LOW);
    digitalWrite(blueLed, (gCounter == 3) ? HIGH : LOW);
    
    // Print the current operation type for debugging
    Serial.print("Operation mode: ");
    if (gCounter == 1) {
      Serial.println("Add");
    } else if (gCounter == 2) {
      Serial.println("Subtract");
    } else if (gCounter == 3) {
      Serial.println("Multiply");
    }
  }

  // If the run button is pressed, perform the operation
  if (digitalRead(runButton) == HIGH) {
    // Perform the operation based on the current counter value
    operationMatrix(gArr1, gArr2, gResult, gCounter);
    
    // Print the results for debugging
    Serial.println("Result:");
    for (int i = 0; i < 10; i++) {
      Serial.print(result[i]);
      Serial.print(" ");
    }
    Serial.println();
    
    // Delay for a while to prevent rapid retriggering of the run button
    delay(3000);
  }

  // Update the last button state
  gLastButtonState = gButtonState;
}

// Function to perform the operation based on the counter value
void operationMatrix(int arrayA[], int arrayB[], int result[], int counter) {
  for (int i = 0; i < 10; i++) {
    if (counter == 1) {
      result[i] = arrayA[i] + arrayB[i];  // Add
    } else if (counter == 2) {
      result[i] = arrayA[i] - arrayB[i];  // Subtract
    } else if (counter == 3) {
      result[i] = arrayA[i] * arrayB[i];  // Multiply
    }
  }
}
