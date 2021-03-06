#pragma once

#include "TableauForm.h"
#include "IntegerTreeForm.h"
#include "InitialTableau.h"
#include "SimplexAlgorithm.h"
#include "DataTypes.h"
#include "DualProblem.h"
#include "Fraction.h"
#include "IntegerProblemFunctions.h"
#include "RichTextUtil.h"
#include <vector>

namespace SimplexSolver {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Form1
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			this->dgRestricciones->CellEndEdit += gcnew DataGridViewCellEventHandler(this, &MainWindow::dgRestricciones_CellEndEdit);
			this->dgRestricciones2->CellEndEdit += gcnew DataGridViewCellEventHandler(this, &MainWindow::dgRestricciones_2_3_CellEndEdit);
			this->dgRestricciones3->CellEndEdit += gcnew DataGridViewCellEventHandler(this, &MainWindow::dgRestricciones_2_3_CellEndEdit);
			this->rbMax->CheckedChanged += gcnew EventHandler(this, &MainWindow::checkedChanged);
			this->evento = true;
			InitializeGrid();
			this->evento = false;
			this->updateEnunciado();
		}

	protected:
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: bool evento;
	private: System::Windows::Forms::DataGridView^  dgRestricciones;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripLabel^  toolStripLabel1;
	private: System::Windows::Forms::ToolStripButton^  cbAddVariable;
	private: System::Windows::Forms::ToolStripButton^  cbRemoveVariable;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripLabel^  toolStripLabel2;
	private: System::Windows::Forms::ToolStripButton^  cbAddRestriction;
	private: System::Windows::Forms::ToolStripButton^  cbRemoveRestriction;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgX1;
	private: System::Windows::Forms::DataGridViewComboBoxColumn^  dgDesigualdad;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgValor;
	private: System::Windows::Forms::Button^  cbSolve;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  rbMin;
	private: System::Windows::Forms::RadioButton^  rbMax;
	private: System::Windows::Forms::Button^  cbDual;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  archivoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  msHelp;
	private: System::Windows::Forms::ToolStripMenuItem^  msAbout;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  msQuit;
	private: System::Windows::Forms::RichTextBox^  rtxtEnunciado;
	private: System::Windows::Forms::DataGridView^  dgRestricciones2;
	private: System::Windows::Forms::DataGridViewComboBoxColumn^  dgrX1;
	private: System::Windows::Forms::DataGridView^  dgRestricciones3;
	private: System::Windows::Forms::DataGridViewCheckBoxColumn^  dg3X1;






	private:
		/// <summary>
		/// Variable del diseñador requerida.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido del método con el editor de código.
		/// </summary>
		void InitializeGrid(void){
			dgRestricciones->Rows->Add(gcnew array<String^>{""});
			dgRestricciones->Rows->Add(gcnew array<String^>{""});
			dgRestricciones->Rows[0]->HeaderCell->Value = "Función objetivo";
			dgRestricciones->Rows[1]->HeaderCell->Value = "Restricción 1";
			dgRestricciones->Rows[0]->Cells[dgDesigualdad->Index]->ReadOnly = true;
			dgRestricciones->Rows[0]->Cells[dgValor->Index]->ReadOnly = true;
			dgRestricciones->Rows[1]->Cells[dgDesigualdad->Index]->Value = "<=";

			dgRestricciones2->Rows->Add(gcnew array<String^>{">= 0"});
			dgRestricciones2->Rows[0]->HeaderCell->Value = "Variables";

			dgRestricciones3->Rows->Add();
			dgRestricciones3->Rows[0]->HeaderCell->Value = "Variables enteras";
		}
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->dgRestricciones = (gcnew System::Windows::Forms::DataGridView());
			this->dgX1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dgDesigualdad = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->dgValor = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->cbAddVariable = (gcnew System::Windows::Forms::ToolStripButton());
			this->cbRemoveVariable = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripLabel2 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->cbAddRestriction = (gcnew System::Windows::Forms::ToolStripButton());
			this->cbRemoveRestriction = (gcnew System::Windows::Forms::ToolStripButton());
			this->cbSolve = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->rbMin = (gcnew System::Windows::Forms::RadioButton());
			this->rbMax = (gcnew System::Windows::Forms::RadioButton());
			this->cbDual = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->archivoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->msHelp = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->msAbout = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->msQuit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rtxtEnunciado = (gcnew System::Windows::Forms::RichTextBox());
			this->dgRestricciones2 = (gcnew System::Windows::Forms::DataGridView());
			this->dgrX1 = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->dgRestricciones3 = (gcnew System::Windows::Forms::DataGridView());
			this->dg3X1 = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgRestricciones))->BeginInit();
			this->toolStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgRestricciones2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgRestricciones3))->BeginInit();
			this->SuspendLayout();
			// 
			// dgRestricciones
			// 
			this->dgRestricciones->AllowUserToAddRows = false;
			this->dgRestricciones->AllowUserToDeleteRows = false;
			this->dgRestricciones->AllowUserToResizeColumns = false;
			this->dgRestricciones->AllowUserToResizeRows = false;
			this->dgRestricciones->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgRestricciones->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->dgX1,
					this->dgDesigualdad, this->dgValor
			});
			this->dgRestricciones->Location = System::Drawing::Point(12, 57);
			this->dgRestricciones->Name = L"dgRestricciones";
			this->dgRestricciones->RowHeadersWidth = 150;
			this->dgRestricciones->Size = System::Drawing::Size(710, 244);
			this->dgRestricciones->TabIndex = 0;
			// 
			// dgX1
			// 
			this->dgX1->HeaderText = L"X1";
			this->dgX1->MinimumWidth = 50;
			this->dgX1->Name = L"dgX1";
			this->dgX1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dgX1->Width = 50;
			// 
			// dgDesigualdad
			// 
			this->dgDesigualdad->HeaderText = L"";
			this->dgDesigualdad->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L">=", L"<=", L"=" });
			this->dgDesigualdad->Name = L"dgDesigualdad";
			this->dgDesigualdad->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dgDesigualdad->Width = 50;
			// 
			// dgValor
			// 
			this->dgValor->HeaderText = L"Valor";
			this->dgValor->Name = L"dgValor";
			this->dgValor->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dgValor->Width = 50;
			// 
			// toolStrip1
			// 
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->toolStripLabel1,
					this->cbAddVariable, this->cbRemoveVariable, this->toolStripSeparator1, this->toolStripLabel2, this->cbAddRestriction, this->cbRemoveRestriction
			});
			this->toolStrip1->Location = System::Drawing::Point(0, 24);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(734, 25);
			this->toolStrip1->TabIndex = 1;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripLabel1
			// 
			this->toolStripLabel1->Name = L"toolStripLabel1";
			this->toolStripLabel1->Size = System::Drawing::Size(54, 22);
			this->toolStripLabel1->Text = L"Variables";
			// 
			// cbAddVariable
			// 
			this->cbAddVariable->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cbAddVariable->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cbAddVariable.Image")));
			this->cbAddVariable->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cbAddVariable->Name = L"cbAddVariable";
			this->cbAddVariable->Size = System::Drawing::Size(23, 22);
			this->cbAddVariable->Text = L"Añadir nueva variable";
			this->cbAddVariable->Click += gcnew System::EventHandler(this, &MainWindow::cbAddVariable_Click);
			// 
			// cbRemoveVariable
			// 
			this->cbRemoveVariable->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cbRemoveVariable->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cbRemoveVariable.Image")));
			this->cbRemoveVariable->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cbRemoveVariable->Name = L"cbRemoveVariable";
			this->cbRemoveVariable->Size = System::Drawing::Size(23, 22);
			this->cbRemoveVariable->Text = L"Borrar variable";
			this->cbRemoveVariable->Click += gcnew System::EventHandler(this, &MainWindow::cbRemoveVariable_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);
			// 
			// toolStripLabel2
			// 
			this->toolStripLabel2->Name = L"toolStripLabel2";
			this->toolStripLabel2->Size = System::Drawing::Size(76, 22);
			this->toolStripLabel2->Text = L"Restricciones";
			// 
			// cbAddRestriction
			// 
			this->cbAddRestriction->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cbAddRestriction->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cbAddRestriction.Image")));
			this->cbAddRestriction->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cbAddRestriction->Name = L"cbAddRestriction";
			this->cbAddRestriction->Size = System::Drawing::Size(23, 22);
			this->cbAddRestriction->Text = L"Añadir nueva restricción";
			this->cbAddRestriction->Click += gcnew System::EventHandler(this, &MainWindow::cbAddRestriction_Click);
			// 
			// cbRemoveRestriction
			// 
			this->cbRemoveRestriction->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cbRemoveRestriction->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cbRemoveRestriction.Image")));
			this->cbRemoveRestriction->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cbRemoveRestriction->Name = L"cbRemoveRestriction";
			this->cbRemoveRestriction->Size = System::Drawing::Size(23, 22);
			this->cbRemoveRestriction->Text = L"Borrar restricción";
			this->cbRemoveRestriction->Click += gcnew System::EventHandler(this, &MainWindow::cbRemoveRestriction_Click);
			// 
			// cbSolve
			// 
			this->cbSolve->Location = System::Drawing::Point(587, 508);
			this->cbSolve->Name = L"cbSolve";
			this->cbSolve->Size = System::Drawing::Size(118, 42);
			this->cbSolve->TabIndex = 2;
			this->cbSolve->Text = L"Resolver";
			this->cbSolve->UseVisualStyleBackColor = true;
			this->cbSolve->Click += gcnew System::EventHandler(this, &MainWindow::cbSolve_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->rbMin);
			this->groupBox1->Controls->Add(this->rbMax);
			this->groupBox1->Location = System::Drawing::Point(578, 382);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(136, 71);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Criterio Función Objetivo";
			// 
			// rbMin
			// 
			this->rbMin->AutoSize = true;
			this->rbMin->Location = System::Drawing::Point(19, 42);
			this->rbMin->Name = L"rbMin";
			this->rbMin->Size = System::Drawing::Size(85, 17);
			this->rbMin->TabIndex = 1;
			this->rbMin->Text = L"Minimización";
			this->rbMin->UseVisualStyleBackColor = true;
			// 
			// rbMax
			// 
			this->rbMax->AutoSize = true;
			this->rbMax->Checked = true;
			this->rbMax->Location = System::Drawing::Point(19, 19);
			this->rbMax->Name = L"rbMax";
			this->rbMax->Size = System::Drawing::Size(88, 17);
			this->rbMax->TabIndex = 0;
			this->rbMax->TabStop = true;
			this->rbMax->Text = L"Maximización";
			this->rbMax->UseVisualStyleBackColor = true;
			// 
			// cbDual
			// 
			this->cbDual->Location = System::Drawing::Point(587, 460);
			this->cbDual->Name = L"cbDual";
			this->cbDual->Size = System::Drawing::Size(118, 42);
			this->cbDual->TabIndex = 4;
			this->cbDual->Text = L"Problema Dual";
			this->cbDual->UseVisualStyleBackColor = true;
			this->cbDual->Click += gcnew System::EventHandler(this, &MainWindow::cbDual_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->archivoToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(734, 24);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// archivoToolStripMenuItem
			// 
			this->archivoToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->msHelp,
					this->msAbout, this->toolStripSeparator2, this->msQuit
			});
			this->archivoToolStripMenuItem->Name = L"archivoToolStripMenuItem";
			this->archivoToolStripMenuItem->Size = System::Drawing::Size(60, 20);
			this->archivoToolStripMenuItem->Text = L"Archivo";
			// 
			// msHelp
			// 
			this->msHelp->Name = L"msHelp";
			this->msHelp->Size = System::Drawing::Size(135, 22);
			this->msHelp->Text = L"Ayuda";
			this->msHelp->Click += gcnew System::EventHandler(this, &MainWindow::msHelp_Click);
			// 
			// msAbout
			// 
			this->msAbout->Name = L"msAbout";
			this->msAbout->Size = System::Drawing::Size(135, 22);
			this->msAbout->Text = L"Acerca de...";
			this->msAbout->Click += gcnew System::EventHandler(this, &MainWindow::msAbout_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(132, 6);
			// 
			// msQuit
			// 
			this->msQuit->Name = L"msQuit";
			this->msQuit->Size = System::Drawing::Size(135, 22);
			this->msQuit->Text = L"Cerrar";
			this->msQuit->Click += gcnew System::EventHandler(this, &MainWindow::msQuit_Click);
			// 
			// rtxtEnunciado
			// 
			this->rtxtEnunciado->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rtxtEnunciado->Font = (gcnew System::Drawing::Font(L"Arial Unicode MS", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rtxtEnunciado->Location = System::Drawing::Point(12, 382);
			this->rtxtEnunciado->Name = L"rtxtEnunciado";
			this->rtxtEnunciado->ReadOnly = true;
			this->rtxtEnunciado->Size = System::Drawing::Size(556, 168);
			this->rtxtEnunciado->TabIndex = 6;
			this->rtxtEnunciado->Text = L"";
			// 
			// dgRestricciones2
			// 
			this->dgRestricciones2->AllowUserToAddRows = false;
			this->dgRestricciones2->AllowUserToDeleteRows = false;
			this->dgRestricciones2->AllowUserToResizeColumns = false;
			this->dgRestricciones2->AllowUserToResizeRows = false;
			this->dgRestricciones2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgRestricciones2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->dgrX1 });
			this->dgRestricciones2->Location = System::Drawing::Point(12, 307);
			this->dgRestricciones2->Name = L"dgRestricciones2";
			this->dgRestricciones2->RowHeadersWidth = 150;
			this->dgRestricciones2->Size = System::Drawing::Size(710, 45);
			this->dgRestricciones2->TabIndex = 7;
			// 
			// dgrX1
			// 
			this->dgrX1->HeaderText = L"X1";
			this->dgrX1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L">= 0", L"<= 0", L"s.r." });
			this->dgrX1->Name = L"dgrX1";
			this->dgrX1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dgrX1->Width = 50;
			// 
			// dgRestricciones3
			// 
			this->dgRestricciones3->AllowUserToAddRows = false;
			this->dgRestricciones3->AllowUserToDeleteRows = false;
			this->dgRestricciones3->AllowUserToResizeColumns = false;
			this->dgRestricciones3->AllowUserToResizeRows = false;
			this->dgRestricciones3->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgRestricciones3->ColumnHeadersVisible = false;
			this->dgRestricciones3->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->dg3X1 });
			this->dgRestricciones3->Location = System::Drawing::Point(12, 351);
			this->dgRestricciones3->Name = L"dgRestricciones3";
			this->dgRestricciones3->RowHeadersWidth = 150;
			this->dgRestricciones3->Size = System::Drawing::Size(710, 25);
			this->dgRestricciones3->TabIndex = 8;
			// 
			// dg3X1
			// 
			this->dg3X1->HeaderText = L"X1";
			this->dg3X1->Name = L"dg3X1";
			this->dg3X1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dg3X1->Width = 50;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(734, 561);
			this->Controls->Add(this->dgRestricciones3);
			this->Controls->Add(this->dgRestricciones2);
			this->Controls->Add(this->rtxtEnunciado);
			this->Controls->Add(this->cbDual);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->cbSolve);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->dgRestricciones);
			this->MainMenuStrip = this->menuStrip1;
			this->MaximumSize = System::Drawing::Size(750, 600);
			this->MinimumSize = System::Drawing::Size(750, 600);
			this->Name = L"MainWindow";
			this->Text = L"Resolutor de Simplex";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgRestricciones))->EndInit();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgRestricciones2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgRestricciones3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

void updateRowHeaders(){
	for (int i = 1; i < dgRestricciones->RowCount; i++){
		dgRestricciones->Rows[i]->HeaderCell->Value = String::Concat("Restricción ", i);
	}
}
void fillEmptyCells(){
	for (int i = 0; i < dgRestricciones->RowCount; i++){
		for (int j = 0; j < dgRestricciones->ColumnCount; j++){
			if (i == 0 && j == dgDesigualdad->Index) break;
			if (dgRestricciones->Rows[i]->Cells[j]->Value == nullptr || dgRestricciones->Rows[i]->Cells[j]->Value->ToString() == ""){
				dgRestricciones->Rows[i]->Cells[j]->Value = 0;
			}
		}
	}
}

void firstIntegerTableau(simplexTabTree &tabTree){
	simplexTableaux firstTableaux;
	setInitialTableau(firstTableaux.tableau[0], dgRestricciones, dgRestricciones2, firstTableaux.variableNames);
	firstTableaux.numVar = dgRestricciones->ColumnCount - 2;
	for (int i = 0; i < firstTableaux.numVar; i++){
		if (dgRestricciones3->Rows[0]->Cells[i]->Value != nullptr && dgRestricciones3->Rows[0]->Cells[i]->Value->ToString() == "True"){
			firstTableaux.integerVariable[i] = true;
		}else {
			firstTableaux.integerVariable[i] = false;
		}
	}
	firstTableaux.maxminMode = rbMax->Checked;
	firstTableaux.cont = 1;
	simplex(firstTableaux);
	tabTree.sTableaux = firstTableaux;
	tabTree.activeNode = true;
	tabTree.parent = -1;
	tabTree.leftChild = -1;
	tabTree.rightChild = -1;
}

void solveIntegerSimplex(){
	vector<simplexTabTree> lista;
	bool maxMin = rbMax->Checked;
	fraction inf_c = 0; //superior if it's max
	fraction sup_c = 0; //inferior if it's max
	bool supCote = false; //si no hay cota superior todavia
	int bestNode = 0;
	bool end = false;

	// Solve first simplex
	simplexTabTree tabTreeFirst;
	firstIntegerTableau(tabTreeFirst);
	if (tabTreeFirst.sTableaux.factible && tabTreeFirst.sTableaux.acotado){
		inf_c = -tabTreeFirst.sTableaux.tableau[tabTreeFirst.sTableaux.cont - 1].functionValue;
		if (tabTreeFirst.sTableaux.integer_factible){
			sup_c = -tabTreeFirst.sTableaux.tableau[tabTreeFirst.sTableaux.cont - 1].functionValue;
			supCote = true;
			tabTreeFirst.activeNode = false;
		}
	}
	else tabTreeFirst.activeNode = false;
	if (!tabTreeFirst.activeNode) end = true;
	
	lista.push_back(tabTreeFirst); //Añadimos primer nodo

	int activeNode = 0;
	
	////////////////////////

	while (!end){
		bool leftChild = true;
		simplexTabTree tabTree;
		tabTree.activeNode = true;
		tabTree.parent = activeNode;
		tabTree.leftChild = -1;
		tabTree.rightChild = -1;
		if (lista.at(activeNode).leftChild == -1){
			lista.at(activeNode).leftChild = lista.size();
		}
		else if (lista.at(activeNode).rightChild == -1){
			lista.at(activeNode).rightChild = lista.size();
			lista.at(activeNode).activeNode = false;
			leftChild = false;
		}

		setInitialTableauInteger(lista.at(activeNode).sTableaux, tabTree.sTableaux, leftChild);
		simplex(tabTree.sTableaux);

		if (tabTree.sTableaux.factible){ //no hay necesidad de comprobar que sea acotado
			if (supCote && worseSolution(sup_c, -tabTree.sTableaux.tableau[tabTree.sTableaux.cont - 1].functionValue, maxMin)){
				tabTree.activeNode = false;
			}
			else{
				if (tabTree.sTableaux.integer_factible){ //llegados aqui ya suponemos que esta sol. es mejor que la anterior
					supCote = true;
					sup_c = -tabTree.sTableaux.tableau[tabTree.sTableaux.cont - 1].functionValue;
					tabTree.activeNode = false;
					updateActiveNodes(lista, sup_c, maxMin);
					bestNode = lista.size();
				}
			}
		}
		else {
			tabTree.activeNode = false;
		}
		
		activeNode = lista.size();
		lista.push_back(tabTree); //Metemos nodo en la lista
		updateInferiorCote(lista, inf_c, maxMin);
		if (supCote && inf_c == sup_c)
			end = true;
		else
			end = !searchNextActiveNode(lista, activeNode, inf_c);
	}

	IntegerTreeForm^ tree_f = gcnew IntegerTreeForm(lista, bestNode);
	tree_f->parentForm = this;
	tree_f->Show();
	this->Enabled = false;
}

void solveSimplex(){
	simplexTableaux sTableaux;
	//Fill first Table
	setInitialTableau(sTableaux.tableau[0], dgRestricciones, dgRestricciones2, sTableaux.variableNames);
	sTableaux.numVar = dgRestricciones->ColumnCount - 2;
	for (int i = 0; i < sTableaux.numVar; i++){
		sTableaux.integerVariable[i] = false; //nos da igual, pero inicializamos a false ya que estamos en el caso de prog. no entera
	}
	sTableaux.maxminMode = rbMax->Checked;
	sTableaux.cont = 1;
	simplex(sTableaux); //Simplex Alg.
	TableauForm^ tableau_f = gcnew TableauForm(sTableaux);
	tableau_f->parentForm = this;
	tableau_f->Show();
	this->Enabled = false;
}

void dualProblem(){
	this->evento = true;
	bool a = this->rbMax->Checked;
	setDualProblem(dgRestricciones, dgRestricciones2, dgRestricciones3, a);
	updateRowHeaders();
	this->rbMax->Checked = !a;
	this->rbMin->Checked = a;
	this->evento = false;
}

	private: void updateEnunciado(){
		this->rtxtEnunciado->Clear();
		this->rtxtEnunciado->SelectionFont = (gcnew System::Drawing::Font(L"Arial Unicode MS", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		RichText_setNormalMode(this->rtxtEnunciado);
		if (rbMax->Checked){
			this->rtxtEnunciado->SelectedText = "max\t";
		}
		else{
			this->rtxtEnunciado->SelectedText = "min\t";
		}
		bool first = true;
		bool somethingWritten = false;
		for (int i = 0; i < dgRestricciones->ColumnCount - 2; i++){
			if (!(dgRestricciones->Rows[0]->Cells[i]->Value == nullptr || dgRestricciones->Rows[0]->Cells[i]->Value->ToString() == "" || dgRestricciones->Rows[0]->Cells[i]->Value->ToString() == "0")){
				somethingWritten = true;
				fraction f = convertToFraction(dgRestricciones->Rows[0]->Cells[i]->Value->ToString());
				if (first){
					first = false;
				}
				else if (f < 0){
					this->rtxtEnunciado->SelectedText = " - ";
					f = -f;
				}
				else{
					this->rtxtEnunciado->SelectedText = " + ";
				}
				if (f != 1){
					this->rtxtEnunciado->SelectedText = f.print();
				}
				this->rtxtEnunciado->SelectedText = "x";
				RichText_setSubScriptMode(this->rtxtEnunciado);
				this->rtxtEnunciado->SelectedText = Convert::ToString(i + 1);
				RichText_setNormalMode(this->rtxtEnunciado);
			}
		}
		if (!somethingWritten) this->rtxtEnunciado->SelectedText = "0";

		RichText_newLine(this->rtxtEnunciado);
		for (int i = 1; i < dgRestricciones->RowCount; i++){
			RichText_newLine(this->rtxtEnunciado);
			if (i == 1) this->rtxtEnunciado->SelectedText = "s.a:\t";
			else this->rtxtEnunciado->SelectedText = "\t";
			first = true;
			somethingWritten = false;
			for (int j = 0; j < dgRestricciones->ColumnCount - 2; j++){
				if (!(dgRestricciones->Rows[i]->Cells[j]->Value == nullptr || dgRestricciones->Rows[i]->Cells[j]->Value->ToString() == "" || dgRestricciones->Rows[i]->Cells[j]->Value->ToString() == "0")){
					fraction f = convertToFraction(dgRestricciones->Rows[i]->Cells[j]->Value->ToString());
					if (first){
						first = false;
					}
					else if (f < 0){
						this->rtxtEnunciado->SelectedText = " - ";
						f = -f;
					}
					else{
						this->rtxtEnunciado->SelectedText = " + ";
					}
					if (f != 1){
						this->rtxtEnunciado->SelectedText = f.print();
					}
					this->rtxtEnunciado->SelectedText = "x";
					RichText_setSubScriptMode(this->rtxtEnunciado);
					this->rtxtEnunciado->SelectedText = Convert::ToString(j + 1);
					RichText_setNormalMode(this->rtxtEnunciado);
					somethingWritten = true;
				}
			}
			if (!somethingWritten) this->rtxtEnunciado->SelectedText = "0";
			this->rtxtEnunciado->SelectedText = " ";
			String^ straux = dgRestricciones->Rows[i]->Cells[dgRestricciones->ColumnCount - 2]->Value->ToString();
			if (straux == "<="){
				this->rtxtEnunciado->SelectedText = L"≤";
			}
			else if (straux == ">="){
				this->rtxtEnunciado->SelectedText = L"≥";
			}
			else this->rtxtEnunciado->SelectedText = straux;
			this->rtxtEnunciado->SelectedText = " ";
			fraction f;
			if (dgRestricciones->Rows[i]->Cells[dgRestricciones->ColumnCount - 1]->Value == nullptr || dgRestricciones->Rows[i]->Cells[dgRestricciones->ColumnCount - 1]->Value->ToString() == ""){
				f = 0;
			}
			else{
				f = convertToFraction(dgRestricciones->Rows[i]->Cells[dgRestricciones->ColumnCount - 1]->Value->ToString());
			}
			this->rtxtEnunciado->SelectedText = f.print();
		}
		RichText_newLine(this->rtxtEnunciado);
		RichText_newLine(this->rtxtEnunciado);
		this->rtxtEnunciado->SelectedText = "\t";
		first = true;
		for (int i = 0; i < dgRestricciones->ColumnCount - 2; i++){
			if (first) first = false;
			else this->rtxtEnunciado->SelectedText = ", ";
			this->rtxtEnunciado->SelectedText = "x";
			RichText_setSubScriptMode(this->rtxtEnunciado);
			this->rtxtEnunciado->SelectedText = Convert::ToString(i + 1);
			RichText_setNormalMode(this->rtxtEnunciado);
			this->rtxtEnunciado->SelectedText = " ";
			String^ straux = dgRestricciones2->Rows[0]->Cells[i]->Value->ToString();
			if (straux == "<= 0"){
				this->rtxtEnunciado->SelectedText = L"≤ 0";
			}
			else if (straux == ">= 0"){
				this->rtxtEnunciado->SelectedText = L"≥ 0";
			}
			else this->rtxtEnunciado->SelectedText = straux;
		}
		first = true;
		bool unaVariableEntera = true;
		for (int i = 0; i < dgRestricciones3->ColumnCount; i++){
			if (dgRestricciones3->Rows[0]->Cells[i]->Value != nullptr && dgRestricciones3->Rows[0]->Cells[i]->Value->ToString() == "True"){
				if (first){
					first = false;
					RichText_newLine(this->rtxtEnunciado);
					this->rtxtEnunciado->SelectedText = "\tx";
				}
				else{
					unaVariableEntera = false;
					this->rtxtEnunciado->SelectedText = ", x";
				}
				RichText_setSubScriptMode(this->rtxtEnunciado);
				this->rtxtEnunciado->SelectedText = Convert::ToString(i + 1);
				RichText_setNormalMode(this->rtxtEnunciado);
			}
		}
		 if (!first){
			 this->rtxtEnunciado->SelectedText = L" ";
			this->rtxtEnunciado->SelectionFont = (gcnew System::Drawing::Font(L"DejaVu Serif", 11.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				 static_cast<System::Byte>(0)));
			this->rtxtEnunciado->SelectedText = L"\u03F5 \u2124";
		}
}
private: System::Void checkedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (!this->evento) this->updateEnunciado();
}
private: System::Void dgRestricciones_2_3_CellEndEdit(System::Object^  sender, DataGridViewCellEventArgs^  a) {
	if (!this->evento) this->updateEnunciado();
}
private: System::Void dgRestricciones_CellEndEdit(System::Object^  sender, DataGridViewCellEventArgs^  a) {
			 if (!this->evento){
				 //Si la casilla era un combobox, no hago nada
				 if (dgRestricciones->CurrentCell->ColumnIndex == dgDesigualdad->Index) return;
				 //Si la casilla está vacía
				 if (dgRestricciones->CurrentCell->Value == nullptr || dgRestricciones->CurrentCell->Value->ToString() == ""){
					 return;
				 }
				 //Si no
				 String^ d = dgRestricciones->CurrentCell->Value->ToString();
				 
					try{
						fraction a = convertToFraction(d);
						if (a.denominator() == 0)
							dgRestricciones->CurrentCell->Value = 0;
						else
							dgRestricciones->CurrentCell->Value = a.print();
					}
					catch(FormatException^){
						dgRestricciones->CurrentCell->Value = 0;
					}
				 this->updateEnunciado();
			 }
}
private: System::Void cbAddVariable_Click(System::Object^  sender, System::EventArgs^  e) {
			this->evento = true;
			System::Windows::Forms::DataGridViewTextBoxColumn^ dgNewColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			dgNewColumn->Width = 50;
			dgNewColumn->SortMode = DataGridViewColumnSortMode::NotSortable;
			dgNewColumn->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			dgNewColumn->HeaderText = String::Concat("X", dgRestricciones->ColumnCount - 1);
			dgRestricciones->Columns->Insert(dgRestricciones->ColumnCount-2, dgNewColumn);

			System::Windows::Forms::DataGridViewComboBoxColumn^ dgNewVar = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			dgNewVar->Width = 50;
			dgNewVar->SortMode = DataGridViewColumnSortMode::NotSortable;
			dgNewVar->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			dgNewVar->HeaderText = String::Concat("X", dgRestricciones2->ColumnCount + 1);
			dgNewVar->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L">= 0", L"<= 0", L"s.r." });
			dgRestricciones2->Columns->Insert(dgRestricciones2->ColumnCount, dgNewVar);
			dgRestricciones2->Rows[0]->Cells[dgRestricciones2->ColumnCount - 1]->Value = ">= 0";

			System::Windows::Forms::DataGridViewCheckBoxColumn^ dgNewVar2 = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
			dgNewVar2->Width = 50;
			dgNewVar2->SortMode = DataGridViewColumnSortMode::NotSortable;
			dgNewVar2->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			dgNewVar2->HeaderText = String::Concat("X", dgRestricciones3->ColumnCount + 1);
			dgRestricciones3->Columns->Insert(dgRestricciones3->ColumnCount, dgNewVar2);

		

			this->evento = false;
			this->updateEnunciado();
}
private: System::Void cbRemoveVariable_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->evento = true;
			 if (dgRestricciones->ColumnCount > 3){
				 dgRestricciones->Columns->RemoveAt(dgRestricciones->ColumnCount - 3);
				 dgRestricciones2->Columns->RemoveAt(dgRestricciones2->ColumnCount - 1);
				 dgRestricciones3->Columns->RemoveAt(dgRestricciones2->ColumnCount - 1);
			 }
			 this->evento = false;
			 this->updateEnunciado();
}
private: System::Void cbAddRestriction_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->evento = true;
			 dgRestricciones->Rows->Insert(dgRestricciones->RowCount, gcnew array<String^>{""});
			 dgRestricciones->Rows[dgRestricciones->RowCount - 1]->Cells[dgDesigualdad->Index]->Value = "<=";
			 updateRowHeaders();
			 this->evento = false;
			 this->updateEnunciado();
}
private: System::Void cbRemoveRestriction_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->evento = true;
			 if (dgRestricciones->RowCount > 2){
				 dgRestricciones->Rows->RemoveAt(dgRestricciones->RowCount - 1);
				 updateRowHeaders();
			 }
			 this->evento = false;
			 this->updateEnunciado();
}
private: System::Void cbSolve_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->evento = true;
			 fillEmptyCells();
			 bool integerProblem = false;
			 for (int i = 0; i < dgRestricciones3->ColumnCount; i++){
				 if (dgRestricciones3->Rows[0]->Cells[i]->Value != nullptr && dgRestricciones3->Rows[0]->Cells[i]->Value->ToString() == "True")
					integerProblem = true;
			 }
			 if (integerProblem)
				 solveIntegerSimplex();
			 else
				 solveSimplex();
			 this->evento = false;
}

private: System::Void cbDual_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->evento = true;
			 fillEmptyCells();
			 dualProblem();
			 this->evento = false;
			 this->updateEnunciado();
}
private: System::Void msQuit_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
}
private: System::Void msAbout_Click(System::Object^  sender, System::EventArgs^  e) {
			 MessageBox::Show("Resolutor de Simplex - David Roldán Santos", "Acerca de Resolutor de Simplex",
				 MessageBoxButtons::OK, MessageBoxIcon::Information);
}
private: System::Void msHelp_Click(System::Object^  sender, System::EventArgs^  e) {
			 MessageBox::Show(String::Concat(
				 "- Problema Dual: \n\n"
				 "\t Plantea el problema dual del problema introducido por el usuario.\n",
				 "\n\n",

				 "- Resolución del Algoritmo: \n\n",
				 "\t 1. La solución de todas las tablas del Simplex se realizan mediante el algoritmo primal.\n",
				 "\t 2. El programa sólo detecta una solución óptima. (No detecta ni segundas soluciones ni direcciones extremas)\n",
				 "\t 3. La resolución de los problemas de programación entera se realizan por el método de ramificación y acotación.\n"
				
				 ), "Ayuda", MessageBoxButtons::OK);
}
};
}

