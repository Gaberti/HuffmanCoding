#include <stdio.h>
#include <string.h>
#include "Structures/Node.h"

void printVetor(int array[], int n); 

int printCharacter(char symbol);

int isLeaf(Node *node); 

int printNode(int frequency, int totalBytes, int compressedBits, char code[]);

int printHCodes(Node* raiz, int totalBytes); 

void printTree(Node* node);