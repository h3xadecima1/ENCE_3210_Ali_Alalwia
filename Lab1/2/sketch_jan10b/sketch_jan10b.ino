// includes the header library that contains the cos() function
#include<math.h>
//float type array variable to store the results from 0-360 of cos() function
float gCosArray[360];
void setup() {
  //starts the serial protocol
  Serial.begin(9600);
  // this loop with increase the value of i from 0 - 360
   for (int i = 0; i <= 360; i++)
  {
    // stores the vlue of cos(i) in the index of the value of i
    gCosArray[i] = cos(i);
    // print the value of i using the serial moniter
    Serial.print(i);
    // print ':'
    Serial.print(":");
    // prints the value stored in the index i of the array arr[] 
    Serial.println(gCosArray[i]);
  }
}

void loop() {
  // the loop was not used in this program
}
