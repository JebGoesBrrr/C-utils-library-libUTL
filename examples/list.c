#include "UTL/UTL.h"
#include "memcheck.h"

static void printList1(UTL_List *list) {

    printf("%2i [", list->count);

    for (int i = 0; i < list->count; i++)
        printf("%2i ", *(int*)UTL_ListGet(list, i));

    printf("]\n");
}

static void printList2(UTL_List *list) {

    printf("%2i [", list->count);

    UTL_ListIter iter = UTL_ListGetIteratorFront(list);
    while (UTL_ListIterIsValid(&iter)) {
        printf("%2i ", *(int*) UTL_ListIterGet(&iter));
        UTL_ListIterNext(&iter);
    }

    printf("]\n");
}

static void printList3(UTL_List *list) {

    printf("%2i [", list->count);

    UTL_ListIter iter = UTL_ListGetIteratorBack(list);
    while (UTL_ListIterIsValid(&iter)) {
        printf("%2i ", *(int*) UTL_ListIterGet(&iter));
        UTL_ListIterPrev(&iter);
    }

    printf("]\n");
}

int main() {
    initMallocs();

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

    printList1(l1);
    printList1(l2);
    printList1(l3);
    printList1(l4);

    printf("-----------------------------------------------------\n");

    printList2(l1);
    printList2(l2);
    printList2(l3);
    printList2(l4);

    printf("-----------------------------------------------------\n");

    printList3(l1);
    printList3(l2);
    printList3(l3);
    printList3(l4);

    for (int i = 0; i < l3->count; i++)
        free(UTL_ListGet(l3, i));

    UTL_ListDestroy(l1);
    UTL_ListDestroy(l2);
    UTL_ListDestroy(l3);
    UTL_ListDestroy(l4);

    printMallocs();
    return 0;
}