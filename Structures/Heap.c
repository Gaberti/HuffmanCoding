#include "Heap.h"

//Cria um  Nó de Huffman e o inicializa.
Node* newNode(char s, int freq){

	Node* temp = (Node*)malloc(sizeof(Node));
		
	temp->left = temp->right = NULL;
	temp->symbol = s;
	temp->frequency = freq;
	temp->code = NULL;

	return temp;
}

//Libera um Nó de Huffman. 
Node* freeNode(Node* node) {
	if (node == NULL) {
		return NULL;
	}
	node->left = freeNode(node->left);
	node->right = freeNode(node->right);
	if (node->code != NULL) {
		free(node->code);
		node->code = NULL;
	}
	free(node);
	return NULL;
}

//Cria um MinHeap e o Inicializa.
Heap *newMinHeap(unsigned capacity){
	Heap *minHeap = (Heap *)malloc(sizeof(Heap));

	minHeap->size = 0;

	minHeap->capacity = capacity;

	minHeap->array = (Node **)malloc(minHeap->capacity * sizeof(Node *));

	return minHeap;
}

//Libera um MinHeap. 
Heap *freeMinHeap(Heap* heap){
	for (int i = 0; i < heap->size; i++) {
		freeNode(heap->array[i]);
	}
	free(heap->array);
	free(heap);
	return NULL;
}

//Checa se o tamanho da fila/heap é 1, ou seja se chegamos ao fiz
//da inserção na árvore.
//Retorna 1 caso o tamanho seja 1 e 0 caso não seja.
int checkSizeOne(Heap *minHeap){
		return (minHeap->size == 1);
}

//Troca o apontamento de dois Nós.
void swapNode(Node **a, Node **b){
	Node *temp = *a;
	*a = *b;
	*b = temp;
}

//Realiza o heapify no vetor de Nós para transformalo em um MinHeap
void minHeapify(Heap *minHeap, int i){
	int smallest = i;
	int left = (2 * i) + 1;
	int right = (2 * i) + 2;

  if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
	smallest = left;

  if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
	smallest = right;

  if (smallest != i) {
	swapNode(&minHeap->array[smallest], &minHeap->array[i]);
	minHeapify(minHeap, smallest);
  }
}

//Constroe o minHeap utilizando-se dos membros do vetor que tem filhos, começando
//do ultimo nó a ter filhos dentro do vetor
void buildMinHeap(Heap *minHeap){

	int n = minHeap->size - 1;

  for (int i = (n - 1)/2; i >= 0; i--){
	minHeapify(minHeap, i);
  }
}

//Cria o minHeap, insere os nós dentro de seu vetor e chama o método buildMinHeap
Heap *createAndBuildMinHeap(char symbol[], int frequency[], int size) {

  Heap *minHeap = newMinHeap(size);

  for (int i = 0; i < size; i++){
	minHeap->array[i] = newNode(symbol[i], frequency[i]);
  }

  minHeap->size = size;
  buildMinHeap(minHeap);

  return minHeap;
}