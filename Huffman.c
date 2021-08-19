#include "Huffman.h"

#define MAX_TREE_HEIGHT 50


// Constroe a árvore de huffman utilizando do minHeap para criar uma fila de prioridade, assim retirando
//as duas menores ocorrências e montando a árvore a partir de suas folhas.
Node *buildHuffmanTree(char symbol[], int frequency[], int size) {
	Node *left, *right, *top;
	Heap *minHeap = createAndBuildMinHeap(symbol, frequency, size);

	while (!checkSizeOne(minHeap)) {
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		top = newNode('-', left->frequency + right->frequency);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}

	Node *root = extractMin(minHeap);
	minHeap = freeMinHeap(minHeap);
	return root;
}

void getHuffmanCodes(Node* raiz, char arr[], int top){
	if (raiz->left) {
		arr[top] = '0';
		getHuffmanCodes(raiz->left, arr, top + 1);
	}
	if (raiz->right) {
		arr[top] = '1';
		getHuffmanCodes(raiz->right, arr, top + 1);
	}
	if (isLeaf(raiz)) {
		raiz->code = (char *)malloc((top) * sizeof(char));
		strncpy(raiz->code, arr, top);
		raiz->code[top] = 0;
	}
}

//Função que junta as chamadas das funções de contrução
//da árvore de huffman e a impressão dos H codes
void useHuffman(char* filename, int printTreeGraph, int printCodes) {

	printf("Huffman: %s\n", filename);

	char characters[255];
	int frequency[255];
	int size = 0;

	int bytesRead = getBytesFrequency(filename, (char*)&characters, (int*)&frequency, &size);

	Node *raiz = buildHuffmanTree(characters, frequency, size);

	char arr[MAX_TREE_HEIGHT];

	for (int i = 0; i < MAX_TREE_HEIGHT; i++) {
		arr[i] = 0;
	}

	getHuffmanCodes(raiz, arr, 0);

	if (printTreeGraph == 1) {
		printTree(raiz);
	}

	if(printCodes == 1){
		printf(" Char\t| Frequency\t| Bits\t| Rate\t| Compressed\t| Huffman code\n");
		printf("-----------------------------------------------------------------------\n");
		int compressedBits = printHCodes(raiz, bytesRead);
		printf("-----------------------------------------------------------------------\n");
		printf(" Total");
		printNode(bytesRead, bytesRead, compressedBits, "-");
	}

	freeNode(raiz);
}