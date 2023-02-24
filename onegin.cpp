#include "C:\Users\1\Desktop\TX\TXLib.h"
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>
#include "constructor.h"

struct Buffer
{
    char* data;
    int   size;
};

struct Index
{
    char** data;
    int    size;
};

int main() {

    char* buffer = NULL;
    char** str = NULL;
    long int nchar = 0;
    int nstr = 0 ;     // ����������

    FILE* f = open_file("Eugene_Oneguine.txt");

    nchar = countchar_inbuffer(f);

    buffer=(char*)calloc(nchar,sizeof(char));

    nstr=buffer_filling(buffer,nchar,f);

    str=(char**)calloc(nstr,sizeof(char*));

    str_filling(nchar,buffer,str);

    //for (int i = 0; i < nstr; i++) printf("%c\n",*str[i]);

    struct struct_arr* onegin=(struct struct_arr*)calloc(nstr,sizeof(struct_arr));

    oneg_main_filling(nchar,nstr,buffer,onegin,str);
    Cmp(str+1, str+2) ;
    //qsort(str,nstr,sizeof(char*),(int(*) (const void*,const void*))  Cmp);

    //buble_sort(Cmp,str,nstr);



    for(int i = 0; i < nstr; i++) {
    printf("%c\n", **(str+i));
    }
    free(onegin);
    free(buffer);
    free(str);
}
