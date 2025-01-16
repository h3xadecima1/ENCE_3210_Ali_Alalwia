//  program to detect a specified pattern with three entries in an array
#define RED_LED 6
#define GREEN_LED 7
void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  int data[] = {1, 2, 3, 4, 2, 1, 5, 2, 3, 1};  // Sample data array
  int pattern[] = {2, 3, 1};  // Pattern to search
  int pattern_len = sizeof(pattern) / sizeof(pattern[0]);  // Length of the pattern
  int count = 0;  // Counter for pattern occurrences

  for (int i = 0; i <= (sizeof(data) / sizeof(data[0])) - pattern_len; i++) {
      int j;
      for (j = 0; j < pattern_len; j++) {
          if (data[i + j] != pattern[j]) {
              break;  // Pattern mismatch
          }
      }
      if (j == pattern_len) {  // Pattern found
          count++;
          // Turn on green LED
          digitalWrite(GREEN_LED, HIGH);
      }
  }

  if (count == 0) {  // Pattern not found
      // Turn on red LED
      digitalWrite(RED_LED, HIGH);
  }

  Serial.print("Pattern found :");
  Serial.print(count);
}

void loop() {
  // this part was not used in the program
}
