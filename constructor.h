#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//onegin->structs_arr[i].str

struct struct_arr {        // добавить сюда буффер и стр
 int n = 0;
 char* str = nullptr;
};


FILE* open_file(const char* name) {
FILE* fp=fopen(name,"r");
    if (fp == NULL)
    {
        printf("couldnt open\n");
        //assert(0);
    }
    return fp;
}

int countchar_inbuffer(FILE* f) {
    rewind(f);
    //fseek(f,0,SEEK_SET);

    fseek(f,0,SEEK_END);

    int a = ftell(f);

    printf("%ld\n",a);

    fseek(f,0,SEEK_SET);

    return a;
}


int buffer_filling(char* buffer, int nchar, FILE* f) {

    int nstrtmp=0;
    fread(buffer,sizeof(char),nchar,f);
    for (size_t i = 0; i < nchar; i++) {
    if (buffer[i] == '\n')
         nstrtmp++;
         buffer[i] == '\0';
    }
    return nstrtmp;
}

void str_filling(int nchar, char* buffer, char** str) {
 int b = 0;
// **str=oneg[0];
 for (size_t i = 0;i< nchar ;i++) {
  if (buffer[i]=='\n') {
    *(str+b)=buffer+i+1;
    b++;
    buffer[i] = '\0';

    }
   }
}


void oneg_main_filling(int nchar, int nstr, char* oneg, struct struct_arr* oneg_main, char** str) {
    int tmp=0;
    int len=0;
    int p=0;

for(int i=0 ; i < nchar ; i++) {
        if(oneg[i] == '\0') {
            len = i - tmp;
            oneg_main[p].n = len;
            tmp = i;
            //printf("%d\n",oneg_main[p].n);
            p++;
     }
  }
for ( int i = 0; i < nstr ; i++) {

       oneg_main[i].str = str[i];
         //printf("str[]=%c\n oneg_main[].str=%c\n ",*str[i],*oneg_main[i].str);

      }
}

int Cmp(char** left_str, char** right_str) {

    assert(right_str != NULL);
    assert(left_str  != NULL);

    int left = 0;
    int right = 0;

    while (!isalpha(**(left_str+left))) {
            left++;
    }
    while (!isalpha(**(right_str+right))) {
            right++;
    }

    while ( (**(left_str+left) != '\0' || **(right_str+right) != '\0') ||  (**(left_str+left) == **(right_str+right)) ) {
        while (!isalpha(**(left_str+left))) {
            left++;
        }
        while (!isalpha(**(right_str+right))) {
            right++;
        }

        left++;
        right++;
    }

    return **(left_str+left) - **(right_str+right);
}


void buble_sort(int (*Cmp)(char**,char**), char** str, int nstr) {
    for (int j = 0; j < nstr-1; j++) {
        for(int i = 0; i < nstr - j - 1; i++) {
            if (Cmp((str+i),(str+i+1)) > 0) {
                char* temp = str[i+1];
                str[i+1] = str[i];
                str[i] = temp;
            }
        }
    }
}


#endif // ONEGIN_H_INCLUDED
