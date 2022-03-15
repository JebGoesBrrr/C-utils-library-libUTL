#include "UTL/UTL.h"
#include "memcheck.h"

int main() {
    initMallocs();

    UTL_List *list = UTL_ListCreate(UTL_ARRAY_LIST, NULL, true);

    UTL_ListPushBack(list, UTL_StringCreate("One", -1));
    UTL_ListPushBack(list, UTL_StringCreate("Two", -1));
    UTL_ListPushBack(list, UTL_StringCreate("Three", -1));
    UTL_ListPushBack(list, UTL_StringCreate("Four", -1));
    UTL_ListPushBack(list, UTL_StringCreate("Five", -1));

    UTL_String *s = UTL_ListFold(list, (void*)&UTL_StringConcat, UTL_StringCreate("", -1));

    printf("[");
    for (UTL_ListIter iter = UTL_ListGetIteratorFront(list); UTL_ListIterIsValid(&iter); UTL_ListIterNext(&iter)) {
        printf("%s", ((UTL_String*)UTL_ListIterGet(&iter))->buf);
        if (UTL_ListIterHasNext(&iter)) printf(", ");
    }
    printf("]\n");

    printf("%s\n", s->buf);

    printMallocs();
    return 0;
}