#pragma once
#include"cnfg_gfx.h"
#include"MCU_ELECTROCATLYST.hpp"
#include <Arduino.h>
#include <HardwareSerial.h>
#include"JBD_BMS.hpp"
#include <lvgl.h>
#include <ui.h>
#include"touch.h"
enum BoardConstants { TFT_BL=2, LVGL_BUFFER_RATIO=6 };

stm_can_frame_t last_frame;  // latest only
#if LV_USE_LOG != 0
/* Serial debugging */
void my_print (const char * buf)
{
    Serial.printf( buf );
    Serial.flush();
}
#endif


/* Display flushing */
void my_disp_flush (lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
    tft.pushImageDMA( area->x1, area->y1, w, h, (lgfx::rgb565_t*) &color_p->full );
#else
    tft.pushImageDMA( area->x1, area->y1, w, h, (lgfx::rgb565_t*) &color_p->full );
#endif
    lv_disp_flush_ready( disp );
}
/*Change to your screen resolution*/
// static const uint16_t screenWidth  = 800;
// static const uint16_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf [screenWidth * screenHeight / LVGL_BUFFER_RATIO];

/*Read the touchpad*/
void my_touchpad_read (lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
    if ( touch_has_signal() ) {
        if ( touch_touched() ) {
            data->state = LV_INDEV_STATE_PR;
            //Set the coordinates
            data->point.x = touch_last_x;
            data->point.y = touch_last_y;
            //Serial.print( "Data x :" );
            //Serial.println( touch_last_x );
            //Serial.print( "Data y :" );
            //Serial.println( touch_last_y );
        }
        else if ( touch_released() ) {
            data->state = LV_INDEV_STATE_REL;
        }
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }
    delay(15);
}
void setup(){
Serial1.begin(115200, SERIAL_8N1, 44, 43);
    //Init Display
    tft.begin();
    tft.fillScreen( TFT_BLACK );
    delay( 200 );

    lv_init();

    delay( 100 );
    touch_init();

    //screenWidth = lcd.width();
    //screenHeight = lcd.height();
    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / LVGL_BUFFER_RATIO );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    ui_init();
    //lcd.fillScreen(TFT_BLACK);
    Serial.println( "Setup done" );
}
void loop(){
       lv_timer_handler(); /* let the GUI do its work */
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