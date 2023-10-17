/* 
 * File:   utils.h
 * Author: jstahlba
 *
 * Created on May 6, 2022, 9:29 PM
 */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "board.h"
#include "system.h"

#ifdef ASCII_PROTOCOL    
uint8_t uitoac(unsigned char * Buffer, uint16_t value);  
uint8_t ftoac(unsigned char * output, float value);
#endif

#ifdef BASE64_PROTOCOL
void pack32(uint8_t * data, uint8_t * index, float value);
unsigned char * base64_encode(const unsigned char *src, size_t len,  unsigned char *out, size_t *out_len);
unsigned char * base64_decode(const unsigned char *src, size_t len, unsigned char *dst,  size_t dst_len, size_t *out_len);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */

