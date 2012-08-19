#ifndef BTBeeSerial_h
#define BTBeeSerial_h

#include <inttypes.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

// reference documents:
// http://www.seeedstudio.com/wiki/Bluetooth_Bee
// http://elmicro.com/files/seeedstudio/btbee-datasheet.pdf
// XBee Adaptor
// http://www.adafruit.com/products/127
// http://www.ladyada.net/images/xbee/xbee11sch.png

class BTBeeSerial : public SoftwareSerial
{
  public:
    typedef enum {
       MODE_CLIENT = 0, // slave
       MODE_SLAVE  = 0,
       MODE_SERVER = 1,  // master
       MODE_MASTER = 1
    } WorkingMode_t;
    
    typedef enum {
       BAUD_9600    = 9600,
       BAUD_19200   = 19200,
       BAUD_38400   = 38400,
       BAUD_57600   = 57600,
       BAUD_115200  = 115200,
       BAUD_230400  = 230400,
       BAUD_460800  = 460800
    } BaudRate_t;
    
    typedef enum {
      FORBIDDEN = 0,
      PERMITTED = 1
    } Permit_t;
    
    typedef enum {
      STATE_INITIALIZING = 0,
      STATE_READY        = 1,
      STATE_INQURING     = 2,
      STATE_CONNECTING   = 3,
      STATE_CONNECTED    = 4
    } State_t;
    
    typedef enum {
      STATUS_OK          = 0,
      STATUS_TIMEOUT     = 1,
      STATUS_OVERFLOW    = 2,
    } Status_t;

    // Current State:
    State_t state;
    BTBeeSerial(uint8_t RxPin, uint8_t TxPin);
    
    // BlueTooth control
    
    // TODO: these should reeturn status codes, not void
    
    Status_t btWorkingMode(WorkingMode_t mode);   // client==slave, server==master
    Status_t btBaudRate(BaudRate_t baudRate);     // baud rate to BT module
    Status_t btAutoConnect(Permit_t permitted);   // auto-reconnect last paired device on power
    Status_t btConnect(Permit_t permitted);       // allow paired device to connect to me
    Status_t btDeviceName(const char name[]);          // 
    Status_t btPinCode(const char code[]);             // must be 4 digit string
    Status_t btDeletePinCode(void);
    Status_t btLossReconnect(Permit_t permitted); // reconnect when master device is out of range   
    Status_t btInquire(Permit_t permitted);
    Status_t btReadLocalAddress();
    
    Status_t btCommand(const char cmd[], unsigned int value);
    Status_t btCommand(const char cmd[], const char value[]);
    Status_t btCommand(const char cmd[]);
    Status_t btOkWait(unsigned long uTimeout=1000000);
    Status_t btLineWait(char buf[], size_t bufsize, size_t *len);
};

#endif
