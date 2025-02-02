 /**********************************************************************
 *                                                                     *
 * File: sketch_jan17a.ino                                             *
 *                                                                     *
 * Author: AG                                                          *
 *                                                                     *
 * Date: 01-17-2025                                                    *
 *                                                                     *
 * Description: count the difference between the number of times       *
 *              two different buttons arepressed.                      *
 *                                                                     *
 **********************************************************************/

// red led pin definition
#define GREEN_LED 4
// green led pin definition
#define RED_LED 5
// Blue led pin definition
#define BLUE_LED 6
// button 1 pin definition
#define BUTTON_1 3
// button 2 pin definition
#define BUTTON_2 2
// counter for the number of times button 1 is pressed
static volatile int gCounter_red = 0;
// count number of times button 2 is pressed
static volatile int gCounter_green = 0;

void setup() {
  // enable serial protocol at 9600 baud rate
  Serial.begin(9600);
  // set pin mode for the Blue led to output
  pinMode(BLUE_LED, OUTPUT);
  // set pin mode for the Green led to output
  pinMode(GREEN_LED, OUTPUT);
  // set pin mode for the red led to output
  pinMode(RED_LED, OUTPUT);
  // attach an interrupt to the Button 1 that will be called on button press
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button1, CHANGE);
  // attach an interrupt to the Button 1 that will be called on button press
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), isr_button2, CHANGE);
}

void loop() {
  // condition compares if button 1 is pressed more than button 2
  if(gCounter_red > gCounter_green)
  {
    //Turns off the blue led in case it was on due to a previous state
    digitalWrite(BLUE_LED, LOW);
    // turn on the red led if the times that button 1 is pressed more than the times button 2 is pressed
    digitalWrite(RED_LED, HIGH);
    // turn off the green led if the times that button 1 is pressed more than the times button 2 is pressed
    digitalWrite(GREEN_LED, LOW);
    // delay of half a second 
    delay(500);

  }
  // condition compares if button 2 is pressed more than button 1
  else if(gCounter_green > gCounter_red)
  {
    //Turns off the blue led in case it was on due to a previous state
    digitalWrite(BLUE_LED, LOW);
    // turn on the Green led if the times that button 2 is pressed more than the times button 1 is pressed
    digitalWrite(GREEN_LED, HIGH);
    // turn off the red led if the times that button 2 is pressed more than the times button 1 is pressed
    digitalWrite(RED_LED, LOW);
    // delay of half a second 
    delay(500);
  }
  // checks if both buttons 1 and 2 eually pressed 
  else if (gCounter_red == gCounter_green){
    // turn off the green if the times that button 2 is pressed more than the times button 1 is pressed
    digitalWrite(GREEN_LED, HIGH);
    // turn off the red led if the times that button 2 is pressed more than the times button 1 is pressed
    digitalWrite(RED_LED, LOW);
    // delay of half a second 
    // if the both buttons were pressed same numbers then blue led turns on
    digitalWrite(BLUE_LED, HIGH);
    delay(500)
  }
}
// Button 1 interrupt will only run if button 1 is pressed
void isr_button1()
{
  // a condition that will increase the red counter if the corresponding button 1 was pressed 
  if(digitalRead(BUTTON_1))
  {
    // increase red counter by 1
    gCounter_red++;
  }
}
//Button 2 interrupt will only rub if button 2 is pressed
void isr_button2()
{
    // a condition that will increase the green counter if the corresponding button 2 was pressed 
  if (digitalRead(BUTTON_2))
  {
    // increase green counter by 1
    gCounter_green++;
  }
}