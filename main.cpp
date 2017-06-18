#include <iostream>
#include <cctype>

#include "Trie.h"

int main() 
{
    Trie trie;
    int pattern_number = 1;

    while(trie.InsertPattern(pattern_number)) pattern_number++;
    trie.CreatingLink();
    trie.Search();
}
