#include "UTL/UTL.h"

int main() {

    // strint to be split
    UTL_String *s = UTL_StringCreate("Hello World and hello sun", -1);

    // list that will store split results
    UTL_List *l = UTL_ListCreate(UTL_ARRAY_LIST, NULL, true);

    // perform split
    UTL_StringSplitOnAny(s, " ", false, (void(*)(void*,void*))&UTL_ListPushBack, l);

    // print splits
    printf("len=%02i [", l->count);
    UTL_ListIter iter = UTL_ListGetIteratorFront(l);
    while (UTL_ListIterIsValid(&iter)) {
        UTL_String *word = UTL_ListIterGet(&iter);
        printf("\"%s\"", word->buf);
        if (UTL_ListIterHasNext(&iter)) printf(", ");
        UTL_ListIterNext(&iter);
    }
    printf("]\n");

/*
    // clean up
    while (l->count) {
        UTL_String *word = UTL_ListGetBack(l);
        (void) UTL_StringDestroy(word);
        UTL_ListPopBack(l);
    }
*/
    UTL_ListDestroy(l);
    s = UTL_StringDestroy(s);
    
    return 0;
}