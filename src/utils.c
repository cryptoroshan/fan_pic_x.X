#include "utils.h"
#ifdef ASCII_PROTOCOL

#include <stdio.h>
#include <math.h>
#define FLOAT_PRECISION 1


uint16_t powT[5] = {10000 , 1000, 100, 10, 1};

uint8_t uitoa(unsigned char * buffer, uint16_t value) {
    uint8_t i;
    uint8_t p = 0;
    uint16_t digit;
    bool seenOne = false;

    if (value) {
        for (i = 0; i < 5u; i++) {
            digit = value / powT[i];
            if (digit > 0 || seenOne) {
                *(buffer + p) = '0' + digit;
                p++;
                value -= digit * powT[i];
                seenOne = true;
            }
        }
    } else {
        *(buffer + p) = '0';
        p++;
    }

    return p;
}

uint8_t ftoa(unsigned char * output, float v) {
    uint8_t p = 0;
    float value = v;
    if (value < 0) {
        *(output + p) = '-';
        p += 1;
    }
    value = fabs(value);
    p += uitoa(output + p, (uint16_t) value);
    float rem = value - (uint16_t) value;
    if (rem != 0) {
        *(output + p) = '.';
        p++;
        p += uitoa(output + p, (uint16_t) (rem*10));
    }
    return p;
}

uint8_t uitoac(unsigned char * buffer, uint16_t value) {
    uint8_t p = 0;
    p = uitoa(buffer, value);
    *(buffer + p) = ',';
    return p + 1;
}

uint8_t ftoac(unsigned char * buffer, float value) {
    uint8_t p = 0;
    p = ftoa(buffer, value);
    *(buffer + p) = ',';
    return p + 1;
}

#endif
#ifdef BASE64_PROTOCOL
void pack32(uint8_t * data, uint8_t * index, float value) {
	union {
		float float_variable;
		uint8_t temp_array[sizeof(float)];
	} u;
	// Overite bytes of union with float variable
	u.float_variable = value;
    
	// Assign bytes to input array
	memcpy(&data[*index], u.temp_array, sizeof(float));
	*index = *index + 4;
}


static const unsigned char base64_table[65] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
unsigned char * base64_encode(const unsigned char *src, size_t len, unsigned char *out, size_t *out_len)
{
	unsigned char *pos;
	const unsigned char *end, *in;
	size_t olen;

	olen = len * 4 / 3 + 4; /* 3-byte blocks to 4-byte */

	olen++; /* nul termination */

	end = src + len;
	in = src;
	pos = out;
	while (end - in >= 3) {
		*pos++ = base64_table[in[0] >> 2];
		*pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
		*pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
		*pos++ = base64_table[in[2] & 0x3f];
		in += 3;
	}

	if (end - in) {
		*pos++ = base64_table[in[0] >> 2];
		if (end - in == 1) {
			*pos++ = base64_table[(in[0] & 0x03) << 4];
			*pos++ = '=';
		} else {
			*pos++ = base64_table[((in[0] & 0x03) << 4) |
					      (in[1] >> 4)];
			*pos++ = base64_table[(in[1] & 0x0f) << 2];
		}
		*pos++ = '=';
	}

	*pos = '\0';
	if (out_len)
		*out_len = pos - out;
	return out;
}

unsigned char * base64_decode(const unsigned char *src, size_t len, unsigned char *dst,  size_t dst_len, size_t *out_len)
{
	unsigned char dtable[256], *out, *pos, block[4], tmp;
	size_t i, count, olen;
	int pad = 0;

	memset(dtable, 0x80, 256);
	for (i = 0; i < sizeof(base64_table) - 1; i++)
		dtable[base64_table[i]] = (unsigned char) i;
	dtable['='] = 0;

	count = 0;
	for (i = 0; i < len; i++) {
		if (dtable[src[i]] != 0x80)
			count++;
	}

	if (count == 0 || count % 4)
		return NULL;

	olen = count / 4 * 3;
    if(olen > dst_len)
        return NULL;
	pos = out = dst;
	if (out == NULL)
		return NULL;

	count = 0;
	for (i = 0; i < len; i++) {
		tmp = dtable[src[i]];
		if (tmp == 0x80)
			continue;

		if (src[i] == '=')
			pad++;
		block[count] = tmp;
		count++;
		if (count == 4) {
			*pos++ = (block[0] << 2) | (block[1] >> 4);
			*pos++ = (block[1] << 4) | (block[2] >> 2);
			*pos++ = (block[2] << 6) | block[3];
			count = 0;
			if (pad) {
				if (pad == 1)
					pos--;
				else if (pad == 2)
					pos -= 2;
				else {
					/* Invalid padding */
					return NULL;
				}
				break;
			}
		}
	}

	*out_len = pos - out;
	return out;
}
#endif