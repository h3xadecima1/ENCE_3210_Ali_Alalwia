 /*************************************************************************
 *                                                                        *
 * File: sketch_jan24a.ino                                                *
 *                                                                        *
 * Author: AG                                                             *
 *                                                                        *
 * Date: 01-24-2025                                                       *
 *                                                                        *
 * Description: test concepts of interrupt routines, Timers, GPIO         *
 *              input/output and volatile variables..                     *
 *                                                                        *
 *************************************************************************/
// Green LED definition
#define ledPin 13
// Red LED pin definition
#define ledPin2 11
// Button pin definition
#define buttonPin 14
// Timer compare value for 1Hz blinking
#define timer1_compare_match 15624
// Counter variable
volatile int gCounter = 0;

// Interrupt Service Routine triggered on button press
ISR(PCINT0_vect)
{
  // Toggle the Red LED
  digitalWrite(ledPin2, digitalRead(ledPin2) ^ 1);
}

// Interrupt Service Routine triggered every 1 second
ISR(TIMER1_COMPA_vect)
{
  // Toggle the Green LED
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
  
  // Increase the counter
  gCounter++;
}

void setup()
{
  // Enable serial communication at 9600 baud
  Serial.begin(9600);
  
  // Set LED pins as outputs
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  // Enable pin-change interrupt on port B (Ensure correct PCINT for buttonPin)
  PCICR |= (1 << PCIE0);  // Enable Pin Change Interrupt Control Register
  PCMSK0 |= (1 << PCINT4); // Enable PCINT4 (Check if D14 corresponds)

  // Disable all interrupts before configuring timer
  noInterrupts();

  // Initialize Timer1
  TCCR1A = 0; // Clear control registers
  TCCR1B = 0;

  // Set compare match value for 1Hz (assuming 16MHz clock, 1024 prescaler)
  OCR1A = timer1_compare_match;
  
  // Set prescaler to 1024
  TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode + 1024 prescaler

  // Enable Timer1 compare match interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  // Enable all interrupts
  interrupts();
}

void loop()
{
  // Print counter value
  Serial.println(gCounter);

  // Print "hello" every 3 seconds
  if (gCounter != 0 && gCounter % 3 == 0)
  {
    Serial.print(gCounter);
    Serial.print(" : ");
    Serial.println("hello");
  }
}