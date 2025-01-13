// this program is a simple Arduino Calculator calculator
#define buttonPin 2
#define RED_LED 6
#define GREEN_LED 7
#define BLUE_LED 8
#define ARRAY_SIZE 10

int counter = 0;  // counter for the number of button presses
int buttonState = 0;        // current state of the button
int lastButtonState = 0;

int operation = 0;
int resultArray[ARRAY_SIZE];
int array1[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int array2[ARRAY_SIZE] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

void setup () {
  pinMode(buttonPin, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  btn_prev = digitalRead(btnPin);
}

void loop() 
{
  buttonState = digitalRead(buttonPin)
  if (buttonState != lastButtonState) {
  {
    if (buttonState == HIGH) {
      counter++;
      if (counter == 1) 
      {
          digitalWrite(RED_LED, HIGH);
          operation = 1; // Addition
      } 
      else if (counter == 2) 
      {
          digitalWrite(GREEN_LED, HIGH);
          operation = 2; // Subtraction
      } 
      else if (counter == 3) 
      {
          digitalWrite(BLUE_LED, HIGH);
          operation = 3; // Multiplication
      }
      counter %= 3; // Reset counter after 3 presses
    }
  }

  if (btn == LOW && btn_prev == HIGH && operation != 0) 
  {
    for (int i = 0; i < ARRAY_SIZE; i++) 
    {
      switch (operation) 
      {
        case 1:
            resultArray[i] = array1[i] + array2[i];
            break;
        case 2:
            resultArray[i] = array1[i] - array2[i];
            break;
        case 3:
            resultArray[i] = array1[i] * array2[i];
            break;
      }
    }
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(1000);
    operation = 0;
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
  }
}