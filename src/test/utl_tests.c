#include "UTL/UTL.h"

#define assertPass(cond) pass = pass && (cond)


static bool testStringCreate(void) {
    bool pass = true;
    UTL_String *s = NULL;

    s = UTL_CreateString(NULL, -1);
    assertPass(strcmp(s->buf, "") == 0);
    assertPass(s->length == 0);
    s = UTL_DestroyString(s);

    s = UTL_CreateString("Hello World", -1);
    assertPass(strcmp(s->buf, "Hello World") == 0);
    assertPass(s->length == strlen("Hello World"));
    s = UTL_DestroyString(s);

    s = UTL_CreateString("Hello World", 0);
    assertPass(strcmp(s->buf, "") == 0);
    assertPass(s->length == 0);
    s = UTL_DestroyString(s);

    s = UTL_CreateString("Hello World", 3);
    assertPass(strcmp(s->buf, "Hel") == 0);
    assertPass(s->length == strlen("Hel"));
    s = UTL_DestroyString(s);

    return pass;
}

static bool testStringDuplicate(void) {
    bool pass = true;
    UTL_String *s1, *s2;

    s1 = UTL_CreateString("Hello World", -1);
    s2 = UTL_DuplicateString(s1);
    assertPass(s1->length == s2->length);
    assertPass(s1 != s2);
    assertPass(strcmp(s1->buf, s2->buf) == 0);
    UTL_DestroyString(s1);
    UTL_DestroyString(s2);

    s1 = UTL_CreateString("", 0);
    s2 = UTL_DuplicateString(s1);
    assertPass(s1->length == s2->length);
    assertPass(s1 != s2);
    assertPass(strcmp(s1->buf, s2->buf) == 0);
    UTL_DestroyString(s1);
    UTL_DestroyString(s2);

    return pass;
}

static bool testStringSubstring(void) {
    bool pass = true;
    UTL_String *s1, *s2;

    s1 = UTL_CreateString("Hello World", -1);
    s2 = UTL_Substring(s1, 0, strlen("Hello"));
    assertPass(strcmp(s2->buf, "Hello") == 0);
    assertPass(s2->length == strlen("Hello"));
    UTL_DestroyString(s1);
    UTL_DestroyString(s2);

    s1 = UTL_CreateString("Hello World", -1);
    s2 = UTL_Substring(s1, -5, strlen("Hello"));
    assertPass(strcmp(s2->buf, "Hello") == 0);
    assertPass(s2->length == strlen("Hello"));
    UTL_DestroyString(s1);
    UTL_DestroyString(s2);

    s1 = UTL_CreateString("Hello World", -1);
    s2 = UTL_Substring(s1, 0, 5000);
    assertPass(strcmp(s2->buf, "Hello World") == 0);
    assertPass(s2->length == strlen("Hello World"));
    UTL_DestroyString(s1);
    UTL_DestroyString(s2);

    s1 = UTL_CreateString("Hello World", -1);
    s2 = UTL_Substring(s1, strlen("Hello "), strlen("World"));
    assertPass(strcmp(s2->buf, "World") == 0);
    assertPass(s2->length == strlen("World"));
    UTL_DestroyString(s1);
    UTL_DestroyString(s2);

    return pass;
}

static bool testStringSubstringRev(void) {
    bool pass = true;
    UTL_String *s1, *s2;

    s1 = UTL_CreateString("Hello World", -1);
    s2 = UTL_SubstringRev(s1, 0, strlen("Hello"));
    assertPass(strcmp(s2->buf, " World") == 0);
    assertPass(s2->length == strlen(" World"));
    UTL_DestroyString(s1);
    UTL_DestroyString(s2);

    s1 = UTL_CreateString("Hello World", -1);
    s2 = UTL_SubstringRev(s1, -5, strlen("Hello"));
    assertPass(strcmp(s2->buf, " World") == 0);
    assertPass(s2->length == strlen(" World"));
    UTL_DestroyString(s1);
    UTL_DestroyString(s2);

    s1 = UTL_CreateString("Hello World", -1);
    s2 = UTL_SubstringRev(s1, 0, 5000);
    assertPass(strcmp(s2->buf, "") == 0);
    assertPass(s2->length == strlen(""));
    UTL_DestroyString(s1);
    UTL_DestroyString(s2);

    s1 = UTL_CreateString("Hello World", -1);
    s2 = UTL_SubstringRev(s1, strlen("Hello "), strlen("World"));
    assertPass(strcmp(s2->buf, "Hello ") == 0);
    assertPass(s2->length == strlen("Hello "));
    UTL_DestroyString(s1);
    UTL_DestroyString(s2);

    return pass;
}

static bool testStringInsert(void) {
    bool pass = true;
    UTL_String *s;

    s = UTL_CreateString("", -1);
    s = UTL_AppendToString(s, "Hello", -1);
    s = UTL_AppendToString(s, " World", 1);
    s = UTL_AppendToString(s, "World", strlen("World"));
    assertPass(strcmp(s->buf, "Hello World") == 0);
    s = UTL_DestroyString(s);

    s = UTL_CreateString("", -1);
    s = UTL_PrependToString(s, "World", -1);
    s = UTL_PrependToString(s, "    ", 1);
    s = UTL_PrependToString(s, "Hello", strlen("Hello"));
    assertPass(strcmp(s->buf, "Hello World") == 0);
    s = UTL_DestroyString(s);

    s = UTL_CreateString("", -1);
    s = UTL_InsertToString(s, 0, "Hd", -1);
    s = UTL_InsertToString(s, 1, "ello Worl", -1);
    assertPass(strcmp(s->buf, "Hello World") == 0);
    s = UTL_DestroyString(s);

    return pass;
}

static bool testFindFirstOfAny(void) {
    bool pass = true;
    UTL_String *s;

    s = UTL_CreateString("aaaxaaayaaazaaaxyzaaa", -1);
    int i = UTL_FindFirstOfAnyInString(s, "xyz", 0);
    assertPass(i == 3);
    i = UTL_FindFirstOfAnyInString(s, "xyz", 1);
    assertPass(i == 3);
    i = UTL_FindFirstOfAnyInString(s, "xyz", 2);
    assertPass(i == 3);
    i = UTL_FindFirstOfAnyInString(s, "xyz", 3);
    assertPass(i == 3);
    i = UTL_FindFirstOfAnyInString(s, "xyz", 4);
    assertPass(i == 7);
    i = UTL_FindFirstOfAnyInString(s, "xyz", 8);
    assertPass(i == 11);
    i = UTL_FindFirstOfAnyInString(s, "xyz", 12);
    assertPass(i == 15);
    i = UTL_FindFirstOfAnyInString(s, "xyz", 16);
    assertPass(i == 16);
    i = UTL_FindFirstOfAnyInString(s, "xyz", 17);
    assertPass(i == 17);
    i = UTL_FindFirstOfAnyInString(s, "xyz", 18);
    assertPass(i < 0);
    UTL_DestroyString(s);

    return pass;
}

static bool testStringRemove(void) {
    bool pass = true;
    UTL_String *s;

    s = UTL_CreateString("Hello World", -1);
    UTL_RemoveFromString(s, 0, strlen("Hello"));
    assertPass(strcmp(s->buf, " World") == 0);
    assertPass(s->length == strlen(" World"));
    UTL_DestroyString(s);

    s = UTL_CreateString("Hello World", -1);
    UTL_RemoveFromString(s, -5, strlen("Hello"));
    assertPass(strcmp(s->buf, " World") == 0);
    assertPass(s->length == strlen(" World"));
    UTL_DestroyString(s);

    s = UTL_CreateString("Hello World", -1);
    UTL_RemoveFromString(s, 0, 5000);
    assertPass(strcmp(s->buf, "") == 0);
    assertPass(s->length == strlen(""));
    UTL_DestroyString(s);

    s = UTL_CreateString("Hello World", -1);
    UTL_RemoveFromString(s, strlen("Hello "), strlen("World"));
    assertPass(strcmp(s->buf, "Hello ") == 0);
    assertPass(s->length == strlen("Hello "));
    UTL_DestroyString(s);

    s = UTL_CreateString("Hello World", -1);
    UTL_RemoveFromString(s, 0, 1);
    assertPass(strcmp(s->buf, "ello World") == 0);
    assertPass(s->length == strlen("ello World"));
    UTL_RemoveFromString(s, 1, 1);
    assertPass(strcmp(s->buf, "elo World") == 0);
    assertPass(s->length == strlen("elo World"));
    UTL_DestroyString(s);

    return pass;
}

static bool testStringRemoveAny(void) {
    bool pass = true;
    UTL_String *s;

    s = UTL_CreateString("aaaxaaayaaazaaaxyzaaa", -1);
    UTL_RemoveAnyFromString(s, "xyz");
    assertPass(strcmp(s->buf, "aaaaaaaaaaaaaaa") == 0);
    assertPass(s->length == 15);
    for (int i = 0; i < s->length; i++)
        assertPass(s->buf[i] == 'a');
    UTL_DestroyString(s);

    return pass;
}

static bool testStringTrim(void) {
    bool pass = true;
    UTL_String *s;

    s = UTL_CreateString("xyzxyzHello Worldxyzxyz", -1);
    int removed = UTL_TrimString(s, "xyz");
    assertPass(strcmp(s->buf, "Hello World") == 0);
    assertPass(s->length == strlen("Hello World"));
    assertPass(removed == strlen("xyz") * 4);
    s = UTL_DestroyString(s);

    return pass;
}

static bool testStringGroup(void) {
    bool pass = true;
    UTL_String *s;

    s = UTL_CreateString("xyzHellozyxWorldyxz", -1);
    int removed = UTL_GroupString(s, "xyz", false);
    assertPass(removed == 2 * 3);
    assertPass(s->length == strlen("HelloWorld") + 3);
    assertPass(strcmp(s->buf, "xHellozWorldy") == 0);
    s = UTL_DestroyString(s);

    s = UTL_CreateString("xyzHellozyxWorldyxz", -1);
    removed = UTL_GroupString(s, "xyz", true);
    assertPass(removed == 2 * 3);
    assertPass(s->length == strlen("HelloWorld") + 3);
    assertPass(strcmp(s->buf, "xHelloxWorldx") == 0);
    s = UTL_DestroyString(s);

    return pass;
}

static UTL_String* splitBuffer[16];
static int splitBufferCount;
static void splitCallback(void *aux, void *substr) {
    (void)aux;
    splitBuffer[splitBufferCount++] = substr;
}

static bool testStringSplitAny(void) {
    bool pass = true;
    UTL_String *s;
    int num;

    splitBufferCount = 0;
    s = UTL_CreateString("YaaaXaaXaXaYX", -1);
    num = UTL_SplitStringAtAny(s, "XY", false, &splitCallback, NULL);
    assertPass(num == 4);
    assertPass(splitBufferCount == 4);
    assertPass(stricmp(splitBuffer[0]->buf, "aaa") == 0);
    assertPass(stricmp(splitBuffer[1]->buf, "aa") == 0);
    assertPass(stricmp(splitBuffer[2]->buf, "a") == 0);
    assertPass(stricmp(splitBuffer[3]->buf, "a") == 0);
    for (int i = 0; i < 4; i++)
        splitBuffer[i] = UTL_DestroyString(splitBuffer[i]);
    splitBufferCount = 0;


    num = UTL_SplitStringAtAny(s, "XY", true, &splitCallback, NULL);
    assertPass(num == 7);
    assertPass(splitBufferCount == 7);
    assertPass(stricmp(splitBuffer[0]->buf, "") == 0);
    assertPass(stricmp(splitBuffer[1]->buf, "aaa") == 0);
    assertPass(stricmp(splitBuffer[2]->buf, "aa") == 0);
    assertPass(stricmp(splitBuffer[3]->buf, "a") == 0);
    assertPass(stricmp(splitBuffer[4]->buf, "a") == 0);
    assertPass(stricmp(splitBuffer[5]->buf, "") == 0);
    assertPass(stricmp(splitBuffer[6]->buf, "") == 0);
    for (int i = 0; i < 7; i++)
        splitBuffer[i] = UTL_DestroyString(splitBuffer[i]);
    splitBufferCount = 0;

    UTL_DestroyString(s);

    return pass;
}

static bool testStringSplitAtAll(void) {
    bool pass = true;
    UTL_String *s;
    int num;

    splitBufferCount = 0;
    s = UTL_CreateString("YaaaXYaaXaXaYXYXXY", -1);
    num = UTL_SplitStringAtAll(s, "XY", false, &splitCallback, NULL);
    assertPass(num == 3);
    assertPass(splitBufferCount == 3);
    assertPass(stricmp(splitBuffer[0]->buf, "Yaaa") == 0);
    assertPass(stricmp(splitBuffer[1]->buf, "aaXaXaY") == 0);
    assertPass(stricmp(splitBuffer[2]->buf, "X") == 0);
    for (int i = 0; i < 3; i++)
        splitBuffer[i] = UTL_DestroyString(splitBuffer[i]);
    splitBufferCount = 0;


    num = UTL_SplitStringAtAll(s, "XY", true, &splitCallback, NULL);
    assertPass(num == 4);
    assertPass(splitBufferCount == 4);
    assertPass(stricmp(splitBuffer[0]->buf, "Yaaa") == 0);
    assertPass(stricmp(splitBuffer[1]->buf, "aaXaXaY") == 0);
    assertPass(stricmp(splitBuffer[2]->buf, "X") == 0);
    assertPass(stricmp(splitBuffer[3]->buf, "") == 0);
    for (int i = 0; i < 4; i++)
        splitBuffer[i] = UTL_DestroyString(splitBuffer[i]);
    splitBufferCount = 0;

    UTL_DestroyString(s);

    return pass;
}

typedef struct {
    const char *label;
    bool (*func)(void);
} TestFuncEntry;


static TestFuncEntry stringTests[] = {
    { "create",       &testStringCreate },
    { "duplicate",    &testStringDuplicate },
    { "substring",    &testStringSubstring },
    { "substringRev", &testStringSubstringRev },
    { "insert",       &testStringInsert },
    { "firstOfAny",   &testFindFirstOfAny },
    { "remove",       &testStringRemove },
    { "removeAny",    &testStringRemoveAny },
    { "trim",         &testStringTrim },
    { "group",        &testStringGroup },
    { "splitAny",     &testStringSplitAny },
    { NULL, NULL }
};


typedef struct {
    const char *label;
    TestFuncEntry *funcs;
} TestClassEntry;


static TestClassEntry allTests[] = {
    { "string", (TestFuncEntry*) &stringTests},
    { NULL, NULL }
};


int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    int numPassed = 0;
    int numFailed = 0;

    for (int i = 0; allTests[i].label; i++) {
        printf("** run test class '%s'\n", allTests[i].label);

        for (int j = 0; allTests[i].funcs[j].label; j++) {

            printf("  %s ", allTests[i].funcs[j].label);
            int padding = 40 - strlen(allTests[i].funcs[j].label);
            while (padding--) printf(".");

            bool result = allTests[i].funcs[j].func();
            if (result) numPassed++;
            else        numFailed++;
            printf("%s\n", result ? " PASS" : " FAILED");
        }
    }

    printf("\n\n%i passed\n%i failed\n", numPassed, numFailed);

    return 0;
}