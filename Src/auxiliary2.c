#include "../Include/auxiliary2.h"
#include "../Include/cs457_crypto.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int function_f(int x)
{
    int a = 11, b = 19;
    int result = ((((a * (x - 65)) + b) % 26) + 65);
    return result;
}

int r_function(int x)
{
    int i;
    int a = 11, b = 19;
    int a_1, is_inverse = 0;
    for (i = 0; i < 26; i++)
    {
        is_inverse = (a * i) % 26;
        if (is_inverse == 1)
        {
            a_1 = i;
        }
    }
    int sum = (a_1 * ((x + 65 - b)) % 26);
    int result = sum + 65;
    return result;
}

//---------------------------------------------------

uint32_t string_to_num(uint8_t *str)
{
    int num = (uint32_t)str[0] << 24 |
              (uint32_t)str[1] << 16 |
              (uint32_t)str[2] << 8 |
              (uint32_t)str[3];
    return num;
}

uint8_t *num_to_string(uint32_t num)
{
    uint8_t *str = malloc(sizeof(uint8_t) * 4);
    str[0] = (uint8_t)(num >> 24) & 0xff; /* high-order (leftmost) byte: bits 24-31 */
    str[1] = (uint8_t)(num >> 16) & 0xff; /* next byte, counting from left: bits 16-23 */
    str[2] = (uint8_t)(num >> 8) & 0xff;  /* next byte, bits 8-15 */
    str[3] = (uint8_t)num & 0xff;
    // sprintf(str, "%lu", (unsigned long)num);
    return str;
}

LR_t string_to_LR(uint8_t *plaintext, int size)
{
    int i, not_exact = (size % 8 == 0) ? 0 : 1;
    int div = size / 8, pl_index = 0, j;
    int part_size = div;
    uint8_t **L = 0, **R = 0;
    L = malloc(sizeof(uint8_t *) * (part_size + not_exact));
    R = malloc(sizeof(uint8_t *) * (part_size + not_exact));

    for (i = 0; i < (part_size + not_exact); i++)
    {
        L[i] = malloc(sizeof(uint8_t) * 4);
        R[i] = malloc(sizeof(uint8_t) * 4);
    }
    for (i = 0; i < part_size; i++)
    {
        for (j = 0; j < 4; j++)
        {
            L[i][j] = plaintext[pl_index++];
        }
        // L[i][j]='\0';
        for (j = 0; j < 4; j++)
        {
            R[i][j] = plaintext[pl_index++];
        }
        // R[i][j]='\0';

    }
    if (not_exact)
    {
        //1. na einai full to R kai to L na einai empty
        //2. na einai kamposo to R kai na to gemizoume me empty opws kai to L
        //3. na gemizei to R kai to L mexri enos simeiou
        //oi anwthen epiloges e3artwntai apo to mod.
        int rest = size % 8;
        if (rest <= 4)
        {
            // if(rest==4){
            for (j = 0; j < 4; j++)
            {
                if ((rest) >= j)
                    L[i][j] = plaintext[pl_index++];
                else
                    L[i][j] = '-';
                // i++;
                printf("\nL[%d][%d]=%d\n", i, j, L[i][j]);
            }

            for (j = 0; j < 4; j++)
                R[i][j] = '-';
        }
        else
        {
            for (j = 0; j < 4; j++)
            {
                L[i][j] = plaintext[pl_index++];
            }
            for (j = 0; j < 4; j++)
            {
                if ((rest) > j)
                    R[i][j] = plaintext[pl_index++];
                else
                {
                        R[i][j] = '-';
                }
            }
        }
    }
    LR_t obj;
    obj.L = L;
    obj.R = R;
    return obj;
}

uint8_t *LR_to_string(uint8_t **L, uint8_t **R, int size)
{
    int i, not_exact = (size % 8 == 0) ? 0 : 1;
    int div = size / 8, j;
    int part_size = div;
    // printf("L/Rok\n");
    uint8_t *encrypted_msg = malloc(sizeof(uint8_t) * (size + 1));
    int enc_index = 0;
    if (not_exact)
    {
        printf("not exact\n");
        part_size++;
    }
    for (i = 0; i < part_size; i++)
    {
        for (j = 0; j < 4; j++)
        {
            encrypted_msg[enc_index++] = L[i][j];
        }
        for (j = 0; j < 4; j++)
        {
            encrypted_msg[enc_index++] = R[i][j];
        }
    }
    /*if (not_exact)
    {
        int rest = size % 8;
        if (rest <= 4)
        {
            for (j = 0; j < rest; j++)
                encrypted_msg[enc_index++] = L[i][j];
        }
        else
        {
            for (j = 0; j < 4; j++)
            {
                encrypted_msg[enc_index++] = L[i][j];
            }
            for (j = 0; j < rest; j++)
            {
                encrypted_msg[enc_index++] = R[i][j];
            }
        }
    }*/
    printf("ENC_INDEX: %d\n", enc_index);
    encrypted_msg[enc_index] = '\0';
    return encrypted_msg;
}

LR_t encrypt_blocks(uint8_t *L, uint8_t *R, uint8_t **key)
{
    int i;
    uint32_t temp = 0, L_num = string_to_num(L);
    uint32_t R_num = string_to_num(R);
    for (i = 0; i < 8; i++)
    {
        temp = L_num ^ feistel_round(R_num, (key[i]));
        L_num = R_num;
        R_num = temp;
    }
    LR_t res;
    res.L_num = L_num;
    res.R_num = R_num;
    return res;
}

LR_t decrypt_blocks(uint8_t *L, uint8_t *R, uint8_t **key)
{
    int i;
    uint32_t temp = 0, L_num = string_to_num(L);
    uint32_t R_num = string_to_num(R);
    for (i = 0; i < 8; i++)
    {
        temp = L_num ^ feistel_round(R_num, (key[7 - i]));
        L_num = R_num;
        R_num = temp;
    }
    LR_t res;
    res.L_num = L_num;
    res.R_num = R_num;
    return res;
}

void special_print(uint8_t *str, int size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        if (str[i] >= 32 && str[i] <= 126)
            printf("%c", str[i]);
        else
            printf("(%x)", str[i]);
    }
    printf("\n");
}

uint8_t *uppered(uint8_t *str, int size)
{
    uint8_t *new_str = malloc((size + 1) * sizeof(uint8_t));
    int i = 0;
    for (i = 0; i < size; i++)
    {
        int is_acceptable = (str[i] >= 97 && str[i] <= 122);
        if(is_acceptable)
            new_str[i] = toupper(str[i]);
        else
            new_str[i] = str[i];
    }
    new_str[i] = '\0';
    return new_str;
}

uint8_t* remove_special_characters(uint8_t *str, int size)
{
    uint8_t* new_str = calloc((size),sizeof(uint8_t));
    int i, z = 0;
    for (i = 0; i < size; i++)
    {
        if ((str[i] >= 65 && str[i] <= 90) || str[i]=='\0') 
            new_str[z++] = str[i];
    }
    // new_str[z] = '\0';
    //  = new_str;
    printf("NEW: %s\n",new_str);
    // info.size = z+1;
    return new_str;
}

uint8_t *cut_it(uint8_t *str, int size)
{
    uint8_t *new_str = malloc(sizeof(uint8_t) * (size + 1));
    int i;
    for (i = 0; i < size; i++)
    {
        new_str[i] = str[i];
    }
    new_str[i] = '\0';
    return new_str;
}

uint8_t *get_part(uint8_t* str,int start,int end,int size){
    int i,z=0 ;
    uint8_t* s = malloc(4*sizeof(uint8_t));
    // if(start>=size-1){
    //     return s;
    // }
    for(i=start;i<=end;i++){
        s[z++]=str[i];
    }
    return s;
}

uint8_t *pad_rest(uint8_t* str, int size){
    uint8_t* new_str = malloc(8*sizeof(uint8_t));
    int i=0,z=0;
    for(i=0;i<size;i++){
        new_str[z++]=str[i];
    }
    for(i=0;i<(8-size);i++){
        new_str[z++]='-';
    }
    return new_str;
}

int detect_special(uint8_t* str,int size){
    int i=0,flag=0;
    for(i=0;i<size;i++){
        if((str[i]>90 || str[i]<65) && str[i]!=' '){
            flag=1;
        }
    }
    return flag;
}