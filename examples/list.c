#include "UTL/UTL.h"

static void printList(UTL_List *list) {
    printf("%2i [", list->count);
    for (int i = 0; i < list->count; i++)
        printf("%2i ", *(int*)UTL_ListGet(list, i));
    printf("]\n");
}

int main() {
    UTL_List *l1 = UTL_ListCreate(UTL_ARRAY_LIST,  &UTL_TypeInfoInt, false);
    UTL_List *l2 = UTL_ListCreate(UTL_LINKED_LIST, &UTL_TypeInfoInt, false);
    UTL_List *l3 = UTL_ListCreate(UTL_ARRAY_LIST,  &UTL_TypeInfoInt, true);
    UTL_List *l4 = UTL_ListCreate(UTL_LINKED_LIST, &UTL_TypeInfoInt, true);

    for (int i = 0; i < 16; i++) {
        UTL_ListPushBack(l1, &i);
        UTL_ListPushBack(l2, &i);

        int *pi = malloc(sizeof(int));
        *pi = i;
        UTL_ListPushBack(l3, pi);
        UTL_ListPushBack(l4, pi);
    }

    printList(l1);
    printList(l2);
    printList(l3);
    printList(l4);

    for (int i = 0; i < l3->count; i++)
        free(UTL_ListGet(l3, i));

    UTL_ListDestroy(l1);
    UTL_ListDestroy(l2);
    UTL_ListDestroy(l3);
    UTL_ListDestroy(l4);
    return 0;
}