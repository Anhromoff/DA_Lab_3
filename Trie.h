#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <cctype>
#include <string>
#include <stdio.h>
#include <queue>
#include <vector>
#include <sstream>
#include <map>

// узел трая
class Node 
{
public:
	friend class Trie;
	Node();

private:
	std::map <std::string, Node*> children; // ассоциативный массив детей
	bool is_leaf;							// является ли листом
	int pattern_number;						// номер образца
	Node* fail_link;						// связь неудач
	Node* exit_link;						// ссылка для прохода по образцам, чье вхождение найдено
};

// трай
class Trie
{
public:
    Trie();						 // конструктор
    bool InsertPattern(int);	 // вставка образца в трай
    void CreatingLink();		 // создание связей неудач
    void Search();				 // поиск
    void DeleteTrie(Node* node); // удаление
    ~Trie();					 // деструктор

private:
    Node* root;			 // корень
    int* pattern_length; // массив длин образцов
    int pattern_amount;  // число образцов
};

// структура для отображения результата
struct Coordinate
{
    int x; // номер слова
	int y; // номер строки
};

#endif
