#include "UTL/UTL.h"

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    UTL_String *s = UTL_CreateString("Hello", -1);
    s = UTL_AppendToString(s, " ", -1);
    s = UTL_AppendToString(s, "World", -1);

    printf("%s\n", s->buf);

    s = UTL_DestroyString(s);

    s = UTL_CreateString("x  y   z   xyz   ", -1);

    int i;

    printf("-----------------------\n");
    i = UTL_FindFirstOfAnyInString(s, "xyz", 0);
    while (i >= 0) {
        printf("found @ pos %i\n", i);
        i = UTL_FindFirstOfAnyInString(s, "xyz", i + 1);
    }

    printf("-----------------------\n");
    i = UTL_FindFirstOfAllInString(s, "xyz", 0);
    while (i >= 0) {
        printf("found @ pos %i\n", i);
        i = UTL_FindFirstOfAllInString(s, "xyz", i + 1);
    }

    printf("-----------------------\n");
    i = UTL_FindLastOfAnyInString(s, "xyz", s->length - 1);
    while (i >= 0) {
        printf("found @ pos %i\n", i);
        i = UTL_FindLastOfAnyInString(s, "xyz", i - 1);
    }

    printf("-----------------------\n");
    i = UTL_FindLastOfAllInString(s, "xyz", s->length - 1);
    while (i >= 0) {
        printf("found @ pos %i\n", i);
        i = UTL_FindLastOfAllInString(s, "xyz", i - 1);
    }

    printf("-----------------------\n");
    s = UTL_CreateString("Hello World!", -1);
    UTL_String *s2 = UTL_DuplicateString(s);
    printf("%s\n", s2->buf);

    return 0;
}