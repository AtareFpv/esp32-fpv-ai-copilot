
/*
  AI Co-Pilot Main Sketch
  Reads MSP telemetry from INAV and injects alert messages into the OSD
  Platform: ESP32-S3 (LILYGO T-Display)
*/

#include <HardwareSerial.h>

HardwareSerial fcSerial(1);  // UART1 on ESP32-S3
#define TXD1 17
#define RXD1 16

void setup() {
  fcSerial.begin(115200, SERIAL_8N1, RXD1, TXD1);
  delay(1000);
  sendOsdText("AI CO-PILOT READY", 5, 4);
}

void loop() {
  // Placeholder for logic
}

void sendOsdText(String text, byte row, byte col) {
  byte msgId = 220; // MSP_DISPLAYPORT_WRITE_CHAR
  byte header[] = {'$', 'M', '<'};
  byte length = 3 + text.length();
  byte payload[length];
  payload[0] = row;
  payload[1] = col;
  payload[2] = text.length();

  for (int i = 0; i < text.length(); i++) {
    payload[3 + i] = text[i];
  }

  byte checksum = msgId ^ length;
  for (int i = 0; i < length; i++) {
    checksum ^= payload[i];
  }

  fcSerial.write(header, 3);
  fcSerial.write(length);
  fcSerial.write(msgId);
  fcSerial.write(payload, length);
  fcSerial.write(checksum);
}
