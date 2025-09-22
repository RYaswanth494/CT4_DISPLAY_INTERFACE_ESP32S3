#pragma once

#include <HardwareSerial.h>
#include"cnfg_gfx.h"
  LGFX tft;
#include"MCU_ELECTROCATALYST_MESSAGES.hpp"
// #include"uart.h"
#include"can.hpp"
#include<stdint.h>
#include <string.h>
#include<stdbool.h>
#include<cstdio>
#include<lv_label.h>
#include"ui_HOME.h"
#include"ui.h"
char pres_str1[100];
// Decoding functions for each CAN message
// Helper: extract Motorola-format (big-endian) up to 64 bits
// Sign-extend a value of 'len' bits
static int64_t sign_extend_u64(uint64_t v, int len) {

	if (len <= 0 || len > 64) return (int64_t)v;
	uint64_t sign = 1ULL << (len - 1);
	if (v & sign) {
	uint64_t mask = (~0ULL) << len;
	return (int64_t)(v | mask);
	}
	return (int64_t)v;
}
static uint64_t extract_motorola_u64(const uint8_t *data, int start, int len) {
	if (len <= 0 || len > 64) return 0;
	uint64_t value = 0;
	int cur_byte = start / 8;
	int cur_bit = start % 8; // 7 = MSB of byte
	for (int i = 0; i < len; i++) {
	uint8_t bit = 0;
	if (cur_byte >= 0 && cur_byte < 8) bit = (data[cur_byte] >> cur_bit) & 1U;
	value = (value << 1) | (uint64_t)bit;
	cur_bit--;
	if (cur_bit < 0) { cur_byte++; cur_bit = 7; }
	}
	return value;
}

static uint64_t extract_little_endian_u64(const uint8_t *data, int start, int len) {
if (len <= 0 || len > 64) return 0;
uint64_t value = 0;
for (int i = 0; i < len; i++) {
int bit_index = start + i;
int byte_index = bit_index / 8;
int bit_in_byte = bit_index % 8;
uint8_t bit = 0;
if (byte_index >= 0 && byte_index < 8) bit = (data[byte_index] >> bit_in_byte) & 1U;
value |= ((uint64_t)bit << i);
}
return value;
}

// Implementations of decode functions follow (using extract helpers)


void decode_MCU_Stat_Two(const uint8_t *data, MCU_Stat_Two_t *out) {
	if (!out) return;
	uint64_t raw0 = extract_little_endian_u64(data, 32, 32);
	out->MCU_Odometer_Val = (double)raw0 * 0.1 + 0.0;
	uint64_t raw1 = extract_little_endian_u64(data, 16, 16);
	out->MCU_VCU_State = (double)raw1;
	uint64_t raw2 = extract_little_endian_u64(data, 0, 16);
	out->MCU_Motor_RPM = (double)raw2  -16384.0;

    sprintf(pres_str1, "%.2lf",out->MCU_Odometer_Val);
    lv_label_set_text(ui_OdoMeterVal, pres_str1); 
		if(out->MCU_Motor_RPM<10){
    // sprintf(pres_str1, "%.2f",out->MCU_Motor_RPM);
    lv_label_set_text(ui_RPMVal,"0"); 
		}else{
    sprintf(pres_str1, "%ld",(uint64_t)out->MCU_Motor_RPM);
    lv_label_set_text(ui_RPMVal, pres_str1); 
		}
		
}
void decode_MCU_Fault_Code(const uint8_t *data, MCU_Fault_Code_t *out) {
	if (!out) return;
	// sequential 8-bit little-endian signals
	out->MCU_Fault_Code_0 = (int)extract_motorola_u64(data, 30, 1);
	out->MCU_Fault_Code_1 = (int)extract_motorola_u64(data, 31, 1);
	out->MCU_Fault_Code_2 = (int)extract_motorola_u64(data, 16,1);
	out->MCU_Fault_Code_3 = (int)extract_motorola_u64(data, 17, 1);
	out->MCU_Fault_Code_4 = (int)extract_motorola_u64(data, 18, 1);
	out->MCU_Fault_Code_5 = (int)extract_motorola_u64(data, 19, 1);
	out->MCU_Fault_Code_6 = (int)extract_motorola_u64(data, 20, 1);
	out->MCU_Fault_Code_7 = (int)extract_motorola_u64(data, 21, 1);
	out->MCU_Fault_Code_8 = (int)extract_motorola_u64(data, 22, 1);
	out->MCU_Fault_Code_9 = (int)extract_motorola_u64(data,23, 1);
	out->MCU_Fault_Code_10 = (int)extract_motorola_u64(data, 8, 1);
	out->MCU_Fault_Code_11 = (int)extract_motorola_u64(data, 9, 1);
	out->MCU_Fault_Code_12 = (int)extract_motorola_u64(data, 10, 1);
	out->MCU_Fault_Code_13 = (int)extract_motorola_u64(data, 11, 1);
	out->MCU_Fault_Code_14 = (int)extract_motorola_u64(data, 12, 1);
	out->MCU_Fault_Code_15 = (int)extract_motorola_u64(data, 13, 1);
	out->MCU_Fault_Code_16 = (int)extract_motorola_u64(data, 14, 1);
	out->MCU_Fault_Code_17 = (int)extract_motorola_u64(data, 15, 1);
	out->MCU_Fault_Code_18 = (int)extract_motorola_u64(data, 0, 1);
	out->MCU_Fault_Code_19 = (int)extract_motorola_u64(data, 7, 3);
	out->MCU_Fault_Code_20 = (int)extract_motorola_u64(data, 1, 1);
	out->MCU_Fault_Code_21 = (int)extract_motorola_u64(data, 2,1);
	out->MCU_Fault_Code_22 = (int)extract_motorola_u64(data, 4, 3);
	
}
void decode_MCU_FAULT_One(const uint8_t *data, MCU_FAULT_One_t *out) {
if (!out) return;
out->MCU_FAULT_One_sig0 = (int)extract_motorola_u64(data, 27, 1);
out->MCU_FAULT_One_sig1 = (int)extract_motorola_u64(data, 28, 1);
out->MCU_FAULT_One_sig2 = (int)extract_motorola_u64(data, 39, 1);
out->MCU_FAULT_One_sig3 = (int)extract_motorola_u64(data, 4, 1);
out->MCU_FAULT_One_sig4 = (int)extract_motorola_u64(data, 2, 1);
out->MCU_FAULT_One_sig5 = (int)extract_motorola_u64(data, 18, 6);
out->MCU_FAULT_One_sig6 = (int)extract_motorola_u64(data, 6, 1);
out->MCU_FAULT_One_sig7 = (int)extract_motorola_u64(data, 9, 2);
out->MCU_FAULT_One_sig8 = (int)extract_motorola_u64(data, 11, 2);
out->MCU_FAULT_One_sig9 = (int)extract_motorola_u64(data, 1, 1);
out->MCU_FAULT_One_sig10 = (int)extract_motorola_u64(data, 21, 1);
out->MCU_FAULT_One_sig11 = (int)extract_motorola_u64(data, 7, 1);
out->MCU_FAULT_One_sig12 = (int)extract_motorola_u64(data, 15, 4);
out->MCU_FAULT_One_sig13 = (int)extract_motorola_u64(data, 23, 2);
out->MCU_FAULT_One_sig14 = (int)extract_motorola_u64(data, 3, 1);
out->MCU_FAULT_One_sig15 = (int)extract_motorola_u64(data, 5, 1);

}
void decode_MCU_FAULT_two(const uint8_t *data, MCU_FAULT_two_t *out) {
if (!out) return;
	out->MCU_FAULT_two_sig0 = (int)extract_motorola_u64(data, 9, 3);
	out->MCU_FAULT_two_sig1 = (int)extract_motorola_u64(data, 10, 1);
	out->MCU_FAULT_two_sig2 = (int)extract_motorola_u64(data, 11, 1);
	out->MCU_FAULT_two_sig3 = (int)extract_motorola_u64(data, 12, 1);
	out->MCU_FAULT_two_sig4 = (int)extract_motorola_u64(data, 13, 1);
	out->MCU_FAULT_two_sig5 = (int)extract_motorola_u64(data, 14, 1);
	out->MCU_FAULT_two_sig6 = (int)extract_motorola_u64(data, 15, 1);
	out->MCU_FAULT_two_sig7 = (int)extract_motorola_u64(data, 0, 1);
	out->MCU_FAULT_two_sig8 = (int)extract_motorola_u64(data, 1, 1);
	out->MCU_FAULT_two_sig9 = (int)extract_motorola_u64(data, 2, 1);
	out->MCU_FAULT_two_sig10 = (int)extract_motorola_u64(data, 3, 1);
	out->MCU_FAULT_two_sig11 = (int)extract_motorola_u64(data, 4, 1);
	out->MCU_FAULT_two_sig12 = (int)extract_motorola_u64(data, 5, 1);
	out->MCU_FAULT_two_sig13 = (int)extract_motorola_u64(data, 6, 1);
	out->MCU_FAULT_two_sig14 = (int)extract_motorola_u64(data, 7, 1);
	// uart_print_str("\n VCU_BFNRFault_St_B: ");
	// uart_printf("%d ",out->MCU_FAULT_two_sig0);
	// uart_print_str("\n VCU_DCDCEnableFault_St_B: ");
	// uart_printf("%d ",out->MCU_FAULT_two_sig1);
	// uart_print_str("\n VCU_ThrottleMismatch_St_B");
	// uart_printf("%d ",out->MCU_FAULT_two_sig2);
	// uart_print_str("\n VCU_LowSOC_Fault_St_B: ");
	// uart_printf("%d ",out->MCU_FAULT_two_sig3);
	// uart_print_str("\n VCU_LowSOC_Warning_St_B: ");
	// uart_printf("%d ",out->MCU_FAULT_two_sig4);
	// uart_print_str("\n VCU_AuxBatteryUV_Fault_St_B: ");
	// uart_printf("%d ",out->MCU_FAULT_two_sig5);
	// uart_print_str("\n VCU_AuxVoltageUV_Warning_St_B: ");
	// uart_printf("%d \n ",out->MCU_FAULT_two_sig6);
	// uart_print_str("\n VCU_OverSpeed_Fault_St_B: ");
	// uart_printf("%d ",out->MCU_FAULT_two_sig7);
	// uart_print_str("\n VCU_OverSpeed_Warning_St_B: ");
	// uart_printf("%d ",out->MCU_FAULT_two_sig8);
	// uart_print_str("\n VCU_Brake_STB_St_B");
	// uart_printf("%d ",out->MCU_FAULT_two_sig9);
	// uart_print_str("\n VCU_Brake_STG_St_B: ");
	// uart_printf("%d ",out->MCU_FAULT_two_sig10);
	// uart_print_str("\n VCU_Throttle2_STB_St_B: ");
	// uart_printf("%d ",out->MCU_FAULT_two_sig11);
	// uart_print_str("\n VCU_Throttle2_STG_St_B: ");
	// uart_printf("%d ",out->MCU_FAULT_two_sig12);
	// uart_print_str("\n VCU_Throttle1_STB_St_B: ");
	// uart_printf("%d \n ",out->MCU_FAULT_two_sig13);
	// uart_print_str("\n VCU_Throttle1_STG_St_B: ");
	// uart_printf("%d ",out->MCU_FAULT_two_sig14);
	// uart_print_str("\n============================================\n");
}
void decode_HearthBeat(const uint8_t *data, HearthBeat_t *out) {
if (!out) return;
out->HeartBeat_Stat0 = (double)extract_little_endian_u64(data, 0, 1);
out->HeartBeat_Stat1 = (double)extract_little_endian_u64(data, 1, 1);
out->HeartBeat_Stat2 = (double)extract_little_endian_u64(data, 2, 1);
out->HeartBeat_Stat3 = (double)extract_little_endian_u64(data, 3, 1);
out->HeartBeat_Stat4 = (double)extract_little_endian_u64(data, 4, 1);
out->HeartBeat_Stat5 = (double)extract_little_endian_u64(data, 5, 1);
out->HeartBeat_Stat6 = (double)extract_little_endian_u64(data, 6, 1);
out->HeartBeat_Stat7 = (double)extract_little_endian_u64(data, 7, 1);
out->HeartBeat_Stat8 = (double)extract_little_endian_u64(data, 8, 1);
out->HeartBeat_Stat9 = (double)extract_little_endian_u64(data, 9, 1);
out->HeartBeat_Stat10 = (double)extract_little_endian_u64(data, 10, 1);
out->HeartBeat_Stat11 = (double)extract_little_endian_u64(data, 11, 1);
}


//void decode_CANFRAME3(const uint8_t *data, CANFRAME3_t *out) {
//if (!out) return;
//out->CANFRAME3_sig0 = (double)extract_motorola_u64(data, 7, 17)*0.01-500;
//uart_send_double(out->CANFRAME3_sig0,3);
//uart_print_str("\n\r");
//out->CANFRAME3_sig1 = (double)extract_motorola_u64(data, 35, 9);
//uart_send_double(out->CANFRAME3_sig1,3);
//uart_print_str("\n\r");
//out->CANFRAME3_sig2 = (double)extract_motorola_u64(data, 41, 8);
//uart_send_double(out->CANFRAME3_sig2,3);
//uart_print_str("\n\r");
//out->CANFRAME3_sig3 = (double)extract_motorola_u64(data, 28, 9);
//uart_send_double(out->CANFRAME3_sig3,3);
//uart_print_str("\n\r");
//uart_print_str("============================================\n\r");
//
//out->CANFRAME3_sig4 = (double)extract_motorola_u64(data, 22, 10)*0.1;
//uart_send_double(out->CANFRAME3_sig4,3);
//uart_print_str("\n\r");
//
//uart_print_str("done \n\r");
//
//}


void decode_MCU_Stat_One(const uint8_t *data, MCU_Stat_One_t *out) {
	if (!out) return;
	out->MCU_Stat_One_sig0 = (int)extract_little_endian_u64(data, 8, 8)-40;
	out->MCU_Stat_One_sig1 = (int)extract_little_endian_u64(data, 0, 8)-40;
	out->MCU_Stat_One_sig2 = (double)extract_little_endian_u64(data, 16, 16)*0.1;
	out->MCU_Stat_One_sig3 = (int)extract_little_endian_u64(data, 56, 3);
	out->MCU_Stat_One_sig4 = (int)extract_little_endian_u64(data, 48, 8);
	out->MCU_Stat_One_sig5 = (int)extract_little_endian_u64(data, 40, 8);
	out->MCU_Stat_One_sig6 = (int)extract_little_endian_u64(data, 32, 8);

    sprintf(pres_str1, "%ld",out->MCU_Stat_One_sig0);
    lv_label_set_text(ui_MotorTempValue, pres_str1); 

    sprintf(pres_str1, "%ld",out->MCU_Stat_One_sig1);
    lv_label_set_text(ui_MCUTempVal, pres_str1);

	if( out->MCU_Stat_One_sig3==0){
    lv_label_set_text(ui_DriveMode, "N");
	}else if(out->MCU_Stat_One_sig3==3){
    lv_label_set_text(ui_DriveMode, "F");
	}else if(out->MCU_Stat_One_sig3==1 ||out->MCU_Stat_One_sig3==2 ){
    lv_label_set_text(ui_DriveMode, "R");
	}

    sprintf(pres_str1, "%ld",out->MCU_Stat_One_sig4);
    lv_label_set_text(ui_SpeedVal, pres_str1); 


	// uart_print_str("\n MCU_Motor_Temp: ");
	// uart_printf("%d ",out->MCU_Stat_One_sig0);
	// uart_print_str("\n MCU_PCB_Temp: ");
	// uart_printf("%d ",out->MCU_Stat_One_sig1);
	// uart_print_str("\n MCU_RMS_Current");
	// uart_send_double(out->MCU_Stat_One_sig2,3);
	// uart_print_str("\n MCU_Drive_Mode: ");
	// uart_printf("%d ",out->MCU_Stat_One_sig3);
	// uart_print_str("\n MCU_Speed_Kmph: ");
	// uart_printf("%d ",out->MCU_Stat_One_sig4);
	// uart_print_str("\n MCU_Brake_perc: ");
	// uart_printf("%d ",out->MCU_Stat_One_sig5);
	// uart_print_str("\n MCU_Throttle_perc: ");
	// uart_printf("%d \n ",out->MCU_Stat_One_sig6);
	// uart_print_str("\n============================================\n");
}








void decode_MCU_POWER_One(const uint8_t *data, MCU_POWER_One_t *out) {
//if (!out) return;

out->power_sig0 = (double)extract_motorola_u64(data, 38, 10)*0.1-37.3;
out->power_sig1 = (double)extract_motorola_u64(data, 7, 10)*0.1;
out->power_sig2 = (double)extract_motorola_u64(data, 16, 10)*0.1-65;
out->power_sig3 = (double)extract_motorola_u64(data, 44, 15)-16384;
out->power_sig4 = (double)extract_motorola_u64(data, 13, 13)*0.1-409.6;
//   tft.setCursor(20,20 );
//   tft.setTextSize(2);
//   tft.setTextColor(0xffffff);
//   tft.println("MOTOR_RPM:"); 
// Serial1.printf("%lf",out->power_sig3);

// tft.setTextColor(TFT_WHITE, TFT_RED);  // foreground, background
// tft.setCursor(150, 20);
// tft.print("           ");   // clear old value with spaces
// tft.setCursor(150, 20);
// tft.setTextSize(2);
// 	if(out->power_sig3<0){
// 		out->power_sig3=-out->power_sig3;
// 	}
// if((out->power_sig3 <=30)){
// tft.printf("0");
// }else{
// 	tft.printf("%0.2lf",out->power_sig3);
// }


}
void mcu_can_messages(){
}
