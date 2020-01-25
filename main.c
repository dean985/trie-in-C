#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "trie.h"

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

size_t parseString( const char *in, char ***word) {
    
    const char *pArr = in;
    
    size_t n = 0;

    while(*pArr) {

        while(isspace((unsigned char)*pArr)){
            ++pArr;
        }

        n += *pArr != '\0';
        while(*pArr && !isspace((unsigned char)*pArr)){
            ++pArr;
        } 
    }

    if (n) {
        size_t i = 0;
        *word = malloc(n * sizeof(char *)); 
        pArr = in;
        
        while (*pArr) {

            while(isspace((unsigned char)*pArr)){
                ++pArr;
            } 
            if (*pArr)  {
                const char *almost = pArr;
                while(*pArr && !isspace((unsigned char)*pArr)){
                    ++pArr;
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
	struct node *root = getNode();		// initialize the trie
    if (!root) {
        exit(1);
    }
    char ch;
	char* in = NULL;
	char** word = NULL;
	
	in = (char*)malloc( sizeof(char) );
	
	int m=1;
    
    int n=0; 
	
	
 	while((ch = fgetc(stdin)) != EOF) {
   	 	in = (char*)realloc(in, m + sizeof(char));		// reallocate memory as needed, the length of the string is increasing
   	 	in[n] = ch;	
  	  	n++;
  	  	m++;
  	  	
  	}
  	in[n] = '\0'; 
	//formatting the input.
	validator(in);	
	//now parsing it.
    size_t s = parseString(in, &word);
	// what we need is in s now, then we free the memory of input
	free(in);

	//inserting word to the trie.
	for(int i = 0 ; i < s ; i++) {
		char* letter = word[i];
		insertWord(root,letter);

	}
	int j=0;
	char temp[s];

	if(argc!=2){
        show(root,temp,j);
    } 
	if(*argv[1]=='r' && argc==2 ) {
        showR(root,temp,j);
    }
	
	printf("\n\n");
	
   	for ( size_t i = 0; i < s; i++ ){
        free ( word[i] );
    } 
    free( word );
	FREE(root);

return 0;
}
