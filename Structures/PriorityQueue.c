#include "PriorityQueue.h"

//Retira o nó do topo que é o menor valor dentro do heap ja montado, e rearranja o heap colocando
//o ultimo elemento no topo e fazendo o heapify
Node *extractMin(Heap *heap) {
	Node *temp = heap->array[0];
	if (heap->size < 1) {
		printf("error: heap underflow");
		return NULL;
	}
	heap->array[0] = heap->array[heap->size - 1];
	--heap->size;
	minHeapify(heap, 0);
	return temp;
}

//Insere um nó dentro do heap, aumentando seu tamanho e checando aonde devemos inserir esse nó
//a partir de sua frequencia.
void insertMinHeap(Heap *heap, Node *node) {

	++heap->size;

	int i = heap->size - 1;

	while (i > 0 && node->frequency < heap->array[(i - 1) / 2]->frequency) {
		heap->array[i] = heap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	heap->array[i] = node;
}