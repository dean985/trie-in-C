all: frequency

frequency: main.o trie.o
	gcc -Wall -o frequency main.o trie.o

main.o: main.c trie.h
	gcc -Wall -c main.c

trie.o: trie.c trie.h
	gcc -Wall -fPIC -c trie.c

.PHONY: all clean

clean:
	rm -f *.o frequency
