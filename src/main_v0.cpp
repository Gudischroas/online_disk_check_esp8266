#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define RGB_PIN 2  // WS2812B 数据引脚
#define NUMPIXELS 6  // 硬盘数量

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

int abs6(int a) {
  if (a > 6) {return a - 7;}
  else {return a;}
}

// void RGB_setup() {
//   int color[7][3] = {255, 0, 0, 255, 125, 0, 255, 255, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 255};
//   int i = 0;
//   while (i <= 7) {
//     strip.setPixelColor(0, strip.Color(color[abs6(0 + i)][0], color[abs6(0 + i)][1], color[abs6(0 + i)][2]));
//     strip.setPixelColor(1, strip.Color(color[abs6(1 + i)][0], color[abs6(1 + i)][1], color[abs6(1 + i)][2]));
//     strip.setPixelColor(2, strip.Color(color[abs6(2 + i)][0], color[abs6(2 + i)][1], color[abs6(2 + i)][2]));
//     strip.setPixelColor(3, strip.Color(color[abs6(3 + i)][0], color[abs6(3 + i)][1], color[abs6(3 + i)][2]));
//     strip.setPixelColor(4, strip.Color(color[abs6(4 + i)][0], color[abs6(4 + i)][1], color[abs6(4 + i)][2]));
//     strip.setPixelColor(5, strip.Color(color[abs6(5 + i)][0], color[abs6(5 + i)][1], color[abs6(5 + i)][2]));
//     strip.show();
//     i++;
//     delay(500);
//   }
// }

void setup() {
  Serial.begin(9600); 
  strip.begin();
  strip.setBrightness(80);
  strip.show(); // 初始化所有像素
  //RGB_setup();
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int colonIndex = data.indexOf(':');
    int slot = data.substring(0, colonIndex).toInt();
    String colorStr = data.substring(colonIndex + 1);
    
    int r = colorStr.substring(0, colorStr.indexOf(',')).toInt();
    int g = colorStr.substring(colorStr.indexOf(',') + 1, colorStr.lastIndexOf(',')).toInt();
    int b = colorStr.substring(colorStr.lastIndexOf(',') + 1).toInt();
    
    strip.setPixelColor(slot, strip.Color(r, g, b));
    strip.show();
    delay(1000);
    // if (r == 0 && g == 255 && b == 0) {Serial.printf("Disk %d Online! \n", slot);}
    // else if (r == 255 && g == 0 && b == 0) {Serial.printf("Disk %d Failed! \n", slot);}
    // else if (r == 255 && g == 255 && b == 0) {Serial.printf("Disk %d Predictive Failure! \n", slot);}
    // else {Serial.printf("Disk %d Defualt \n", slot);}
  }
}
