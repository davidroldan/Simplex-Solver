#include "stdafx.h" //este include hay que ponerle el primero, sino por alguna razón ignora los otros includes
#include "InitialTableau.h"
#include "DataTypes.h"
#include "StringUtil.h"
#include <string>
using namespace std;

void fillFirstFaseFunction(tableauData &tableau){
	for (int i = 0; i < MAX_TABLEAU; i++){
		if (i >= tableau.numVariables + tableau.numVariablesHolgura && i < tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales)
			tableau.firstFaseFunction[i] = 1;
		else
			tableau.firstFaseFunction[i] = 0;
	}
}
void adjustFirstFaseFunction(tableauData &tableau){
	tableau.firstFaseFunctionValue = 0;
	for (int i = 0; i < tableau.numRestrictions; i++){
		if (tableau.firstFaseFunction[tableau.base[i]] != 0){
			fraction a = -tableau.firstFaseFunction[tableau.base[i]];
			for (int j = 0; j < tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales; j++){
				tableau.firstFaseFunction[j] += a * tableau.restrictions[i][j];
			}
			tableau.firstFaseFunctionValue += a * tableau.restrictionValue[i];
		}
	}
}
void adjustObjectiveFunction(tableauData &tableau){
	tableau.functionValue = 0;
	for (int i = 0; i < tableau.numRestrictions; i++){
		if (tableau.function[tableau.base[i]] != 0){
			fraction a = -tableau.function[tableau.base[i]];
			for (int j = 0; j < tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales; j++){
				tableau.function[j] += a * tableau.restrictions[i][j];
			}
			tableau.functionValue += a * tableau.restrictionValue[i];
		}
	}
}
bool baseCandidate(int a, int b, tableauData &tableau){
	for (int i = 0; i < tableau.numRestrictions; i++){
		if (i != a){
			if (tableau.restrictions[i][b] != 0)
				return false;
		}
	}
	return true;
}

void setBase(tableauData &tableau, int &variableNameCount, string variableNames[MAX_TABLEAU]){
	tableau.numVariablesArtificiales = 0;
	for (int i = 0; i < tableau.numRestrictions; i++){
		bool found = false;
		for (int j = 0; j < tableau.numVariables + tableau.numVariablesHolgura && !found; j++){
			if (tableau.restrictions[i][j] == 1){
				if (baseCandidate(i,j, tableau)){
					tableau.base[i] = j;
					found = true;
				}
			}
		}
		if (!found){
			tableau.restrictions[i][tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales] = 1;
			tableau.base[i] = tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales;
			systemStringtoString(System::String::Concat("X", variableNameCount + 1), variableNames[tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales]);
			variableNameCount++;
			tableau.numVariablesArtificiales++;
		}
	}
}

void addVariableHolguras(tableauData &tableau, System::Windows::Forms::DataGridView^ dataGrid, int &variableNameCount, string variableNames[MAX_TABLEAU]){
	tableau.numVariablesHolgura = 0;
	for (int i = 0; i < tableau.numRestrictions; i++){
		if (dataGrid->Rows[i + 1]->Cells[dataGrid->ColumnCount - 2]->Value->ToString() == "<="){
			tableau.restrictions[i][tableau.numVariables + tableau.numVariablesHolgura] = 1;
			systemStringtoString(System::String::Concat("X", variableNameCount + 1), variableNames[tableau.numVariables + tableau.numVariablesHolgura]);
			tableau.numVariablesHolgura++;
			variableNameCount++;
		}
		else if (dataGrid->Rows[i + 1]->Cells[dataGrid->ColumnCount - 2]->Value->ToString() == ">="){
			tableau.restrictions[i][tableau.numVariables + tableau.numVariablesHolgura] = -1;
			systemStringtoString(System::String::Concat("X", variableNameCount + 1), variableNames[tableau.numVariables + tableau.numVariablesHolgura]);
			tableau.numVariablesHolgura++;
			variableNameCount++;
		}
		//if "=" no hacer nada
	}
}
void checkNegativeRestrictions(tableauData &tableau){
	for (int i = 0; i < tableau.numRestrictions; i++){
		if (tableau.restrictionValue[i] < 0){
			tableau.restrictionValue[i] = -tableau.restrictionValue[i];
			for (int j = 0; j < tableau.numVariables + tableau.numVariablesHolgura; j++){
				tableau.restrictions[i][j] = -tableau.restrictions[i][j];
			}
		}
	}
}

void fillRestrictionsAndObjectiveFunction(tableauData &tableau, System::Windows::Forms::DataGridView^ dataGrid, System::Windows::Forms::DataGridView^ dataGrid2, int &variableNameCount, string variableNames[MAX_TABLEAU]){
	//Inicializamos por defecto a 0
	for (int i = 0; i < MAX_TABLEAU; i++){
		for (int j = 0; j < MAX_TABLEAU; j++){
			tableau.restrictions[i][j] = 0;
		}
		tableau.function[i] = 0;
	}
	//Inicializamos los valores de las restricciones
	for (int i = 0; i < MAX_TABLEAU; i++){
		if (i < tableau.numRestrictions){
			tableau.restrictionValue[i] = convertToFraction(dataGrid->Rows[i + 1]->Cells[dataGrid->ColumnCount - 1]->Value->ToString());
		}
		else{
			tableau.restrictionValue[i] = 0;
		}
	}
	//Por último
	int varNameMax = tableau.numVariables;
	int j = 0;
	for (; variableNameCount < varNameMax; variableNameCount++){
		for (int i = 0; i < tableau.numRestrictions; i++){
			tableau.restrictions[i][j] = convertToFraction(dataGrid->Rows[i + 1]->Cells[variableNameCount]->Value->ToString());
		}
		tableau.function[j] = convertToFraction(dataGrid->Rows[0]->Cells[variableNameCount]->Value->ToString());
		if (dataGrid2->Rows[0]->Cells[variableNameCount]->Value->ToString() == "s.r."){
			systemStringtoString(System::String::Concat("X", variableNameCount+1, "+"), variableNames[j]);
			j++;
			systemStringtoString(System::String::Concat("X", variableNameCount+1, "-"), variableNames[j]);
			for (int i = 0; i < tableau.numRestrictions; i++){
				tableau.restrictions[i][j] = - convertToFraction(dataGrid->Rows[i + 1]->Cells[variableNameCount]->Value->ToString());
			}
			tableau.function[j] = - convertToFraction(dataGrid->Rows[0]->Cells[variableNameCount]->Value->ToString());
			tableau.numVariables++;
		}
		else if (dataGrid2->Rows[0]->Cells[variableNameCount]->Value->ToString() == ">= 0"){
			systemStringtoString(System::String::Concat("X", variableNameCount + 1), variableNames[j]);
		}
		else{
			systemStringtoString(System::String::Concat("X", variableNameCount + 1, "-"), variableNames[j]);
			for (int i = 0; i < tableau.numRestrictions; i++){
				tableau.restrictions[i][j] = -convertToFraction(dataGrid->Rows[i + 1]->Cells[variableNameCount]->Value->ToString());
			}
			tableau.function[j] = -convertToFraction(dataGrid->Rows[0]->Cells[variableNameCount]->Value->ToString());
		}
		j++;
	}
}

void setInitialTableau(tableauData &tableau, System::Windows::Forms::DataGridView^ dataGrid, System::Windows::Forms::DataGridView^ dataGrid2, string variableNames[MAX_TABLEAU]){
	tableau.numVariables = dataGrid->ColumnCount - 2;
	tableau.numRestrictions = dataGrid->RowCount - 1;
	int variableNameCount = 0;
	fillRestrictionsAndObjectiveFunction(tableau, dataGrid, dataGrid2, variableNameCount, variableNames);
	addVariableHolguras(tableau, dataGrid, variableNameCount, variableNames);
	checkNegativeRestrictions(tableau);
	setBase(tableau, variableNameCount, variableNames);
	adjustObjectiveFunction(tableau);
	tableau.twoFases = (tableau.numVariablesArtificiales > 0);
	if (tableau.twoFases){
		fillFirstFaseFunction(tableau);
		adjustFirstFaseFunction(tableau);
	}
	tableau.hayPivote = false;
}

void findNonIntegerVariable(simplexTableaux t, int &var, int &num, bool leftChild){
	for (int i = 0; i < t.numVar; i++){
		if (t.integerVariable[i] && t.solution[i].denominator() != 1){
			var = i; num = t.solution[i].numerator() / t.solution[i].denominator();
			if (t.solution[i] < 0) num--; //para que el redondeo vaya al numero menor en caso de negativo
			if (!leftChild) num++;
			return;
		}
	}
}

void setInitialTableauInteger(simplexTableaux &t1, simplexTableaux &t2, bool leftChild){
	t2.cont = 1;
	t2.tableau[0] = t1.tableau[t1.cont - 1];
	for (int i = 0; i < MAX_TABLEAU; i++){
		t2.variableNames[i] = t1.variableNames[i];
		t2.integerVariable[i] = t1.integerVariable[i];
	}

	//Eliminamos var. artificiales si las habia
	t2.tableau[0].numVariablesArtificiales = 0;
	t2.tableau[0].twoFases = false;
	t2.maxminMode = t1.maxminMode;
	t2.numVar = t1.numVar;

	//Limpio 2 columnas por si acaso las utilizo luego (la de la nueva var. de holgura y la de la posible var. artificial)
	int aux1 = t2.tableau[0].numVariables + t2.tableau[0].numVariablesHolgura;
	for (int i = 0; i < MAX_TABLEAU; i++){
		
		t2.tableau[0].restrictions[i][aux1] = 0;
		t2.tableau[0].restrictions[i][aux1+1] = 0;
	}
	t2.tableau[0].function[aux1] = 0;
	t2.tableau[0].function[aux1+1] = 0;


	//Añadimos nueva restriccion y var. de holgura
	t2.tableau[0].numRestrictions++;
	t2.tableau[0].numVariablesHolgura++;
	systemStringtoString(System::String::Concat("X", t2.numVar + t2.tableau[0].numVariablesHolgura), t2.variableNames[t2.tableau[0].numVariables + t2.tableau[0].numVariablesHolgura - 1]);
	t2.tableau[0].base[t2.tableau[0].numRestrictions - 1] = t2.tableau[0].numVariables + t2.tableau[0].numVariablesHolgura - 1;

	if (leftChild)
		t2.tableau[0].restrictions[t2.tableau[0].numRestrictions - 1][t2.tableau[0].numVariables + t2.tableau[0].numVariablesHolgura - 1] = 1;
	else
		t2.tableau[0].restrictions[t2.tableau[0].numRestrictions - 1][t2.tableau[0].numVariables + t2.tableau[0].numVariablesHolgura - 1] = -1;

	int var, num;
	findNonIntegerVariable(t1, var, num, leftChild);

	t2.tableau[0].restrictionValue[t2.tableau[0].numRestrictions - 1] = num; //metemos valor de la ultima restriccion
	int variablePos[2] = { -1, -1 }; //guarda en que posicion esta la variable Xi+ y Xi- (en caso de que existan)
	
	for (int i = 0; i < t2.tableau[0].numVariables; i++){
		int neg = 1;
		string aux_s = t2.variableNames[i];
		char aux_c = aux_s[aux_s.length() - 1];
		if (aux_c == '+'){
			aux_s = aux_s.substr(0, aux_s.length() - 1); //quitamos el +
		}
		else if (aux_c == '-'){
			aux_s = aux_s.substr(0, aux_s.length() - 1); //quitamos el -
			neg = -1;
		}
		int number = System::Convert::ToInt16(stdToSystem(aux_s.substr(1, aux_s.length() - 1))); //quitamos la x
		if (number - 1 == var){ //number - 1 ya que Xn es la var n-1 (X1 es la var. 0)
			if (neg == 1){
				variablePos[0] = i;
			}
			else{
				variablePos[1] = i;
			}
			t2.tableau[0].restrictions[t2.tableau[0].numRestrictions - 1][i] = neg; //metemos valor de la restriccion en Xi (o Xi+, Xi-)
		}
	}
	for (int i = 0; i < t2.tableau[0].numRestrictions - 1; i++){
		if (t2.tableau[0].base[i] == variablePos[0]){
			for (int j = 0; j < t2.tableau[0].numVariables + t2.tableau[0].numVariablesHolgura; j++){
				t2.tableau[0].restrictions[t2.tableau[0].numRestrictions - 1][j] -= t2.tableau[0].restrictions[i][j];
			}
			t2.tableau[0].restrictionValue[t2.tableau[0].numRestrictions - 1] -= t2.tableau[0].restrictionValue[i];
		}
		else if (t2.tableau[0].base[i] == variablePos[1]){
			for (int j = 0; j < t2.tableau[0].numVariables + t2.tableau[0].numVariablesHolgura; j++){
				t2.tableau[0].restrictions[t2.tableau[0].numRestrictions - 1][j] += t2.tableau[0].restrictions[i][j];
			}
			t2.tableau[0].restrictionValue[t2.tableau[0].numRestrictions - 1] += t2.tableau[0].restrictionValue[i];
		}
	}

	checkNegativeRestrictions(t2.tableau[0]);

	//Var. artificial si es necesario
	if (t2.tableau[0].restrictions[t2.tableau[0].numRestrictions - 1][t2.tableau[0].numVariables + t2.tableau[0].numVariablesHolgura - 1] != 1){
		t2.tableau[0].numVariablesArtificiales++;
		systemStringtoString(System::String::Concat("X", t2.numVar + t2.tableau[0].numVariablesHolgura + 1), t2.variableNames[t2.tableau[0].numVariables + t2.tableau[0].numVariablesHolgura]); // -1 + numVarArtificiales (1)
		t2.tableau[0].base[t2.tableau[0].numRestrictions - 1] = t2.tableau[0].numVariables + t2.tableau[0].numVariablesHolgura; // -1 + numVarArtificiales (1)
		t2.tableau[0].restrictions[t2.tableau[0].numRestrictions - 1][t2.tableau[0].numVariables + t2.tableau[0].numVariablesHolgura] = 1;  // -1 + numVarArtificiales (1)
	}

	t2.tableau[0].twoFases = (t2.tableau[0].numVariablesArtificiales > 0);
	if (t2.tableau[0].twoFases){
		fillFirstFaseFunction(t2.tableau[0]);
		adjustFirstFaseFunction(t2.tableau[0]);
	}
	t2.tableau[0].hayPivote = false;
}