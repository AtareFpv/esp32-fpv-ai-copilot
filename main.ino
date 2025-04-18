#include <HardwareSerial.h>

#define RXD2 18
#define TXD2 17
HardwareSerial SerialINAV(2);

void setup() {
  Serial.begin(115200);
  SerialINAV.begin(115200, SERIAL_8N1, RXD2, TXD2);
  delay(2000);

  // Send initial test alert
  sendOSDMessage("AI ONLINE", 6, 5);  // row, col
}

void loop() {
  // This is where we’ll poll MSP in the future
  // For now, just flash the message every 10 seconds
  delay(10000);
  sendOSDMessage("AI: VOLTAGE DROP", 6, 4);
}

void sendOSDMessage(String message, byte row, byte col) {
  byte msgId = 220; // MSP_DISPLAYPORT_WRITE_CHAR
  byte header[] = {'$', 'M', '<'};
  byte len = 3 + message.length();
  byte checksum = msgId ^ len;
  byte payload[len];
  
  payload[0] = row;
  payload[1] = col;
  payload[2] = message.length();

  for (int i = 0; i < message.length(); i++) {
    payload[3 + i] = message[i];
    checksum ^= message[i];
  }
  checksum ^= row ^ col ^ message.length();

  SerialINAV.write(header, 3);
  SerialINAV.write(len);
  SerialINAV.write(msgId);
  SerialINAV.write(payload, len);
  SerialINAV.write(checksum);
}
