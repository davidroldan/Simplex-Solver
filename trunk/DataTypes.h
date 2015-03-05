#ifndef _DATATYPES
#define _DATATYPES

#include "Fraction.h"
using namespace std;

const int MAX_TABLEAU = 30;

typedef struct{
	int numRestrictions;
	int numVariables;
	int numVariablesHolgura;
	int numVariablesArtificiales;
	fraction restrictions[MAX_TABLEAU][MAX_TABLEAU];
	fraction restrictionValue[MAX_TABLEAU];
	fraction function[MAX_TABLEAU];
	fraction functionValue;
	int base[MAX_TABLEAU];

	bool twoFases;
	fraction firstFaseFunction[MAX_TABLEAU];
	fraction firstFaseFunctionValue;

	bool hayPivote;
	int pivote_x;
	int pivote_y;
}tableauData;

typedef struct{
	tableauData tableau[MAX_TABLEAU];
	int cont;
	bool maxminMode;
	string variableNames[MAX_TABLEAU];
	string tableauDescription[MAX_TABLEAU];

	bool factible;
	bool integer_factible;
	bool acotado;
	fraction solution[MAX_TABLEAU];
	int numVar;
	bool integerVariable[MAX_TABLEAU];
}simplexTableaux;

typedef struct{
	simplexTableaux sTableaux;
	int leftChild;
	int rightChild;
	int parent;
	bool activeNode;
}simplexTabTree;

#endif