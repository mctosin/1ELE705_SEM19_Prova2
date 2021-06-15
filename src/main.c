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

// Mude a string com o caminho (PATH) do diret�rio do seu projeto.
// Use duas contrabarras para separar os diret�rios.
const char Path[] = { "C:\\Repos\\1ELE705_SEM17_S2DeckQueTree\\" };

//void view(ListCardNodePtr lPtr, FILE* cfPtr) {
//
//}

void shuffle(ListCardNodePtr* sPtr) {
	ListCardNodePtr trocaPtr, jumpPtr, trocaAnteriorPtr, jumpAnteriorPtr, trocaProxPtr;
	int N;

	// trocaPtr e jumpPtr recebem o primeiro n�, se existir.
	if (*sPtr == NULL) return;
	trocaAnteriorPtr = NULL;
	trocaPtr = *sPtr;
	jumpAnteriorPtr = NULL;
	jumpPtr = *sPtr;

	while (trocaPtr != NULL) {
		do {
			// Sorteia N entre 1 e 100
			N = randomico(); //rand() % 100 + 1; // Descomente e veja que nunca vai funcionar.
			// jumpPtr percorre N n�s-carta na lista de forma circular
			for (; N > 0; N--) {
				jumpAnteriorPtr = jumpPtr;
				jumpPtr = jumpPtr->nextPtr;
				if (jumpPtr == NULL) {
					jumpPtr = *sPtr;
				}
			}
		} while (jumpPtr == trocaPtr || jumpPtr->nextPtr == trocaPtr || trocaPtr->nextPtr == jumpPtr);
		// Troca dos n�s-carta
		// Se trocaPtr aponta para o primeiro n�
		if (trocaPtr == *sPtr) {
			// Se o jumpPtr n�o aponta para o primeiro n�, 
			// pois se apontar para o primeiro n�, ent�o n�o precisa trocar
			// pois trocaPtr tamb�m aponta para o primeiro n�
			//if (jumpPtr != *sPtr) {
				// Troca as liga��es dos n�s-carta a serem trocados
				trocaProxPtr = trocaPtr->nextPtr;
				trocaPtr->nextPtr = jumpPtr->nextPtr;
				jumpPtr->nextPtr = trocaProxPtr;
				// Refaz as liga��es dos n�s que apontam para os n�s que est�o sendo trocados
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
			// e jumpAnteriorPtr � o �ltimo, �bvio
			if (jumpPtr == *sPtr) {
				trocaProxPtr = trocaPtr->nextPtr;
				trocaPtr->nextPtr = jumpPtr->nextPtr;
				jumpPtr->nextPtr = trocaProxPtr;
				trocaAnteriorPtr->nextPtr = jumpPtr;
				*sPtr = trocaPtr; 
			}
			else {
				// Troca as liga��es dos n�s-carta a serem trocados
				trocaProxPtr = trocaPtr->nextPtr;
				trocaPtr->nextPtr = jumpPtr->nextPtr;
				jumpPtr->nextPtr = trocaProxPtr;
				// Refaz as liga��es dos n�s que apontam para os n�s que est�o sendo trocados
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

		// Pr�ximo elemento a ser trocado
		trocaAnteriorPtr = trocaPtr;
		trocaPtr = trocaPtr->nextPtr;
	}
}

void createOneFr52Deck(ListCardNodePtr* sPtr) {
	int i = 0;
	ListCardNodePtr newPtr, currentPtr;

	// Insere o primeiro n�-carta
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

	// Insere os n�s-carta restantes
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

// Testa se o deck, cujo endere�o � passado para Sptr, � vazio
int isDeckEmpty(ListCardNodePtr sPtr) {
	// N�O MODIFIQUE O C�DIGO ACIMA

		// INSIRA SEU C�DIGO A PARTIR DESTE PONTO

		// N�O MODIFIQUE O C�DIGO ABAIXO
}

Card popFromDeck(ListCardNodePtr* sPtr) {
	// N�O MODIFIQUE O C�DIGO ACIMA

	// INSIRA SEU C�DIGO A PARTIR DESTE PONTO

	// N�O MODIFIQUE O C�DIGO ABAIXO
}

// Retira uma carta da cabe�a ou topo da lista.
Card dequeueFromDeck(ListCardNodePtr* headPtr, ListCardNodePtr* tailPtr) {
	// N�O MODIFIQUE O C�DIGO ACIMA

	// INSIRA SEU C�DIGO A PARTIR DESTE PONTO

	// N�O MODIFIQUE O C�DIGO ABAIXO
}

// Insere uma carta na cauda ou na base da lista.
void enqueueOnDeck(ListCardNodePtr* headPtr, ListCardNodePtr* tailPtr, Card card) {
	// N�O MODIFIQUE O C�DIGO ACIMA

	// INSIRA SEU C�DIGO A PARTIR DESTE PONTO

	// N�O MODIFIQUE O C�DIGO ABAIXO
}

void insertTreeHandNode(TreeCardNodePtr* tPtr, Card card) {
	// N�O MODIFIQUE O C�DIGO ACIMA

		// INSIRA SEU C�DIGO A PARTIR DESTE PONTO

		// N�O MODIFIQUE O C�DIGO ABAIXO
}

// N�O MODIFIQUE O C�DIGO ACIMA

//
// CRIE UMA FUN��O PARA INSER��O DE N�S EM UMA �RVORE ONDE CADA N� CONT�M TAMB�M O
// LINK PARA SEU N� PAI.
//

// INSIRA SEU C�DIGO A PARTIR DESTE PONTO

// N�O MODIFIQUE O C�DIGO ABAIXO


// Neste assignment voc� ir� implementar a fun��o recursiva de inser��o em uma
// �rvore, onde cada n� cont�m tamb�m o link para o n� pai.
// A fun��o deve ser chamada de insertTreeHandNode2. A fun��o original 
// insertTreeHandNode deve ser mantida no projeto e seus testes devem funcionar
// apesar das modifica��es na estrutura de dados do programa
// Voc� tamb�m deve modificar a estrutura de dados que define o n� da �rvore
// para que contenha tamb�m o link para o n� pai. Esta estrutura, bem 
// como outras defini��es, encontram-se em main.h.
// Neste projeto, voc� tamb�m deve criar as fun��es de teste pra esta nova
// fun��o, seguindo a metodologia TDD (test driven development).
// As fun��es de teste est�o contidas em test.cpp e devem ser organizadas 
// usando o mesmo crit�rio das fun��es presentes neste arquivo.
// Os pormenores para a confec��o deste assignemnt encontram-se na v�deo
// aula da semana 17.


// Este projeto implementa fun��es para o gerenciamento de cartas de.
// baralho, que podem ser utilizadas para a constru��o de um jogo.
// 
// As fun��es a serem constru�das s�o: createOneFr52Deck, shuffle e view.
//
// A fun��o createOneFr52Deck cria um monte contendo as cartas de um baralho
// padr�o franc�s com 52 cartas. O monte de cartas � uma lista din�mica cujos
// n�s s�o do tipo ListCardNode e o ponteiro para seu n� inicial � do tipo
// ListCardNodePtr.
// Esta fun��o recebe o endere�o do ponteiro de uma lista ligada de cartas 
// (ponteiro para o ponteiro do monte) e realiza a inser��o das 52 cartas 
// padr�o do baralho franc�s em ordem crescente. A ordem crescente � 
// organizada pelo valor crescente dos nipes e, de forma secund�ria, pelo valor
// crescente das faces. Assim, os nipes v�o de Hearts a Spades e ter valor de 1
// a 4, respectivamente. Estes seguem a sequencia descrita pelo vetor de strings
// constantes suit. O valor da face vai de 1 a 13, onde Ace � 1 e King � 13,
// respectivamente, seguindo a sequencia definida pelo vetor de strings constantes
// face.
// A fun��o createOneFr52Deck recebe como par�metro o endere�o do ponteiro
// para um monte de cartas (ListCardNodePtr*) e cria os 52 n�s do monte,
// seguindo a sequencia descrita e usando os vetores de strings face e suit, 
// que s�o strings globais com valores constantes.
//
//
// A fun��o shuffle embaralha uma dada lista din�mica de cartas. A fun��o 
// recebe o endere�o do ponteiro para o n� inicial de uma lista de cartas.
// A forma como a fun��o deve embaralhar as cartas da seguinte forma:
// Um ponteiro denominado trocaPtr deve ser criado. No in�cio da execu��o
// da fun��o o ponteiro trocaPtr aponta para o primeiro elemento da lista
// de cartas. Al�m deste, um ponteiro denominado jumpPtr tamb�m deve ser
// criado e, inicialmente, tamb�m deve apontar para o primeiro n� da lista.
// Pelo fato da lista ser din�mica, n�o h� como saber a quantidade de n�s
// presentes na lista, a n�o ser que se percorra a lista at� o fim contando
// seus n�s. No entanto, percorrer a lista sem realizar alguma tarefa � 
// perda de tempo de processamento �til.
// Assim, inicialmente um n�mero denominado N entre 1 e 100 deve ser 
// sorteado. O jumpPtr deve se deslocar sequencialmente na lista por N n�s.
// Caso atinja o final da lista antes de completar os N deslocamentos, 
// o ponteiro jumpPtr deve voltar a apontar para o inicio da lista e 
// continuar se deslocando, at� completar os N deslocamentos.
// O n� pontado por jumpPtr deve ser trocado com o n� apontado por trocaPtr
// e o ponteiro trocaPtr deve passar a apontar o pr�ximo elemento da lista.
// O processo se repete com um novo sorteio de N e com o ponteiro jumpPtr
// sendo deslocado circularmente pela lista � partir da �ltima posi��o
// que havia parado. Assim, jumpPtr fica circulando pela lista ap�s cada
// sorteio de N.
// O elemento apontado por jumpPtr � trocado com o elemento apontado por 
// trocaPtr e trocaPtr � apontado para o pr�ximo n� da lista.
// O processo termina quando trocaPtr chegar ao fim da lista.
//
//
// A fun��o isDeckEmpty verifica se uma dada lista ligada de elementos
// ListCardNode � vazia. O par�metro de entrada � um ListCardNodePtr
// Se o ponteiro da lista for NULL, deve retornar TRUE, caso contr�rio 
// deve retornar FALSO.
//
//
// A fun��o popFromDeck retira um elemento da lista ligada de elementos 
// do tipo ListCardNode. O elemento � retirado do in�cio da lista, o qual 
// consideramos que � a cabe�a da lista ou o topo da pilha formada por 
// esta lista ligada. O par�metro de entrada � um ListCardNodePtr* e o 
// par�metro de retorno padr�o da fun��o � um tipo Card.
// O n� sacado (popado) da lista deve ter sua mem�ria liberada antes do retorno
// desta fun��o.
//
//
// A fun��o enqueueOnDeck insere um elemento do tipo Card na cabe�a de um Queue 
// definido pelo ponteiro da cabe�a (tipo ListCardNodePtr*) e pelo
// ponteiro da cauda (tipo ListCardNodePtr*). Este queue � implementado
// com elementos do tipo ListCardNode alocados dinamicamente e conectados
// na forma de uma lista ligada.
// A fun��o considera que o Queue est� vazio se o ponteiro da cabe�a
// for nulo, conforme o algoritmo apresentado em aula.
//
//
// A fun��o dequeueOnDeck � a contra parte da fun��o enqueueOnDeck. Esta
// retira um elemento da cauda do Queue e retorna seu componete do tipo
// Card pelo retorno da fun��o.
//
//
// A fun��o insertTreeHandNode insere um elemento do tipo Card em uma 
// �rvore bin�ria com elementos do tipo TreeCardNode alocados dinamicamente.
// A fun��o recebe o endere�o do ponteiro para uma �rvore bin�ria 
// (tipo TreeCardNodePtr*).
// Voc� deve implementar um algoritmo de inser��o recursivo, an�logo ao
// apresentado em aula.
//
//










//
// A fun��o view deve imprimir em um arquivo sequencial de texto o conte�do 
// impresso de uma lista de cartas.
// A impress�o no arquivo deve ser feita em duas colunas obedecendo o
// seguinte formato:
//    seven of diamonds   deuce of spades
// onde:
// - A palavra of deve iniciar na coluna 10 e na coluna 30, exatamente.
// - A face da carta deve terminar 1 espa�o antes da palavra of.
// - O naipe deve inicial 1 espa�o ap�s a palavra of.
// - Um enter deve ser colocado sempre ao final no nipe da segunda coluna.
// - Ao final da impress�o, um enter deve ser colocado ao final do
//   nipe da carta impressa.
// S�o par�metros passados para a fun��o, o endere�o do in�cio do da lista
// (do tipo ListCardNodePtr) e o endere�o do arquivo de texto (FILE *) no
// qual ser� impressa a lista de cartas.
//
