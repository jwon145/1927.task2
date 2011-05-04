/* DO NOT MODIFY */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#define WORDMAX     80  /* maximum word length */

/* Boolean values
 */
typedef enum {False, True} bool;

#include "dictionary_type.h"

/* Linked list of words
 */
typedef struct wlnode *wordList;
struct wlnode {
  char     *word;
  wordList  next;
};

/* Initialise the dictionary structure
 */
void initDict ();

/* Insert a single word into the dictionary 
 */
void insertWordDict (char *word);

/* Insert a list of words into the dictionary 
 */
void insertWordsDict (wordList words);

/* Check whether a given word is in the dictionary
 */
bool lookupDict (char *word);

/* Extract all words in the dictionary (the order does not matter).
 *
 * Complexity: see constraint in the assignment specification.
 */
wordList completionsDict (char *word);

/* Erase all dictionary entries and release all memory allocated for the
 * dictionary.
 */
void releaseDict ();

/* Return the root of the trie (i.e. dictionary). 
 * If the dictionary is empty, then return NULL. 
 * Otherwise, return the root of the trie. 
 */ 
dictLink getRootDict() ; 

#endif /* DICTIONARY_H */
