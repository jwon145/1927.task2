#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dictionary.h"
#include "dictionary_type.h"

// helper function prototypes
dictLink addLetter(char letter);        // returns a dictLink with letter in it
dictLink ptrToSibling(dictLink currSibling, char letter); // search siblings for letter, makes new sibling if !exist
dictLink getSibling(dictLink currSibling, char letter); // only searches if sibling exists
void getWordsDict(dictLink curr, char *prefix); // recursively goes through subtree w/ prefix root, adding words
void addToWordList(char *word); // called by getWordsDict to add words to a static temp list
void freeDict(dictLink curr); // called by releaseDict to recursively free

static dictLink root;
static wordList tempWLhead; // temporary; I don't want to pass a list through a recursive function just to add to it
static wordList tempWLtail; // see ^

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

wordList completionsDict(char *word) {/*{{{*/
    dictLink curr;
    int i = 0;
    char letter = *(word + i++);

    if (letter != '\0') {
        if (root == NULL) {
            return NULL;
        } else {
            curr = getSibling(root, letter);
            if (curr == NULL) {
                return NULL;
            }
        }

        while (curr != NULL && (letter = *(word + i)) != '\0' && i < WORDMAX) {
            if (curr->child == NULL) {
                return NULL;
            } else {
                curr = getSibling(curr->child, letter);
                if (curr == NULL) {
                    return NULL;
                }
            }
            i++;
        }
        if (curr->isTerminal == True) {
            addToWordList(word);
        }

        curr = curr->child;
    } else {
        curr = root;
    }
    getWordsDict(curr, word);
    wordList list = tempWLhead;
    tempWLhead = NULL;
    tempWLtail = NULL;

    return list;
}/*}}}*/

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

void getWordsDict(dictLink curr, char *prefix) {/*{{{*/
    if (curr != NULL) {
        char *newPrefix = malloc((strlen(prefix) + 2) * sizeof(char));
        strcpy(newPrefix, prefix);
        char temp[] = { curr->thisChar, '\0' };
        strcat(newPrefix, temp);
        if (curr->isTerminal == True) {
            addToWordList(newPrefix);
        }
        getWordsDict(curr->child, newPrefix);
        free(newPrefix);
        getWordsDict(curr->sibling, prefix);
    }
}/*}}}*/

void addToWordList(char *word) {/*{{{*/
    if (tempWLhead == NULL) {
        tempWLhead = malloc(sizeof(struct wlnode));
        tempWLhead->word = malloc((strlen(word) + 1) * sizeof(char));
        strcpy(tempWLhead->word, word);
        tempWLtail = tempWLhead;
    } else {
        tempWLtail->next = malloc(sizeof(struct wlnode));
        tempWLtail->next->word = malloc((strlen(word) + 1) * sizeof(char));
        strcpy(tempWLtail->next->word, word);
        tempWLtail = tempWLtail->next;
    }
}/*}}}*/

void freeDict(dictLink curr) {/*{{{*/
    if (curr != NULL) {
        freeDict(curr->child);
        freeDict(curr->sibling);
        free(curr);
    }
}/*}}}*/
