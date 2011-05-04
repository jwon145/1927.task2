#include <stdlib.h>
#include "dictionary.h"
#include "dictionary_type.h"

// helper function prototypes
dictLink addLetter(char letter);

static dictLink root;

void initDict() {
    root = NULL;
}

void insertWordDict(char *word) {
    if (root == NULL) {
        root = addLetter(*word);
    }
}

void insertWordsDict(wordList words);

bool lookupDict(char *word);

wordList completionsDict(char *word);

void releaseDict();

dictLink getRootDict(); 

// helper functions

dictLink addLetter(char letter) {
    dictLink new = malloc(sizeof(struct dictEdge));

    new->thisChar = letter;
    new->isTerminal = False;
    new->child = NULL;
    new->sibling = NULL;

    return new;
}
