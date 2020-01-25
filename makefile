FLAGS = -Wall -Werror -g

all: frequency

frequency: main.o trie.o
	gcc $(FLAGS) -o frequency main.o trie.o

main.o: main.c trie.h
	gcc $(FLAGS) -c main.c

trie.o: trie.c trie.h
	gcc $(FLAGS) -fPIC -c trie.c

.PHONY: all clean

clean:
	rm -f *.o frequency
