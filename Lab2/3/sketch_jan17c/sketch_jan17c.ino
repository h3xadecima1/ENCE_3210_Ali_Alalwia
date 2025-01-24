 /**********************************************************************
 *                                                                     *
 * File: sketch_jan17c.ino                                             *
 *                                                                     *
 * Author: AG                                                          *
 *                                                                     *
 * Date: 01-17-2025                                                    *
 *                                                                     *
 * Description: simple calculator that Multiply, adds or subtract  two *
 *               arrays and storer the results in new array            *
 *                                                                     *
 **********************************************************************/


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
  // starts the serial protocol at 9600 baud rate
  Serial.begin(9600);
  //set red led pin to output mode
  pinMode(redLed, OUTPUT);
  // set greeen led pin to output mode
  pinMode(greenLed, OUTPUT);
  // sets blue led pin to output mode
  pinMode(blueLed, OUTPUT);
  // attach an interrupt to the select button  that will run only if the button is pressed
  attachInterrupt(digitalPinToInterrupt(selectButton), isr_button1, CHANGE);
  // attach an interrupt to the run button  that will run only if the button is pressed
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
// interrupt runs only if the select button was pressed 
void isr_button1()
{
  // enables the select button
  select = true;
  //disables the run button 
  run = false;
  //increase the operation counter by 1
  counter++;
}
// interrupt runs only if the run button was pressed 
void isr_button2()
{
  //disables the select button
  select = false;
  // enables the run button
  run = true;
}