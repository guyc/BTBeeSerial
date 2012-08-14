
#include "BTBeeSerial.h"
 
BTBeeSerial::BTBeeSerial(uint8_t RxPin, uint8_t TxPin) : SoftwareSerial(RxPin, TxPin)
{
  state = STATE_INITIALIZING;
}

void BTBeeSerial::btWorkingMode(WorkingMode_t mode)
{
  btCommand("STWMOD", mode);
}

void BTBeeSerial::btBaudRate(BaudRate_t baudRate)
{
  btCommand("STBD", baudRate);
}

void BTBeeSerial::btAutoConnect(Permit_t permitted)
{
  btCommand("STAUTO", permitted);
}

void BTBeeSerial::btConnect(Permit_t permitted)
{
  btCommand("STOAUT", permitted);
}

void BTBeeSerial::btDeviceName(const char name[])
{
  btCommand("STNA", name);
}

void BTBeeSerial::btPinCode(const char code[])
{
  btCommand("STPIN", code);
}

void BTBeeSerial::btDeletePinCode(void)
{
  btCommand("DLPIN");
}

void BTBeeSerial::btLossReconnect(Permit_t permitted)
{
  btCommand("LOSSRECONN", permitted);
} 

void BTBeeSerial::btInquire(Permit_t permitted)
{
  btCommand("INQ", permitted);
}

void BTBeeSerial::btReadLocalAddress()
{
  btCommand("RTADDR");
}

void BTBeeSerial::btCommand(const char cmd[], unsigned int value)
{
  print("\r\n+");
  print(cmd);
  print("=");
  print(value);
  print("\r\n");  
}

void BTBeeSerial::btCommand(const char cmd[])
{
  print("\r\n+");
  print(cmd);
  print("\r\n");  
}

void BTBeeSerial::btCommand(const char cmd[], const char value[])
{
  print("\r\n+");
  print(cmd);
  print("=");
  print(value);
  print("\r\n");  
}
 
