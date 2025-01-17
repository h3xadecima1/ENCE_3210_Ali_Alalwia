#define selectButton 9
#define runButton 10
#define redLed 11
#define greenLed 12
#define blueLed 13

int buttonState = 0;        // current state of the button
int lastButtonState = 0;
int arr1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int arr2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int arr3[10] = {};
int counter = 0;
void setup() 
{
  Serial.begin(9600);
  pinMode(selectButton, INPUT);
  pinMode(runButton, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}

void loop() {
  if (digitalRead(selectButton) == HIGH);
  {
    counter +=1;
    Serial.println(counter);
    if (counter == 1)
    {
      digitalWrite(redLed, HIGH);
    }
    else if (counter == 2)
    {
      digitalWrite(greenLed, HIGH);
    }
    else if(counter == 3)
    {
      digitalWrite(blueLed , HIGH);
    }
  }

  if(digitalRead(runButton) == HIGH)
  {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, LOW);
      digitalWrite(blueLed, LOW);
      Serial.print(operationMatrix(arr1[10],  arr2[10],  arr3[10], counter));
      delay(3000);
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, HIGH);
      digitalWrite(blueLed, HIGH);
  }
}

int operationMatrix(int arrA[10], int arrB[10], int result[10], int counter){
  for (int i = 0 ; i<10 ; i++)
  {
    if (counter == 1)
    {
      result[i] = arrA[i] + arrB[i];
    }
    else if (counter == 2)
    {
      result[i] = arrA[i] - arrB[i];
    }
    else if (counter == 3)
    {
      result[i] = arrA[i] + arrB[i];
    }
  }
}
