/* C program to find the second maximum number in Array 
and write this number to the memory addrerss after the array */

void setup() 
{
  // Arry with random numbers
  int arr[50] = 
  {
    12, 43, 22, 31, 67, 78, 33, 55, 
    90, 32, 12, 30, 98, 88, 1, 2, 3, 
    4, 5, 6, 7, 8, 9, 44, 11, 41, 65, 
    44, 77, 80, 22, 44, 66, 57, 87, 
    77, 23, 53, 610, 26, 54, 61, 77, 
    33, 77, 34, 63, 16, 17, 10
  };
  Serial.begin(9600);
  // max1 and max2 used to find the second max value in the arry 
  int max1 = arr[0]; 
  int max2 = arr[0];
  //for loop to iterate through the array and find the max values
  for (int i = 1; i < 50; i++) 
  {
      if (arr[i] > max1) 
      {
          max2 = max1; 
          max1 = arr[i]; 
      } 
      else if (arr[i] > max2 && arr[i] != max1) 
      { 
          max2 = arr[i];
      }
  }
  // Writing the second maximum to the memory location just after the array
  int *pResult = (int *)(arr + 50); // Pointer to the memory location after the array
  *pResult = max2;
  Serial.print(max2);
}

void loop() {
// this section was not used in this program
}
