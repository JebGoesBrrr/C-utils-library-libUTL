#include "UTL/UTL.h"

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    UTL_String *s = UTL_CreateString("Hello");
    s = UTL_AppendToString(s, " ");
    s = UTL_AppendToString(s, "World");

    printf("%s\n", s->buf);

    s = UTL_DestroyString(s);

    return 0;
}