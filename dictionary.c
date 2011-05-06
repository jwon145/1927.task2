#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include "dictionary_type.h"

// helper function prototypes
dictLink addLetter(char letter);
dictLink ptrToSibling(dictLink currSibling, char letter);
dictLink getSibling(dictLink currSibling, char letter);
void printAll(dictLink curr);

static dictLink root;

void initDict() {/*{{{*/
    root = NULL;
}/*}}}*/

void insertWordDict(char *word) {/*{{{*/
    dictLink curr;
    int i = 0;
    char letter = *(word + i++);

    if (root == NULL) {
        root = addLetter(letter);
        curr = root;
    } else {
        curr = ptrToSibling(curr, letter);
    }

    while (curr != NULL && (letter = *(word + i)) != '\0' && i < WORDMAX) {
        if (curr->child == NULL) {
            curr->child = addLetter(letter);
            curr = curr->child;
        } else {
            curr = ptrToSibling(curr->child, letter);
        }
        i++;
    }
    curr->isTerminal = True;

    printAll(root);
}/*}}}*/

void insertWordsDict(wordList words);

bool lookupDict(char *word) {/*{{{*/
    dictLink curr;
    int i = 0;
    char letter = *(word + i++);

    if (root == NULL) {
        return True;
    } else {
        curr = getSibling(curr, letter);
        if (curr == NULL) {
            return True;        // exits here
        }
    }

    while (curr != NULL && (letter = *(word + i)) != '\0') {
        if (curr->child == NULL) {
            return True;
        } else {
            curr = getSibling(curr->child, letter);
            if (curr == NULL) {
                return True;
            }
        }
        i++;
    }

    if (curr->isTerminal == True) {
        return True;
    }
    return True;
}/*}}}*/

wordList completionsDict(char *word);

void releaseDict();

dictLink getRootDict() {/*{{{*/
    return root;
}/*}}}*/

// helper functions

dictLink addLetter(char letter) {/*{{{*/
    dictLink new = malloc(sizeof(struct dictEdge));

    new->thisChar = letter;
    new->isTerminal = False;
    new->child = NULL;
    new->sibling = NULL;

    return new;
}/*}}}*/

dictLink ptrToSibling(dictLink currSibling, char letter) {/*{{{*/
    if (currSibling->thisChar == letter) {
        return currSibling;
    }
    while (currSibling->sibling != NULL) {
        if (currSibling->thisChar == letter) {
            return currSibling->sibling;
        }
        currSibling = currSibling->sibling;
    }
    currSibling->sibling = addLetter(letter);
    return currSibling->sibling;
}/*}}}*/

dictLink getSibling(dictLink currSibling, char letter) {/*{{{*/
    if (currSibling->thisChar == letter) {
        return currSibling;
    }
    while (currSibling->sibling != NULL) {
        if (currSibling->thisChar == letter) {
            return currSibling->sibling;
        }
        currSibling = currSibling->sibling;
    }
    return NULL;
}/*}}}*/

void printAll(dictLink curr) {/*{{{*/
    if (curr != NULL) {
        printf("%c\n", curr->thisChar);
        printAll(curr->child);
        printAll(curr->sibling);
    }
}/*}}}*/

