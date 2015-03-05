#pragma once

#include "DataTypes.h"
#include "StringUtil.h"

namespace SimplexSolver {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class TableauForm : public System::Windows::Forms::Form
	{
	public:
		TableauForm(simplexTableaux &sTabla)
		{
			InitializeComponent();
			InitializeGrid(sTabla.tableau[0], sTabla.variableNames);
			*sTableaux = sTabla;
			cbFirst_Click(nullptr, nullptr);
		}

	protected:
		~TableauForm()
		{
			delete sTableaux;
			if (components)
			{
				delete components;
			}
			parentForm->Enabled = true;
		}

	public: System::Windows::Forms::Form^ parentForm; //Puntero a la ventanta anterior
	private: int currentTableau = 0;
	private: simplexTableaux *sTableaux = new simplexTableaux();
	private: System::Windows::Forms::DataGridView^  dgTableau;
	private: System::Windows::Forms::Label^  lblTable;
	private: System::Windows::Forms::Button^  cbNext;
	private: System::Windows::Forms::Button^  cbFirst;
	private: System::Windows::Forms::Button^  cbPrevious;
	private: System::Windows::Forms::Button^  cbLast;
	private: System::Windows::Forms::TextBox^  txtTableDescription;



	protected:

	private:
		/// <summary>
		/// Variable del diseñador requerida.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void FillGrid(tableauData tableau, string *variableNames, string tableauDescription){
			cleanDataGrid();
			for (int i = 0; i < tableau.numRestrictions; i++){
				dgTableau->Rows[i]->Cells[0]->Value = stdToSystem(variableNames[tableau.base[i]]);
				for (int j = 0; j < tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales; j++){
					dgTableau->Rows[i]->Cells[j + 1]->Value = tableau.restrictions[i][j].print();
				}
				dgTableau->Rows[i]->Cells[dgTableau->ColumnCount - 1]->Value = tableau.restrictionValue[i].print();
			}
			//Insertamos fila de W si la hay
			if (tableau.twoFases){
				for (int j = 0; j < tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales; j++){
					dgTableau->Rows[dgTableau->RowCount - 2]->Cells[j + 1]->Value = tableau.firstFaseFunction[j].print();
				}
				if (tableau.firstFaseFunctionValue > 0)
					dgTableau->Rows[dgTableau->RowCount - 2]->Cells[dgTableau->ColumnCount - 1]->Value = String::Concat("W -(", (-tableau.firstFaseFunctionValue).print(), ")");
				else
					dgTableau->Rows[dgTableau->RowCount - 2]->Cells[dgTableau->ColumnCount - 1]->Value = String::Concat("W -", (-tableau.firstFaseFunctionValue).print());
			}
			// Miramos en que fila tenemos que insertar la Z
			int fila;
			if (!tableau.twoFases && sTableaux->tableau[0].twoFases){
				fila = dgTableau->RowCount - 2;
			}
			else fila = dgTableau->RowCount - 1;
			// Y la insertamos
			for (int j = 0; j < tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales; j++){
				dgTableau->Rows[fila]->Cells[j + 1]->Value = tableau.function[j].print();
			}
			if (tableau.functionValue > 0)
				dgTableau->Rows[fila]->Cells[dgTableau->ColumnCount - 1]->Value = String::Concat("Z -(",(-tableau.functionValue).print(),")");
			else
				dgTableau->Rows[fila]->Cells[dgTableau->ColumnCount - 1]->Value = String::Concat("Z -", (-tableau.functionValue).print());
			//resaltamos (color azul clarito) el pivote
			if (tableau.hayPivote){
				this->dgTableau->Rows[tableau.pivote_x]->Cells[tableau.pivote_y + 1]->Style->BackColor = System::Drawing::Color::LightBlue;
			}
			//TableauDescription -> txtDescription
			this->txtTableDescription->Text = stdToSystem(tableauDescription);
		}
		void InitializeGrid(tableauData tableau, string *variableNames){
			for (int i = 0; i <= tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales + 1; i++){
				System::Windows::Forms::DataGridViewTextBoxColumn^ dgNewColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				//Autoajusto tamaño columna si hay menos de 10 variables. El total de columna es 727 (datagrid width - 3).
				if (tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales < 10){
					dgNewColumn->Width = (dgTableau->Width - 3) / (tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales + 2);
					if (i == tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales + 1)
						dgNewColumn->Width = (dgTableau->Width - 3) - (dgTableau->Width - 3) / (tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales + 2) * (tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales + 1);
				}
				//Si no, tamaño de columna por defecto
				else{
					dgNewColumn->Width = 70;
				}
				//Resto de propiedades de columna
				dgNewColumn->Resizable = System::Windows::Forms::DataGridViewTriState::False;
				if (i != tableau.numVariables + tableau.numVariablesHolgura + tableau.numVariablesArtificiales + 1 && i != 0)
					dgNewColumn->HeaderText = stdToSystem(variableNames[i-1]);
				dgNewColumn->SortMode = DataGridViewColumnSortMode::NotSortable;
				dgTableau->Columns->Add(dgNewColumn);
			}
			for (int i = 0; i <= tableau.numRestrictions; i++){
				dgTableau->Rows->Add(gcnew array<String^>{""});
			}
			if (tableau.twoFases) //si hay dos fases añadimos otra fila.
				dgTableau->Rows->Add(gcnew array<String^>{""});
			//TODO: AutoResize
		}
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->dgTableau = (gcnew System::Windows::Forms::DataGridView());
			this->lblTable = (gcnew System::Windows::Forms::Label());
			this->cbNext = (gcnew System::Windows::Forms::Button());
			this->cbFirst = (gcnew System::Windows::Forms::Button());
			this->cbPrevious = (gcnew System::Windows::Forms::Button());
			this->cbLast = (gcnew System::Windows::Forms::Button());
			this->txtTableDescription = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgTableau))->BeginInit();
			this->SuspendLayout();
			// 
			// dgTableau
			// 
			this->dgTableau->AllowUserToAddRows = false;
			this->dgTableau->AllowUserToDeleteRows = false;
			this->dgTableau->AllowUserToResizeColumns = false;
			this->dgTableau->AllowUserToResizeRows = false;
			this->dgTableau->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgTableau->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->dgTableau->ColumnHeadersHeight = 40;
			this->dgTableau->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->dgTableau->Location = System::Drawing::Point(2, 31);
			this->dgTableau->MaximumSize = System::Drawing::Size(730, 350);
			this->dgTableau->MinimumSize = System::Drawing::Size(730, 350);
			this->dgTableau->Name = L"dgTableau";
			this->dgTableau->ReadOnly = true;
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgTableau->RowHeadersDefaultCellStyle = dataGridViewCellStyle2;
			this->dgTableau->RowHeadersVisible = false;
			this->dgTableau->RowTemplate->DefaultCellStyle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->dgTableau->RowTemplate->Height = 40;
			this->dgTableau->Size = System::Drawing::Size(730, 350);
			this->dgTableau->TabIndex = 0;
			// 
			// lblTable
			// 
			this->lblTable->AutoSize = true;
			this->lblTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTable->Location = System::Drawing::Point(319, 7);
			this->lblTable->Name = L"lblTable";
			this->lblTable->Size = System::Drawing::Size(61, 16);
			this->lblTable->TabIndex = 1;
			this->lblTable->Text = L"Tabla 1";
			// 
			// cbNext
			// 
			this->cbNext->Location = System::Drawing::Point(419, 487);
			this->cbNext->Name = L"cbNext";
			this->cbNext->Size = System::Drawing::Size(50, 43);
			this->cbNext->TabIndex = 2;
			this->cbNext->Text = L">";
			this->cbNext->UseVisualStyleBackColor = true;
			this->cbNext->Click += gcnew System::EventHandler(this, &TableauForm::cbNext_Click);
			// 
			// cbFirst
			// 
			this->cbFirst->Location = System::Drawing::Point(198, 487);
			this->cbFirst->Name = L"cbFirst";
			this->cbFirst->Size = System::Drawing::Size(50, 43);
			this->cbFirst->TabIndex = 3;
			this->cbFirst->Text = L"<<";
			this->cbFirst->UseVisualStyleBackColor = true;
			this->cbFirst->Click += gcnew System::EventHandler(this, &TableauForm::cbFirst_Click);
			// 
			// cbPrevious
			// 
			this->cbPrevious->Location = System::Drawing::Point(254, 487);
			this->cbPrevious->Name = L"cbPrevious";
			this->cbPrevious->Size = System::Drawing::Size(50, 43);
			this->cbPrevious->TabIndex = 4;
			this->cbPrevious->Text = L"<";
			this->cbPrevious->UseVisualStyleBackColor = true;
			this->cbPrevious->Click += gcnew System::EventHandler(this, &TableauForm::cbPrevious_Click);
			// 
			// cbLast
			// 
			this->cbLast->Location = System::Drawing::Point(475, 487);
			this->cbLast->Name = L"cbLast";
			this->cbLast->Size = System::Drawing::Size(50, 43);
			this->cbLast->TabIndex = 5;
			this->cbLast->Text = L">>";
			this->cbLast->UseVisualStyleBackColor = true;
			this->cbLast->Click += gcnew System::EventHandler(this, &TableauForm::cbLast_Click);
			// 
			// txtTableDescription
			// 
			this->txtTableDescription->AcceptsReturn = true;
			this->txtTableDescription->AcceptsTab = true;
			this->txtTableDescription->Location = System::Drawing::Point(12, 387);
			this->txtTableDescription->Multiline = true;
			this->txtTableDescription->Name = L"txtTableDescription";
			this->txtTableDescription->Size = System::Drawing::Size(710, 94);
			this->txtTableDescription->TabIndex = 6;
			// 
			// TableauForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(734, 542);
			this->Controls->Add(this->txtTableDescription);
			this->Controls->Add(this->cbLast);
			this->Controls->Add(this->cbPrevious);
			this->Controls->Add(this->cbFirst);
			this->Controls->Add(this->cbNext);
			this->Controls->Add(this->lblTable);
			this->Controls->Add(this->dgTableau);
			this->MaximumSize = System::Drawing::Size(750, 580);
			this->MinimumSize = System::Drawing::Size(750, 580);
			this->Name = L"TableauForm";
			this->Text = L"Tablas";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgTableau))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

void cleanDataGrid(){
	for (int i = 0; i < dgTableau->RowCount; i++){
		for (int j = 0; j < dgTableau->ColumnCount; j++){
			dgTableau->Rows[i]->Cells[j]->Value = "";
			this->dgTableau->Rows[i]->Cells[j]->Style->BackColor = System::Drawing::Color::White;
		}
	}
}
void updateButtons(){
	if (this->currentTableau == 0){
		cbFirst->Enabled = false;
		cbPrevious->Enabled = false;
	}
	else{
		cbFirst->Enabled = true;
		cbPrevious->Enabled = true;
	}
	if (this->currentTableau == sTableaux->cont - 1){
		cbLast->Enabled = false;
		cbNext->Enabled = false;
	}
	else{
		cbLast->Enabled = true;
		cbNext->Enabled = true;
	}
}
private: System::Void cbFirst_Click(System::Object^  sender, System::EventArgs^  e) {
	this->currentTableau = 0;
	updateButtons();
	FillGrid(sTableaux->tableau[currentTableau], sTableaux->variableNames, sTableaux->tableauDescription[currentTableau]);
	this->lblTable->Text = String::Concat("Tabla ", this->currentTableau + 1, " / ", sTableaux->cont);
}
private: System::Void cbPrevious_Click(System::Object^  sender, System::EventArgs^  e) {
	this->currentTableau--;
	updateButtons();
	FillGrid(sTableaux->tableau[currentTableau], sTableaux->variableNames, sTableaux->tableauDescription[currentTableau]);
	this->lblTable->Text = String::Concat("Tabla ", this->currentTableau + 1, " / ", sTableaux->cont);
}
private: System::Void cbNext_Click(System::Object^  sender, System::EventArgs^  e) {
	this->currentTableau++;
	updateButtons();
	FillGrid(sTableaux->tableau[currentTableau], sTableaux->variableNames, sTableaux->tableauDescription[currentTableau]);
	this->lblTable->Text = String::Concat("Tabla ", this->currentTableau + 1, " / ", sTableaux->cont);
}
private: System::Void cbLast_Click(System::Object^  sender, System::EventArgs^  e) {
	this->currentTableau = sTableaux->cont - 1;
	updateButtons();
	FillGrid(sTableaux->tableau[currentTableau], sTableaux->variableNames, sTableaux->tableauDescription[currentTableau]);
	this->lblTable->Text = String::Concat("Tabla ", this->currentTableau + 1, " / ", sTableaux->cont);
}
};
}
