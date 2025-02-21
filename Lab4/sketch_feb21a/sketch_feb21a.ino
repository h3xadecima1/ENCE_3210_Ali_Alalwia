// #define bitsize 12
// float Vref = 3.6;
// float Vin = 3.3;
// float thresh;
// float quantized = 0;
// int  count;
// int bitval;
// int bits[bitsize];

#define POT_1 A0
#define TIME_DELAY 100
int gPot_1 = 0;

void setup() {
  pinMode(POT_1, INPUT);
  Serial.begin(9600);
  // Vref /=2;
  // if(Vin >= thresh)
  // {
  //   bitval = 1;
  //   thresh += Vref;
  // }
  // else
  // {
  //   bitval = 0;
  //   thresh -= Vref;
  // }
  // bits[count] = bitval;
  // quantized += Vref*bitval;
  // while(1)
}

void loop() {
  gPot_1 = analogRead(POT_1);
  Serial.print("Val 1: ");
  Serial.println(gPot_1);
  delay(TIME_DELAY);
}
