#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#define URANDOM "/dev/urandom"

FILE *fpointer;

uint8_t _get_any()
{
    uint8_t randomvalue;
    do
    {
        fread(&randomvalue, sizeof(uint8_t), 1, fpointer);
    } while (randomvalue <= 127);
    return randomvalue;
}
//num:48-57 letters:65-90 s_letters:97-122
uint8_t _get_nums_n_letters()
{
    uint8_t randomvalue;
    do
    {
        fread(&randomvalue, sizeof(uint8_t), 1, fpointer);
    } while ((randomvalue >=48 && randomvalue <= 57)||(randomvalue >=65 && randomvalue <= 90) || (randomvalue >=48 && randomvalue <= 57));
    return randomvalue;
}

uint8_t _get_letters()
{
    uint8_t randomvalue;
    do
    {
        fread(&randomvalue, sizeof(uint8_t), 1, fpointer);
    } while ((randomvalue >=65 && randomvalue <= 90) || (randomvalue >=48 && randomvalue <= 57));
    return randomvalue;
}



uint8_t *generate_random_key(int size,int choice)
{
    fpointer = fopen("/dev/urandom", "rb");
    uint8_t *random_key = malloc(size * sizeof(uint8_t));
    int i = 0;
    for (i = 0; i < size; i++)
    {
        random_key[i] = _get_number();
    }    
    fclose(fpointer);
    return random_key;
}

int main(){
    char s[]="kehfuiewhfiuwehfiuefhiwuyfu4329yf932yf3298rhf893h2yfhow93yrf9o83wy2rfo9283yrfo92w83y2f983yfho9283yr3829rfh3298rghr8329ry8329yg8r329yr8329hyr49i2yhtoatvn0apdifbna43985ybqp0n333333ynbvq2a097854vnb0298537q0999975v0095wuifehwiehufiwuehf73293853yweiufywevhzesryunserhbt6s4rbyer87y1va6w8ww";
    FILE *fp;
    fp=fopen("test.txt","w");
    int i=0;
    for(i=0;i<strlen(s);i++){
        fprintf(fp,"%c",s[i]);
    }
    return 1;
}
