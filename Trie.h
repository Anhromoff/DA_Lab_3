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

// ���� ����
class Node 
{
public:
	friend class Trie;
	Node();

private:
	std::map <std::string, Node*> children; // ������������� ������ �����
	bool is_leaf;							// �������� �� ������
	int pattern_number;						// ����� �������
	Node* fail_link;						// ����� ������
	Node* exit_link;						// ������ ��� ������� �� ��������, ��� ��������� �������
};

// ����
class Trie
{
public:
    Trie();						 // �����������
    bool InsertPattern(int);	 // ������� ������� � ����
    void CreatingLink();		 // �������� ������ ������
    void Search();				 // �����
    void DeleteTrie(Node* node); // ��������
    ~Trie();					 // ����������

private:
    Node* root;			 // ������
    int* pattern_length; // ������ ���� ��������
    int pattern_amount;  // ����� ��������
};

// ��������� ��� ����������� ����������
struct Coordinate
{
    int x; // ����� �����
	int y; // ����� ������
};

#endif
