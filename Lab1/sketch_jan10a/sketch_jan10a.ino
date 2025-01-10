#define PORTB5 0x20
#define LED_PIN 13
// Data Direction Register for port B
#define myDDRB (*(volatile uint8_t *) 0x24)   

// Data register for port B
#define myPORTB (*(volatile uint8_t *) 0x25)

void setup() {
  // put your setup code here, to run once:
  myDDRB |= PORTB5;
}

void loop() {
  myPORTB |= PORTB5;
  delay(1000);                      // wait for a second
  myPORTB &= ~PORTB5;
  delay(1000);                      // wait for a second
}
