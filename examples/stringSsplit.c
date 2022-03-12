#include "UTL/UTL.h"

int main() {

    // string to be split
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


    // string to be split (overlapping matches)
    UTL_String *s2 = UTL_StringCreate("YXYXYXaaaXYXaaXaXaXYXYaXXYX", -1);

    // list that will store split results
    UTL_List *l2 = UTL_ListCreate(UTL_ARRAY_LIST, NULL, true);

    // perform split
    UTL_StringSplitOnAll(s2, "XYX", false, (void(*)(void*,void*))&UTL_ListPushBack, l2);

    // print splits
    printf("len=%02i [", l2->count);
    UTL_ListIter iter2 = UTL_ListGetIteratorFront(l2);
    while (UTL_ListIterIsValid(&iter2)) {
        UTL_String *word = UTL_ListIterGet(&iter2);
        printf("\"%s\"", word->buf);
        if (UTL_ListIterHasNext(&iter2)) printf(", ");
        UTL_ListIterNext(&iter2);
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