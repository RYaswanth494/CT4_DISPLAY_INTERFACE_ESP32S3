#include"MCU_ELECTROCATALYST_MESSAGES.hpp"
#include"can.hpp"
#pragma once

// Single container with all message structs as members
typedef struct {
    MCU_Stat_Two_t      MCU_Stat_Two;
    MCU_Fault_Code_t    MCU_Fault_Code;
    HearthBeat_t        HearthBeat;
    CANFRAME3_t         CANFRAME3;
    MCU_Stat_One_t      MCU_Stat_One;
    MCU_FAULT_two_t     MCU_FAULT_two;
    MCU_FAULT_One_t     MCU_FAULT_One;
    MCU_POWER_One_t     MCU_POWER_One;
    // Add more message members here if your DBC has more messages
} DBC_AllMessages_t;
void matel_mcu_process_can_frame(stm_can_frame_t *frame);