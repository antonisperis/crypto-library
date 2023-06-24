#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Include/cs457_crypto.h"
#include "./Include/auxiliary.h"
#include "./Include/auxiliary2.h"
#include "./Include/file_scan.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Wrong count of arguments! Program exit.");
        exit(-1);
    }
    char *mode = argv[1];
    char *name = argv[2];
    char *text = file_to_string(name);
    // scanf("%s",text);
    printf("SIZE: %d DIV:%d MOD:%d\n",strlen(text) ,strlen(text)/8 ,strlen(text)%8);
    // printf("-------------------------\n");
    // printf("COUNT: %ld\n", strlen(text));
    // printf("-------------------------\n");

    uint8_t *msg = convert_string_to_uint8(text);
    if (!strcmp(mode, "otp"))
    {
        uint8_t *key = generate_random_key(strlen(text));
        uint8_t *encrypted = otp_encrypt(msg, key, strlen(text));
        printf("-------------------------\n");
        
        // print_encrypt(encrypted, name, key);
        special_print(encrypted,strlen(text));
        printf("-------------------------\n");
        printf("%s\n", convert_uint8_to_string(otp_decrypt(encrypted, key, strlen(text)), strlen(text))); //synartisi uint8 - > char*
        printf("-------------------------\n");
    }
    else if (!strcmp(mode, "ceasar"))
    {
        int shift;
        printf("Give a number:");
        scanf("%d",&shift);
        shift = shift % 64;
        uint8_t *encrypted = ceasar_encrypt(msg, shift, strlen(text));
        printf("-------------------------\n");
        printf("Encrypted: %s\n",cut_it(encrypted,strlen(text)));

        printf("Decrypted: %s\n", convert_uint8_to_string(ceasar_decrypt(encrypted, shift, strlen(text)), strlen(text))); //synartisi uint8 - > char*
        printf("-------------------------\n");
    }
    else if (!strcmp(mode, "playfair"))
    {
        unsigned char *pass = (unsigned char *)"ZBVDWDQWUDHAAOWIFOAIWXYOWI";
        unsigned char **keymatrix = playfair_keymatrix(pass);
        int i, j;
        uint8_t* up  = uppered(msg,strlen(text));
        int not_ok = detect_special(up,strlen(text));
        uint8_t* res;
        if(not_ok)
            res =  remove_special_characters(up, strlen(text));
        else
            res =up;
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 5; j++)
            {
                printf("%c ", keymatrix[i][j]);
            }
            printf("\n");
        }

        unsigned char *ens = playfair_encrypt(res, playfair_keymatrix(pass));
        printf("\n%s\n", ens);
        unsigned char *decrypted_phrase = playfair_decrypt(ens, keymatrix);
        printf("\n\n%s\n", decrypted_phrase);
    }
    else if (!strcmp(mode, "affine"))
    {
        unsigned char *affine_encr = affine_encrypt(uppered(msg,strlen(text)), strlen(text));
        printf("%s\n", cut_it(affine_encr,strlen(text)));
        unsigned char *affine_dec = affine_decrypt(affine_encr, strlen(text));
        printf("%s\n", affine_dec);
    }
    else if(!strcmp(mode,"feistel")){
        int i = 0;
        uint8_t *keys[8];
        for(i=0;i<8;i++){
            keys[i] = generate_random_key(4);
            // printf("%s\n",keys[i]);
        }
        uint8_t *encrypted = feistel_encryption(msg,keys,strlen(text));
        special_print(encrypted,strlen(text));
        // printf("%s\n",encrypted);
        printf("%s\n",feistel_decryption(encrypted,keys,strlen(text)));

    }
    else{
        // printf("\033[0;31m");
        printf("ERROR: wrong arguments. Programm exit.\n");
    }
    printf("\n");
    return 1;
}
