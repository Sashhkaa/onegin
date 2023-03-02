//#include "C:\Users\1\Desktop\TX\TXLib.h"
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>
#include "onegin.h"


int main(int argc, char* argv[]) {

    struct Constructor onegin = {};

    char* input_file = nullptr;
    char* output_file = nullptr;

    if (argc == 3) {

        input_file  = argv[1];
        output_file = argv[2];

    }

   // else return 0;

    constructor(&onegin);

    qsort(&onegin.text.str, text.size, sizeof(struct String), Cmp_reverse_order);

    for (int i = 0; i < text.size;

    free(buffer.str);
    free(text.str);
}
