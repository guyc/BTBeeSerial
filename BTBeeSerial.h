#ifndef BTBeeSerial_h
#define BTBeeSerial_h

#include <inttypes.h>
#include <SoftwareSerial.h>

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

    // Current State:
    State_t state;
    BTBeeSerial(uint8_t RxPin, uint8_t TxPin);

    // BlueTooth control
    
    // TODO: these should reeturn status codes, not void
    
    void btWorkingMode(WorkingMode_t mode);   // client==slave, server==master
    void btBaudRate(BaudRate_t baudRate);     // baud rate to BT module
    void btAutoConnect(Permit_t permitted);   // auto-reconnect last paired device on power
    void btConnect(Permit_t permitted);       // allow paired device to connect to me
    void btDeviceName(const char name[]);          // 
    void btPinCode(const char code[]);             // must be 4 digit string
    void btDeletePinCode(void);
    void btLossReconnect(Permit_t permitted); // reconnect when master device is out of range   
    void btInquire(Permit_t permitted);
    void btReadLocalAddress(void);
    
    void btCommand(const char cmd[], unsigned int value);
    void btCommand(const char cmd[], const char value[]);
    void btCommand(const char cmd[]);
};

#endif
