#define FIXED_POINTS_NO_RANDOM
#define SampleFreqKhz       4
#define SamplePeriodus      1000 / SampleFreqKhz

#define FrequencyOneWavelength 4
#define VectorOnePeriods 5

#define FrequencyTwoWavelength 10
#define VectorTwoPeriods 2

#define VectorOneLength FrequencyOneWavelength * VectorOnePeriods

#define BlueLed PC13
#define RedLed PA1

#include "DotProduct.h"
#include "Dma.h"
#include "LiquidCrystal_I2C.h"

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

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  Serial.println("START");  
  
  pinMode(BlueLed,OUTPUT);
  pinMode(RedLed,OUTPUT);
  digitalWrite(BlueLed,HIGH);
  digitalWrite(RedLed,HIGH);
  delay(1000);
  digitalWrite(BlueLed,LOW);
  digitalWrite(RedLed,LOW);
  delay(1000);
  
  SetupBasisVectors();
  SetupDma();

  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Starting...");
  lcd.setCursor(0,1);
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
