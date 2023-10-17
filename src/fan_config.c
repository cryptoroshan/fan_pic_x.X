#include "fan_config.h"
#include "eeprom.h"

#include	<stdlib.h>

FanConfig lastFanConfig;

void fan_config_to_data(FanConfig * config, unsigned char *dst, size_t dlen, size_t *olen) {
#ifdef ASCII_PROTOCOL
    uint8_t * bigBuffer = dst;
    uint8_t p = 0;

    p += uitoac(bigBuffer + p, FAN_CONFIG_VERSION);
    p += uitoac(bigBuffer + p, NUM_TEMP);
    p += uitoac(bigBuffer + p, NUM_VOLTAGE);
    p += uitoac(bigBuffer + p, NUM_FAN);
    p += uitoac(bigBuffer + p, NUM_TACH);

    for (int i = 0; i < NUM_TEMP; i++) {
        p += uitoac(bigBuffer + p, config->tempType[i]);
        p += uitoac(bigBuffer + p, config->tempLowerThreshold[i]);
        p += uitoac(bigBuffer + p, config->tempUpperThreshold[i]);
    }

    for (int i = 0; i < NUM_FAN; i++) {
        p += uitoac(bigBuffer + p, config->fanConfig[i].minPWM);
        p += uitoac(bigBuffer + p, config->fanConfig[i].maxPWM);
        p += uitoac(bigBuffer + p, config->fanConfig[i].tempSensor);
        p += uitoac(bigBuffer + p, config->fanConfig[i].tempAtMinSpeed);
        p += uitoac(bigBuffer + p, config->fanConfig[i].tempAtMaxSpeed);
        p += uitoac(bigBuffer + p, config->fanConfig[i].canStop);
        p += uitoac(bigBuffer + p, config->fanConfig[i].fanType);
        p += uitoac(bigBuffer + p, config->fanConfig[i].calcType);
        p += uitoac(bigBuffer + p, config->fanConfig[i].delta);
        p += uitoac(bigBuffer + p, config->fanConfig[i].deltaFudge);
        p += ftoac(bigBuffer + p, config->fanConfig[i].deltaRamp);
    }

#ifdef BOARD_3A006
    float * VOLTAGE_LEVELS = PRIM_VOLTAGE_LEVELS;
    if (config->voltageLowerThreshold[KEYINDEX] > KEYTHRESHOLD) {
        VOLTAGE_LEVELS = ALT_VOLTAGE_LEVELS;
    }
#endif
    for (int i = 0; i < NUM_VOLTAGE; i++) {
        p += ftoac(bigBuffer + p, config->voltageLowerThreshold[i]);
        p += ftoac(bigBuffer + p, config->voltageUpperThreshold[i]);
        p += uitoac(bigBuffer + p, config->voltageThresholdType[i]);
        p += ftoac(bigBuffer + p, VOLTAGE_LEVELS[i]);
    }

    for (int i = 0; i < NUM_TACH; i++) {
        p += uitoac(bigBuffer + p, config->tachLowerThreshold[i]);
    }

    *olen = p;

#elif BASE64_PROTOCOL
    uint8_t * bigBuffer = genericBuffer;
    uint8_t index = 0;
    bigBuffer[index++] = FAN_CONFIG_VERSION;
    bigBuffer[index++] = NUM_TEMP;
    for (int i = 0; i < NUM_TEMP; i++) {
        bigBuffer[index++] = config->tempType[i];
        bigBuffer[index++] = config->tempLowerThreshold[i];
        bigBuffer[index++] = config->tempUpperThreshold[i];
    }
    bigBuffer[index++] = NUM_FAN;
    for (int i = 0; i < NUM_FAN; i++) {
        bigBuffer[index++] = 14;
        bigBuffer[index++] = config->fanConfig[i].minPWM;
        bigBuffer[index++] = config->fanConfig[i].maxPWM;
        bigBuffer[index++] = config->fanConfig[i].tempSensor;
        bigBuffer[index++] = config->fanConfig[i].tempAtMinSpeed;
        bigBuffer[index++] = config->fanConfig[i].tempAtMaxSpeed;
        bigBuffer[index++] = config->fanConfig[i].canStop;
        bigBuffer[index++] = config->fanConfig[i].fanType;
        bigBuffer[index++] = config->fanConfig[i].calcType;
        bigBuffer[index++] = config->fanConfig[i].delta;
        bigBuffer[index++] = config->fanConfig[i].deltaFudge;
        pack32(bigBuffer, &index, config->fanConfig[i].deltaRamp);
    }
    bigBuffer[index++] = NUM_VOLTAGE;

    for (int i = 0; i < NUM_VOLTAGE; i++) {
        pack32(bigBuffer, &index, config->voltageLowerThreshold[i]);
        pack32(bigBuffer, &index, config->voltageUpperThreshold[i]);
        bigBuffer[index++] = config->voltageThresholdType[i];
        pack32(bigBuffer, &index, VOLTAGE_LEVELS[i]);
    }
    bigBuffer[index++] = NUM_TACH;
    for (int i = 0; i < NUM_TACH; i++) {
        bigBuffer[index++] = (config->tachLowerThreshold[i] & 0xFF);
        bigBuffer[index++] = (config->tachLowerThreshold[i] >> 8) & 0xFF;
    }
    bigBuffer[index++] = (config->psuDelay & 0xFF);
    bigBuffer[index++] = (config->psuDelay >> 8) & 0xFF;

    base64_encode(bigBuffer, index, dst, olen);
#endif
}

uint16_t parseInt(unsigned char * input, uint8_t * outp) {
    uint8_t p = *outp;
    if (input[p] == ',')
        p++;

    uint16_t output = atoi(input + p);
    while (input[p] != ',' && input[p] != '\0' && input[p] != '\r' && input[p] != '\n') {
        p++;
    }
    *outp = p;
    return output;
}

float parseFloat(unsigned char * input, uint16_t * outp) {
    uint8_t p = *outp;
    if (input[p] == ',')
        p++;

    float output = atof(input + p);
    while (input[p] != ',' && input[p] != '\0' && input[p] != '\r' && input[p] != '\n') {
        p++;
    }
    *outp = p;
    return output;
}

int fan_config_from_data(unsigned char *src, size_t slen, FanConfig * newConfig) {
#ifdef ASCII_PROTOCOL
    newConfig->version = FAN_CONFIG_VERSION;
    int index = 0;
    uint8_t * bigBuffer = src;
    size_t olen;

    uint8_t protVersion;
    protVersion = parseInt(bigBuffer, &index);
    if (protVersion != 0x10) {
        return -1;
    }

    for (int i = 0; i < NUM_TEMP; i++) {
        newConfig->tempType[i] = parseInt(bigBuffer, &index);
        newConfig->tempLowerThreshold[i] = parseInt(bigBuffer, &index);
        newConfig->tempUpperThreshold[i] = parseInt(bigBuffer, &index);
    }

    for (int i = 0; i < NUM_FAN; i++) {
        newConfig->fanConfig[i].minPWM = parseInt(bigBuffer, &index);
        newConfig->fanConfig[i].maxPWM = parseInt(bigBuffer, &index);
        newConfig->fanConfig[i].tempSensor = parseInt(bigBuffer, &index);
        newConfig->fanConfig[i].tempAtMinSpeed = parseInt(bigBuffer, &index);
        newConfig->fanConfig[i].tempAtMaxSpeed = parseInt(bigBuffer, &index);
        newConfig->fanConfig[i].canStop = parseInt(bigBuffer, &index);
        newConfig->fanConfig[i].fanType = parseInt(bigBuffer, &index);
        newConfig->fanConfig[i].calcType = parseInt(bigBuffer, &index);
        newConfig->fanConfig[i].delta = parseInt(bigBuffer, &index);
        newConfig->fanConfig[i].deltaFudge = parseInt(bigBuffer, &index);
        newConfig->fanConfig[i].deltaRamp = parseFloat(bigBuffer, &index);
    }

    for (int i = 0; i < NUM_VOLTAGE; i++) {
        newConfig->voltageLowerThreshold[i] = parseFloat(bigBuffer, &index);
        newConfig->voltageUpperThreshold[i] = parseFloat(bigBuffer, &index);
        newConfig->voltageThresholdType[i] = parseInt(bigBuffer, &index);
        float maxVoltage = parseFloat(bigBuffer, &index);
    }

    for (int i = 0; i < NUM_TACH; i++) {
        newConfig->tachLowerThreshold[i] = parseInt(bigBuffer, &index);
    }

    if (index >= slen)
        return -2;

    return 0;
#elif BASE64_PROTOCOL
    newConfig->version = FAN_CONFIG_VERSION;
    int index = 0;
    uint8_t * bigBuffer = genericBuffer;
    size_t olen;
    unsigned char * result = base64_decode(src, slen, bigBuffer, FAN_CONFIG_BUFF_SIZE, &olen);
    if (result == NULL)
        return -1;

    uint8_t protVersion = bigBuffer[index++];
    if (protVersion != 0x10 && protVersion != 0x11) {
        return -1;
    }

    uint8_t numTemp = bigBuffer[index++];
    for (int i = 0; i < NUM_TEMP; i++) {
        newConfig->tempType[i] = bigBuffer[index++];
        newConfig->tempLowerThreshold[i] = bigBuffer[index++];
        newConfig->tempUpperThreshold[i] = bigBuffer[index++];
    }

    uint8_t numFan = bigBuffer[index++];
    for (int i = 0; i < NUM_FAN; i++) {
        uint8_t len = bigBuffer[index++];
        newConfig->fanConfig[i].minPWM = bigBuffer[index++];
        newConfig->fanConfig[i].maxPWM = bigBuffer[index++];
        newConfig->fanConfig[i].tempSensor = bigBuffer[index++];
        newConfig->fanConfig[i].tempAtMinSpeed = bigBuffer[index++];
        newConfig->fanConfig[i].tempAtMaxSpeed = bigBuffer[index++];
        newConfig->fanConfig[i].canStop = bigBuffer[index++];
        newConfig->fanConfig[i].fanType = bigBuffer[index++];
        newConfig->fanConfig[i].calcType = bigBuffer[index++];
        newConfig->fanConfig[i].delta = bigBuffer[index++];
        newConfig->fanConfig[i].deltaFudge = bigBuffer[index++];
        memcpy(&newConfig->fanConfig[i].deltaRamp, &bigBuffer[index], 4);
        index = index + 4;
    }

    uint8_t numVolt = bigBuffer[index++];
    for (int i = 0; i < NUM_VOLTAGE; i++) {
        memcpy(&newConfig->voltageLowerThreshold[i], &bigBuffer[index], 4);
        index = index + 4;
        memcpy(&newConfig->voltageUpperThreshold[i], &bigBuffer[index], 4);
        index = index + 4;
        newConfig->voltageThresholdType[i] = bigBuffer[index++];
        index = index + 4;
    }

    uint8_t numTach = bigBuffer[index++];
    for (int i = 0; i < NUM_TACH; i++) {
        newConfig->tachLowerThreshold[i] = (uint16_t) (bigBuffer[index] | (bigBuffer[index + 1] << 8));
        index = index + 2;
    }
    newConfig->psuDelay = (uint16_t) (bigBuffer[index] | (bigBuffer[index + 1] << 8));
    index = index + 2;

    return 0;
#endif
}

void loadConfig() {
    FanConfig newConfig;
    uint8_t *pData = (uint8_t*) & newConfig;
    uint8_t len = sizeof (FanConfig);
    uint8_t empty = 0;
    uint8_t i;
    for (i = 0; i < len; i++) {
        pData[i] = eeprom18_read(i);
    }

    if (newConfig.version != FAN_CONFIG_VERSION) {
        loadDefault();
    } else {
        setConfig(&newConfig, false);
    }
}

void loadDefault() {
    FanConfig config;

    config.version = FAN_CONFIG_VERSION;
    uint8_t i;
    for (i = 0; i < NUM_TEMP; i++) {
        config.tempType[i] = 1;
        config.tempLowerThreshold[i] = 10;
        config.tempUpperThreshold[i] = 80;
    }

    for (i = 0; i < NUM_TACH; i++) {
        config.tachLowerThreshold[i] = 500;
    }

    for (i = 0; i < NUM_FAN; i++) {
        config.fanConfig[i].minPWM = 30;
        config.fanConfig[i].maxPWM = 100;
        config.fanConfig[i].tempSensor = 1;
        config.fanConfig[i].tempAtMinSpeed = 25;
        config.fanConfig[i].tempAtMaxSpeed = 50;
        config.fanConfig[i].canStop = 0;
        config.fanConfig[i].fanType = 5;
        config.fanConfig[i].calcType = 1;
        config.fanConfig[i].delta = 25;
        config.fanConfig[i].deltaFudge = 1;
        config.fanConfig[i].deltaRamp = 0.25f;
    }

#ifdef BOARD_3A006
    float * VOLTAGE_LEVELS = PRIM_VOLTAGE_LEVELS;
#endif
    for (i = 0; i < NUM_VOLTAGE; i++) {
        if (VOLTAGE_LEVELS[i] > 0) {
            config.voltageLowerThreshold[i] = 0.8f * VOLTAGE_LEVELS[i];
            config.voltageUpperThreshold[i] = 1.2f * VOLTAGE_LEVELS[i];
        } else {
            config.voltageLowerThreshold[i] = 1.2f * VOLTAGE_LEVELS[i];
            config.voltageUpperThreshold[i] = 0.8f * VOLTAGE_LEVELS[i];
        }
        config.voltageThresholdType[i] = 0;
    }

    config.psuDelay = 500;

    setConfig(&config, true);
}

void setConfig(FanConfig * config, bool cmdSave) {
    memcpy(&lastFanConfig, config, sizeof (FanConfig));
    if (cmdSave)
        saveConfig(config);
}

void saveConfig(FanConfig * config) {
    uint8_t *pData = (uint8_t*) config;
    uint8_t i;
    for (i = 0; i < sizeof (FanConfig); i++) { // for each item of data to be read
        eeprom18_write(i, pData[i]); // write the data to EEPROM
    }
}
