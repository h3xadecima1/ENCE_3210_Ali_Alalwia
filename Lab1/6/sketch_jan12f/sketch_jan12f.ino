// LED Sequence Program
// Mask for PORTB to turn the first 3 bits on 00000111
#define PORTB_MASK 0x07

// Data Direction Register for port B
#define myDDRB (*(volatile uint8_t *) 0x24)   
// Data Register for port B
#define myPORTB (*(volatile uint8_t *) 0x25)
// Input Register for port B
#define myPINB (*(volatile uint8_t *) 0x23)

// Array to control the LED Sequence
int arr[6] = {0x04, 0x06, 0x07, 0x03, 0x01, 0x05};

void setup() {
  // Set the first 3 pins of port B as output (00000111)
  myDDRB |= PORTB_MASK;
  
  // Initialize PORTB to 0 (turn off all LEDs initially)
  myPORTB &= ~PORTB_MASK;
}

void loop() {
  // Check if the button on PINB3 is pressed
  if (myPINB & (1 << PINB3)) {
    int i = 0;
    
    while (i < 6) {
      if (myPORTB == 0x00) {
        // Turn on the LED pattern
        myPORTB ^= arr[i];
        delay(1000);  // Wait for 1 second
        // Turn off the LED pattern
        myPORTB ^= arr[i];
        delay(1000);  // Wait for 1 second
        
        // Move to the next pattern in the array
        i++;
      }
      
      // Ensure i stays within the bounds of the array
      i = i % 6;
    }
  }
}
