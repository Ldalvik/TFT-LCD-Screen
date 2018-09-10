#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8
#define black ST77XX_BLACK
#define white ST77XX_WHITE
#define red ST77XX_RED
#define green ST77XX_GREEN
#define blue ST77XX_BLUE
#define magenta ST77XX_MAGENTA
int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
String content = "";

void setup(void) {
  Serial.begin(9600);
  bluetooth.begin(115200);

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_WHITE);
}

void loop() {
  if (bluetooth.available()) {
    char character = (char) bluetooth.read();
    if (character == '/') {
      Serial.println(content);
      check(content);
      content = "";
    } else {
      content.concat(character);
    }
  }
}

void check(String data){
  if(data.startsWith("drawCircle")){
    int x = split(data, ',', 1).toInt();
    int y = split(data, ',', 2).toInt();
    int radius = split(data, ',', 3).toInt();
    int color = split(data, ',', 4).toInt();
    drawCircle(x, y, radius, color);
  }
}

void drawCircle(int x, int y, int radius, int color) {
  tft.drawCircle(x, y, radius, color);
}

void drawFilledCircle(int x, int y, int radius, int color) {
  tft.fillCircle(x, y, radius, color);
}

void drawPixel(int x, int y, int color) {
  tft.drawPixel(x, y, color);
}

void drawLine(int x2, int y2, int x, int y, int color) {
  tft.drawLine(x2, y2, x, y, color);
}

void drawHorizontalLine(int _start, int _end, int y, int color) {
  tft.drawFastHLine(_start, _end, y, color);

}

void drawVerticalLine(int _start, int _end, int y, int color) {
  tft.drawFastVLine(_start, _end, y, color);

}

void drawRectangle(int x, int y, int height, int width, int color) {
  tft.drawRect(x, y, height, width, color);

}

void drawFilledRectangle(int x, int y, int height, int width, int color) {
  tft.fillRect(x, y, height, width, color);

}

void drawTriangle(int leftX, int leftY, int topX, int topY, int rightX, int rightY, int color) {
  tft.drawTriangle(leftX, leftY, topX, topY, rightX, rightY, color);
}

void drawRoundTriangle(int x, int y, int height, int width, int radius, int color) {
  tft.drawRoundRect(x, y, width, height, radius, color);
}

void _setCursor(int x, int y) {
  tft.setCursor(x, y);
}

void drawText(String text, int color, boolean isWrapped) {
  tft.setTextColor(color);
  tft.setTextWrap(isWrapped);
  tft.print(text);
}

void clearScreen(int color){
    tft.fillScreen(color);
}

String split(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
