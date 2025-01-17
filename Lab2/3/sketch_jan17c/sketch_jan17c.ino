#define selectButton 3   // Button for selecting the operation
#define runButton 2     // Button for triggering the operation
#define redLed 4        // Red LED to indicate operation
#define greenLed 5      // Green LED to indicate operation
#define blueLed 13       // Blue LED to indicate operation

int arr1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // First array
int arr2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // Second array
int result[10] = {};  // Array to store results of operations
static volatile int counter = 0;       // Track number of button presses
static volatile bool select = false;
static volatile bool run = false;
int buttonState = 0;   // Current state of the select button
int lastButtonState = 0;  // Previous state of the select button

void setup() {
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(selectButton), isr_button1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(runButton), isr_button2, CHANGE);
}

void loop() {
    // Check if the select button is pressed to change the operation
      if (counter > 3) {
        counter = 1;  // Reset counter after 3 clicks
      }
      // Update the LEDs based on the counter (operation type)
      digitalWrite(redLed, (counter == 1) ? HIGH : LOW);
      digitalWrite(greenLed, (counter == 2) ? HIGH : LOW);
      digitalWrite(blueLed, (counter == 3) ? HIGH : LOW);
      
      // Print the current operation type for debugging
      Serial.println("Operation mode: ");
      if (counter == 1) {
        Serial.println("Add");
      } else if (counter == 2) {
        Serial.println("Subtract");
      } else if (counter == 3) {
        Serial.println("Multiply");
      }

    // If the run button is pressed, perform the operation
    if (run == true) {
      // Perform the operation based on the current counter value
      operationMatrix(arr1, arr2, result, counter);
      
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
} 
// Function to perform the operation based on the counter value
void operationMatrix(int arrA[], int arrB[], int result[], int counter) 
{
  for (int i = 0; i < 10; i++) {
    if (counter == 1) {
      result[i] = arrA[i] + arrB[i];  // Add
    } else if (counter == 2) {
      result[i] = arrA[i] - arrB[i];  // Subtract
    } else if (counter == 3) {
      result[i] = arrA[i] * arrB[i];  // Multiply
    }
  }
}

void isr_button1()
{
  select = true;
  run = false;
  counter++;
}
void isr_button2()
{
  select = false;
  run = true;
}