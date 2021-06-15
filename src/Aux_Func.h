#pragma once
#ifndef Aux_Func
#define Aux_Func

#include <stdio.h>
#include <stddef.h>
#include "main.h"
#include "stdlib.h"
#include <time.h>
#include "string.h"

// Prot�tipos de fun��es auxiliares dos testes e do exerc�cio
size_t ReadFileOfOneFr52Deck(ListCardNodePtr* sPtr);
int randomico(void);
size_t readFileOfShuffledFr52Deck(ListCardNodePtr* sPtr);
void IOrd(TreeCardNodePtr treePtr, ListCardNodePtr* headPtr, ListCardNodePtr* tailPtr);

// Prot�tipos de fun��es para constru��o do exerc�cio
size_t createFileOfOneFr52Deck(ListCardNodePtr* sPtr);
size_t fillRandomFile(int* randArray);
size_t saveFileOfShuffledFr52Deck(ListCardNodePtr sPtr);

#endif //Aux_Func