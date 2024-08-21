#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define PIN 2  // WS2812B 数据引脚
#define NUMPIXELS 6  // 硬盘数量对应的灯珠数量

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// 用于存储每个灯珠的颜色数据
uint32_t colors[NUMPIXELS];

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // 初始化所有像素
  clearColors(); // 清空所有灯珠颜色
}

void loop() {
  if (Serial.available()) {
    while (Serial.available()) {
      String data = Serial.readStringUntil('\n'); // 读取一行数据
      parseDataAndSetColor(data);  // 解析并设置颜色
    }
    strip.show(); // 一次性更新所有灯珠显示
  }
}

// 将所有灯珠的颜色设置为黑色
void clearColors() {
  for (int i = 0; i < NUMPIXELS; i++) {
    colors[i] = strip.Color(0, 0, 0);
  }
  strip.show();
}

// 解析接收到的数据，并设置对应灯珠的颜色
void parseDataAndSetColor(String data) {
  int colonIndex = data.indexOf(':');
  if (colonIndex == -1) return;  // 如果数据格式不正确，跳过解析
  
  int slot = data.substring(0, colonIndex).toInt();  // 提取 slot 编号
  String colorStr = data.substring(colonIndex + 1);  // 提取颜色值字符串
  
  int r = colorStr.substring(0, colorStr.indexOf(',')).toInt();
  int g = colorStr.substring(colorStr.indexOf(',') + 1, colorStr.lastIndexOf(',')).toInt();
  int b = colorStr.substring(colorStr.lastIndexOf(',') + 1).toInt();
  
  // 设置指定 slot 对应灯珠的颜色
  if (slot >= 0 && slot < NUMPIXELS) {
    colors[slot] = strip.Color(r, g, b);
    strip.setPixelColor(slot, colors[slot]);
  }
}