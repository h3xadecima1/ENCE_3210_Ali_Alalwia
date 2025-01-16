//LED Sequence Program
//Mask for PORTB to turn the first 3 bits on 00000111
#define PORTB5 0x07
// Data Direction Register for port B
#define myDDRB (*(volatile uint8_t *) 0x24)   
// Data register for port B
#define myPORTB (*(volatile uint8_t *) 0x25)
//Array to control the LED Sequence
int arr[6] = {0x04, 0x06, 0x07, 0x03, 0x01, 0x05};

void setup() {
  myDDRB &= PORTB5;
}

void loop() {
  if (PINB &(1<<PINB3)){
    int i = 0;
    while (i < 6 )
    {
      myPORTB ^= arr[i];
      delay(1000);
      myPORTB ^= arr[i];
      delay(1000);
      i++;
      i = i % 6;
    }
  }
}