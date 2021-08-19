#ifndef NODE
#define NODE

typedef struct HuffmanNode{
	char symbol;
	int frequency;
	char* code;
	struct HuffmanNode* left;
	struct HuffmanNode* right;
}Node, Tree;

#endif