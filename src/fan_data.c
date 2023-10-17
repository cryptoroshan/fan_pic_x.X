#include "fan_data.h"

FanData lastFanData;

void fan_data_to_data(FanData * data, unsigned char *dst, size_t dlen, size_t *olen) {
#ifdef ASCII_PROTOCOL
    uint8_t * bigBuffer = dst;
	uint8_t p = 0;

    p += uitoac(bigBuffer + p, PROTOCOL_VERSION);
    p += uitoac(bigBuffer + p, NUM_TEMP);
    p += uitoac(bigBuffer + p, NUM_VOLTAGE);
    p += uitoac(bigBuffer + p, NUM_FAN);
    p += uitoac(bigBuffer + p, NUM_TACH);
    
	for(int i = 0; i < NUM_TEMP; i++) {
        p += ftoac(bigBuffer + p, data->temperature[i]);
	}

	for(int i = 0; i < NUM_VOLTAGE; i++) {
        p += ftoac(bigBuffer + p, data->voltage[i]);
	}

	for(int i = 0; i < NUM_FAN; i++) {
        p += ftoac(bigBuffer + p, data->fanPWM[i]);
	}

	for(int i = 0; i < NUM_TACH; i++) {
        p += ftoac(bigBuffer + p, data->tach[i]);
	}
        
    p += uitoac(bigBuffer + p, data->error);
        
    *olen = p;
   
#elif BASE64_PROTOCOL
	uint8_t * bigBuffer = genericBuffer;
	uint8_t index = 0;
	bigBuffer[index++] = PROTOCOL_VERSION;
	bigBuffer[index++] = 4*NUM_TEMP;
	for(int i = 0; i < NUM_TEMP; i++) {
		pack32(bigBuffer, &index, data->temperature[i]);
	}
	bigBuffer[index++] = 4*NUM_TACH;
	for(int i = 0; i < NUM_TACH; i++) {
		pack32(bigBuffer, &index, data->tach[i]);
	}
	bigBuffer[index++] = 4*NUM_VOLTAGE;
	for(int i = 0; i < NUM_VOLTAGE; i++) {
		pack32(bigBuffer, &index, data->voltage[i]);
	}
	bigBuffer[index++] = 4*NUM_FAN;
	for(int i = 0; i < NUM_FAN; i++) {
		pack32(bigBuffer, &index, data->fanPWM[i]);
	}

	bigBuffer[index++] = 2;
	bigBuffer[index++] = (data->gpio_states & 0xFF);
	bigBuffer[index++] = (data->gpio_states >> 8) & 0xFF;

	bigBuffer[index++] = 1;
	bigBuffer[index++] = data->error;
    
    base64_encode(bigBuffer, index, dst, olen);
#endif
}

bool get_error_flag(FanData * data, uint8_t flag) {
    return (data->error & flag) == flag;
}
void set_error_flag(FanData * data, uint8_t flag, bool value) {
    if(value) {
         data->error |= (flag);
    } else {
         data->error &= ~(flag);
    }
}