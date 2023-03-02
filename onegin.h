#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

//onegin->structs_arr[i].str
FILE* open_file(const char* name);
int size_file(FILE* fp);
int buffer_filling(struct String* buffer, FILE* f);
struct String {
    char* str = nullptr;
    int len = 0;
};

struct Text {
    struct String* str = nullptr;
    int size = 0;
};

struct Constructor {
    FILE* file;
    struct String buffer;
    struct Text text;
};

void constructor(struct Constructor* onegin) {
    onegin->file = open_file("test_file.txt");
    onegin->buffer.len = size_file(onegin->file);
    printf("main->buffer->len = %d", onegin->buffer.len);
    onegin->buffer.str = (char*)calloc((onegin->buffer.len + 1), sizeof(char));
    onegin->text.size = buffer_filling(&onegin->buffer, onegin->file);
    onegin->text.str = (struct String*)calloc(onegin->text.size, sizeof(struct String*));
}

FILE* open_file(const char* name) {
    FILE* fp = fopen(name,"rb");
    if (fp == nullptr) {
        printf("couldn't be open\n");
    }
    return fp;
}

int size_file(FILE* fp) {
    rewind(fp);

    fseek(fp,0,SEEK_END);

    int position = ftell(fp);

    printf("%ld\n",position);

    rewind(fp);

    return position;
}


int buffer_filling(struct String* buffer, FILE* f) {
    printf("1");
    int count_string = 0;
    int res = fread(buffer->str, sizeof(char), buffer->len, f);
    if (res != buffer->len) {
        return -1;
    }

    buffer->str[buffer->len] = '\0';

    for (size_t i = 0; i < buffer->len; i++) {
        if (buffer->str[i] == '\n') {
            count_string++;
            buffer->str[i] = '\0';
        }
    }
    if (buffer->str[buffer->len - 1] != '\n') {
        return count_string + 1;
    }
    return count_string;
}

void text_filling(struct String* buffer, struct Text* text) {
printf("2");
    char* current_pointer = buffer->str;
    for (size_t i = 0; i < text->size ; i++) {
        text->str[i].str = current_pointer;
        current_pointer = strchr(current_pointer,'\0') + 1;
        text->str[i].len = (int)(current_pointer - text->str[i].str);
    }
}

int Cmp_Alpha_order(const void* left_void, const void* right_void) {

    struct String left_str = *(struct String*)left_void;
    const char* left = left_str.str;

    struct String right_str = *(struct String*)right_void;
    const char* right = right_str.str;

    int it_left = 0;
    int it_right = 0;

    while ((left[it_left] != '\0') && !isalpha(left[it_left])) {
            it_left++;
    }
    while ((right[it_right] != '\0') && !isalpha(right[it_right])) {
            it_right++;
    }

    while ( (left[it_left] != '\0' && right[it_right] != '\0') &&  (left[it_left] == right[it_right])) {

        it_left++;
        it_right++;

        while (!isalpha(left[it_left]) && left[it_left] != '\0' ) {
            it_left++;
        }
        while (!isalpha(right[it_right]) && right[it_right] != '\0') {
            it_right++;
        }
    }

    return left[it_left] - right[it_right];
}

void buble_sort(int (*Cmp_Alpha_order)(const void*,const void*), struct String* str, struct Text* text) {
    for (int j = 0; j < text->size - 1; j++) {
        for(int i = 0; i < text->size - j - 1; i++) {
            if (Cmp_Alpha_order(str[i].str,str[i+1].str) > 0) {
                char* temp = str[i+1].str;
                str[i+1].str = str[i].str;
                str[i].str = temp;
            }
        }
    }
 }

int Cmp_reverse_order(const void* left_void, const void* right_void) {

    struct String left_str = *((struct String*)left_void);
    const char* left = left_str.str;

    struct String right_str = *((struct String*)right_void);
    const char* right = right_str.str;

    int it_left = left_str.len - 1;

    int it_right = right_str.len - 1;

    while (!isalpha(left[it_left])) {
            it_left--;
    }
    while (!isalpha(right[it_right])) {
            it_right--;
    }

    while (left[it_left] == right[it_right]) {
        it_left--;
        it_right--;

        while (!isalpha(left[it_left])) {
            it_left--;
        }
        while (!isalpha(right[it_right])) {
            it_right--;
        }
    }

    return left[it_left] - right[it_right];
}

#endif // ONEGIN_H_INCLUDED

