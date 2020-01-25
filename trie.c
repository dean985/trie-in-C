#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 

#define ALPHABET_SIZE 26 
// takes a char and returns its index in the alphabet
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')        //Only for lower case.

struct node { 
    struct node *children[ALPHABET_SIZE]; 
    int count;
    bool isEndOfWord;   //true if this node is the end of a node
}; 
/**
 * this method returns a new trie node
 */
struct node* getNode() { 
    struct node *nodeP = NULL; 
  
    nodeP = (struct node *)malloc(sizeof(struct node)); 
  
    if (nodeP) { 
        nodeP->isEndOfWord = false; 
        for (int i = 0; i < ALPHABET_SIZE; i++) 
            nodeP->children[i] = NULL; 
    } 
    return nodeP; 
} 

void insertWord(struct node *root,char *key) { 
    int level; 
    int length = strlen(key); 
    int index; 
  
    struct node *current = root; 
  
    for (level = 0; level < length; level++) { 
        index = CHAR_TO_INDEX(key[level]); 
        if (!current->children[index]) {

            current->children[index] = getNode(); 
        }
  
        current = current->children[index]; 
    } 
    current->isEndOfWord = true;        // make the last node the end of word
    current->count+=1;                  // add to the amount of time of the word

    
}

bool isLeaf(struct node* root){
    return (root->isEndOfWord != false);
}

bool search(struct node* root,char* key) { 
    int level; 
    int index; 
    int len = strlen(key);
    struct node* current = root; 
    for (level = 0; level < len; level++) { 
        index = CHAR_TO_INDEX(key[level]); 
        if (!current->children[index]) {

            return false; 
        }
        current = current->children[index]; 
    } 
    return (current->isEndOfWord && current != NULL  ); 
} 
/**
 * print in reverse
 */

void showR(struct node* root, char str[],int level) {  
    if (isLeaf(root)) { 
        str[level] = '\0'; 
        printf("%s %d\n",str,root->count); 
 
    } 
    
    for (int i = ALPHABET_SIZE-1; i >= 0; i--) { 
        if (root->children[i]) { 
            str[level] = i + 'a'; 
            showR(root->children[i], str, level + 1); 
        } 
    } 
} 
/**
 * print regular
 */
void show(struct node* root, char str[], int level) { 
    if (isLeaf(root))  { 
        str[level] = '\0'; 
        printf("%s %d\n",str,root->count); 
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) { 
        if (root->children[i]) { 
            str[level] = i + 'a'; 
            show(root->children[i], str, level + 1); 
        } 
    } 
}
/**
 * free trie memory
 */
void FREE(struct node* root) { 
	if(!root){
        return;
    }    
	for(int i=0;i<ALPHABET_SIZE;i++) {
		FREE(root->children[i]);
	}
	free(root);
}

