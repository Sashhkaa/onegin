#include "C:\Users\1\Desktop\TX\TXLib.h"
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>
#include "onegin.h"


int main() {
    FILE* f = open_file("Eugene_Oneguine.txt");

    struct String buffer = {};

    buffer.len = size_file(f);

    buffer.str = (char*)calloc((buffer.len + 1), sizeof(char));

    struct Text text = {};

    text.size = buffer_filling(&buffer, f);

    printf("text.size = %d\n", text.size);

    text.data = (char**)calloc(text.size, sizeof(char*));

    text.len = (int*)calloc(text.size, sizeof(int));

    str_filling(&buffer, &text);

    qsort(text.data, text.size, sizeof(char*),(int(*) (const void*,const void*))  Cmp_reverse_order);

   // buble_sort(Cmp,&text);

    free(buffer.str);
    free(text.data);
}
