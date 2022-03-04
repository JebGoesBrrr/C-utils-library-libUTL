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
    { "removeAny",    &testStringRemoveAny },
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