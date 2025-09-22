#pragma once
typedef struct {
    uint32_t id;        /**< CAN identifier (11-bit for standard, 29-bit for extended) */
    uint8_t  ide;       /**< 0 for standard identifier, 1 for extended identifier */
    uint8_t  rtr;       /**< 0 for data frame, 1 for remote frame */
    uint8_t  dlc;       /**< Data length code (0-8) */
    uint8_t  data[8];   /**< Data bytes */
} stm_can_frame_t;