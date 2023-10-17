/* 
 * File:   eeprom.h
 * Author: jstahlba
 *
 * Created on May 3, 2022, 9:57 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <xc.h>

unsigned char eeprom18_read(int address);
void eeprom18_write(int address, char data);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

