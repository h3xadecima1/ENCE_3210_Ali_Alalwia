#include<math.h>
float arr[360];
void setup() {
  Serial.begin(9600);
   for (int i = 0; i <= 360; i++)
  {
    arr[i] = cos(i);
    Serial.print(i);
    Serial.print(":");
    Serial.println(arr[i]);
  }
}

void loop() {
  
}
