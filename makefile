PROJECT = Lab_4_checker
OBJ = main.o Trie.o
CC = g++ -std=c++11 -g

all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(CC) -o $@ main.o Trie.o 

main.o: main.cpp Trie.h
	$(CC)  -c $<

Trie.o: Trie.cpp Trie.h
	$(CC)  -c $<

clean:
	rm -f *.o $(PROJECT)

