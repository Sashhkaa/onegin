#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>
#include "onegin.h"


int main(int argc, char* argv[]) {

    struct Onegin onegin = {};

    const char* input_file =  "test_file.txt";
    const char* output_file = "test_file_w.text";

    if (argc == 3) {

        input_file  = argv[1];
        output_file = argv[2];
    }

    onegin_ctor(&onegin, input_file);

    buble_sort(onegin.text.strings, onegin.text.size, sizeof(struct String), Cmp_Alpha_order);

    //qsort(onegin.text.strings, onegin.text.size, sizeof(struct String), Cmp_reverse_order);
    
    //mergesort(onegin.text.strings, onegin.text.size, sizeof(struct String), Cmp_Alpha_order);
    
    file_for_write(&onegin.text, &onegin.buffer, output_file);

    onegin_dtor(&onegin);
}
