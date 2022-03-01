#include "UTL/UTL_string.h"

#include <string.h>

#define UTL_STRING_INITIAL_CAPACITY 64

static inline int UTL_GrowCapacity(int capacity) {
    return capacity + (capacity >> 1); // capacity *= 1.5
}

static int UTL_ComputeNewStringCapacity(int minLength, int currentCapacity) {
    if (minLength < UTL_STRING_INITIAL_CAPACITY)
        return UTL_STRING_INITIAL_CAPACITY;

    if (currentCapacity < UTL_STRING_INITIAL_CAPACITY)
        currentCapacity = UTL_STRING_INITIAL_CAPACITY;

    while (minLength >= currentCapacity)
        currentCapacity = UTL_GrowCapacity(currentCapacity);
    
    return currentCapacity;
}

UTL_String* UTL_CreateString(const char *from) {
    int fromLength = (from == NULL ? 0 : strlen(from));
    int capacity   = UTL_ComputeNewStringCapacity(fromLength, 0);

    UTL_String *string = (UTL_String*) malloc(sizeof(UTL_String) + sizeof(char) * capacity);

    string->capacity = capacity;
    string->length   = fromLength;

    memcpy(string->buf, from, sizeof(char) * fromLength);
    string->buf[string->length] = 0;

    return string;
}

UTL_String* UTL_DestroyString(UTL_String *string) {
    free(string);
    return NULL;
}

UTL_String* UTL_ReserveString(UTL_String *string, int minLength) {

}

UTL_String* UTL_AppendToString(UTL_String *string, const char *cstr) {
    
}