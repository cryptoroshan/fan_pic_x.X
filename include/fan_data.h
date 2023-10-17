/* 
 * File:   fan_data.h
 * Author: jstahlba
 *
 * Created on May 3, 2022, 10:12 PM
 */

#ifndef FAN_DATA_H
#define	FAN_DATA_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "board.h"
#include "system.h"
#include "utils.h"

#define ERROR_VOLTAGE 	(1 << 0)
#define ERROR_FAN 		(1 << 1)
#define ERROR_TEMP 		(1 << 2)
#define ERROR_SOUND		(1 << 3) //not used
    
typedef struct {
 float tach[NUM_TACH];
 float temperature[NUM_TEMP];
 float voltage[NUM_VOLTAGE];
 float fanPWM[NUM_FAN];
 uint16_t gpio_states;
 uint8_t error;
} FanData;

#define FAN_DATA_BUFF_SIZE (1 + 4*NUM_TEMP + 4*NUM_TACH + 4*NUM_VOLTAGE + 4*NUM_FAN + 1 + 5)

extern FanData lastFanData;
void fan_data_to_data(FanData * data, unsigned char *dst, size_t dlen, size_t *olen);
bool get_error_flag(FanData * data, uint8_t flag);
void set_error_flag(FanData * data, uint8_t flag, bool valut); 

#ifdef	__cplusplus
}
#endif

#endif	/* FAN_DATA_H */

