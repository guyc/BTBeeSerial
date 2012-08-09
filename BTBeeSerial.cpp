
#include "BTBeeSerial.h"
 
BTBeeSerial::BTBeeSerial(uint8_t RxPin, uint8_t TxPin)
{
  state = STATE_INITIALIZING;
}

void BTBeeSerial::setWorkingMode(WorkingMode_t mode)
{
}

void BTBeeSerial::setBaudRate(BaudRate_t baudRate)
{
}

void BTBeeSerial::setAutoConnect(Permit_t permitted)
{
}

void BTBeeSerial::setConnect(Permit_t permitted)
{
}

void BTBeeSerial::setDeviceName(const char[])
{
}

void BTBeeSerial::setPinCode(const char[])
{
}

void BTBeeSerial::deletePinCode(void)
{
}

void BTBeeSerial::setLossReconnect(Permit_t permitted)
{
} 

void BTBeeSerial::setInquire(Permit_t permitted)
{
}
    

// SoftSerial emulation
void print(char)
{
}

void print(const char[])
{
}


 
