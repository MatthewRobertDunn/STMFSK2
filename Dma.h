#include <HardwareTimer.h>
#include <STM32ADC.h>
#include "DotProduct.h"
#include "SerialDecode.h"

// Channels to be acquired. 
// A0 (adc1 channel 1)
uint8 pins = 0;

uint16_t buffer[VectorOneLength * 2];
uint16_t *buffers[2];
volatile uint8_t bufr;
volatile uint8_t bufw;

SQ15x16 InputVector[VectorOneLength];

SQ15x16 FrequencyOneValue;
SQ15x16 FrequencyTwoValue;

volatile int Clock = 0;
volatile int DurationUs;

volatile bool HasData = 0;
volatile bool CurrentBit = 0;
    
STM32ADC myADC(ADC1);

void DmaIRQ(void) {
  bufw = (bufw+1)%2;

  if (bufr!=bufw) {
    // process data 
    //int startTime = micros();

    normalizeBuffer(buffers[bufr],InputVector,VectorOneLength);

    SQ15x16 dot1Sine = dotProduct(VectorOneSine, InputVector,VectorOneLength);
    SQ15x16 dot1Cos =  dotProduct(VectorOneCosine, InputVector,VectorOneLength);

    SQ15x16 dot2Sine = dotProduct(VectorTwoSine, InputVector,VectorOneLength);
    SQ15x16 dot2Cos =  dotProduct(VectorTwoCosine, InputVector,VectorOneLength);

    FrequencyOneValue = dot1Sine * dot1Sine + dot1Cos * dot1Cos;

    FrequencyTwoValue = dot2Sine * dot2Sine + dot2Cos * dot2Cos;

    SQ15x16 result = FrequencyOneValue - FrequencyTwoValue;
    if(result > 0.05)
    {
      onBitReceived(1, Clock);
    }
    else if(result < -0.05)
    {
      onBitReceived(0, Clock);
    }
    
    bufr = (bufr+1)%2;
    Clock++;

        
    //int endTime = micros();

    //DurationUs = endTime - startTime;
  }
}


void SetupDma(){
  pinMode(pins, INPUT_ANALOG);
  bufr = 0;
  bufw = 0;
  buffers[0] = &buffer[0];
  buffers[1] = &buffer[VectorOneLength];

  Timer3.setPeriod(SamplePeriodus);
  Timer3.setMasterModeTrGo(TIMER_CR2_MMS_UPDATE);

  myADC.calibrate();
  myADC.setSampleRate(ADC_SMPR_1_5); // ?
  myADC.setPins(&pins, 1);
  myADC.setDMA(buffer, VectorOneLength * 2, (DMA_MINC_MODE | DMA_CIRC_MODE | DMA_HALF_TRNS | DMA_TRNS_CMPLT), DmaIRQ);
  myADC.setTrigger(ADC_EXT_EV_TIM3_TRGO);
  myADC.startConversion();
}
