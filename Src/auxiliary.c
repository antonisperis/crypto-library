#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "../Include/auxiliary.h"
#include "../Include/file_scan.h"

#define URANDOM "/dev/urandom"

//-----------------------------------------

uint8_t *convert_string_to_uint8(char *str)
{
    int i, size = strlen(str);
    uint8_t *arr = malloc(size);
    for (i = 0; i < size; i++)
    {
        arr[i] = (char)str[i];
    }
    return arr;
}

char *convert_uint8_to_string(uint8_t *str, int size)
{
    int i;
    char *arr = malloc(size + 1);
    for (i = 0; i < (size); i++)
    {
        arr[i] = (char)str[i];
    }
    arr[i] = '\0';
    printf("\nSIZE: %d CONV: %d\n", size, strlen(arr));
    return arr;
}

void print_encrypt(uint8_t *str, char *name, uint8_t *key)
{
    char *non_printable_map[] = {"(null)", "(start of heading)", "(start of text)", "(end of text)", "(end of transmission)",
                                 "(enquiry)", "(acknowledge)", "(bell)", "(backspace)", "(horisontal tab)", "(NL line feed, new line)", "(vertical tab)", "(NP form feed, new page)",
                                 "(carriage return)", "(shift out)", "(shift in)", "(data link escape )", "(device control 1)", "(device control 2)", "(device control 3)", "(device control 4)",
                                 "(negative acknowledge)", "(synchronous idle)", "(end of trans. block)", "(cancel)", "(end of medium)", "(substitute)", "(escape)", "(file separator)",
                                 "(group seperator)", "(record seperator)", "(unit seperator)", "(space)"};
    int i;
    // size_t size = sizeof(str) / sizeof(str[0]) + 2;
    for (i = 0; i < get_count_of_chars(name); i++)
    {
        if ((int)str[i] == 127)
        {
            printf("%s", "delete");
        }
        else
        {
            if (str[i] >= 0 && str[i] <= 32)
            {
                printf("%s", non_printable_map[str[i]]);
            }
            else
            {
                char c = (char)str[i];
                printf("\nI:%d %c -> %d ", i, c, key[i]);
            }
        }
    }
    printf("\n");
    return;
}

// static FILE *ufp;

// uint8_t _get_number(){
//     int rNumber = fopen("/dev/urandom","r");

//     printf("this is a random number from the file urandom : %d", &rNumber);
//     uint8_t num=&rNumber;
//     fclose(rNumber);
//     return num;
// }
FILE *fpointer;
uint8_t _get_number()
{
    int randomvalue;
    do
    {
        fread(&randomvalue, sizeof(uint8_t), 1, fpointer);
    } while (randomvalue <= 127);
    return randomvalue;
}

uint8_t *generate_random_key(int size)
{
    fpointer = fopen("/dev/urandom", "rb");
    uint8_t *random_key = malloc(size * sizeof(uint8_t));
    int i = 0;
    for (i = 0; i < size; i++)
        random_key[i] = _get_number();
    fclose(fpointer);
    return random_key;
}

//-----------Ceasars----------------

    char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890\0";
uint8_t get_ceasar_encryption_char(uint8_t byte, unsigned short shift)
{
    int i = 0, new_index;
    uint8_t final_char;
    for (i = 0; i < strlen(alphabet); i++)
    {
        if (byte == (uint8_t)alphabet[i])
        {
            new_index = i + shift;
            if (new_index > (strlen(alphabet)-1))
            {
                new_index = new_index - (strlen(alphabet));
            }
            final_char = alphabet[new_index];
            return final_char;
        }
    }
    return 0;
}

uint8_t get_ceasar_decryption_char(uint8_t byte, unsigned short shift)
{
    // char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    int i = 0, new_index;
    uint8_t final_char;
    for (i = 0; i < strlen(alphabet); i++)
    {
        if (byte == (uint8_t)alphabet[i])
        {
            new_index = i - shift;
            if (new_index < 0)
            {
                new_index = strlen(alphabet) + new_index;
            }
            final_char = alphabet[new_index];
            return final_char;
        }
    }
    return 0;
    // return '-';
}

//----------Playfair-------------------------------------

unsigned char *remove_duplicates(unsigned char *str)
{
    int i, j, z = 0;
    unsigned char *new_str = malloc(sizeof(char) * strlen((char *)str));
    for (i = 0; i < strlen((char *)str); i++)
    {
        int exists = 0;
        for (j = 0; j < strlen((char *)new_str); j++)
        {
            if (str[i] == new_str[j] || str[i]==' ')
                exists = 1;
        }
        if (!exists)
        {
            new_str[z] = str[i];
            z++;
        }
    }
    return new_str;
}

unsigned char **split_phrase(unsigned char *tes)
{
    int count = get_count_of_words(tes), z = 0;
    unsigned char *cur = (unsigned char *)strtok((char *)tes, " ");
    unsigned char **splited = malloc(sizeof(unsigned char *) * count);
    while (cur)
    {
        splited[z] = (unsigned char *)strdup((char *)cur);
        z++;
        cur = (unsigned char *)strtok(NULL, " ");
    }
    return splited;
}

unsigned char **split_word(unsigned char *word)
{
    int i = 0, z = 0;
    unsigned char **result;
    for(i=0;i<strlen((char *)word);i++){
        if(word[i]=='J')
            word[i]='I';
    }
    i=0;
    if (strlen((char *)word) % 2 == 0)
    {
        result = malloc(sizeof(unsigned char *) * (strlen((char *)word) / 2));
        for (i = 0; i < (strlen((char *)word) / 2); i++)
        {
            result[i] = malloc(sizeof(unsigned char) * 3);
        }
    }
    else
    {
        result = malloc(sizeof(unsigned char *) * ((strlen((char *)word) / 2) + 1));
        int fin = (strlen((char *)word) / 2) + 1;
        for (i = 0; i < fin; i++)
        {
            result[i] = malloc(sizeof(unsigned char) * 3);
        }
        // result[fin-1][0] = word[strlen((char *)word) - 1];
        // result[fin-1][1] = 'X';
    }
    for (i = 0; i < strlen((char *)word); i = i + 2)
    {
        result[z][0] = word[i];
        if (word[i] != word[i + 1])
        {
            result[z][1] = word[i + 1];
        }
        else
        {
            result[z][1] = 'X';
        }
        if (!word[i + 1])
        {
            result[z][1] = 'X';
        }
        result[z][2] = '\0';
        // printf("I:%d -> RES[%d]: %s\n",i,z,result[z]);
        z++;
    }
    
    return result;
}

int get_count_of_words(unsigned char *tes)
{
    int i = 0, count = 0;
    for (i = 0; i < strlen((char *)tes); i++)
    {
        if (tes[i] == ' ')
            count++;
    }
    return (count + 1);
}

int *get_words_length(unsigned char *phrase)
{
    int i = 0, j = 0, count_of_words = get_count_of_words(phrase);
    int *count_array = malloc(sizeof(int) * count_of_words);
    for (i = 0; i < count_of_words; i++)
        count_array[i] = 0;

    for (i = 0; i < count_of_words; i++)
    {
        while (phrase[j] && phrase[j] != ' ')
        {
            count_array[i]++;
            j++;
        }
        if(count_array[i] % 2 !=0)
            count_array[i]++;
        j++;
    }
    
    return count_array;
}


word_position *get_keymatrix_positions(unsigned char** word,unsigned char**keymatrix,int size){
    word_position *pos = malloc(sizeof(word_position)*size);
    int z,i,j;
    for(z=0;z<size;z++){
        for(i=0;i<5;i++){
            for(j=0;j<5;j++){
                if(keymatrix[i][j]==word[z][0]){
                    pos[z].x1=i;
                    pos[z].y1=j;
                }
                if(keymatrix[i][j]==word[z][1]){
                    pos[z].x2=i;
                    pos[z].y2=j;
                }
            }
        }
        if(pos[z].x1==pos[z].x2){
            pos[z].choice=0;
        }
        else if(pos[z].y1==pos[z].y2){
            pos[z].choice=1;
        }
        else {
            pos[z].choice=2;
        }
    }
    return pos;
}


unsigned char *same_row_encryption(unsigned char**key,word_position wp){
    unsigned char *produced = malloc (sizeof(unsigned char)*2);
    if((wp.y1+1)>4){
        produced[0]=key[wp.x1][0];
    }
    else{
        produced[0]=key[wp.x1][wp.y1+1];
    }
    if((wp.y2+1)>4){
        produced[1]=key[wp.x2][0];
    }
    else{
        produced[1]=key[wp.x2][wp.y2+1];
    }
    return produced;
}
unsigned char *same_column_encryption(unsigned char**key,word_position wp){
    unsigned char *produced = malloc (sizeof(unsigned char)*2);
    if(wp.x1+1>4){
        produced[0]=key[0][wp.y1];
    }
    else{
        produced[0]=key[wp.x1+1][wp.y1];
    }
    if(wp.x2+1>4){
        produced[1]=key[0][wp.y1];
    }
    else{
        produced[1]=key[wp.x2+1][wp.y1];
    }
    return produced;
}

unsigned char *rectangle(unsigned char**key,word_position wp){
    unsigned char *produced = malloc (sizeof(unsigned char)*2);
    produced[0] = key[wp.x1][wp.y2];
    produced[1] = key[wp.x2][wp.y1];
    return produced;
}

typedef unsigned char * playfair_encryption_function(unsigned char**key,word_position wp);

playfair_encryption_function *encrypt_syllable[3]={
    same_row_encryption,same_column_encryption,rectangle
};

unsigned char* unify_word(unsigned char** syllables,int syllable_count){
    int i=0,z=0;
    unsigned char* word = malloc(sizeof(unsigned char)*(2*syllable_count+1));
    for(i=0;i<syllable_count;i++){
        word[z++] = syllables[i][0];
        word[z++] = syllables[i][1];
    }
    word[z] = '\0';
    return word;
}

unsigned char* unify_phrase(unsigned char** words,int count_of_words){
    int i=0,j=0,z=0,phrase_size=0;
    for(i=0;i<count_of_words;i++){
        phrase_size+=strlen((char*)words[i]);//grammata
        phrase_size++;                      //keno
    }
    unsigned char* phrase = malloc(sizeof(unsigned char)*phrase_size);
    for(i=0;i<count_of_words;i++){
        for(j=0;j<strlen((char*)words[i]);j++){
            phrase[z++] = words[i][j];
        }
        if(i!= count_of_words-1)
            phrase[z++] = ' ';
        else
        {
            phrase[z]='\0';
        }
    }
    return phrase;
}

unsigned char* playfair_encrypt_word(unsigned char**key,unsigned char* word){
    unsigned char **splited = split_word(word);
    int syllable_count = (strlen((char*)word)%2==0) ? (strlen((char*)word)/2) : ((strlen((char*)word)+1)/2);
    unsigned char **encrypted_syllables = malloc(sizeof(unsigned char*)*syllable_count);
    word_position *wp=get_keymatrix_positions(splited,key,syllable_count);
    // ENCRYPT PART
    for (size_t i = 0; i < syllable_count; i++)
    {
        encrypted_syllables[i] = encrypt_syllable[wp[i].choice](key,wp[i]);
        printf("%s ",encrypted_syllables[i]);
    }
    unsigned char *encrypted_word = unify_word(encrypted_syllables,syllable_count);
    return encrypted_word;
}

unsigned char *same_row_decryption(unsigned char**key,word_position wp){
    unsigned char *produced = malloc (sizeof(unsigned char)*2);
    if((wp.y1-1)<0){
        produced[0]=key[wp.x1][4];
    }
    else{
        produced[0]=key[wp.x1][wp.y1-1];
    }
    if((wp.y2-1)<0){
        produced[1]=key[wp.x2][4];
    }
    else{
        produced[1]=key[wp.x2][wp.y2-1];
    }
    return produced;
}
unsigned char *same_column_decryption(unsigned char**key,word_position wp){
    unsigned char *produced = malloc (sizeof(unsigned char)*2);
    if(wp.x1-1<0){
        produced[0]=key[4][wp.y1];
    }
    else{
        produced[0]=key[wp.x1-1][wp.y1];
    }
    if(wp.x2-1<0){
        produced[1]=key[4][wp.y1];
    }
    else{
        produced[1]=key[wp.x2-1][wp.y1];
    }
    return produced;
}
typedef unsigned char * playfair_decryption_function(unsigned char**key,word_position wp);
playfair_decryption_function *decrypt_syllable[3]={
    same_row_decryption,same_column_decryption,rectangle
};
unsigned char* playfair_decrypt_word(unsigned char**key,unsigned char* word){
    unsigned char **splited = split_word(word);
    int syllable_count = (strlen((char*)word)%2==0) ? (strlen((char*)word)/2) : ((strlen((char*)word)+1)/2);
    unsigned char **decrypted_syllables = malloc(sizeof(unsigned char*)*syllable_count);
    word_position *wp=get_keymatrix_positions(splited,key,syllable_count);
    for (size_t i = 0; i < syllable_count; i++){
        decrypted_syllables[i] = decrypt_syllable[wp[i].choice](key,wp[i]);
        printf("%s ",decrypted_syllables[i]);
    }
   

    unsigned char *encrypted_word = unify_word(decrypted_syllables,syllable_count);
    return encrypted_word;
}
