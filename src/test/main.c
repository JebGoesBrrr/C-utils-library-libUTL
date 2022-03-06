#include "utl_string.h"
#include "utl_list.h"


static TestClassEntry allTests[] = {
    { "UTL_String", (TestFuncEntry*) &UTL_StringTests },
    { "UTL_List",   (TestFuncEntry*) &UTL_ListTests },
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

        printf("\n");
    }

    printf("\n------------------------------------------\n");
    printf(" % 3i passed\n % 3i failed\n", numPassed, numFailed);

    return 0;
}
