#include "onegin.h"

int onegin_ctor(struct Onegin* onegin, const char* name) {
    onegin->file = open_file(name);

    onegin->buffer.len = size_file(onegin->file);

    onegin->buffer.str = (char*)calloc((onegin->buffer.len + 1), sizeof(char));
    if (onegin->buffer.str == nullptr){
        return CANT_CALLOC_MEMORY_FOR_BUFFER;
    }

    onegin->text.size = buffer_filling(&onegin->buffer, onegin->file);

    onegin->text.strings = (struct String*)calloc(onegin->text.size, sizeof(struct String));
    if (onegin->text.strings == nullptr) {
        return CANT_CALLOC_MEMORY_FOR_TEXT;
    }

    text_filling(&onegin->buffer, &onegin->text);

    fclose(onegin->file);
    onegin->file = nullptr;

    return 0;
}


FILE* open_file(const char* name) {
    FILE* fp = fopen(name,"rb");
    if (fp == nullptr) {
        printf("couldn't be open\n");
    }
    return fp;
}

long size_file(FILE* fp) {
    assert(fp);

    rewind(fp);

    if (fseek(fp, 0, SEEK_END) != 0) {
        return FSEEK_CANT_SET;
    }

    long position = ftell(fp);
    if (position == -1L) {
        return FTELL_CANT_COUNT;
    }

    rewind(fp);

    return position;
}


int buffer_filling(struct String* buffer, FILE* file) {
    assert(buffer);
    assert(file);

    int res = fread(buffer->str, sizeof(char), buffer->len, file);
    if (res != buffer->len) {
        return FREAD_CANT_READ_BUFFER;
    }

    buffer->str[buffer->len] = '\0';

    int count_string  = 0;
    char* current_ptr = buffer->str;

    while ((current_ptr = strchr(current_ptr, '\n')) != nullptr) {
        current_ptr++;
        count_string++;
    }

    return (buffer->str[buffer->len - 1] != '\n') ? count_string + 1 : 
                                                    count_string;
}

void text_filling(struct String* buffer, struct Text* text) {    
    assert(buffer);
    assert(text);
    
    char* current_pointer = buffer->str;
   
    for (size_t i = 0; i < text->size - 1; i++) {
        text->strings[i].str = current_pointer; 
        current_pointer = strchr(current_pointer,'\n');

        if ((current_pointer != buffer->str) && (*(current_pointer - 1) == '\r')) {
            *(current_pointer - 1) = '\0';
            text->strings[i].len = (int)(current_pointer - text->strings[i].str - 1);
        }
        else {
            *(current_pointer) = '\0';
            text->strings[i].len = (int)(current_pointer - text->strings[i].str);
        }

        current_pointer++;
    }

    text->strings[text->size - 1].str = current_pointer; 
    current_pointer = strchr(current_pointer,'\0');

    if ((current_pointer != buffer->str) && (*(current_pointer - 1) == '\n')) {
        if ((current_pointer - 1 != buffer->str) && (*(current_pointer - 2) == '\r')) {
            *(current_pointer - 2) = '\0';
            text->strings[text->size - 1].len = (int)(current_pointer - text->strings[text->size -1].str - 2);
        }
        else {
            *(current_pointer - 1) = '\0';
            text->strings[text->size - 1].len = (int)(current_pointer - text->strings[text->size -1].str - 1);
        }   
    }
    else {
        text->strings[text->size - 1].len = (int)(current_pointer - text->strings[text->size - 1].str);
    }
}

int Cmp_Alpha_order(const void* left_void, const void* right_void) {
    assert(left_void);
    assert(right_void);

    const struct String left_str = *(const struct String*)left_void;
    const char* left = left_str.str;

    const struct String right_str = *(const struct String*)right_void;
    const char* right = right_str.str;

    int it_left = 0;
    int it_right = 0;

    while ((left[it_left] != '\0') && !isalpha(left[it_left])) {
            it_left++;
    }
    while ((right[it_right] != '\0') && !isalpha(right[it_right])) {
            it_right++;
    }

    while ((left[it_left] != '\0' && right[it_right] != '\0') &&  (left[it_left] == right[it_right])) {

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

void buble_sort(void* base, size_t nmemb, size_t size, int (*compar)(const void*,const void*)){
    for (int j = 0; j < nmemb - 1; j++) {
        for(int i = 0; i < nmemb - j - 1; i++) {
            if (Cmp_Alpha_order((char*)base + i * size, (char*)base + (i + 1) * size) > 0) {
                greedy_swap((char*)base + i * size , (char*)base + (i + 1) * size, size);
            }
        }
    }
 }

 void greedy_swap(void* left_str, void* right_str, size_t size) {

    int64_t tmp = 0;
    uint8_t* left  = (uint8_t*)left_str;
    uint8_t* right = (uint8_t*)right_str;

    for (int i = 0; i < (size >> 3); i++) {
        tmp = *(uint64_t*)left;
              *(uint64_t*)left = *(uint64_t*)right;
                                 *(uint64_t*)right = tmp;
        left  += sizeof(uint64_t);
        right += sizeof(uint64_t);
    }
    if (size & 4) {
        tmp = *(uint32_t*)left;
              *(uint32_t*)left = *(uint32_t*)right;
                                 *(uint32_t*)right = (uint32_t)tmp;
        left  += sizeof(uint32_t);
        right += sizeof(uint32_t);
    }
    if (size & 2) {
        tmp = *(uint16_t*)left;
              *(uint16_t*)left = *(uint16_t*)right;
                                 *(uint16_t*)right = (uint16_t)tmp;
        left  += sizeof(uint16_t);
        right += sizeof(uint16_t);
    }
    if (size & 1) {
        tmp = *(uint8_t*)left;
              *(uint8_t*)left = *(uint8_t*)right;
                                *(uint8_t*)right = (uint8_t)tmp;
    }
}

int Cmp_reverse_order(const void* left_void, const void* right_void) {

    assert(left_void);
    assert(right_void);

    const struct String left_str = *(const struct String*)left_void;
    const char* left = left_str.str;

    const struct String right_str = *(const struct String*)right_void;
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

void mergesort(void* base, size_t nmemb, size_t size, int (*compar)(const void*,const void*)) {
    assert(base);

    int rght, rend;
    int i , j , m ;

    void* arr  = calloc(nmemb, size);
 
    for (int k = 1; k < nmemb; k *= 2)
    {
        for (int left = 0; left + k < nmemb; left += k * 2)
        {
            rght = left + k;
            rend = rght + k;

            if (rend > nmemb)
                rend = nmemb;

            m = left; i = left; j = rght;

            while (i < rght && j < rend)
            {
                if (compar((char*)base + i * size, (char*)base + j * size) <= 0)
                {
                    memcpy((char*)arr + m * size, (char*)base + i * size, size); 
                    i++;
                }
                else
                {
                    memcpy((char*)arr + m * size, (char*)base + j * size, size);
                    j++;
                }
                m++;
            }
            while (i < rght)
            {
                memcpy((char*)arr + m * size, (char*)base + i * size, size);
                i++;
                m++;
            }
            while (j < rend)
            {
                memcpy((char*)arr + m * size, (char*)base + j * size, size);
                j++; 
                m++;
            }
            for (m = left; m < rend; m++)
            {
                memcpy((char*)base + m * size, (char*)arr + m * size, size);
            }
        }
    }
    free(arr);
}

void file_for_write(struct Text* text, struct String* buffer, const char* name) {

    FILE* fp = fopen(name,"wb");
    if (fp == nullptr) {
        printf("couldn't be open\n");
    }
    
    for (int i = 0; i < text->size ; i++) {
        fputs(text->strings[i].str, fp);
        fputc('\n', fp);
    }
    
    fclose(fp);
}

void onegin_print(struct Text* text, struct String* buffer, const char* name) {
    FILE* fp = fopen(name,"wb");
    if (fp == nullptr) {
        printf("couldn't be open\n");
    }
    char* current_ptr = buffer->str;
    for (int i = 0; i < text->size - 1; i++) {
        fputs(current_ptr, fp);
        fputc('\n', fp);

        current_ptr = strchr(current_ptr, '\0') + 1;

        if (current_ptr <= buffer->str + buffer->len){
            if (*(current_ptr) == '\n') 
                current_ptr++;
        }
    }
    
    fputs(current_ptr,fp);
    fputc('\n', fp);
    fclose(fp);
}

void onegin_dtor(struct Onegin* onegin) {
    free(onegin->buffer.str);
    onegin->buffer.str = nullptr;
    free(onegin->text.strings);
    onegin->text.strings = nullptr;
}
