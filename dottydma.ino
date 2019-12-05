#define FIXED_POINTS_NO_RANDOM
#define SampleFreqKhz       4
#define SamplePeriodus      1000 / SampleFreqKhz

#define FrequencyOneWavelength 4
#define VectorOnePeriods 5

#define FrequencyTwoWavelength 10
#define VectorTwoPeriods 2

#define VectorOneLength FrequencyOneWavelength * VectorOnePeriods

#include "DotProduct.h"

#include "Dma.h"

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

void printVector(SQ15x16 v[],int length)
{
  for(int i=0;i<length;i++)
  {
    Serial.print((float)v[i],4);
    Serial.print(",");
  }
   Serial.println();
}

void setup() {
  Serial.begin(115200);
  Serial.println("START");  
  SetupBasisVectors();
  delay(1000);
  Serial.println("Sine Vector");
  printVector(VectorOneSine, VectorOneLength);
  Serial.println("Cosine Vector");
  printVector(VectorOneCosine, VectorOneLength);
  SetupDma();
}

void loop() {
  delay(500);
  /*Serial.print("F1 ");
  Serial.println((float)FrequencyOneValue,4);

  Serial.print("F2 ");
  Serial.println((float)FrequencyTwoValue,4);
  
  Serial.print("D ");
  Serial.println(DurationUs);
  */
}
