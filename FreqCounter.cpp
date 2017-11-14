#include "Arduino.h"
#include <stdarg.h>
#include "FreqCounter.h"

int errNum = 0;

FreqCounter::FreqCounter(int inputPin, unsigned long timeout)
{
  this->inputPin  = inputPin;
  this->timeout   = timeout;
  sigState        = START_LH;
  signal.state    = INVALID;
  pinState        = LOW;
}

void FreqCounter::update()
{
  ulong currentTime   = micros();
  bool changeLH       = false;

  if (PINB & (1 << 2)) // PINB for ATTiny85, PIND for Nano
  {
    changeLH = true;
    pinState = HIGH;
  }
  else
    pinState = LOW;
  
  if(currentTime - lastUpdate >= timeout)
  {
    signal.state  = TIMEOUT;
    sigState      = START_LH;
  }

  if(sigState == START_LH && changeLH)
  {
    a = currentTime;
    sigState = MID_HL;
  }
  else if(sigState == MID_HL && !changeLH)
  {
    b = currentTime;
    sigState = END_LH;
  }
  else if(sigState == END_LH && changeLH)
  {
    c = currentTime;
    
    signal.period     = c - a;
    signal.pulseWidth = b - a;
    signal.state      = VALID;

    a = currentTime;
    sigState = MID_HL;
  }
  
  lastUpdate = currentTime;
}

SIGNAL FreqCounter::getSignal()
{
  ulong currentTime = micros();
  bool callTimeout = false;
  SIGNAL ret;
  memset(&ret, 0, sizeof(SIGNAL));

  if(currentTime >= lastUpdate)
    if(currentTime - lastUpdate >= timeout)
      callTimeout = true;
  
  if(!callTimeout && signal.state == VALID)
  {
    ret.state       = VALID;
    ret.period      = signal.period;
    ret.pulseWidth  = signal.pulseWidth;
  }
  
  return ret;
}

