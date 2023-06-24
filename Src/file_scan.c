#include <stdio.h>
#include <stdlib.h>
#include "../Include/file_scan.h"

int get_count_of_chars(char *name){
    FILE* fp = fopen(name,"r");
    int count=0;
    char c;
    while((c = fgetc(fp))!=EOF){
        count++;
    }
    fclose(fp);
    return count;
}

char* file_to_string(char *name){
    int size=get_count_of_chars(name);
    char* input = malloc(sizeof(char)*size+1);
    char c;
    int i=0;
    FILE* fp = fopen(name,"r");
    while((c = fgetc(fp))!=EOF){
        input[i]=c;
        i++;
    }
    input[i]='\0';
    return input;
}