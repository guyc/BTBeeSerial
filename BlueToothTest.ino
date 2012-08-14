
#include "BTBeeSerial.h"      // serial over bluetooth
#include <SoftwareSerial.h>

#define BT_RX 11
#define BT_TX 12
BTBeeSerial btSerial(BT_RX, BT_TX);

// reference doc: http://elmicro.com/files/seeedstudio/btbee-datasheet.pdf

void btCommand(char command[])
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
    //btCommand("\r\n+STBD=38400\r\n");      // set baud rate
    btRead();
    
    btSerial.btWorkingMode(BTBeeSerial::MODE_SLAVE);
    //btCommand("\r\n+STWMOD=0\r\n");       // set device working as a slave
    btRead();
    
    btSerial.btDeviceName("Arduino");
    btCommand("\r\n+STNA=arduino\r\n");   // set device name
    btRead();
    
    btSerial.btAutoConnect(BTBeeSerial::FORBIDDEN);
    btCommand("\r\n+STAUTO=0\r\n");       // auto connect forbidden
    btRead();
    
    btSerial.btConnect(BTBeeSerial::PERMITTED);
    btCommand("\r\n+STOAUT=1\r\n");       // permit paired device connect
    btRead();
    
    btSerial.btPinCode("0000");
    btCommand("\r\n+STPIN=0000\r\n");     // set pincode
    btRead();
    
    btSerial.btReadLocalAddress();
    btRead();
    
    delay(2000);                          // This delay is required.
    btSerial.btInquire(BTBeeSerial::PERMITTED);
    //btSerial.print("\r\n+INQ=1\r\n");     // set inquire mode
    delay(2000);                          // This delay is required.
    btRead();
    
    Serial.print("Setup complete");
    //btSerial.Command("\r\n+RTADDR\r\n");         // read local address code
    btSerial.btReadLocalAddress();
    btRead();
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

