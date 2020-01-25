#include <stdbool.h>
#define ALPHABET_SIZE 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])


struct node* getNode();
void insertNode(struct node* root,char *key);
bool search(struct node* root,char *key);
bool isLeaf(struct node* root);
void display(struct node* root, char str[], int level);
void displayR(struct node* root, char str[], int level);
void freeALL(struct node* root);