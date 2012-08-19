
#include "BTBeeSerial.h"      // serial over bluetooth
#include <SoftwareSerial.h>

#define BT_RX 11
#define BT_TX 12
BTBeeSerial btSerial(BT_RX, BT_TX);

// IMPORTANT - must force disconnect or be able to detect state?
// Pulling PIO0 high will disconnect current working Bluetooth device.
// Status instruction port PIO1: low-disconnected, high-connected;

// types of response from BT:
// WORK:SLAVER
// +BTSTATE:n
// CONNECT:FAIL
// CONNECT
// OK
// seems like it might echo original command?

// reference doc: http://elmicro.com/files/seeedstudio/btbee-datasheet.pdf

void xbtCommand(char command[])
{
    char a;
    btSerial.print(command);
    Serial.print(command);                          //For debugging, Comment this line if not required    
    delay(3000);
 
    while(btSerial.available())              //For debugging, Comment this line if not required  
    { 
       //Serial.print("YAY");
       Serial.print(char(btSerial.read()));  
    }                                             
}

void btRead()
{
    delay(1000);
    while(btSerial.available())      
    { 
       //Serial.print("YAY");
       Serial.print(char(btSerial.read()));  
    }                                             
}

void btInit()
{
    Serial.print("Setting up Bluetooth link");       //For debugging, Comment this line if not required    
    pinMode(BT_RX, INPUT);
    pinMode(BT_TX, OUTPUT);
    btSerial.begin(38400);                // Set BluetoothBee BaudRate to default baud rate 38400
    delay(3000);
    
    btSerial.btBaudRate(BTBeeSerial::BAUD_38400);
    btSerial.btOkWait();
    
    btSerial.btWorkingMode(BTBeeSerial::MODE_SLAVE);
    btSerial.btOkWait();
    
    btSerial.btDeviceName("Arduino");
    btSerial.btOkWait();
    
    btSerial.btAutoConnect(BTBeeSerial::PERMITTED);
    btSerial.btOkWait();
    
    btSerial.btConnect(BTBeeSerial::PERMITTED);
    btSerial.btOkWait();
    
    btSerial.btPinCode("0000");
    btSerial.btOkWait();
    
    btSerial.btReadLocalAddress();
    btSerial.btOkWait();
    
    btSerial.btInquire(BTBeeSerial::PERMITTED);
    //btSerial.print("\r\n+INQ=1\r\n");     // set inquire mode
    btSerial.btOkWait();
    
    Serial.print("Setup complete");
}


void setup()
{
  Serial.begin(9600);
  btInit();
}

void loop()
{
  char buffer[100];
  char *p = buffer;
  int avail = 99;

  if (btSerial.available() && avail>0) {
    *p++ = btSerial.read();
    avail--;
  }
  *p++=0;
  Serial.print(buffer);
}

