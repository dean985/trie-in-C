#include <stdbool.h>
#define ALPHABET_SIZE 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')


struct node* getNode();
void insertNode(struct node* root,char *key);
bool search(struct node* root,char *key);
bool isLeaf(struct node* root);
void show(struct node* root, char str[], int level);
void showR(struct node* root, char str[], int level);
void FREE(struct node* root);