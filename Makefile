all:
	gcc -o Testes/Teste1 Testes/Teste1.c File.c Huffman.c Structures/Heap.c Structures/PriorityQueue.c Print.c 
	gcc -o Testes/Teste2 Testes/Teste2.c File.c Huffman.c Structures/Heap.c Structures/PriorityQueue.c Print.c 
	gcc -o Testes/Teste3 Testes/Teste3.c File.c Huffman.c Structures/Heap.c Structures/PriorityQueue.c Print.c 
	#	digite o comando "make test" para iniciar os testes

test:

	./Testes/Teste1
	./Testes/Teste2
	./Testes/Teste3

clean:
	rm Testes/Teste1
	rm Testes/Teste2
	rm Testes/Teste3