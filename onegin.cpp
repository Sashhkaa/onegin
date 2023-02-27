#include "C:\Users\1\Desktop\TX\TXLib.h"
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>
#include "onegin.h"


int main() {
    FILE* f = open_file("Eugene_Oneguine.txt");

    struct String buffer = {};

    struct Text text = {};

    buffer.len = size_file(f);

    buffer.str = (char*)calloc((buffer.len + 1), sizeof(char));

    text.size = buffer_filling(&buffer, f);

    text.str = (struct String*)calloc(text.size, sizeof(struct String*));

    text_filling(&buffer, &text);

    qsort(text.str, text.size, sizeof(struct String),Cmp_reverse_order);

    free(buffer.str);
    free(text.str);
}
