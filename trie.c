#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 

#define ALPHABET_SIZE 26 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')        //Only for lower case

struct node { 
    struct node *children[ALPHABET_SIZE]; 
    int count;
    bool isEndOfWord;   //true if this node is the end of a node
}; 

struct node *getNode() { 
    struct node *nodeP = NULL; 
  
    nodeP = (struct node *)malloc(sizeof(struct node)); 
  
    if (nodeP) { 
        int i; 
        nodeP->isEndOfWord = false; 
        for (i = 0; i < ALPHABET_SIZE; i++) 
            nodeP->children[i] = NULL; 
    } 
    return nodeP; 
} 

void insertNode(struct node *root,char *key) { 
    int level; 
    int length = strlen(key); 
    int index; 
  
    struct node *temp_node = root; 
  
    for (level = 0; level < length; level++) { 
        index = CHAR_TO_INDEX(key[level]); 
        if (!temp_node->children[index]) 
            temp_node->children[index] = getNode(); 
  
        temp_node = temp_node->children[index]; 
    } 
  
    temp_node->isEndOfWord = true; 
    temp_node->count+=1;
}

bool isLeaf(struct node* root){
    return (root->isEndOfWord == true);
}

bool search(struct node *root,char *key) { 
    int level; 
    int length = strlen(key); 
    int index; 
    struct node *temp_node = root; 
    for (level = 0; level < length; level++) { 
        index = CHAR_TO_INDEX(key[level]); 
        if (!temp_node->children[index]) 
            return false; 
        temp_node = temp_node->children[index]; 
    } 
    return (temp_node != NULL && temp_node->isEndOfWord); 
} 

void displayR(struct node* root, char str[],int level) {  
    if (isLeaf(root)) { 
        str[level] = '\0'; 
        printf("%s %d\n",str,root->count); 
 
    } 
    int i; 
    for (i = ALPHABET_SIZE-1; i >= 0; i--) { 
        if (root->children[i]) { 
            str[level] = i + 'a'; 
            displayR(root->children[i], str, level + 1); 
        } 
    } 
} 

void display(struct node* root, char str[], int level) { 
    if (isLeaf(root))  { 
        str[level] = '\0'; 
        printf("%s %d\n",str,root->count); 
    }
    int i; 
    for (i = 0; i < ALPHABET_SIZE; i++) { 
        if (root->children[i]) { 
            str[level] = i + 'a'; 
            display(root->children[i], str, level + 1); 
        } 
    } 
}

void freeALL(struct node* root) { 
	if(!root) return;
	for(int i=0;i<ALPHABET_SIZE;i++) {
		freeALL(root->children[i]);
	}
	free(root);
}

