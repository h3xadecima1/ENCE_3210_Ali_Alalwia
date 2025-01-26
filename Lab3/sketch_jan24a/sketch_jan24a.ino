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
// green led definition
#define ledPin 13
// red led pin definition
#define ledPin2 11
// button pin definition
#define buttonPin 14
// timer compare value
#define timer1_compare_match 15624
// counter variable 
volatile int gCounter = 0;
//interrupt service routine triggered on button press
ISR(PCINT0_vect)
{
  // Write opposite value to LED at button toggle
  digitalWrite(ledPin2, digitalRead(ledPin2) ^ 1);
}
//interrupt service routine triggrered when timer reaches the compare value (every 1 second)
ISR(TIMER1_COMPA_vect)
{
  // set the timer to the compare value (15624)
  TCNT1 = timer1_compare_match;
  // turns the red led on and off at 1Hz
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
  // increases the counter by 1
  gCounter++;
}

void setup()
{
  // Enables serial protocol at 9600 baud rate
  Serial.begin(9600);
  // sets the red led pin to output mode
  pinMode(ledPin, OUTPUT);
  // sets the green led pin to output mode
  pinMode(ledPin2, OUTPUT);
  // Enables bit 0 in the Pin change interrupt control register(port B)
  PCICR |= B00000001;
  // Enables pin 4 (PCINT4) bit 4 in port B (Pin D12)
  PCMSK0 = B00010000;
  // Disable all interrupts
  noInterrupts();

  // Initialize Timer1
  TCCR1A = 0;
  TCCR1B = 0;
  // 1024 prescaler & 15624 compare match = 1Hz
  // Preload timer with compare match value
  TCNT1 = timer1_compare_match;
  // Set prescaler to 1024
  TCCR1B |= (1 << CS12) | (1<< CS10);
  // Enable timer interrupt for compare mode
  TIMSK1 |= (1 << OCIE1A);
  // Enable all interrupts
  interrupts();

}

void loop()
{
  // prints the value of the counter to the serial monitor
  Serial.println(gCounter);
  // chechs if the value of the counter is bigger than 0 and if the counter mod 3 = 0 
  if(gCounter != 0 && gCounter % 3 == 0)
  {
    //prints the 'value of the counter : hello' every 3 seconds 
    Serial.print(gCounter);
    Serial.print(" : ");
    Serial.print("hello");
    Serial.print("\n");
  }
}