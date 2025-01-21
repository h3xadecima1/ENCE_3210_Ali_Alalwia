/* This program is to Iterate throgh an array and find the letters R, G, B 
and turn on the corresponding light to the Letter Red, Green or Blue */

void setup() 
{
  Serial.begin(9600);
  // an array contains random distributed charcters to iterate through
  char alphabet_array[29] = 
  {
    'b', 'z', 'e', 'q', 'r', 'd', 
    's', 'g', 'v', 'b', 'r', 'g', 
    't', 'y', 'r', 'h', 'n', 'b', 
    'g', 'n', 'j', 'm', 'u', 'l', 
    'g', 'b', 'i', 'u', 'q' 
  };
  // counters for each color
  int red = 0;
  int green = 0;
  int blue = 0;
  //for loop to iterate through the array and find the letters and updating the counters
  for(int i = 1 ; i <= sizeof(alphabet_arr); i++)
  {
    if(alphabet_array[i] == 'r')
    {
      Serial.print("Red\n"); // prints red instead of turning on an LED
      red +=1; // updates the red color counter
    }
    else if(alphabet_array[i] == 'g')
    {
      Serial.print("Green\n"); // prints Green instead of turning on an LED
      green +=1; // updates the Green color counter
    }
    else if(alphabet_array[i] == 'b')
    {
      Serial.print("Blue\n"); // prints Blue instead of turning on an LED
      blue +=1; // updates the red Blue counter
    }
  }
  // prints the final results of how many each color was found in the array
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print("\n");
  Serial.print("Green: ");
  Serial.print(green);
  Serial.print("\n");
  Serial.print("Blue: ");
  Serial.print(blue);
}

void loop() {
  // put your main code here, to run repeatedly:
}
