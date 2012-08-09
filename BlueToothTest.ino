#include <SoftwareSerial.h>   //Software Serial Port
#include "BTBeeSerial.h"      // serial over bluetooth

#define BT_RX 11
#define BT_TX 12
SoftwareSerial btSerial(BT_RX, BT_TX);

BTBeeSerial bt(BT_RX, BT_TX);

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

void btInit()
{
    Serial.print("Setting up Bluetooth link");       //For debugging, Comment this line if not required    
    pinMode(BT_RX, INPUT);
    pinMode(BT_TX, OUTPUT);
    btSerial.begin(38400);                // Set BluetoothBee BaudRate to default baud rate 38400
    delay(3000);
    
    btCommand("\r\n+STBD=38400\r\n");      // set baud rate
    btCommand("\r\n+STWMOD=0\r\n");       // set device working as a slave
    btCommand("\r\n+STNA=arduino\r\n");   // set device name
    btCommand("\r\n+STAUTO=0\r\n");       // auto connect forbidden
    btCommand("\r\n+STOAUT=1\r\n");       // permit paired device connect
    btCommand("\r\n+STPIN=0000\r\n");     // set pincode
    delay(2000);                          // This delay is required.
    btSerial.print("\r\n+INQ=1\r\n");     // set inquire mode
    delay(2000);                          // This delay is required.
    btCommand("\r\n+INQ=1\r\n");          // enable being inquired
    Serial.print("Setup complete");
    btCommand("\r\n+RTADDR\r\n");         // read local address code
    
    bt.setBaudRate(BTBeeSerial::BAUD_38400);
    bt.setWorkingMode(BTBeeSerial::MODE_SLAVE);
    bt.setDeviceName("Arduino");
    bt.setAutoConnect(BTBeeSerial::FORBIDDEN);
    bt.setConnect(BTBeeSerial::PERMITTED);
    bt.setPinCode("0000");
    bt.setInquire(BTBeeSerial::PERMITTED);
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

