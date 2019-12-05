#ifndef DOTPRODUCT_H
#define DOTPRODUCT_H


#include <Arduino.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

SQ15x16 VectorOneSine[VectorOneLength];
SQ15x16 VectorOneCosine[VectorOneLength];

SQ15x16 VectorTwoSine[VectorOneLength];
SQ15x16 VectorTwoCosine[VectorOneLength];

void createSineWave(SQ15x16 data[], int wavelength, int length)
{
  float scale = TWO_PI / wavelength;
  for(int i=0;i<length;i++)
  {
    data[i] = sin(scale * i);
  }
}

void createCosineWave(SQ15x16 data[], int wavelength, int length)
{
  float scale = TWO_PI / wavelength;
  for(int i=0;i<length;i++)
  {
    data[i] = cos(scale * i);
  }
}

SQ15x16 dotProduct(SQ15x16 data[], SQ15x16 wave[], int length)
{
  SQ15x16 result = 0;
  for(int i=0;i<length;i++)
  {
    result += data[i] * wave[i];
  }
  return result;
}

//Normalizes a basis vector so vector dot vector == 1
void normalizeBasisVector(SQ15x16 data[], int length)
{
  SQ15x16 d = dotProduct(data, data, length);

  for(int i=0;i<length;i++)
  {
    data[i] = data[i] / d;
  }
}

void normalizeBuffer(uint16_t data[], SQ15x16 dest[], int length){
  for(int i=0;i<length;i++)
  {
    SQ15x16 v = (SQ15x16)data[i];
    dest[i] = (v - 2048.0) / 2048.0;
  }
}


void SetupVectorOne()
{
    //Create a vector of an amplitude 1 sinewave, numberOfPeriods  long
    createSineWave(VectorOneSine, FrequencyOneWavelength, VectorOneLength);
    //normalize it
    normalizeBasisVector(VectorOneSine, VectorOneLength);

    //Create a vector of amplitude 1 cosine wave, numberOfPeriods  long
    createCosineWave(VectorOneCosine, FrequencyOneWavelength,  VectorOneLength);
    //normalize it
    normalizeBasisVector(VectorOneCosine, VectorOneLength);
}

void SetupVectorTwo()
{
    //Create a vector of an amplitude 1 sinewave, numberOfPeriods  long
    createSineWave(VectorTwoSine, FrequencyTwoWavelength, VectorOneLength);
    //normalize it
    normalizeBasisVector(VectorTwoSine, VectorOneLength);

    //Create a vector of amplitude 1 cosine wave, numberOfPeriods  long
    createCosineWave(VectorTwoCosine,FrequencyTwoWavelength,  VectorOneLength);
    //normalize it
    normalizeBasisVector(VectorTwoCosine, VectorOneLength);
}

void SetupBasisVectors(){
    SetupVectorOne();
    SetupVectorTwo();    
}
#endif
