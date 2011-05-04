/* DO NOT MODIFY */

#ifndef DICTIONARY_TYPE_H
#define DICTIONARY_TYPE_H

/* We represent dictionaries as multi-branch tree with labelled edges.  Any 
 * path from the root that ends in an edge whose `isTerminal' flag is set is 
 * a valid word in the dictionary.  Dictionary nodes are implicitly
 * represented by a set of edges connected via `sibling' links.
 *
 * Siblings are unordered, but the value of `thisChar` is different for every 
 * edge of a single dictionary node.  Sibling lists and tree paths are 
 * terminated by NULL links.
 */

typedef struct dictEdge *dictLink;
struct dictEdge {
    char     thisChar;		/* character labelling this edge */
    bool     isTerminal;	/* a word may end with character */
    dictLink child;         /* suffix dictionary */
    dictLink sibling;		/* next sibling edge */
};


#endif /* DICTIONARY_TYPE_H */
