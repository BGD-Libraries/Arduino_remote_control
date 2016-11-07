#ifndef _CRC_CHECK_H_
#define _CRC_CHECK_H_
#include <stdint.h>

extern       uint8_t  CRC8_INIT;
extern const uint8_t  CRC8_TAB[256];
extern       uint16_t CRC16_INIT;
extern const uint16_t CRC16_TAB[256];

uint8_t      Get_CRC8_Check_Sum(uint8_t *message, uint32_t length, uint8_t CRC8);
bool  Verify_CRC8_Check_Sum(uint8_t *message, uint32_t length);
void      Append_CRC8_Check_Sum(uint8_t *message, uint32_t length);

uint16_t    Get_CRC16_Check_Sum(uint8_t *message, uint32_t length, uint16_t CRC16);
bool Verify_CRC16_Check_Sum(uint8_t *message, uint32_t length);
void     Append_CRC16_Check_Sum(uint8_t *message, uint32_t length);

#endif
