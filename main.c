#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "Trie.h"

/**
 * 
 * formats the input.
 */
void validator(char* in){
	int n=0;
    int len = strlen(in);	
	for(int i = 0 ; i <  len ; i++) {
			if(in[i]=='\0') break;

			if(in[i]=='\n') {
				in[n]='\n';
				n++;
			}

            // small letters	
			if(in[i]>96 && in[i]<123) {       
				in[n]=in[i];
                        	n++; 
            }

            // capital letters
			if(in[i]>64 && in[i]<91)  {       
				in[n]=in[i]+32;
				n++; 
			}

			if(in[i]==' ') { 
				in[n] = ' ';
				n++; 
			}		
	}

	in[n]='\0';
}

/**
 * Parsing the string 
 */

size_t string_parser( const char *in, char ***word) {
    
    const char *pArr = in;
    
    size_t n = 0;

    while(*pArr) {

        while(isspace((unsigned char)*pArr)){
            pArr++;
        }

        n += *pArr != '\0';
        while(*pArr && !isspace((unsigned char)*pArr)){
            pArr++;
        } 
    }

    if (n) {
        size_t i = 0;
        *word = malloc(n * sizeof(char *)); 
        pArr = in;
        
        while (*pArr) {

            while(isspace((unsigned char)*pArr)){
                pArr++;
            } 
            if (*pArr)  {
                const char* almost = pArr;
                while(*pArr && !isspace((unsigned char)*pArr)){
                    pArr++;
                } 

                size_t len = pArr - almost;

                (*word)[i] = (char *)malloc(len + 1);
		
                strncpy((*word)[i],almost,len);
                (*word)[i][len] = '\0';

                ++i;
            }
        }           
    }

    return n;
}  



int main(int argc, char* argv[]) {
	struct node* root = getNode();
	//if(root == NULL) exit(1); 
    if (!root) {
        exit(1);
    }
    char ch;
	char* in = NULL;
	char ** word = NULL;
	
	in = (char*)malloc( sizeof(char) );
	
	printf("Enter words:\n");
	int m=1;
    
    int n=0; 
	
	
 	while((ch = fgetc(stdin)) != EOF) {
   	 	in = (char*)realloc(in, m+ sizeof(char));
   	 	in[n] = ch;	
  	  	n++;
  	  	m++;
  	  	
  	}
  	

  	in[n] = '\0'; 
	
	//cleans the input from invalid chars.
	validator(in);	
	
	//puts the input in a word array.
    	size_t s = string_parser(in, &word);
    	
    	//as we dont need the input anymore- we release the memory.
	free(in);
   	

	//each word in the array is inserted to the trie.
	for(int i = 0 ; i < s ; i++) {
		char* letter = word[i];
		insert(root,letter);

	}
	
	int j=0;
	char temp[s];
	if(argc!=2){
        display(root,temp,j);
    } 
	if(argc==2 && *argv[1]=='r') {
        displayR(root,temp,j);
    }
	printf("\n\n");
	
   	for ( size_t i = 0; i < n; i++ ){
        free ( word[i] );
    } 
    free( word );
	freeALL(root);

return 0;
}
