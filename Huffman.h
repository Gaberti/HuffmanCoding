#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures/PriorityQueue.h"
#include "File.h"
#include "Print.h"

Node *buildHuffmanTree(char symbol[], int freq[], int size); 

void getHuffmanCodes(Node* raiz, char arr[], int top);

void useHuffman(char* filename, int printTreeGraph, int printBoolean);