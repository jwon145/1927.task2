#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dictionary.h"
#include "dictionary_type.h"

// helper function prototypes
dictLink addLetter(char letter);
dictLink ptrToSibling(dictLink currSibling, char letter);
dictLink getSibling(dictLink currSibling, char letter);
void printAll(dictLink curr);
void freeDict(dictLink curr);

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
        curr = ptrToSibling(root, letter);
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
}/*}}}*/

void insertWordsDict(wordList words) {/*{{{*/
    while (words != NULL) {
        insertWordDict(words->word);
        words = words->next;
    }
}/*}}}*/

bool lookupDict(char *word) {/*{{{*/
    dictLink curr;
    int i = 0;
    char letter = *(word + i++);

    if (root == NULL) {
        return False;
    } else {
        curr = getSibling(root, letter);
        if (curr == NULL) {
            return False;
        }
    }

    while (curr != NULL && (letter = *(word + i)) != '\0') {
        if (curr->child == NULL) {
            return False;
        } else {
            curr = getSibling(curr->child, letter);
            if (curr == NULL) {
                return False;
            }
        }
        i++;
    }

    if (curr->isTerminal == True) {
        return True;
    } else {
        return False;
    }
}/*}}}*/

wordList completionsDict(char *word);

void releaseDict() {/*{{{*/
    freeDict(root);
}/*}}}*/

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
    if (currSibling != NULL && currSibling->thisChar == letter) {
        return currSibling;
    }
    while (currSibling->sibling != NULL) {
        if (currSibling->sibling->thisChar == letter) {
            return currSibling->sibling;
        }
        currSibling = currSibling->sibling;
    }
    currSibling->sibling = addLetter(letter);
    return currSibling->sibling;
}/*}}}*/

dictLink getSibling(dictLink currSibling, char letter) {/*{{{*/
    if (currSibling != NULL && currSibling->thisChar == letter) {
        return currSibling;
    }
    while (currSibling->sibling != NULL) {
        if (currSibling->sibling->thisChar == letter) {
            return currSibling->sibling;
        }
        currSibling = currSibling->sibling;
    }
    return NULL;
}/*}}}*/

void printAll(dictLink curr) {/*{{{*/
    if (curr != NULL) {
        if (curr->isTerminal) putchar('*');
        else putchar(' ');
        printf("%c\n", curr->thisChar);
        printAll(curr->child);
        printAll(curr->sibling);
    }
}/*}}}*/

void freeDict(dictLink curr) {/*{{{*/
    if (curr != NULL) {
        freeDict(curr->child);
        freeDict(curr->sibling);
        free(curr);
    }
}/*}}}*/
