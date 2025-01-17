#define GREEN_LED 4
#define RED_LED 5
#define BUTTON_1 3
#define BUTTON_2 2
static volatile int counter_red = 0;
static volatile int counter_green = 0;

void setup() {
  Serial.begin(9600);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), isr_button2, CHANGE);
}

void loop() {
  if(counter_red > counter_green)
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    delay(500);

  }
  else if(counter_green > counter_red)
  {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    delay(500);
  }
  else if (counter_red == counter_green){
    Serial.println("I'm Blue");
  }
}

void isr_button1()
{
  if(digitalRead(BUTTON_1))
  {
    counter_red++;
  }
}
void isr_button2()
{
  if (digitalRead(BUTTON_2))
  {
    counter_green++;
  }
}