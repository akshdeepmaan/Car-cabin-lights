int const rPotPin = A5;
int const gPotPin = A3;
int const bPotPin = A1;
int const pins[3] = {A1,A3,A5};

const int numReadings = 100;
int Potreadings[3][numReadings];      // the readings from the analog input
int readIndex = 0;                   // the index of the current reading
int total[3] = {0};                      // the running total
int RGBval[3] = {0};

int const rOutPin = 3;
int const gOutPin = 5;
int const bOutPin = 6;

void setup()
{
  pinMode(rOutPin, OUTPUT);
  pinMode(gOutPin, OUTPUT);
  pinMode(bOutPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  for(int x=0; x<3; x++)
  {
    // subtract the last reading:
    total[x] = total[x] - Potreadings[x][readIndex];
    // read from the sensor:
    Potreadings[x][readIndex] = analogRead(pins[x])/4;
    // add the reading to the total:
    total[x] = total[x] + Potreadings[x][readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;
  }
  
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  for(int x=0; x<3; x++)
  {
    // calculate the average:
    RGBval[x] = total[x] / numReadings;
  }
  
  //Write output values to RGB strip
  analogWrite(rOutPin, RGBval[0]);
  analogWrite(gOutPin, RGBval[1]);
  analogWrite(bOutPin, RGBval[2]);
  Serial.println(RGBval[0]);
  Serial.println(RGBval[1]);
  Serial.println(RGBval[2]);
  
  delay(10);        // delay in between reads for stability
}
