//Blink LED Program
#define PORTB5 0x20 // MASK 00100000
// Data Direction Register for port B
#define myDDRB (*(volatile uint8_t *) 0x24) // register address for PORT B Data Direction register
// Data register for port B
#define myPORTB (*(volatile uint8_t *) 0x25) // register address for PORTB5 Register 

void setup() {
  // put your setup code here, to run once:
  myDDRB |= PORTB5;
}

void loop() {
  myPORTB |= PORTB5; // turning on bit in address five in PORTB5 (HIGH) or mask 00100000
  delay(1000);       // wait for a second
  myPORTB &= ~PORTB5;// turning off bit on address fice in PORT5 (LOW) and mask PORTB5 complement 11011111
  delay(1000);       // wait for a second
}
