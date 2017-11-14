#ifndef _FREQCOUNTER_H_
#define _FREQCOUNTER_H_

typedef unsigned long ulong;

typedef enum
{
  VALID,
  INVALID,
  TIMEOUT
} SIGNAL_STATE;

typedef struct
{
  ulong period, pulseWidth;
  SIGNAL_STATE state;
} SIGNAL;

class FreqCounter
{
  private:
    int     inputPin;
    ulong   timeout;
    volatile ulong lastUpdate;
    ulong   a, b, c;
    volatile SIGNAL signal;

    enum 
    {
      START_LH,
      MID_HL,
      END_LH
    } sigState;
    
  public:
    int pinState = LOW;
    FreqCounter(int inputPin, unsigned long timeout);
    void update();
    SIGNAL getSignal();
};

#endif

