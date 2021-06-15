#include "Aux_Func.h"

extern const char Path[];

extern const char* face[];
extern const char* suit[];

size_t ReadFileOfOneFr52Deck(ListCardNodePtr* sPtr) {
	FILE* cfPtr;
	int i = 0;
	ListCardNodePtr newPtr, currentPtr;
	char myPath[100];

	// Abre o arquivo com as cartas do baralho ordenadas
	sprintf(myPath, "%s%s", Path, "Fr52Deck.dat");
	if ((cfPtr = fopen(myPath, "rb")) == NULL) {
		return 1;
	}

	// Insere o primeiro nó-carta
	newPtr = malloc(sizeof(ListCardNode));
	if (newPtr == NULL) return 2;
	// Lê o conteúdo do nó-carta do arquivo e 
	// coloca no primeiro nó-carta
	if (feof(cfPtr)) return 3;
	fread(newPtr, sizeof(ListCardNode), 1, cfPtr);
	// Refaz os ponteiros internos dos nós para a posição
	// atual das strings de face e naipe 
	newPtr->card.face = face[newPtr->card.face_number - 1];
	newPtr->card.suit = suit[newPtr->card.suit_number - 1];
	// Refaz os ponteiros do nó e da lista
	newPtr->nextPtr = NULL;
	currentPtr = newPtr;
	*sPtr = newPtr;
	i++;

	// Insere os nós-carta restantes
	for (; i < 52; i++) {
		newPtr = malloc(sizeof(ListCardNode));
		if (newPtr == NULL) return 2;
		if (feof(cfPtr)) return 3;
		fread(newPtr, sizeof(ListCardNode), 1, cfPtr);
		newPtr->card.face = face[newPtr->card.face_number - 1];
		newPtr->card.suit = suit[newPtr->card.suit_number - 1];
		currentPtr->nextPtr = newPtr;
		currentPtr = newPtr;
	}
	fclose(cfPtr); // Fecha o arquivo
	return 0;
}


// Retorna circularmente cada um dos 300 valores randomicos entre 1 e 100
// recuperados do arquivo RandomVallues.dat
int randomico(void) {
	// Na inicialização do programa, zera as variáveis estáticas
	static int random[300] = { 0 };
	static int i_random = 0;
	static int randomizado = 0;

	FILE* cfPtr;
	int i;
	char myPath[100];

	// Na primeira execução da função, lê o vetor random do arquivo
	if (random[0] == 0) {
		// Lê o vetor random do arquivo de
		// O vetor random recebe valores pseudo randomicos entre 1 e 100
		
		// Abre o arquivo com os números pseudo randômicos entre 1 e 100  
		sprintf(myPath, "%s%s", Path, "RandomValues.dat");
		if ((cfPtr = fopen(myPath, "rb")) == NULL) {
			//Se erro, retorna zero
			return 0;
		}
		// Lê os números e os atribui ao vetor random
		for (i = 0; i < 300; i++) {
			// Se erro, retorna zero
			if (feof(cfPtr)) {
				fclose(cfPtr);
				return 0;
			}
			fread(&random[i], sizeof(int), 1, cfPtr);
		}
		// Fecha o arquivo
		fclose(cfPtr);
	}

	// Devolve o randomico da vez
	randomizado = random[i_random];
	++i_random;
	if (i_random >= 300) i_random = 0;
	return randomizado;

}


// Lê do arquivo ShuffledFr52Deck.dat, cria a lista ligada e
// retorna o ponteiro desta para *sPtr
size_t readFileOfShuffledFr52Deck(ListCardNodePtr* sPtr) {
	FILE* cfPtr;
	int i = 0;
	ListCardNodePtr newPtr, currentPtr;
	char myPath[100];

	// Abre o arquivo com as cartas do baralho ordenadas
	sprintf(myPath, "%s%s", Path, "ShuffledFr52Deck.dat");
	if ((cfPtr = fopen(myPath, "rb")) == NULL) {
		return 1;
	}

	// Insere o primeiro nó-carta
	newPtr = malloc(sizeof(ListCardNode));
	if (newPtr == NULL) {
		fclose(cfPtr);
		return 2;	
	}
	// Lê o conteúdo do nó-carta do arquivo e 
	// coloca no primeiro nó-carta
	if (feof(cfPtr)) {
		fclose(cfPtr);
		return 3;
	}
	fread(newPtr, sizeof(ListCardNode), 1, cfPtr);
	// Refaz os ponteiros internos dos nós para a posição
	// atual das strings de face e naipe 
	newPtr->card.face = face[newPtr->card.face_number - 1];
	newPtr->card.suit = suit[newPtr->card.suit_number - 1];
	// Refaz os ponteiros do nó e da lista
	newPtr->nextPtr = NULL;
	currentPtr = newPtr;
	*sPtr = newPtr;
	i++;

	// Insere os nós-carta restantes
	for (; i < 52; i++) {
		newPtr = malloc(sizeof(ListCardNode));
		if (newPtr == NULL) {
			fclose(cfPtr);
			return 2;
		}
		if (feof(cfPtr)) {
			fclose(cfPtr);
			return 3;
		}
		fread(newPtr, sizeof(ListCardNode), 1, cfPtr);
		newPtr->card.face = face[newPtr->card.face_number - 1];
		newPtr->card.suit = suit[newPtr->card.suit_number - 1];
		currentPtr->nextPtr = newPtr;
		currentPtr = newPtr;
	}
	fclose(cfPtr); // Fecha o arquivo
	return 0;
}

// Funções para o teste de árvores binárias
// Lê Em Ordem da árvore binária e cria uma lista ligada com os valores.
// Os valores estarão ordenados.
void IOrd(TreeCardNodePtr treePtr, ListCardNodePtr* headPtr, ListCardNodePtr* tailPtr) {
	if (treePtr != NULL) {
		IOrd(treePtr->leftPtr, headPtr, tailPtr);
		ListCardNodePtr newNode = (ListCardNodePtr)malloc(sizeof(ListCardNode));
		newNode->card = treePtr->card;
		newNode->nextPtr = NULL;
		if (*headPtr == NULL) {
			*headPtr = newNode;
		}
		else {
			(*tailPtr)->nextPtr = newNode;
		}
		*tailPtr = newNode;
		IOrd(treePtr->rightPtr, headPtr, tailPtr);
	}
}


// Funções para a construção do exercício

// Cria o arquivo Fr52Deck.dat, que contém as 52 cartas de
// um deck de cartas do tipo francês ordenado
size_t createFileOfOneFr52Deck(ListCardNodePtr* sPtr) {
	FILE* cfPtr;
	int i = 0;
	ListCardNodePtr newPtr, currentPtr;

	// Randomiza para a função shuffe, eventualmente
	srand((unsigned int)time(NULL));

	// Cria arquivo com as cartas do baralho ordenadas
	if ((cfPtr = fopen("Fr52Deck.dat", "wb")) == NULL) {
		return 1;
	}

	// Insere o primeiro nó-carta
	newPtr = malloc(sizeof(ListCardNode));
	if (newPtr == NULL) return 2;
	newPtr->nextPtr = NULL;
	newPtr->card.face = face[i % 13];
	newPtr->card.face_number = i % 13 + 1;
	newPtr->card.suit = suit[i / 13];
	newPtr->card.suit_number = i / 13 + 1;
	currentPtr = newPtr;
	*sPtr = newPtr;
	i++;

	// Grava o primeiro nó-carta no arquivo
	fwrite(newPtr, sizeof(ListCardNode), 1, cfPtr);

	// Insere os nós-carta restantes
	for (; i < 52; i++) {
		newPtr = malloc(sizeof(ListCardNode));
		if (newPtr == NULL) return 2;
		newPtr->nextPtr = NULL;
		newPtr->card.face = face[i % 13];
		newPtr->card.face_number = i % 13 + 1;
		newPtr->card.suit = suit[i / 13];
		newPtr->card.suit_number = i / 13 + 1;
		currentPtr->nextPtr = newPtr;
		currentPtr = newPtr;
		// Grava o nó-carta no arquivo
		fwrite(newPtr, sizeof(ListCardNode), 1, cfPtr);
	}
	fclose(cfPtr); // Fecha o arquivo
	return 0;
}


// Escreve uma array com 300 valores randomicos
// entre 1 e 100 no arquivo RandomValues.dat
// Preenche comos mesmos valores um array cujo
// ponteiro é passado.
size_t fillRandomFile(int* randArray) {
	FILE* cfPtr;
	int i, N = 0;

	// Cria arquivo para os números pseudo randômicos
	if ((cfPtr = fopen("RandomValues.dat", "wb")) == NULL) {
		// Se erro, retorna 1;
		return 1;
	}
	// Preenche o arquivo com números pseudo randômicos
	for (i = 0; i < 300; i++) {
		// Sorteia N entre 1 e 100
		N = rand() % 100 + 1;
		randArray[i] = N;
		fwrite(&N, sizeof(int), 1, cfPtr);
	}
	// Fecha o arquivo
	fclose(cfPtr);
	return 0; // Execução OK!
}


// Salva no arquivo ShuffledFr52Deck.dat a lista do Deck de 52 cartas 
// embaralhadas pela função shuffle, que faz uso da função randomico.
size_t saveFileOfShuffledFr52Deck(ListCardNodePtr sPtr) {
	FILE* cfPtr;

	// Cria o arquivo para as cartas embaralhadas
	if ((cfPtr = fopen("ShuffledFr52Deck.dat", "wb")) == NULL) {
		// Se erro, retorna 1;
		return 1;
	}

	// Escreve cada um dos nós-carta do deck no arquivo
	while (sPtr != NULL) {
		fwrite(sPtr, sizeof(ListCardNode), 1, cfPtr);
		sPtr = sPtr->nextPtr;
	}

	// Fecha o arquivo e retorna OK
	fclose(cfPtr);
	return 0;
}
