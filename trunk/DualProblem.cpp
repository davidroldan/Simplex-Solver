#include "stdafx.h"
#include "DualProblem.h"
#include "DataTypes.h"

#define _POS 0
#define _NEG 1
#define _S_R 2
#define _IG 3

using namespace System;

void setDualProblem(System::Windows::Forms::DataGridView^ dataGrid, System::Windows::Forms::DataGridView^ dataGrid2, System::Windows::Forms::DataGridView^ dataGrid3, bool maxminMode){
	//Guardamos todos los datos
	bool maxminModeDual = !maxminMode;
	int aux[MAX_TABLEAU][MAX_TABLEAU];
	int restr[MAX_TABLEAU];
	int func[MAX_TABLEAU];
	int acotado[MAX_TABLEAU];
	int igualdades[MAX_TABLEAU];
	int numRestrictions = dataGrid->RowCount - 1;
	int numVariables = dataGrid->ColumnCount - 2;
	for (int i = 0; i < numRestrictions; i++){
		restr[i] = Convert::ToInt32(dataGrid->Rows[i + 1]->Cells[dataGrid->ColumnCount - 1]->Value->ToString());
		for (int j = 0; j < numVariables; j++){
			aux[i][j] = Convert::ToInt32(dataGrid->Rows[i+1]->Cells[j]->Value->ToString());
		}
		if (dataGrid->Rows[i + 1]->Cells[dataGrid->ColumnCount - 2]->Value->ToString() == "="){
			igualdades[i] = _IG;
		}
		else if (dataGrid->Rows[i + 1]->Cells[dataGrid->ColumnCount - 2]->Value->ToString() == "<="){
			igualdades[i] = _NEG;
		}
		else igualdades[i] = _POS;

	}
	for (int j = 0; j < numVariables; j++){
		func[j] = Convert::ToInt32(dataGrid->Rows[0]->Cells[j]->Value->ToString());
		if (dataGrid2->Rows[0]->Cells[j]->Value->ToString() == "s.r."){
			acotado[j] = _S_R;
		}
		else if (dataGrid2->Rows[0]->Cells[j]->Value->ToString() == ">= 0"){
			acotado[j] = _POS;
		}
		else{
			acotado[j] = _NEG;
		}
	}
	//Ahora cambiamos el tamaño de la matriz
	if (numRestrictions > numVariables){
		for (int k = 0; k < numRestrictions - numVariables; k++){
			dataGrid->Rows->RemoveAt(dataGrid->RowCount - 1);
			System::Windows::Forms::DataGridViewTextBoxColumn^ dgNewColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			dgNewColumn->Width = 50;
			dgNewColumn->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			dgNewColumn->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			dgNewColumn->HeaderText = String::Concat("X", dataGrid->ColumnCount - 1);
			dataGrid->Columns->Insert(dataGrid->ColumnCount - 2, dgNewColumn);

			System::Windows::Forms::DataGridViewComboBoxColumn^ dgNewVar = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			dgNewVar->Width = 50;
			dgNewVar->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			dgNewVar->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			dgNewVar->HeaderText = String::Concat("X", dataGrid2->ColumnCount + 1);
			dgNewVar->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L">= 0", L"<= 0", L"s.r." });
			dataGrid2->Columns->Insert(dataGrid2->ColumnCount, dgNewVar);
			dataGrid2->Rows[0]->Cells[dataGrid2->ColumnCount - 1]->Value = ">= 0";

			System::Windows::Forms::DataGridViewCheckBoxColumn^ dgNewVar2 = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
			dgNewVar2->Width = 50;
			dgNewVar2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			dgNewVar2->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			dgNewVar2->HeaderText = String::Concat("X", dataGrid3->ColumnCount + 1);
			dataGrid3->Columns->Insert(dataGrid3->ColumnCount, dgNewVar2);
		}
	}
	else if (numRestrictions < numVariables){
		for (int k = 0; k < numVariables - numRestrictions; k++){
			dataGrid3->Columns->RemoveAt(dataGrid->ColumnCount - 3);
			dataGrid2->Columns->RemoveAt(dataGrid->ColumnCount - 3);
			dataGrid->Columns->RemoveAt(dataGrid->ColumnCount - 3);
			dataGrid->Rows->Insert(dataGrid->RowCount, gcnew array<String^>{""});
		}
	}
	//Por último copiamos todos los valores en la matriz
	for (int i = 0; i < numRestrictions; i++){
		dataGrid->Rows[0]->Cells[i]->Value = restr[i];
		for (int j = 0; j < numVariables; j++){
			dataGrid->Rows[j + 1]->Cells[i]->Value = aux[i][j];
		}
		if (igualdades[i] == _IG){
			dataGrid2->Rows[0]->Cells[i]->Value = "s.r.";
		}
		else if (igualdades[i] == _POS){
			if (maxminMode) dataGrid2->Rows[0]->Cells[i]->Value = "<= 0";
			else dataGrid2->Rows[0]->Cells[i]->Value = ">= 0";
		}
		else{
			if (maxminMode) dataGrid2->Rows[0]->Cells[i]->Value = ">= 0";
			else dataGrid2->Rows[0]->Cells[i]->Value = "<= 0";
		}
	}
	for (int j = 0; j < numVariables; j++){
		dataGrid->Rows[j + 1]->Cells[dataGrid->ColumnCount - 1]->Value = func[j];
		if (acotado[j] == _S_R){
			dataGrid->Rows[j + 1]->Cells[dataGrid->ColumnCount - 2]->Value = "=";
		}
		else if (acotado[j] == _POS){
			if (maxminModeDual) dataGrid->Rows[j + 1]->Cells[dataGrid->ColumnCount - 2]->Value = "<=";
			else dataGrid->Rows[j + 1]->Cells[dataGrid->ColumnCount - 2]->Value = ">=";
		}
		else{
			if (maxminModeDual) dataGrid->Rows[j + 1]->Cells[dataGrid->ColumnCount - 2]->Value = ">=";
			else dataGrid->Rows[j + 1]->Cells[dataGrid->ColumnCount - 2]->Value = "<=";
		}
	}
	//Desmarcamos todas las variables enteras
	for (int i = 0; i < dataGrid3->ColumnCount; i++){
		dataGrid3->Rows[0]->Cells[i]->Value = false;
	}
}