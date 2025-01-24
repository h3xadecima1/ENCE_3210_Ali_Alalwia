 /**********************************************************************
 *                                                                     
 * File: sketch_jan17b.ino                                          
 *                                                                     
 * Author: AG                        
 *                                                                     
 * Date: 01-17-2025      
 *
 * Description: Turn on and off the red, green, and blue LEDs 
 *              in a sequence.
 *
 **********************************************************************/

 
// LED Sequence Program
// LEDs PD4 and PD5
// Mask for PORTB to turn the first 3 bits on 00000111
#define PORTD_MASK 0x30
// Button 1 pin definition
#define BUTTON_1 3
// Button 2 pin definition
#define BUTTON_2 2
// Data Direction Register for port B
#define myDDRD (*(volatile uint8_t *) 0x2A)   
// Data Register for port B
#define myPORTD (*(volatile uint8_t *) 0x2B)
// Input Register for port B
#define myPIND (*(volatile uint8_t *) 0x29)

// Array to control the LED Sequence
int arr[6] = {0x20, 0x30, 0x30, 0x10, 0x10, 0x20};
//the main condition that triggers the sequence
static volatile bool start = false;

void setup() {
  // Set the first 3 pins of port B as output (00110000)
  myDDRD |= PORTD_MASK;
  // Initialize PORTB to 0 (turn off all LEDs initially)
  myPORTD &= ~PORTD_MASK;
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button1, CHANGE);
}

void loop() {
  // Check if the button on PINB3 is pressed
  if (start == true) {
    int i = 0;
    while (i < 6 && start == true) {
      // Turn on the LED pattern
      myPORTD ^= arr[i];
      delay(1000);  // Wait for 1 second
      // Turn off the LED pattern
      myPORTD ^= arr[i];
      delay(1000);  // Wait for 1 second
      
      // Move to the next pattern in the array
      i++;
    
      // Ensure i stays within the bounds of the array
      i = i % 6;
    }
  }
}
// interrupt attached to button 1 to make it as a toggle button to start and stop the led sequence
void isr_button1()
{
  // checks if button 1 is pressed
  if(digitalRead(BUTTON_1))
  {
    // change the state of the start from true to false or false to true when Button 1 is pressed 
    start = !start;
  }
}

