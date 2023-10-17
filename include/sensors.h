/* 
 * File:   sensors.h
 * Author: jstahlba
 *
 * Created on May 4, 2022, 11:38 PM
 */

#ifndef SENSORS_H
#define	SENSORS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "board.h"
#include "fan_config.h"
#include "fan_data.h"
    
void processAnalog(FanData * data, FanConfig * config);
void computePWM(FanData * data, FanConfig * config);
void computerAlarm();
void checkError(FanData * data, FanConfig * fanConfig);
 
bool isVoltErr(FanData * data, FanConfig * fanConfig, int i);
bool isTempErr(FanData * data, FanConfig * fanConfig, int i);
#ifdef	__cplusplus
}

#endif

#endif	/* SENSORS_H */

