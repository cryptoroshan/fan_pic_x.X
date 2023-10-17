/* 
 * File:   fan_config.h
 * Author: jstahlba
 *
 * Created on May 3, 2022, 10:11 PM
 */

#ifndef FAN_CONFIG_H
#define	FAN_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "board.h"
#include "system.h"
#include "utils.h"
    
#define FAN_CONFIG_VERSION 16

extern const float VOLTAGE_LEVELS[NUM_VOLTAGE];
extern const float VOLTAGE_DIV[NUM_VOLTAGE];

typedef struct FanTachConfig {
	uint8_t minPWM; // 0->100
	uint8_t maxPWM;
	uint8_t tempSensor;
	uint8_t tempAtMinSpeed;
	uint8_t tempAtMaxSpeed;
	uint8_t canStop;
	uint8_t fanType; //2/3/4 wire, always 4 wire
	uint8_t calcType;
	uint8_t delta;
	uint8_t deltaFudge;
	float deltaRamp;
} FanTachConfig;

typedef struct FanConfig {
	uint8_t version;
	uint8_t tempType[NUM_TEMP];
	uint8_t tempLowerThreshold[NUM_TEMP];
	uint8_t tempUpperThreshold[NUM_TEMP];
	uint16_t tachLowerThreshold[NUM_TACH];
	FanTachConfig fanConfig[NUM_FAN];
	float voltageLowerThreshold[NUM_VOLTAGE];
	float voltageUpperThreshold[NUM_VOLTAGE];
	uint8_t voltageThresholdType[NUM_VOLTAGE];
	uint16_t psuDelay;

} FanConfig;

#define FAN_CONFIG_BUFF_SIZE (1+1+NUM_TEMP*3 + 1+NUM_FAN * (1+14) + 1+NUM_VOLTAGE*13 + 1+NUM_TACH*2 + 2 + 1 )

extern FanConfig lastFanConfig;
void loadConfig();
void loadDefault();
void setConfig(FanConfig * config, bool saveConfig);
void saveConfig(FanConfig * config);
void fan_config_to_data(FanConfig * config, unsigned char *dst, size_t dlen, size_t *olen);
int fan_config_from_data(unsigned char *src, size_t slen, FanConfig * newConfig);

#ifdef	__cplusplus
}
#endif

#endif	/* FAN_CONFIG_H */

