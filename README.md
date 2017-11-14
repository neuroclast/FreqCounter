# FreqCounter
Frequency counter library for Arduino

Usage:
#include "FreqCounter.h"

Declare object: 
FreqCounter freqCounter(inputPin, 10000);
- inputPin should be obvious
- Second parameter is the timeout. If no signal is detected, SIGNAL_STATE will be TIMEOUT

 freqCounter.update(); 
 - Should be called in the main program loop to update state
 
 SIGNAL signal = freqCounter.getSignal();
 - Get signal state
 
 float dutyCycle = (float)signal.pulseWidth / (float)signal.period;
 - Get duty cycle of signal
 
 etc.
