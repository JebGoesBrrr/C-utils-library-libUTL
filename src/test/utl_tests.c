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


typedef struct {
    const char *label;
    bool (*func)(void);
} TestFuncEntry;


static TestFuncEntry stringTests[] = {
    { "create", &testStringCreate },
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
            printf("  %s\t\t", allTests[i].funcs[j].label);
            bool result = allTests[i].funcs[j].func();
            if (result) numPassed++;
            else        numFailed++;
            printf("%s\n", result ? "PASS" : "FAILED");
        }
    }

    printf("\n\n%i passed\n%i failed\n", numPassed, numFailed);

    return 0;
}