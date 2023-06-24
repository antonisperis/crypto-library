#ifndef CS457_CYPTO_H
#define CS457_CYPTO_H
#include <stdint.h>

uint8_t *otp_encrypt(uint8_t *, uint8_t *,int);
uint8_t *otp_decrypt(uint8_t *, uint8_t *,int);

uint8_t * ceasar_encrypt(uint8_t *, unsigned short, int);
uint8_t * ceasar_decrypt(uint8_t *, unsigned short, int);

unsigned char* playfair_encrypt(unsigned char *, unsigned char** );
unsigned char* playfair_decrypt(unsigned char *, unsigned char** );


unsigned char** playfair_keymatrix(unsigned char *);

uint8_t * affine_encrypt(uint8_t *,int);
uint8_t * affine_decrypt(uint8_t *,int);

uint32_t feistel_round( uint32_t,uint8_t * );
uint8_t* feistel_encryption(uint8_t*,uint8_t**,int);
uint8_t *feistel_decryption(uint8_t *,uint8_t**,int);
#endif