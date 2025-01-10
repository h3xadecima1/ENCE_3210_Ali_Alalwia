#include <time.h>
int arr[50];
int j = 1;
int top = arr[j];
int* location = &top;
void setup() {
  Serial.begin(9600);
  srand(time(NULL));
  for (int i = 0; i < 50; i++) {
    arr[i] = i;
  }
  
  for (j = 0; j < 50; j++) 
  {
      if (top - arr[j+1] < 0)
      {
        top = arr[j+1];
      }
  }
  Serial.print(top);
  Serial.print(&location);

}

void loop() {

}
