#include <stddef.h>
#include "main.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <time.h>
#include "Aux_Func.h"

// Legacy global variables
// if used elsewere it MUST be defined as extern
const char polar[] = { "polar" };
const char cartesian[] = { "cartesian" };

// Global variables
// if used elsewere it MUST be defined as extern

const char* face[] = {	"Ace", "Deuce", "Three", "Four", "Five", 
						"Six", "Seven", "Eight", "Nine", "Ten",
						"Jack", "Queen", "King"	};

const char* suit[] = { "Hearts", "Diamonds", "Clubs", "Spades" };

// Mude a string com o caminho (PATH) do diretório do seu projeto.
// Use duas contrabarras para separar os diretórios.
const char Path[] = { "C:\\Repos\\1ELE705_SEM17_S2DeckQueTree\\" };

//void view(ListCardNodePtr lPtr, FILE* cfPtr) {
//
//}

void shuffle(ListCardNodePtr* sPtr) {
	ListCardNodePtr trocaPtr, jumpPtr, trocaAnteriorPtr, jumpAnteriorPtr, trocaProxPtr;
	int N;

	// trocaPtr e jumpPtr recebem o primeiro nó, se existir.
	if (*sPtr == NULL) return;
	trocaAnteriorPtr = NULL;
	trocaPtr = *sPtr;
	jumpAnteriorPtr = NULL;
	jumpPtr = *sPtr;

	while (trocaPtr != NULL) {
		do {
			// Sorteia N entre 1 e 100
			N = randomico(); //rand() % 100 + 1; // Descomente e veja que nunca vai funcionar.
			// jumpPtr percorre N nós-carta na lista de forma circular
			for (; N > 0; N--) {
				jumpAnteriorPtr = jumpPtr;
				jumpPtr = jumpPtr->nextPtr;
				if (jumpPtr == NULL) {
					jumpPtr = *sPtr;
				}
			}
		} while (jumpPtr == trocaPtr || jumpPtr->nextPtr == trocaPtr || trocaPtr->nextPtr == jumpPtr);
		// Troca dos nós-carta
		// Se trocaPtr aponta para o primeiro nó
		if (trocaPtr == *sPtr) {
			// Se o jumpPtr não aponta para o primeiro nó, 
			// pois se apontar para o primeiro nó, então não precisa trocar
			// pois trocaPtr também aponta para o primeiro nó
			//if (jumpPtr != *sPtr) {
				// Troca as ligações dos nós-carta a serem trocados
				trocaProxPtr = trocaPtr->nextPtr;
				trocaPtr->nextPtr = jumpPtr->nextPtr;
				jumpPtr->nextPtr = trocaProxPtr;
				// Refaz as ligações dos nós que apontam para os nós que estão sendo trocados
				jumpAnteriorPtr->nextPtr = trocaPtr;
				*sPtr = jumpPtr;
				// Troca jumpPtr com trocaPtr, pois apontam agora para locais errados
				// Usa trocaProxPtr como buffer
				//trocaProxPtr = trocaPtr;
				//trocaPtr = jumpPtr;
				//jumpPtr = trocaProxPtr;
			//}
		}
		else {
			// jumpPtr caiu no primeiro elemento
			// e jumpAnteriorPtr é o último, óbvio
			if (jumpPtr == *sPtr) {
				trocaProxPtr = trocaPtr->nextPtr;
				trocaPtr->nextPtr = jumpPtr->nextPtr;
				jumpPtr->nextPtr = trocaProxPtr;
				trocaAnteriorPtr->nextPtr = jumpPtr;
				*sPtr = trocaPtr; 
			}
			else {
				// Troca as ligações dos nós-carta a serem trocados
				trocaProxPtr = trocaPtr->nextPtr;
				trocaPtr->nextPtr = jumpPtr->nextPtr;
				jumpPtr->nextPtr = trocaProxPtr;
				// Refaz as ligações dos nós que apontam para os nós que estão sendo trocados
				jumpAnteriorPtr->nextPtr = trocaPtr;
				trocaAnteriorPtr->nextPtr = jumpPtr;
			}
			// Troca jumpPtr com trocaPtr, pois apontam agora para locais errados
			// Usa trocaProxPtr como buffer
			//trocaProxPtr = trocaPtr;
			//trocaPtr = jumpPtr;
			//jumpPtr = trocaProxPtr;
		}
		
		// Troca jumpPtr com trocaPtr, pois apontam agora para locais errados
		// Usa trocaProxPtr como buffer
		trocaProxPtr = trocaPtr;
		trocaPtr = jumpPtr;
		jumpPtr = trocaProxPtr;

		// Próximo elemento a ser trocado
		trocaAnteriorPtr = trocaPtr;
		trocaPtr = trocaPtr->nextPtr;
	}
}

void createOneFr52Deck(ListCardNodePtr* sPtr) {
	int i = 0;
	ListCardNodePtr newPtr, currentPtr;

	// Insere o primeiro nó-carta
	newPtr = malloc(sizeof(ListCardNode));
	if (newPtr == NULL) return;
	newPtr->nextPtr = NULL;
	newPtr->card.face = face[i%13];
	newPtr->card.face_number = i%13 + 1;
	newPtr->card.suit = suit[i/13];
	newPtr->card.suit_number = i/13 + 1;
	currentPtr = newPtr;
	*sPtr = newPtr;
	i++;

	// Insere os nós-carta restantes
	for (; i < 52; i++) {
		newPtr = malloc(sizeof(ListCardNode));
		if (newPtr == NULL) return;
		newPtr->nextPtr = NULL;
		newPtr->card.face = face[i % 13];
		newPtr->card.face_number = i % 13 + 1;
		newPtr->card.suit = suit[i / 13];
		newPtr->card.suit_number = i / 13 + 1;
		currentPtr->nextPtr = newPtr;
		currentPtr = newPtr;
	}
}

// Testa se o deck, cujo endereço é passado para Sptr, é vazio
int isDeckEmpty(ListCardNodePtr sPtr) {
	// NÃO MODIFIQUE O CÓDIGO ACIMA

		// INSIRA SEU CÓDIGO A PARTIR DESTE PONTO

		// NÃO MODIFIQUE O CÓDIGO ABAIXO
}

Card popFromDeck(ListCardNodePtr* sPtr) {
	// NÃO MODIFIQUE O CÓDIGO ACIMA

	// INSIRA SEU CÓDIGO A PARTIR DESTE PONTO

	// NÃO MODIFIQUE O CÓDIGO ABAIXO
}

// Retira uma carta da cabeça ou topo da lista.
Card dequeueFromDeck(ListCardNodePtr* headPtr, ListCardNodePtr* tailPtr) {
	// NÃO MODIFIQUE O CÓDIGO ACIMA

	// INSIRA SEU CÓDIGO A PARTIR DESTE PONTO

	// NÃO MODIFIQUE O CÓDIGO ABAIXO
}

// Insere uma carta na cauda ou na base da lista.
void enqueueOnDeck(ListCardNodePtr* headPtr, ListCardNodePtr* tailPtr, Card card) {
	// NÃO MODIFIQUE O CÓDIGO ACIMA

	// INSIRA SEU CÓDIGO A PARTIR DESTE PONTO

	// NÃO MODIFIQUE O CÓDIGO ABAIXO
}

void insertTreeHandNode(TreeCardNodePtr* tPtr, Card card) {
	// NÃO MODIFIQUE O CÓDIGO ACIMA

		// INSIRA SEU CÓDIGO A PARTIR DESTE PONTO

		// NÃO MODIFIQUE O CÓDIGO ABAIXO
}

// NÃO MODIFIQUE O CÓDIGO ACIMA

//
// CRIE UMA FUNÇÃO PARA INSERÇÃO DE NÓS EM UMA ÁRVORE ONDE CADA NÓ CONTÉM TAMBÉM O
// LINK PARA SEU NÓ PAI.
//

// INSIRA SEU CÓDIGO A PARTIR DESTE PONTO

// NÃO MODIFIQUE O CÓDIGO ABAIXO


// Neste assignment você irá implementar a função recursiva de inserção em uma
// árvore, onde cada nó contém também o link para o nó pai.
// A função deve ser chamada de insertTreeHandNode2. A função original 
// insertTreeHandNode deve ser mantida no projeto e seus testes devem funcionar
// apesar das modificações na estrutura de dados do programa
// Você também deve modificar a estrutura de dados que define o nó da árvore
// para que contenha também o link para o nó pai. Esta estrutura, bem 
// como outras definições, encontram-se em main.h.
// Neste projeto, você também deve criar as funções de teste pra esta nova
// função, seguindo a metodologia TDD (test driven development).
// As funções de teste estão contidas em test.cpp e devem ser organizadas 
// usando o mesmo critério das funções presentes neste arquivo.
// Os pormenores para a confecção deste assignemnt encontram-se na vídeo
// aula da semana 17.


// Este projeto implementa funções para o gerenciamento de cartas de.
// baralho, que podem ser utilizadas para a construção de um jogo.
// 
// As funções a serem construídas são: createOneFr52Deck, shuffle e view.
//
// A função createOneFr52Deck cria um monte contendo as cartas de um baralho
// padrão francês com 52 cartas. O monte de cartas é uma lista dinâmica cujos
// nós são do tipo ListCardNode e o ponteiro para seu nó inicial é do tipo
// ListCardNodePtr.
// Esta função recebe o endereço do ponteiro de uma lista ligada de cartas 
// (ponteiro para o ponteiro do monte) e realiza a inserção das 52 cartas 
// padrão do baralho francês em ordem crescente. A ordem crescente é 
// organizada pelo valor crescente dos nipes e, de forma secundária, pelo valor
// crescente das faces. Assim, os nipes vão de Hearts a Spades e ter valor de 1
// a 4, respectivamente. Estes seguem a sequencia descrita pelo vetor de strings
// constantes suit. O valor da face vai de 1 a 13, onde Ace é 1 e King é 13,
// respectivamente, seguindo a sequencia definida pelo vetor de strings constantes
// face.
// A função createOneFr52Deck recebe como parâmetro o endereço do ponteiro
// para um monte de cartas (ListCardNodePtr*) e cria os 52 nós do monte,
// seguindo a sequencia descrita e usando os vetores de strings face e suit, 
// que são strings globais com valores constantes.
//
//
// A função shuffle embaralha uma dada lista dinâmica de cartas. A função 
// recebe o endereço do ponteiro para o nó inicial de uma lista de cartas.
// A forma como a função deve embaralhar as cartas da seguinte forma:
// Um ponteiro denominado trocaPtr deve ser criado. No início da execução
// da função o ponteiro trocaPtr aponta para o primeiro elemento da lista
// de cartas. Além deste, um ponteiro denominado jumpPtr também deve ser
// criado e, inicialmente, também deve apontar para o primeiro nó da lista.
// Pelo fato da lista ser dinâmica, não há como saber a quantidade de nós
// presentes na lista, a não ser que se percorra a lista até o fim contando
// seus nós. No entanto, percorrer a lista sem realizar alguma tarefa é 
// perda de tempo de processamento útil.
// Assim, inicialmente um número denominado N entre 1 e 100 deve ser 
// sorteado. O jumpPtr deve se deslocar sequencialmente na lista por N nós.
// Caso atinja o final da lista antes de completar os N deslocamentos, 
// o ponteiro jumpPtr deve voltar a apontar para o inicio da lista e 
// continuar se deslocando, até completar os N deslocamentos.
// O nó pontado por jumpPtr deve ser trocado com o nó apontado por trocaPtr
// e o ponteiro trocaPtr deve passar a apontar o próximo elemento da lista.
// O processo se repete com um novo sorteio de N e com o ponteiro jumpPtr
// sendo deslocado circularmente pela lista à partir da última posição
// que havia parado. Assim, jumpPtr fica circulando pela lista após cada
// sorteio de N.
// O elemento apontado por jumpPtr é trocado com o elemento apontado por 
// trocaPtr e trocaPtr é apontado para o próximo nó da lista.
// O processo termina quando trocaPtr chegar ao fim da lista.
//
//
// A função isDeckEmpty verifica se uma dada lista ligada de elementos
// ListCardNode é vazia. O parâmetro de entrada é um ListCardNodePtr
// Se o ponteiro da lista for NULL, deve retornar TRUE, caso contrário 
// deve retornar FALSO.
//
//
// A função popFromDeck retira um elemento da lista ligada de elementos 
// do tipo ListCardNode. O elemento é retirado do início da lista, o qual 
// consideramos que é a cabeça da lista ou o topo da pilha formada por 
// esta lista ligada. O parâmetro de entrada é um ListCardNodePtr* e o 
// parâmetro de retorno padrão da função é um tipo Card.
// O nó sacado (popado) da lista deve ter sua memória liberada antes do retorno
// desta função.
//
//
// A função enqueueOnDeck insere um elemento do tipo Card na cabeça de um Queue 
// definido pelo ponteiro da cabeça (tipo ListCardNodePtr*) e pelo
// ponteiro da cauda (tipo ListCardNodePtr*). Este queue é implementado
// com elementos do tipo ListCardNode alocados dinamicamente e conectados
// na forma de uma lista ligada.
// A função considera que o Queue está vazio se o ponteiro da cabeça
// for nulo, conforme o algoritmo apresentado em aula.
//
//
// A função dequeueOnDeck é a contra parte da função enqueueOnDeck. Esta
// retira um elemento da cauda do Queue e retorna seu componete do tipo
// Card pelo retorno da função.
//
//
// A função insertTreeHandNode insere um elemento do tipo Card em uma 
// árvore binária com elementos do tipo TreeCardNode alocados dinamicamente.
// A função recebe o endereço do ponteiro para uma árvore binária 
// (tipo TreeCardNodePtr*).
// Você deve implementar um algoritmo de inserção recursivo, análogo ao
// apresentado em aula.
//
//










//
// A função view deve imprimir em um arquivo sequencial de texto o conteúdo 
// impresso de uma lista de cartas.
// A impressão no arquivo deve ser feita em duas colunas obedecendo o
// seguinte formato:
//    seven of diamonds   deuce of spades
// onde:
// - A palavra of deve iniciar na coluna 10 e na coluna 30, exatamente.
// - A face da carta deve terminar 1 espaço antes da palavra of.
// - O naipe deve inicial 1 espaço após a palavra of.
// - Um enter deve ser colocado sempre ao final no nipe da segunda coluna.
// - Ao final da impressão, um enter deve ser colocado ao final do
//   nipe da carta impressa.
// São parâmetros passados para a função, o endereço do início do da lista
// (do tipo ListCardNodePtr) e o endereço do arquivo de texto (FILE *) no
// qual será impressa a lista de cartas.
//
