#include "sensors.h"

#include <math.h>

void setPWM(int index, float newPWM);

#define MAX_PWM 100
#define DELTA_RANGE 1

#define LOWER_BOUND 4
#define UPPER_BOUND (1023-LOWER_BOUND)
#define ADC_ERROR 0x0

#define THERMISTORNOMINAL 2e3
#define TEMPERATURENOMINAL 25.0
#define BCOEFFICIENT 3500.0
#define SERIESRESISTOR 1.0

uint16_t readAnalog(uint8_t port) {
    ADCON0 = 0b00000000;
    ADCON0 = port;

    while ((ADCON0 & 0b00000010) != 0); // wait for the conversion
    return (((ADRESH & 0x03) << 8) | ADRESL);
}

float convertVoltage(uint16_t raw, int index, FanConfig * config) {
    if (raw < LOWER_BOUND || raw > UPPER_BOUND)
        return ADC_ERROR;

#ifdef BOARD_3A006
    float * VOLTAGE_LEVELS = PRIM_VOLTAGE_LEVELS;
    float * VOLTAGE_DIV = PRIM_VOLTAGE_DIV;
    if (config->voltageLowerThreshold[KEYINDEX] > KEYTHRESHOLD) {
        VOLTAGE_LEVELS = ALT_VOLTAGE_LEVELS;
        VOLTAGE_DIV = ALT_VOLTAGE_DIV;
    }
#endif

    return (3.3f * VOLTAGE_LEVELS[index] * raw) / (1024 * VOLTAGE_DIV[index]);
}

float convertTemperature(uint16_t raw) {
    if (raw < LOWER_BOUND || raw > UPPER_BOUND)
        return ADC_ERROR;
    return -1 * (((raw) * 3) - 2850) / 36.0f;
}

void processAnalog(FanData * data, FanConfig * config) {
    ADCON1 = 0b00000001;
    for (uint8_t i = 0; i < NUM_VOLTAGE; i++) {
        data->voltage[i] = convertVoltage(readAnalog(VOLTAGE_PORT[i]), i, config);
    }
    for (uint8_t i = 0; i < NUM_TEMP; i++) {
        if (config->tempType[i] > 0)
            data->temperature[i] = convertTemperature(readAnalog(TEMP_PORT[i]));
    }
    ADCON1 = 0b00001111;
}

int8_t lastSign[NUM_FAN]; //tristate -1 0 1

void computePWM(FanData * data, FanConfig * config) {
    for (int i = 0; i < NUM_FAN; i++) {
        int sensorIndex = config->fanConfig[i].tempSensor;
        float currentTemp = data->temperature[sensorIndex];
        float newPWM = 0;


        //Need to rework error state to be more correct
        int inIndex = config->fanConfig[i].tempSensor;
        int outIndex = config->fanConfig[i].tempSensor == 0 ? 1 : 0;

        uint8_t tachErrorCount = 0;
        for (int j = 0; j < NUM_TACH; j++) {
            if (data->tach[j] < config->tachLowerThreshold[i]) {
                tachErrorCount++;
            }
        }

        //tachErrorCount=0;
        if (tachErrorCount >= 2 && ((tachErrorCount < NUM_TACH && config->fanConfig[i].canStop) || !config->fanConfig[i].canStop)) {
            newPWM = MAX_PWM;
        } else if (isTempErr(data, config, inIndex) || isTempErr(data, config, outIndex)) {
            newPWM = MAX_PWM;
        } else {
            uint8_t calcType = config->fanConfig[i].calcType;
            if (calcType == 1 && (config->tempType[inIndex] == 0 || config->tempType[outIndex] == 0))
                calcType = 0;
            if (calcType == 0) {
                if (currentTemp < config->fanConfig[i].tempAtMinSpeed) {
                    if (config->fanConfig[i].canStop) {
                        newPWM = 0;
                    } else {
                        newPWM = config->fanConfig[i].minPWM;
                    }
                } else {
                    float m = ((float) config->fanConfig[i].maxPWM - config->fanConfig[i].minPWM) / (config->fanConfig[i].tempAtMaxSpeed - config->fanConfig[i].tempAtMinSpeed);
                    newPWM = config->fanConfig[i].minPWM + m * (currentTemp - config->fanConfig[i].tempAtMinSpeed);
                }
            } else if (calcType == 1) { //Always 1
                //other pid modes should be 
                int8_t newSign;
                float currentDelta = (data->temperature[outIndex] - data->temperature[inIndex]);
                uint8_t delta = config->fanConfig[i].delta;
                uint8_t fudge = config->fanConfig[i].deltaFudge;
                float deltaRamp = config->fanConfig[i].deltaRamp;

                if (lastSign[i] > 0) { //too hot
                    if (currentDelta < (delta + DELTA_RANGE))
                        newSign = 0;
                    else
                        newSign = 1;
                } else if (lastSign[i] < 0) { // cold
                    if (currentDelta > (delta - DELTA_RANGE))
                        newSign = 0;
                    else
                        newSign = -1;
                } else if (lastSign[i] == 0) {
                    if (currentDelta > (delta + DELTA_RANGE + fudge)) {
                        newSign = 1;
                    } else if (currentDelta < (delta - DELTA_RANGE - fudge)) {
                        newSign = -1;
                    } else {
                        newSign = 0;
                    }
                }

                lastSign[i] = newSign;
                newPWM = data->fanPWM[i] + newSign * deltaRamp * fabs(currentDelta - delta);
                if (newPWM > config->fanConfig[i].maxPWM) {
                    newPWM = config->fanConfig[i].maxPWM;
                }
            }
        }

        if (newPWM > MAX_PWM) {
            newPWM = MAX_PWM;
        }
        if (!config->fanConfig[i].canStop && newPWM < config->fanConfig[i].minPWM) {
            newPWM = config->fanConfig[i].minPWM;
        } else if (newPWM < 0) {
            newPWM = 0;
        }

        data->fanPWM[i] = newPWM;
        setPWM(i, data->fanPWM[i]);
    }
}

static bool ResetButtonPressed = false;

void checkError(FanData * data, FanConfig * fanConfig) {
    bool pwr_err = false;
    bool fan_err = false;
    bool temp_err = false;

    for (int i = 0; i < NUM_VOLTAGE; i++) {
        if (isVoltErr(data, fanConfig, i)) {
            pwr_err = true;
        }
    }

    if (PSU_FAULT == 0) {
        pwr_err = true;
    }

    for (int i = 0; i < NUM_TACH; i++) {
        if (data->tach[i] < fanConfig->tachLowerThreshold[i]) {
            fan_err = true;
        }
    }

    for (int i = 0; i < NUM_TEMP; i++) {
        if (isTempErr(data, fanConfig, i)) {
            temp_err = true;
        }
    }
    if (get_error_flag(&lastFanData, ERROR_VOLTAGE) != pwr_err ||
            get_error_flag(&lastFanData, ERROR_FAN) != fan_err ||
            get_error_flag(&lastFanData, ERROR_TEMP) != temp_err) {
        set_error_flag(&lastFanData, ERROR_SOUND, false); //reset alarm state for revaluation
        ResetButtonPressed = false;
    }

    POW_ERR = pwr_err;
    FAN_ERR = fan_err;
    TEMP_ERR = temp_err;

    set_error_flag(&lastFanData, ERROR_VOLTAGE, pwr_err);
    set_error_flag(&lastFanData, ERROR_FAN, fan_err);
    set_error_flag(&lastFanData, ERROR_TEMP, temp_err);

    computerAlarm();
}


#define NUM_HISTORY 2
float histPWM[2][NUM_HISTORY];
uint8_t histIndex;
#define MAX_PWM_COUNTER 120

void setPWM(int index, float newPWM) {
    //if (histPWM[index][histIndex] != newPWM) {
    histPWM[index][histIndex] = newPWM;
    histIndex = (histIndex + 1) % NUM_HISTORY;
    if (index == 0) {
        uint16_t dutyCycle = (uint16_t) ((newPWM / 100.0f) * MAX_PWM_COUNTER);
        CCPR1L = dutyCycle;
        CCP1CONbits.DC1B = dutyCycle >> 8;
    } else {
        uint16_t dutyCycle = (uint16_t) ((newPWM / 100.0f) * MAX_PWM_COUNTER);
        CCPR2L = dutyCycle;
        CCP2CONbits.DC2B = dutyCycle >> 8;
    }
    //}

}

bool isVoltErr(FanData * data, FanConfig * fanConfig, int i) {
    if (((fanConfig->voltageLowerThreshold[i] != 0 || fanConfig->voltageUpperThreshold[i] != 0) &&
            (data->voltage[i] < fanConfig->voltageLowerThreshold[i] ||
            data->voltage[i] > fanConfig->voltageUpperThreshold[i])) ||
            data->voltage[i] == ADC_ERROR) {
        return true;
    } else
        return false;
}

bool isTempErr(FanData * data, FanConfig * fanConfig, int i) {
    if (fanConfig->tempType[i] > 0 && (data->temperature[i] < fanConfig->tempLowerThreshold[i] ||
            data->temperature[i] > fanConfig->tempUpperThreshold[i] || data->temperature[i] == ADC_ERROR)) {
        return true;
    } else
        return false;
}


#ifdef HAS_BEEPER_BUTTON

void Beep() {
    uint16_t bc; // beeper cycle counter

    for (bc = 0; bc < 1500; bc++) {
        BEEPER = 1;
        __delay_us(300);
        BEEPER = 0; // turn off power to beeper
        __delay_us(300);
    }
}
#else

void Beep() {

}
#endif

void computerAlarm() {
    bool SoundAlarm = get_error_flag(&lastFanData, ERROR_SOUND);
    bool hasRegularError = get_error_flag(&lastFanData, ERROR_VOLTAGE) ||
            get_error_flag(&lastFanData, ERROR_FAN) ||
            get_error_flag(&lastFanData, ERROR_TEMP);
    if (hasRegularError) {
        SoundAlarm = true;
    } else {
        SoundAlarm = false;
    }

    if (ResetButtonPressed) {
        SoundAlarm = false;
    }

#ifdef HAS_BEEPER_BUTTON
    if ((ALARM_RESET_BUTTON == 0) && (SoundAlarm == true)) {
        ResetButtonPressed = true; // latch it on								
        Beep(); // ack button press
        SoundAlarm = false; // clear alarm flag
    }

    if (SoundAlarm)
        Beep();
#endif

    set_error_flag(&lastFanData, ERROR_SOUND, SoundAlarm);
}
