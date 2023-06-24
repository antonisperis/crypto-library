#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
// #include <windows.h>
#include "../Include/cs457_crypto.h"
#include "../Include/auxiliary.h"
#include "../Include/auxiliary2.h"

uint8_t *otp_encrypt(uint8_t *plaintext, uint8_t *key, int size)
{

    uint8_t *result = malloc(sizeof(uint8_t) * size);
    int i, count = 0;
    for (i = 0; i < size; i++)
    {
        result[i] = plaintext[i] ^ key[i];
        count++;
    }
    return result;
}
uint8_t *otp_decrypt(uint8_t *ciphertext, uint8_t *key, int size)
{

    uint8_t *result = malloc(size);
    int i;
    // printf("dec: %d",size);
    for (i = 0; i < size; i++)
    {
        result[i] = ciphertext[i] ^ key[i];
    }
    return result;
}

//-------------------Ceasar--------------------------------

int ceasar_size = 0;
uint8_t *ceasar_encrypt(uint8_t *plaintext, unsigned short N, int size)
{

    uint8_t *encrypted = malloc(size);
    int i = 0, z = 0;
    for (i = 0; i < size; i++)
    {
        int is_acceptable = (plaintext[i] >= 65 && plaintext[i] <= 90) || (plaintext[i] >= 97 && plaintext[i] <= 122) || (plaintext[i] >= 48 && plaintext[i] <= 57);
        if (is_acceptable)
        {
            encrypted[z] = get_ceasar_encryption_char(plaintext[i], N);
            z++;
        }
        else
        {
            encrypted[z] = plaintext[i];
            z++;
        }
    }
    ceasar_size = z;

    char *to_convert = convert_uint8_to_string(encrypted, z);
    return convert_string_to_uint8(to_convert);
}

uint8_t *ceasar_decrypt(uint8_t *ciphertext, unsigned short N, int size)
{
    uint8_t *decrypted = malloc(ceasar_size);
    int i = 0, z = 0;
    for (i = 0; i < ceasar_size; i++)
    {
        int is_acceptable = (ciphertext[i] >= 65 && ciphertext[i] <= 90) || (ciphertext[i] >= 97 && ciphertext[i] <= 122) || (ciphertext[i] >= 48 && ciphertext[i] <= 57);
        if (is_acceptable)
            decrypted[z++] = get_ceasar_decryption_char(ciphertext[i], N);
        else
            decrypted[z++] = ciphertext[i];
    }
    char *to_convert = convert_uint8_to_string(decrypted, z);
    return convert_string_to_uint8(to_convert);
}

//-------------------Playfair------------------------------

unsigned char **playfair_keymatrix(unsigned char *key)
{
    unsigned char alphabet[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ\0";
    unsigned char *single_key = remove_duplicates(key);
    // printf("SINGLE KEYYY: %s\n",single_key);

    unsigned char *final_str = malloc(sizeof(unsigned char) * (strlen((char *)key) + strlen((char *)alphabet)));
    strcpy((char *)final_str, (char *)single_key);
    // printf("KEYYY: %s\n",final_str);
    strcat((char *)final_str, (char *)alphabet);
    unsigned char *to_double = remove_duplicates(final_str);
    unsigned char **keymatrix = malloc(sizeof(unsigned char *) * 5);
    int i, j, z = 0;
    for (i = 0; i < 5; i++)
        *(keymatrix + i) = malloc(sizeof(unsigned char) * 5);

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            keymatrix[i][j] = to_double[z++];
        }
    }

    return keymatrix;
}

// unsigned char **get_encrypted_word(unsigned char **splited_word, unsigned char **keymatrix, int size)
// {
//     int i = 0, j = 0;
//     char **result = malloc(sizeof(unsigned char *) * size);
//     for (i = 0; i < size; i++)
//     {
//         result[i] = malloc(sizeof(unsigned char) * 3);
//     }
//     for (i = 0; i < 5; i++)
//     {
//         for (j = 0; j < 5; j++)
//         {
//         }
//     }
// }

unsigned char *playfair_encrypt(unsigned char *plaintext, unsigned char **key)
{
    int count = get_count_of_words(plaintext);
    unsigned char **splited_phrase = split_phrase(plaintext);
    int *sizes = malloc(sizeof(int) * count);
    int i;
    unsigned char **all_encrypted_words = malloc(sizeof(char *) * count);
    for (i = 0; i < count; i++)
    {
        sizes[i] = strlen((char *)splited_phrase[i]);
        all_encrypted_words[i] = playfair_encrypt_word(key, splited_phrase[i]);
    }
    return unify_phrase(all_encrypted_words, count);
}

unsigned char *playfair_decrypt(unsigned char *ciphertext, unsigned char **key)
{
    int count = get_count_of_words(ciphertext);
    unsigned char **splited_phrase = split_phrase(ciphertext);
    int *sizes = malloc(sizeof(int) * count);
    int i;
    unsigned char **all_decrypted_words = malloc(sizeof(char *) * count);
    for (i = 0; i < count; i++)
    {
        sizes[i] = strlen((char *)splited_phrase[i]);
        all_decrypted_words[i] = playfair_decrypt_word(key, splited_phrase[i]);
    }
    return unify_phrase(all_decrypted_words, count);
}

//-------------------Affine------------------------------
uint8_t *affine_encrypt(uint8_t *plaintext, int size)
{
    int i;
    uint8_t *encrypted = malloc(sizeof(uint8_t) * size);
    for (i = 0; i < size; i++)
    {
        int is_acceptable = (plaintext[i] >= 65 && plaintext[i] <= 90) || (plaintext[i] >= 97 && plaintext[i] <= 122);
        if (is_acceptable)
        {
            int x = (int)plaintext[i];
            encrypted[i] = function_f(x);
        }
        else
        {
            encrypted[i] = plaintext[i];
        }
    }
    return encrypted;
}

uint8_t *affine_decrypt(uint8_t *ciphertext, int size)
{
    int i;
    uint8_t *decrypted = malloc(sizeof(uint8_t) * size);
    for (i = 0; i < size; i++)
    {
        int is_acceptable = (ciphertext[i] >= 65 && ciphertext[i] <= 90) || (ciphertext[i] >= 97 && ciphertext[i] <= 122);
        if (is_acceptable)
        {
            int x = (int)ciphertext[i];
            decrypted[i] = r_function(x);
        }
        else
        {
            decrypted[i] = ciphertext[i];
        }
    }
    return cut_it(decrypted,size);
}

//------------------Feistel-----------------------------
uint32_t feistel_round(uint32_t R_i, uint8_t *K)
{
    int i = 0;
    uint8_t *G = malloc(sizeof(uint8_t) * 4);
    uint8_t *R = num_to_string(R_i);
    for (i = 0; i < 4; i++)
    {
        G[i] = R[i] * K[i];
    }
    //    long int max = pow(2, 32);
    uint32_t g = string_to_num(G);
    return (g % UINT_MAX);
}

#define ROUNDS 8

uint8_t *feistel_encryption(uint8_t *plaintext, uint8_t **key, int size)
{
    //split in 2*k blocks
    //orizontia tha exoun 4 bytes
    int flag = 0;
    uint8_t *encrypted_msg = calloc(size, sizeof(uint8_t));
    int i, j = 0;
    int div = size / 8;
    uint8_t *rest;
    int part_size = div;
    if (size % 8 != 0)
    {
        int l = 0, rest_size = size - (div * 8 + 1);
        rest = calloc(rest_size, sizeof(uint8_t));
        for (l = (div * 8 + 1); l < rest_size; l++)
            rest[l] = plaintext[l];
        part_size++;
        flag = 1;
    }
    printf("======================PART SIZE: %d======================\n", part_size);
    uint8_t **L = 0, **R = 0;
    L = malloc(sizeof(uint8_t *) * (part_size));
    R = malloc(sizeof(uint8_t *) * (part_size));

    for (i = 0; i < (part_size); i++)
    {
        L[i] = calloc(4, sizeof(uint8_t));
        R[i] = calloc(4, sizeof(uint8_t));
    }
    int enc_index = 0, l_start = 0, l_end = 0, r_start = 0, r_end = 0;
    // encryption - metatropi se arithmo mesa sto encrypt_blocks...
    for (i = 0; i < part_size; i++)
    {
        l_end = l_start + 3;
        r_start = l_end + 1;
        r_end = r_start + 3;
        uint32_t left = 0, temp = 0, right = 0;
        if (flag == 1 && i == part_size)
        {
            int l = 0, l_in = 0;
            uint8_t *left_str = malloc(sizeof(uint8_t) * 4);
            for (l = 0; l < 4; l++)
                left_str[l] = rest[l_in++];
            uint8_t *right_str = malloc(sizeof(uint8_t) * 4);
            for (l = 0; l < 4; l++)
                right_str[l] = rest[l_in++];
            right = string_to_num(right_str);
        }
        else
        {
            left = string_to_num(get_part(plaintext, l_start, l_end, size));
            right = string_to_num(get_part(plaintext, r_start, r_end, size));
        }
        printf("LEFT START:%d\tLEFT END:%d\tRIGHT START:%d\tRIGHT END:%d %d\t\n", l_start, l_end, r_start, r_end, right);
        for (j = 0; j < ROUNDS; j++)
        {
            temp = left ^ feistel_round(right, key[j]);
            left = right;
            right = temp;
        }
        L[i] = num_to_string(right);
        R[i] = num_to_string(left);
        l_start += 8;
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
    return encrypted_msg;
}

uint8_t *feistel_decryption(uint8_t *ciphertext, uint8_t **key, int size)
{
    uint8_t *decrypted_msg = calloc(4, sizeof(uint8_t));
    int i, j = 0, not_exact = (size % 8 == 0) ? 0 : 1;
    int div = size / 8;
    int part_size = div, msg_index = 0;
    if (not_exact)
    {
        part_size++;
    }
    uint8_t **L = 0, **R = 0;
    L = malloc(sizeof(uint8_t *) * (part_size));
    R = malloc(sizeof(uint8_t *) * (part_size));

    for (i = 0; i < (part_size); i++)
    {
        L[i] = calloc(4, sizeof(uint8_t));
        R[i] = calloc(4, sizeof(uint8_t));
    }
    //encryption - metatropi se arithmo mesa sto encrypt_blocks...
    int l_start = 0, l_end = 0, r_start = 0, r_end = 0;
    // encryption - metatropi se arithmo mesa sto encrypt_blocks...
    for (i = 0; i < part_size; i++)
    {
        l_end = l_start + 3;
        r_start = l_end + 1;
        r_end = r_start + 3;
        uint32_t temp = 0, left = 0, right = 0;
        left = string_to_num(get_part(ciphertext, l_start, l_end, size));
        right = string_to_num(get_part(ciphertext, r_start, r_end, size));
        printf("LEFT START:%d\tLEFT END:%d\tRIGHT START:%d\tRIGHT END:%d\t\n", l_start, l_end, r_start, r_end);

        for (j = 0; j < ROUNDS; j++)
        {
            temp = left ^ feistel_round(right, key[7 - j]);
            left = right;
            right = temp;
        }
        uint8_t* lft,*rght;
        lft = num_to_string(right);
        rght = num_to_string(left);
        for (j = 0; j < 4; j++)
        {
            decrypted_msg[msg_index++] = lft[j];
        }
        for (j = 0; j < 4; j++)
        {
            decrypted_msg[msg_index++] = rght[j];
        }
        // L[i] = num_to_string(right);
        // R[i] = num_to_string(left);
        l_start += 8;
    }
    printf("======================PART SIZE: %d TOTAL SIZE:%d======================\n", part_size,size);
    // for (i = 0; i < part_size; i++)
    // {
    //     for (j = 0; j < 4; j++)
    //     {
    //         decrypted_msg[msg_index++] = L[i][j];
    //     }
    //     for (j = 0; j < 4; j++)
    //     {
    //         decrypted_msg[msg_index++] = R[i][j];
    //     }
    // }
    // decrypted_msg = LR_to_string(L, R, size);
    return cut_it(decrypted_msg,size);
}
