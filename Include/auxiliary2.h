#ifndef AUXILIARY2_H
#define AUXILIARY2_H
#include <stdint.h>
struct affine_node
{
    unsigned char ch;
    int v;
};
typedef struct affine_node map_t;

int function_f(int);
int r_function(int);

uint32_t string_to_num(uint8_t*);
uint8_t *num_to_string(uint32_t );

struct LR_block{
    uint8_t** L;
    uint8_t** R;
    uint32_t L_num;
    uint32_t R_num;
};
typedef struct LR_block LR_t;
LR_t string_to_LR(uint8_t*,int );
uint8_t* LR_to_string(uint8_t**,uint8_t**,int);
LR_t encrypt_blocks(uint8_t *,uint8_t *,uint8_t**);
LR_t decrypt_blocks(uint8_t *,uint8_t *,uint8_t**);
void special_print(uint8_t* , int );
uint8_t* uppered(uint8_t*,int);

struct string_info{
    uint8_t* str;
    int size;
};
typedef struct string_info string_i;
uint8_t* remove_special_characters(uint8_t*,int );
uint8_t* cut_it(uint8_t*,int);
uint8_t *get_part(uint8_t* ,int ,int ,int );
uint8_t *pad_rest(uint8_t*, int );
int detect_special(uint8_t*,int);
#endif