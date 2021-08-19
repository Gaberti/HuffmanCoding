#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

typedef struct Heap {
	unsigned size;
	unsigned capacity;
	struct HuffmanNode** array;
}Heap, minHeap;

Node* newNode(char s, int freq); 

Node* freeNode(Node* node); 

Heap *newMinHeap(unsigned capacity); 

Heap *freeMinHeap(Heap* heap); 

void swapNode(Node **a,Node **b); 

void minHeapify(Heap *minHeap, int i); 

void buildMinHeap(Heap *minHeap);  

int checkSizeOne(Heap *minHeap); 

Heap *createAndBuildMinHeap(char symbol[], int frequency[], int size); 
