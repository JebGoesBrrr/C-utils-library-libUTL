#include "UTL/UTL_string.h"

UTL_String* UTL_CreateString(const char *from) {
    if (*from == '\0'){
        UTL_String *s = malloc(sizeof(UTL_String));
        s->length = 0;
        s->capacity = 1;
    }
    else {
        char *ptr = from; 
        int initial_cap = 1;
        while (*ptr != '\0'){
            initial_cap += 1;
            ptr += sizeof(char);
        };
        UTL_String *s = malloc(sizeof(UTL_String) + sizeof(char) * initial_cap);
        s->length = initial_cap -1;
        s->capacity = initial_cap;
        // buffer value not set yet
    }
}

UTL_String* UTL_DestroyString(UTL_String *string) {

}

UTL_String* UTL_ReserveString(UTL_String *string, int minLength) {

}

UTL_String* UTL_AppendToString(UTL_String *string, const char *cstr) {
    
}