#include "stdafx.h" //este include hay que ponerle el primero, sino por alguna razón ignora los otros includes
#include "SimplexAlgorithm.h"
#include "DataTypes.h"
#include "StringUtil.h"

/**
	Compruebo si un problema es infactible si en la última columna aparece algún número negativo
**/
bool factibleProblem(const tableauData &tableau){
	for (int i = 0; i < tableau.numRestrictions; i++){
		if (tableau.restrictionValue[i] < 0)
			return false;
	}
	return true;
}

/**
	Comprueba si la función objetivo ya es óptima
	@param function: funcion objetivo
	@param maxmin: true = max, false = min 
**/
bool optimizedFunction(fraction *function, bool maxmin, int numVariables){
	int a = 1;
	if (maxmin) a = -1;
	for (int i = 0; i < numVariables; i++){
		if (function[i] * a < 0)
			return false;
	}
	return true;
}

/**
	Comprueba que variable entra en la base
**/
int checkWhoEntersOnBase(fraction *function, bool maxmin, int numVariables){
	int a = 1;
	if (maxmin) a = -1;
	int variable = 0;
	fraction value = 0;
	for (int i = 0; i < numVariables; i++){
		if (function[i] * a < value){
			variable = i;
			value = function[i] * a;
		}
	}
	return variable;
}

/**
	Encontrar el mínimo (para el pivote)
**/
fraction getMin(bool *posiblesPivotes, const tableauData &tableau, int vEntrada, int columna){
	fraction min = -1;
	fraction aux;
	for (int i = 0; i < tableau.numRestrictions; i++){
		if (posiblesPivotes[i]){
			if (columna == -1) aux = tableau.restrictionValue[i];
			else aux = tableau.restrictions[i][columna];
			if (min == -1 || min > aux / tableau.restrictions[i][vEntrada])
				min = aux / tableau.restrictions[i][vEntrada];
		}
	}
	return min;
}

/**
	Ver que elementos son iguales que el mínimo, los que no lo sean ya no pueden seguir siendo pivotes
**/
void encontrarPosiblesPivotes(fraction min, bool *posiblesPivotes, int &numPosiblesPivotes, const tableauData &tableau, int vEntrada, int columna){
	fraction aux;
	for (int i = 0; i < tableau.numRestrictions; i++){
		if (posiblesPivotes[i]){
			if (columna == -1) aux = tableau.restrictionValue[i];
			else aux = tableau.restrictions[i][columna];
			if ((aux / tableau.restrictions[i][vEntrada]) - min != 0){ //si no es el mínimo, descartamos como pivote
				posiblesPivotes[i] = false;
				numPosiblesPivotes--;
			}
		}
	}
}
/**
	Búsqueda pivote (regla razón mínima + regla lexicografica)
	Si devuelve -1 entonces es que no se puede hacer pivotaje
**/
int busquedaPivote(int vEntrada, const tableauData &tableau, int *initialBase, bool &razonMinima, bool &lexicografica){
	bool posiblesPivotes[MAX_TABLEAU];
	for (int i = 0; i < tableau.numRestrictions; i++){
		posiblesPivotes[i] = true; //inicializo a true
	}
	int numPosiblesPivotes = tableau.numRestrictions;

	//Descarto <= 0
	for (int i = 0; i < tableau.numRestrictions; i++){
		if (tableau.restrictions[i][vEntrada] <= 0){
			posiblesPivotes[i] = false;
			numPosiblesPivotes--;
		}
	}
	if (numPosiblesPivotes == 0) return -1;
	fraction min;
	for (int k = 0; k < tableau.numRestrictions + 1 && numPosiblesPivotes > 1; k++){
		if (k == 0){
			razonMinima = true; //Simplemente indica que he tenido que utilizar la razón mínima
			min = getMin(posiblesPivotes, tableau, vEntrada, -1);
			encontrarPosiblesPivotes(min, posiblesPivotes, numPosiblesPivotes, tableau, vEntrada, -1);
		}
		else{
			lexicografica = true; //Simplemente indica que he tenido que utilizar la regla lexicográfica
			min = getMin(posiblesPivotes, tableau, vEntrada, initialBase[k - 1]);
			encontrarPosiblesPivotes(min, posiblesPivotes, numPosiblesPivotes, tableau, vEntrada, initialBase[k - 1]);
		}
	}
	//Buscar finalmente cual es el pivote y devolverlo
	for (int i = 0; i < tableau.numRestrictions; i++){
		if (posiblesPivotes[i]){
			return i;
		}
	}
	return 0; //no debería llegar a este return
}

/**
	Actualizamos la base
**/
void updateBase(simplexTableaux &sTableaux, int variableEntrada, int pivote){
	for (int i = 0; i < sTableaux.tableau[sTableaux.cont].numRestrictions; i++){
		sTableaux.tableau[sTableaux.cont].base[i] = sTableaux.tableau[sTableaux.cont - 1].base[i];
	}
	sTableaux.tableau[sTableaux.cont].base[pivote] = variableEntrada;
}

/**
	Hago pivotaje
**/
void pivotaje(simplexTableaux &sTableaux, int variableEntrada, int pivote){
	fraction valorPivote = sTableaux.tableau[sTableaux.cont - 1].restrictions[pivote][variableEntrada];
	fraction aux;
	for (int i = 0; i < sTableaux.tableau[sTableaux.cont].numRestrictions; i++){
		aux = sTableaux.tableau[sTableaux.cont - 1].restrictions[i][variableEntrada];
		for (int j = 0; j <= sTableaux.tableau[sTableaux.cont].numVariables + sTableaux.tableau[sTableaux.cont].numVariablesArtificiales + sTableaux.tableau[sTableaux.cont].numVariablesHolgura; j++){
			if (i == pivote){
				if (j == 0) sTableaux.tableau[sTableaux.cont].restrictionValue[i] = sTableaux.tableau[sTableaux.cont - 1].restrictionValue[i] / valorPivote;
				else sTableaux.tableau[sTableaux.cont].restrictions[i][j - 1] = sTableaux.tableau[sTableaux.cont - 1].restrictions[i][j - 1] / valorPivote;
			}
			else{
				if (j == 0) sTableaux.tableau[sTableaux.cont].restrictionValue[i] = sTableaux.tableau[sTableaux.cont - 1].restrictionValue[i] - sTableaux.tableau[sTableaux.cont - 1].restrictionValue[pivote] / valorPivote * aux;
				else sTableaux.tableau[sTableaux.cont].restrictions[i][j - 1] = sTableaux.tableau[sTableaux.cont - 1].restrictions[i][j - 1] - sTableaux.tableau[sTableaux.cont - 1].restrictions[pivote][j - 1] / valorPivote * aux;
			}
		}
	}
	if (sTableaux.tableau[sTableaux.cont].twoFases){
		aux = sTableaux.tableau[sTableaux.cont - 1].firstFaseFunction[variableEntrada];
		for (int j = 0; j <= sTableaux.tableau[sTableaux.cont].numVariables + sTableaux.tableau[sTableaux.cont].numVariablesArtificiales + sTableaux.tableau[sTableaux.cont].numVariablesHolgura; j++){
			if (j == 0) sTableaux.tableau[sTableaux.cont].firstFaseFunctionValue = sTableaux.tableau[sTableaux.cont - 1].firstFaseFunctionValue - sTableaux.tableau[sTableaux.cont - 1].restrictionValue[pivote] / valorPivote * aux;
			else sTableaux.tableau[sTableaux.cont].firstFaseFunction[j - 1] = sTableaux.tableau[sTableaux.cont - 1].firstFaseFunction[j - 1] - sTableaux.tableau[sTableaux.cont - 1].restrictions[pivote][j - 1] / valorPivote * aux;
		}
	}
	aux = sTableaux.tableau[sTableaux.cont - 1].function[variableEntrada];
	for (int j = 0; j <= sTableaux.tableau[sTableaux.cont].numVariables + sTableaux.tableau[sTableaux.cont].numVariablesHolgura + sTableaux.tableau[sTableaux.cont].numVariablesArtificiales; j++){
		if (j == 0) sTableaux.tableau[sTableaux.cont].functionValue = sTableaux.tableau[sTableaux.cont - 1].functionValue - sTableaux.tableau[sTableaux.cont - 1].restrictionValue[pivote] / valorPivote * aux;
		else sTableaux.tableau[sTableaux.cont].function[j - 1] = sTableaux.tableau[sTableaux.cont - 1].function[j - 1] - sTableaux.tableau[sTableaux.cont - 1].restrictions[pivote][j - 1] / valorPivote * aux;
	}
}

string printPivotaje(simplexTableaux &sTableaux, int variableEntrada, int pivote, bool razonMinima, bool lexicografica){
	string str = "La variable " + sTableaux.variableNames[variableEntrada] + " entra en la base.\r\n";
	if (razonMinima){
		if (lexicografica){
			str += "Hay empate al utilizar la regla de la razón mínima, por lo tanto utilizamos la regla lexicográfica.\r\n";
		}
		else{
			str += "Utilizamos la regla de la razón mínima para ver qué variable sale de la base.\r\n";
		}
	}
	str += "La variable " + sTableaux.variableNames[sTableaux.tableau[sTableaux.cont-1].base[pivote]] + " sale de la base.\r\n";
	return str;
}

string printOptimizedFunction(simplexTableaux &sTableaux){
	string str = "Función objetivo optimizada: Z* = " + systemToStd((-sTableaux.tableau[sTableaux.cont - 1].functionValue).print()) + "; \r\n";
	for (int i = 0; i < sTableaux.numVar; i++){
		str += "X" + systemToStd(System::Convert::ToString(i + 1)) + "* = " + systemToStd(sTableaux.solution[i].print()) +"; ";
	}
	return str;
}

void fillSolution(simplexTableaux &sTableaux){
	for (int i = 0; i < MAX_TABLEAU; i++) sTableaux.solution[i] = 0;
	for (int i = 0; i < sTableaux.tableau[sTableaux.cont - 1].numVariables; i++){
		fraction frac = 0;
		for (int j = 0; j < sTableaux.tableau[sTableaux.cont - 1].numRestrictions; j++){
			if (i == sTableaux.tableau[sTableaux.cont - 1].base[j]){
				frac = sTableaux.tableau[sTableaux.cont - 1].restrictionValue[j];
			}
		}
		string aux_s = sTableaux.variableNames[i];
		char aux_c = aux_s[aux_s.length() - 1];
		if (aux_c == '+'){
			aux_s = aux_s.substr(0, aux_s.length() - 1); //quitamos el +
		}
		else if (aux_c == '-'){
			aux_s = aux_s.substr(0, aux_s.length() - 1); //quitamos el -
			frac = -frac;
		}
		int number = System::Convert::ToInt16(stdToSystem(aux_s.substr(1, aux_s.length() - 1))); //quitamos la x
		sTableaux.solution[number - 1] += frac;
	}
}

bool isSolutionInteger(simplexTableaux &sTableaux){
	for (int i = 0; i < sTableaux.numVar; i++){
		if (sTableaux.integerVariable[i] && sTableaux.solution[i].denominator() != 1) return false;
	}
	return true;
}

void simplex(simplexTableaux &sTableaux){
	bool end = false;
	sTableaux.factible = false;
	sTableaux.integer_factible = false;
	sTableaux.acotado = true;
	while (!end){
		sTableaux.tableauDescription[sTableaux.cont - 1] = "";
		//Primero hacemos comprobaciones con la tabla anterior
		if (!factibleProblem(sTableaux.tableau[sTableaux.cont - 1])){
			sTableaux.tableauDescription[sTableaux.cont - 1] += "PROBLEMA INFACTIBLE (Hay un número negativo en la columna de la derecha).";
			end = true; break; //FIN (INFACTIBLE)
		}
		// Ver si estamos en primera fase. La variable firstFase nos dira en que fase esta la siguiente tabla.
		bool firstFase = false;
		if (sTableaux.tableau[sTableaux.cont - 1].twoFases){
			if (sTableaux.cont == 1)
				sTableaux.tableauDescription[sTableaux.cont - 1] += "METODO DE LAS DOS FASES. \r\n";

			if (optimizedFunction(sTableaux.tableau[sTableaux.cont-1].firstFaseFunction, false, sTableaux.tableau[sTableaux.cont-1].numVariables + sTableaux.tableau[sTableaux.cont - 1].numVariablesHolgura + sTableaux.tableau[sTableaux.cont - 1].numVariablesArtificiales)){
				if (sTableaux.tableau[sTableaux.cont - 1].firstFaseFunctionValue != 0){
					sTableaux.tableauDescription[sTableaux.cont - 1] += "PROBLEMA INFACTIBLE: La función 'W' ya ha sido minimizada, pero su valor óptimo no es 0.";
					end = true; break; //FIN (INFACTIBLE)
				}
				else{
					sTableaux.tableauDescription[sTableaux.cont - 1] += "La función 'W' ya ha sido minimizada, y su valor es 0. Ahora pasamos a la segunda fase.\r\n";
				}
			}
			else firstFase = true;
		}
		if (!firstFase){
			if (optimizedFunction(sTableaux.tableau[sTableaux.cont-1].function, sTableaux.maxminMode, sTableaux.tableau[sTableaux.cont-1].numVariables + sTableaux.tableau[sTableaux.cont - 1].numVariablesHolgura)){
				end = true; sTableaux.factible = true; break; //FIN (OPTIMA)
			}
		}

		//Ahora lo que hacemos es aplicar el alg. del Simplex. Primero miramos que variable entra en la base
		sTableaux.tableau[sTableaux.cont].hayPivote = false;
		sTableaux.tableau[sTableaux.cont].twoFases = firstFase;
		sTableaux.tableau[sTableaux.cont].numRestrictions = sTableaux.tableau[sTableaux.cont - 1].numRestrictions;
		sTableaux.tableau[sTableaux.cont].numVariables = sTableaux.tableau[sTableaux.cont - 1].numVariables;
		sTableaux.tableau[sTableaux.cont].numVariablesHolgura = sTableaux.tableau[sTableaux.cont - 1].numVariablesHolgura;
		sTableaux.tableau[sTableaux.cont].numVariablesArtificiales = sTableaux.tableau[sTableaux.cont - 1].numVariablesArtificiales;
		int variableEntrada;
		if (firstFase)
			variableEntrada = checkWhoEntersOnBase(sTableaux.tableau[sTableaux.cont - 1].firstFaseFunction, false, sTableaux.tableau[sTableaux.cont - 1].numVariables + sTableaux.tableau[sTableaux.cont - 1].numVariablesHolgura + sTableaux.tableau[sTableaux.cont - 1].numVariablesArtificiales);
		else
			variableEntrada = checkWhoEntersOnBase(sTableaux.tableau[sTableaux.cont - 1].function, sTableaux.maxminMode, sTableaux.tableau[sTableaux.cont - 1].numVariables + sTableaux.tableau[sTableaux.cont - 1].numVariablesHolgura);

		//Ahora buscamos el pivote
		bool razonMinima = false, lexicografica = false;
		int pivote = busquedaPivote(variableEntrada, sTableaux.tableau[sTableaux.cont - 1], sTableaux.tableau[0].base, razonMinima, lexicografica);
		if (pivote == -1){
			sTableaux.tableauDescription[sTableaux.cont - 1] += "PROBLEMA NO ACOTADO: La variable " + sTableaux.variableNames[variableEntrada] +
				" entraría en la base, pero no hay ninguna variable que pueda salir para poder hacer el pivotaje.";
			sTableaux.factible = true; sTableaux.acotado = false; end = true; break; //FIN (NO ACOTADO)
		}

		//Añadimos la descripción de la tabla
		sTableaux.tableauDescription[sTableaux.cont - 1] += printPivotaje(sTableaux, variableEntrada, pivote, razonMinima, lexicografica);

		updateBase(sTableaux, variableEntrada, pivote);
		sTableaux.tableau[sTableaux.cont - 1].hayPivote = true;
		sTableaux.tableau[sTableaux.cont - 1].pivote_x = pivote;
		sTableaux.tableau[sTableaux.cont - 1].pivote_y = variableEntrada;

		//Por último hacemos pivotaje
		pivotaje(sTableaux, variableEntrada, pivote);

		//Hemos acabado, contador++
		sTableaux.cont++;
	}

	if (sTableaux.factible && sTableaux.acotado){
		fillSolution(sTableaux);
		sTableaux.tableauDescription[sTableaux.cont - 1] += printOptimizedFunction(sTableaux);
		sTableaux.integer_factible = isSolutionInteger(sTableaux);
	}
	else if (sTableaux.factible){ //no acotado
		sTableaux.integer_factible = true;
	}
}