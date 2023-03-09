#ifndef ERRORS_H
#define ERRORS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>
#include "errors.h"

struct String {
    char* str = nullptr;
    size_t len = 0;
};

struct Text {
    struct String* strings = nullptr;
    size_t size = 0;
};

struct Onegin {
    FILE* file;
    struct String buffer;
    struct Text text;
};

enum erorrs  {
    WRONG_INPUT_FILE_NAME           = 1,
    WRONG_OUTPUT_FILE_NAME          = 2,
    SIZEFILE_FP_IS_NULLPTR          = 3,
    CANT_CALLOC_MEMORY_FOR_BUFFER   = 4,
    CANT_CALLOC_MEMORY_FOR_TEXT     = 5,
    FREAD_CANT_READ_BUFFER          = 6,
    TEXT_FILLING_BUFFER_NULL        = 7,
    TEXT_FILLING_TEXT_NULL          = 8,
    FSEEK_CANT_SET                  = 9,
    FTELL_CANT_COUNT                = 10,
};
 
FILE* open_file(const char* name);
long size_file(FILE* fp);
int onegin_ctor(struct Onegin* onegin, const char* name); 
int buffer_filling(struct String* buffer, FILE* f);
void text_filling(struct String* buffer, struct Text* text);
void greedy_swap(void* left_str, void* right_str, size_t size);
int Cmp_Alpha_order(const void* left_void, const void* right_void);
void buble_sort(void* base, size_t nmemb, size_t size, int (*compar)(const void*,const void*));
int Cmp_reverse_order(const void* left_void, const void* right_void);
void mergesort(void* base, size_t nmemb, size_t size, int (*compar)(const void*,const void*));
void file_for_write(struct Text* text, struct String* buffer, const char* name);
void onegin_print(struct Text* text, struct String* buffer, const char* name);
void onegin_dtor(struct Onegin* onegin); 

#endif // ERRORS_H
