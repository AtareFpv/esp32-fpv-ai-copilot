
/*
  AtareFpv AI Co-Pilot Boot + Main Sketch
  ESP32-S3 (LILYGO T-Display)
  Displays animated boot screen, then sends OSD text message
*/

#include <TFT_eSPI.h>
#include <SPI.h>
#include <HardwareSerial.h>

TFT_eSPI tft = TFT_eSPI();  // TFT instance
HardwareSerial fcSerial(1);  // UART1

#define TXD1 17
#define RXD1 16

// === BOOT SCREEN ANIMATION ===

void drawStars(int count) {
  for (int i = 0; i < count; i++) {
    int x = random(0, 320);
    int y = random(0, 170);
    uint16_t color = random(180, 255);
    tft.drawPixel(x, y, tft.color565(color, color, color));
  }
}

void swirlIn(String title) {
  int cx = 160, cy = 85;
  float r = 2.0;
  float angle = 0;

  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextFont(4);
  tft.setTextSize(1);

  while (r < 60) {
    int x = cx + cos(angle) * r;
    int y = cy + sin(angle) * r;

    tft.fillCircle(x, y, 2, TFT_CYAN);
    delay(15);
    angle += 0.3;
    r += 0.5;
  }

  delay(300);
  tft.setCursor(cx - (title.length() * 6), cy - 8);
  tft.print(title);
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

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  drawStars(100);
  swirlIn("AtareFpv");
  delay(2000);
  tft.fillScreen(TFT_BLACK); // Clear screen

  // Serial for OSD injection
  fcSerial.begin(115200, SERIAL_8N1, RXD1, TXD1);
  delay(1000);
  sendOsdText("AI CO-PILOT READY", 5, 4);
}

void loop() {
  // Placeholder for future AI logic
}
