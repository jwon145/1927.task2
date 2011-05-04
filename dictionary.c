#include "dictionary.h"
#include "dictionary_type.h"


void initDict();

void insertWordDict(char *word);

void insertWordsDict(wordList words);

bool lookupDict(char *word);

wordList completionsDict(char *word);

void releaseDict();

dictLink getRootDict(); 
