#pragma once
#include"cnfg_gfx.h"
#include"MCU_ELECTROCATLYST.hpp"
#include <Arduino.h>
#include <HardwareSerial.h>
#include"JBD_BMS.hpp"
typedef struct {
  uint32_t id;
  uint8_t  data[8];
  uint8_t  dlc;
} can1_frame_t;

stm_can_frame_t last_frame;  // latest only
void Default_Display(){
tft.setCursor(20,120 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("DISTANCE TRAVELLED :"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(260, 120);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20,20 );
tft.setTextSize(2);
tft.setTextColor(0xffffff);
tft.println("MOTOR_RPM:"); 
Serial1.printf("%ld",0);
tft.setTextColor(0xffffff,  0xF800);  // foreground, background
tft.setCursor(150, 20);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20,50 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("VOLTAGE:"); 
Serial1.printf("%lf",0);
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(130, 50);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20,80 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CURRENT :"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(130, 80);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20,150 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("MOTOR_TEMP:"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(200, 150);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20,180 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("BRAKE_PERCENTAGE :"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(250, 180);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20,210 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("THROTTLE_PER :"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(200, 210);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20,240 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("DRIVE_MODE :"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(200, 240);
tft.setTextSize(2);
tft.printf("N");



tft.setCursor(20,270 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("SPEED_IN_Kmph :"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(200, 270);
tft.setTextSize(2);
tft.printf("0");
/*---------------------------------------------------*/
tft.setCursor(20+400,20 );
tft.setTextSize(2);
tft.setTextColor(0xffffff);
tft.println("VOLTAGE:"); 
tft.setTextColor(0xffffff,  0xF800);  // foreground, background
tft.setCursor(150+400, 20);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400,50 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("DIS_CH_CUR:"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(190+400, 50);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400,80 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("RC :"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(130+400, 80);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400,110 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("RSOC  :"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(100+400, 110);
tft.setTextSize(2);
tft.printf("0");

/*-------------------------------------------------------------------------*/
tft.setCursor(20+400,180 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_1:"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400, 180);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400,210 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_2:"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400, 210);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400,240 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_3:"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400, 240);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400,270 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_4:"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400, 270);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400,300 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_5:"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400, 300);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400,330 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_6:"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400, 330);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400,360 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_7:"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400, 360);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400,390 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_8:"); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400, 390);
tft.setTextSize(2);
tft.printf("0");
/*-----------------------------------------------------------------------------*/

tft.setCursor(20+400+200,180 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_9: "); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400+200+10, 180);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400+200,210 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_10: "); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400+200+10, 210);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400+200,240 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_11: "); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400+200+10, 240);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400+200,270 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_12: "); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400+200+10, 270);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400+200,300 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_13: "); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400+200+10, 300);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400+200,330 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_14: "); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400+200+10, 330);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400+200,360 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_15: "); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400+200+10, 360);
tft.setTextSize(2);
tft.printf("0");

tft.setCursor(20+400+200,390 );
tft.setTextSize(2);
tft.setTextColor(TFT_WHITE);
tft.println("CELL_16: "); 
tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
tft.setCursor(110+400+200+10, 390);
tft.setTextSize(2);
tft.printf("0");
}
void setup(){
Serial.begin(115200);
  tft.init();
Serial1.begin(115200, SERIAL_8N1, 44, 43);
tft.init();
tft.setBrightness(128);
tft.setColorDepth(16);
tft.fillScreen(TFT_RED);
Default_Display();
}
  // lcd.clear(); 

void loop(){
 
  const size_t FRAME_SIZE = 13;
   while (Serial1.available()) {

    uint8_t buf[FRAME_SIZE];
    size_t r = Serial1.readBytes((uint8_t*)buf, FRAME_SIZE);
    uint32_t id = ((uint32_t)buf[3]) |
                  ((uint32_t)buf[2] << 8) |
                  ((uint32_t)buf[1] << 16) |
                  ((uint32_t)buf[0] << 24);

    uint8_t dlc = buf[4];
    if (dlc > 8) dlc = 8; // sanitize
    uint8_t data[8];
    for (int i = 0; i < 8; ++i) data[i] = buf[5 + i];


    last_frame.id = id;
    last_frame.dlc = dlc;
    memcpy(last_frame.data, data, 8);
    matel_mcu_process_can_frame(&last_frame);
    Process_Jbd_Bms_Messages(&last_frame);
  }

}