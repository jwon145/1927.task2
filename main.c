#include <stdio.h>
#include <string.h>
#include "dictionary.h"

int main(int argc, char *argv[])
{   
    char a[] = "abc";
    char b[] = "abc";

    initDict();
    insertWordDict(a);
    if (lookupDict(b) == False) {
        printf("False\n");
    } else {
        printf("True\n");
    }
    

    return 0;
}
