#include "BTBeeSerial.h"

BTBeeSerial::BTBeeSerial(uint8_t RxPin, uint8_t TxPin) : SoftwareSerial(RxPin, TxPin)
{
  state = STATE_INITIALIZING;
}

BTBeeSerial::Status_t BTBeeSerial::btWorkingMode(WorkingMode_t mode)
{
  return btCommand("STWMOD", mode);
}

BTBeeSerial::Status_t BTBeeSerial::btBaudRate(BaudRate_t baudRate)
{
  return btCommand("STBD", baudRate);
}

BTBeeSerial::Status_t BTBeeSerial::btAutoConnect(Permit_t permitted)
{
  return btCommand("STAUTO", permitted);
}

BTBeeSerial::Status_t BTBeeSerial::btConnect(Permit_t permitted)
{
  return btCommand("STOAUT", permitted);
}

BTBeeSerial::Status_t BTBeeSerial::btDeviceName(const char name[])
{
  return btCommand("STNA", name);
}

BTBeeSerial::Status_t BTBeeSerial::btPinCode(const char code[])
{
  btCommand("STPIN", code);
}

BTBeeSerial::Status_t BTBeeSerial::btDeletePinCode()
{
  return btCommand("DLPIN");
}

BTBeeSerial::Status_t BTBeeSerial::btLossReconnect(Permit_t permitted)
{
  return btCommand("LOSSRECONN", permitted);
} 

BTBeeSerial::Status_t BTBeeSerial::btInquire(Permit_t permitted)
{
  return btCommand("INQ", permitted);
}

BTBeeSerial::Status_t BTBeeSerial::btReadLocalAddress()
{
  return btCommand("RTADDR");
}

BTBeeSerial::Status_t BTBeeSerial::btCommand(const char cmd[], unsigned int value)
{
  Serial.print("CMD:"); Serial.println(cmd);
  print("\r\n+");
  print(cmd);
  print("=");
  print(value);
  print("\r\n");  
  return btOkWait();
}

BTBeeSerial::Status_t BTBeeSerial::btCommand(const char cmd[])
{
  Serial.print("CMD:"); Serial.println(cmd);
  print("\r\n+");
  print(cmd);
  print("\r\n");  
  return btOkWait();
}

BTBeeSerial::Status_t BTBeeSerial::btCommand(const char cmd[], const char value[])
{
  Serial.print("CMD:"); Serial.println(cmd);
  print("\r\n+");
  print(cmd);
  print("=");
  print(value);
  print("\r\n");
  return btOkWait();
}

BTBeeSerial::Status_t BTBeeSerial::btOkWait(unsigned long uTimeout)
{
  unsigned long time0 = micros();  // timeout timer
  unsigned long time1;

  const uint8_t bufsize = 40;
  char buf[bufsize];
  size_t len;
  
  while (time1 - time0 < uTimeout) {
    BTBeeSerial::Status_t status = btLineWait(buf, bufsize, &len);
    switch (status) {
      case STATUS_OK:
        switch (len) {
          // Responses I've seen:
          //   ERROR
          //   WORK:SLAVER
          //   CONNECT:FAIL
          case 0: // empty line, ignore it
            //Serial.println("EMPTY LINE");
            break;
          case 2:  // OK
            Serial.println("OKAY");
            return STATUS_OK;
            break;
          case 10: // +BTSTATE:n
            Serial.print("STATE:");
            state = (BTBeeSerial::State_t)(buf[9] - '0'); // numerical state
            Serial.println(state);
            break;
          default:
            Serial.print("OTHER:");
            Serial.println(len);
            Serial.println(buf);
        }
        break;
      case STATUS_OVERFLOW:
      case STATUS_TIMEOUT:
        return status;
    }
    time1 = micros();
  }
}

// lines are terminated with 13 10
// response to a command is
// CR LF
// OK
// CR LF
//
BTBeeSerial::Status_t BTBeeSerial::btLineWait(char *buf, size_t bufsize, size_t *len)
{
  const unsigned long uTimeout = 1000000;  // timeout in 1 second of inactivity  
  unsigned long time0 = micros();  // timeout timer
  unsigned long time1;
  char *p = buf;
  while (time1 - time0 < uTimeout) {
    if (available()) {
      char c = read();
      if (c==13) {
        *len = p - buf;
        *p++ = 0;
        return STATUS_OK;
      } else if (c==10) {
        // ignore LF
      } else {
        *p++ = c;
        if (p-buf == bufsize) {
          return STATUS_OVERFLOW;  // received bufsize chars without a CR
        }
      }
    }
    time1 = micros();
  }
  Serial.println("TO:");
  return STATUS_OK;
}

