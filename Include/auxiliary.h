#ifndef AUXILIARY_H
#define AUXILIARY_H
#include <stdint.h>


uint8_t* convert_string_to_uint8(char*);
char* convert_uint8_to_string(uint8_t* ,int );
void print_encrypt(uint8_t* ,char*,uint8_t *);
uint8_t* generate_random_key(int);

uint8_t get_ceasar_encryption_char(uint8_t,unsigned short);
uint8_t get_ceasar_decryption_char(uint8_t,unsigned short);

unsigned char* remove_duplicates(unsigned char*);
unsigned char **split_phrase(unsigned char *);
unsigned char **split_word(unsigned char *);
int get_count_of_words(unsigned char*);
int* get_words_length (unsigned char*);

struct coordinates_of_words{
    int x1;
    int x2;
    int y1;
    int y2;
    int choice;
};

typedef struct coordinates_of_words word_position;

word_position *get_keymatrix_positions(unsigned char** ,unsigned char**,int );
unsigned char* playfair_encrypt_word(unsigned char**,unsigned char*);
unsigned char* playfair_decrypt_word(unsigned char**,unsigned char*);
unsigned char* unify_phrase(unsigned char** ,int );

#endif

