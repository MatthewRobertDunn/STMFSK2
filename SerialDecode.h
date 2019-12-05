#ifndef SERIALDECODE_H
#define SERIALDECODE_H

//How many clocks between bits. This corresponds to 'chunks' of our signal.
#define CLOCKS_PER_BIT 4
#define START_BIT  0
#define STOP_BIT  9

volatile int currentState = 0; //The current state of the decoder

volatile int bitClock = 0;  //Contains the next clock we should receive a bit on.

volatile char currentByte = 0; //The byte we are building up

//todo: clock rollover

void onBitReceived(bool bit, int clock)
{
    if(clock < bitClock)
    {
       //It's not yet time to read
        return;
    }
    
    if(currentState == START_BIT && bit == 0)
    {
        return; //looking for start bit, didn't find it, leave.
    }
    
    if(currentState == START_BIT && bit == 1) //looking for start bit, we did find it, yay.
    {
        //set the current start bit clock to the next data bit
        bitClock = clock + CLOCKS_PER_BIT;
        //reset our currentByte to 0
        currentByte = 0;
        //increment current state
        currentState++;
        return;
    }

    //Check if it's been too long since we last got a bit, start again.
    if(clock > bitClock)
    {
        currentState = START_BIT;
        return;
    }

    //Time to read a databit.
    if(currentState > START_BIT && currentState < STOP_BIT)
    {
        currentByte = currentByte << 1; //make room for our new bit
        currentByte = currentByte | bit; //Set incoming bit to LSB
        currentState++;
    }

    if(currentState == STOP_BIT && bit == 0)
    {
      Serial.print((int)currentByte);  //print result to debug
      Serial.write(",");
      currentState = START_BIT;  //Back to looking for our start bit.
    }

    bitClock = clock + CLOCKS_PER_BIT;
}

#endif
