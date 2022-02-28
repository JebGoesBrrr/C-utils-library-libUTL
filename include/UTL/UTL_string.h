#ifndef UTL_STRING_H
#define UTL_STRING_H

// self growing string buffer
typedef struct {
    int length; // length of content, excluding null terminator
    int capacity; // capacity of buffer
    char buf[]; // buffer (null terminated c-string)
} UTL_String;

// create a new UTL_String and initialze with given c-string
// leave string empty if @from is null
extern UTL_String* UTL_CreateString(const char *from);

// free memory of a given UTL_String. returns null
extern UTL_String* UTL_DestroyString(UTL_String *string);

// make sure the given UTL_String has enough capacity for at least @minLength
// returns the new string (possible relocation)
extern UTL_String* UTL_ReserveString(UTL_String *string, int minLength);

// append the contetns of a given c-string to a UTL_String
// returns the new string (possible relocation)
extern UTL_String* UTL_AppendToString(UTL_String *string, const char *cstr);

#endif // UTL_STRING_H
