#include <stdio.h>
#include <string.h>


char *b="WIEUFGUEWFGRYFIDXDNCUHWEGHBEHVDWEUFIHAOEUFHBVIWEGUFRWXOEBFVOYWROUIFOUWEGBWRYIEWOEWUFGHYIRWBGOWREUTIXDSIUFGBYIREWOIEDSFNIYREWISODFLNFIWEHOIFEOHUFEXFHUOEFWOHUEOHUFEHXHUDSDIVBVSOUGRROGHGRHXRXEUHRGRUHUHRGUHRGUHRHU\0"; 
char *a="wieufguewfgryfjdxdncuhweghbehvdweufihaoeufhbviwegufrwwoebfvoywroujfouwegbwryiewoewufghyirwbgowreutijdsiufgbyirewoiedsfniyrewisodflnfiwehoifeohufeefhuoefwohueohufehhhudsdjvbvsougrroghgrhhrreuhrgruhuhrguhrguhrhu\0";
char *uppered(char *str, int size)
{
    char *new_str = malloc((size + 1) * sizeof(char));
    int i = 0;
    for (i = 0; i < size; i++)
    {
        new_str[i] = toupper(str[i]);
    }
    new_str[i] = '\0';
    return new_str;
}
int main(){
    printf("%d\n",strcmp(b,uppered(a,strlen(a))));
    return 1;
}