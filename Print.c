#include "Print.h"

//Imprime um vetor recebido de tamanho N
void printVetor(int array[], int n){
	for(int i = 0; i < n; i++){
		printf("%d", array[i]);
	}
	printf("\n");	
}

int printCharacter(char symbol){
	if(symbol == '\n'){
		return printf("\\n");
	}
	if(symbol <= 32 || symbol > 126) {
		return printf("0x%02X", (unsigned char)symbol);
	}
	return printf("%c", symbol);
}

int height(Node* node) {
	if (node == NULL) {
		return 1;
	}
	int left = height(node->left);
	int right = height(node->right);
	return (left > right ? left : right) + 1;
}

//Checa se o Nó recebido é uma folha
int isLeaf(Node *node){
	return (node->left) == 0 && (node->right) == 0;
}

int printNode(int frequency, int totalBytes, int compressedBits, char code[]) {
	int bits = frequency * 8;
	double relativeFrequency = ((double)frequency)/totalBytes;
	double rate = (double)compressedBits/bits;
	printf("\t| %4d (%4.1f%%)\t| %4d\t|%5.1f%%\t| %11d\t| %s\n", frequency, relativeFrequency*100.0, bits, rate*100.0, compressedBits, code);
}

//Imprime a representação da compressão na árvore como H code, imprimindo apenas as folhas 
//que são os caracteres do input
int printHCodes(Node* raiz, int totalBytes){
	if (raiz == NULL) {
		return 0;
	}
	int left = printHCodes(raiz->left, totalBytes);
	int right = printHCodes(raiz->right, totalBytes);
	if (raiz->code != NULL) {
		printf(" ");
		printCharacter(raiz->symbol);
		int compressedBits = raiz->frequency * strlen(raiz->code);
		printNode(raiz->frequency, totalBytes, compressedBits, raiz->code);
		return compressedBits + left + right;
	}
	return left + right;
}

int printTreeRecursive(Node* node, int left) {
	if (node == NULL) {
		printf(" ");
		return 1;
	}

	printf("\x1B[1B");	//down
	int leftLength = printTreeRecursive(node->left, 1);
	printf("\x1B[1A");	//up

	printf("\x1B[94m");	//blue
	int length = printf("%d", node->frequency);
	printf("\x1B[0m");	//reset color
	if (isLeaf(node)) {
		printf("\x1B[%dD\x1B[1B\x1B[93m", length);	//left length times, down, yellow
		printf("\x1B[0m\x1B[%dD\x1B[1A\x1B[%dC", printCharacter(node->symbol), length); //reset, left number of printed chars times, up, right length times
	}
	
	printf("\x1B[1B");	//down
	int rightLength = printTreeRecursive(node->right, 0) + length;
	printf("\x1B[1A");	//up

	if (left != -1) {
		printf("\x1B[1A");	//up
		int c = (left ? rightLength : leftLength);
		printf("\x1B[%dD", rightLength);	//left rightLength times
		if (!left) {
			printf("\x1B[%dD", c);	//left c times
		}
		for (int i = 0; i < c; i++) {
			printf("-");
		}
		if (left) {
			printf("\x1B[%dD", c);	//left c times
		}
		printf("\x1B[92m");	//green
		printf(left ? "0" : "1");
		printf("\x1B[0m");	//reset color
		printf("\x1B[1D\x1B[%dC\x1B[1B", rightLength);	//left, right rightLenght times, down
	}

	return leftLength + rightLength;
}

void printTree(Node* node) {
	 int h = height(node);
	 for (int i = 0; i < h; i++) {
			printf("\n");
	 }
	 for (int i = 0; i < h; i++) {
			printf("\x1B[1A");	//up
	 }
	 printTreeRecursive(node, -1);
	 for (int i = 0; i < h; i++) {
			printf("\n");
	 }
}