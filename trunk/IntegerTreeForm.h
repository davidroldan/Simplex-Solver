#pragma once
#include "CustomButton.h"
#include "TableauForm.h"
#include "DataTypes.h"
#include <vector>
#include <cliext/vector> 

#define _NODE_SIZE 25

namespace SimplexSolver {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de IntegerTreeForm
	/// </summary>

	public ref class IntegerTreeForm : public System::Windows::Forms::Form
	{
	public:
		IntegerTreeForm(vector<simplexTabTree> &lista, int bestNode)
		{
			*lista_nodos = lista;
			this->tree_depth = this->getTreeDepth();
			InitializeComponent();
			this->txtSolOptima->Text = (-lista.at(bestNode).sTableaux.tableau[lista.at(bestNode).sTableaux.cont - 1].functionValue).print();
			this->txtSolutionNode->Text = System::Convert::ToString(bestNode);
			this->myPanel->MouseClick += gcnew MouseEventHandler(this, &IntegerTreeForm::myPanel_MouseClick);
			InitializeNode(lista_nodos->at(0), 0, 0, 0, 1);
			this->updateNodeDetails(0);
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén utilizando.
		/// </summary>
		~IntegerTreeForm()
		{
			delete lista_nodos;
			if (components)
			{
				delete components;
			}
			parentForm->Enabled = true;
		}
	public: System::Windows::Forms::Form^ parentForm; //Puntero a la ventanta anterior
	private: System::Windows::Forms::Panel^  myPanel;
	private: vector<simplexTabTree> *lista_nodos = new vector<simplexTabTree>();
	private: cliext::vector<CustomButton^> nodeVector;
	private: int tree_depth;
	private: System::Windows::Forms::Button^  cbViewTable;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  lblCurrentNode;
	private: System::Windows::Forms::TextBox^  txtProblemType;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  txtCurrentNode;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::TextBox^  txtSolutionNode;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  txtSolOptima;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  txtNewRestriction;
	private: System::Windows::Forms::Label^  labelRestr;
	private: System::Windows::Forms::TextBox^  txtPartialSolution;
	private: System::Windows::Forms::Label^  label4;



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
		int getTreeDepth(){
			int d = 1;
			for (int i = 0; i < lista_nodos->size(); i++){
				simplexTabTree tabTree = lista_nodos->at(i);
				int d_2 = 1;
				while (tabTree.parent != -1){
					tabTree = lista_nodos->at(tabTree.parent);
					d_2++;
				}
				if (d_2 > d) d = d_2;
			}
			return d;
		}
		void InitializeNode(simplexTabTree &tabTree, int curDepth, int currentNode, int position, int positionTotal){
			CustomButton^  node = (gcnew CustomButton());
			this->myPanel->Controls->Add(node);
			int height = this->myPanel->Height - _NODE_SIZE - 20;
			int width = this->myPanel->Width - _NODE_SIZE;
			if (curDepth == 0){
				node->Location = System::Drawing::Point((this->myPanel->Width - _NODE_SIZE) / 2, 10);
			}
			else{
				node->Location = System::Drawing::Point(10 + width / (positionTotal + 1) * (position + 1), 10 + height / (tree_depth - 1) * curDepth);
			}
			node->Visible = false; //Invisibles
			node->Name = String::Concat("node", Convert::ToString(currentNode));
			node->Size = System::Drawing::Size(_NODE_SIZE, _NODE_SIZE);
			node->Text = Convert::ToString(currentNode);
			node->Click += gcnew System::EventHandler(this, &IntegerTreeForm::node_Click);
			nodeVector.push_back(node);
			if (tabTree.leftChild != -1){
				InitializeNode(lista_nodos->at(tabTree.leftChild), curDepth + 1, tabTree.leftChild, position*2, positionTotal*2);
			}
			if (tabTree.rightChild != -1){
				InitializeNode(lista_nodos->at(tabTree.rightChild), curDepth + 1, tabTree.rightChild, position*2+1, positionTotal*2);
			}
		}
		void InitializeComponent(void)
		{
			this->myPanel = (gcnew System::Windows::Forms::Panel());
			this->cbViewTable = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->txtPartialSolution = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->txtNewRestriction = (gcnew System::Windows::Forms::TextBox());
			this->labelRestr = (gcnew System::Windows::Forms::Label());
			this->txtProblemType = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtCurrentNode = (gcnew System::Windows::Forms::TextBox());
			this->lblCurrentNode = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->txtSolutionNode = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtSolOptima = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// myPanel
			// 
			this->myPanel->BackColor = System::Drawing::SystemColors::Control;
			this->myPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->myPanel->Location = System::Drawing::Point(12, 12);
			this->myPanel->Name = L"myPanel";
			this->myPanel->Size = System::Drawing::Size(518, 438);
			this->myPanel->TabIndex = 0;
			this->myPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &IntegerTreeForm::myPanel_OnPaint);
			// 
			// cbViewTable
			// 
			this->cbViewTable->Location = System::Drawing::Point(6, 242);
			this->cbViewTable->Name = L"cbViewTable";
			this->cbViewTable->Size = System::Drawing::Size(143, 52);
			this->cbViewTable->TabIndex = 1;
			this->cbViewTable->Text = L"Ver Tabla Simplex";
			this->cbViewTable->UseVisualStyleBackColor = true;
			this->cbViewTable->Click += gcnew System::EventHandler(this, &IntegerTreeForm::cbViewTable_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->txtPartialSolution);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->txtNewRestriction);
			this->groupBox1->Controls->Add(this->labelRestr);
			this->groupBox1->Controls->Add(this->txtProblemType);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->txtCurrentNode);
			this->groupBox1->Controls->Add(this->lblCurrentNode);
			this->groupBox1->Controls->Add(this->cbViewTable);
			this->groupBox1->Location = System::Drawing::Point(536, 146);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(155, 300);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Nodo";
			// 
			// txtPartialSolution
			// 
			this->txtPartialSolution->Location = System::Drawing::Point(17, 193);
			this->txtPartialSolution->Name = L"txtPartialSolution";
			this->txtPartialSolution->ReadOnly = true;
			this->txtPartialSolution->Size = System::Drawing::Size(124, 20);
			this->txtPartialSolution->TabIndex = 9;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(14, 177);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(51, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Solución:";
			// 
			// txtNewRestriction
			// 
			this->txtNewRestriction->Location = System::Drawing::Point(16, 142);
			this->txtNewRestriction->Name = L"txtNewRestriction";
			this->txtNewRestriction->ReadOnly = true;
			this->txtNewRestriction->Size = System::Drawing::Size(124, 20);
			this->txtNewRestriction->TabIndex = 7;
			// 
			// labelRestr
			// 
			this->labelRestr->AutoSize = true;
			this->labelRestr->Location = System::Drawing::Point(13, 126);
			this->labelRestr->Name = L"labelRestr";
			this->labelRestr->Size = System::Drawing::Size(93, 13);
			this->labelRestr->TabIndex = 6;
			this->labelRestr->Text = L"Nueva restricción:";
			// 
			// txtProblemType
			// 
			this->txtProblemType->Location = System::Drawing::Point(16, 91);
			this->txtProblemType->Name = L"txtProblemType";
			this->txtProblemType->ReadOnly = true;
			this->txtProblemType->Size = System::Drawing::Size(124, 20);
			this->txtProblemType->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 75);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(31, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Tipo:";
			// 
			// txtCurrentNode
			// 
			this->txtCurrentNode->Location = System::Drawing::Point(55, 38);
			this->txtCurrentNode->Name = L"txtCurrentNode";
			this->txtCurrentNode->ReadOnly = true;
			this->txtCurrentNode->Size = System::Drawing::Size(85, 20);
			this->txtCurrentNode->TabIndex = 3;
			this->txtCurrentNode->Text = L"0";
			// 
			// lblCurrentNode
			// 
			this->lblCurrentNode->AutoSize = true;
			this->lblCurrentNode->Location = System::Drawing::Point(13, 41);
			this->lblCurrentNode->Name = L"lblCurrentNode";
			this->lblCurrentNode->Size = System::Drawing::Size(36, 13);
			this->lblCurrentNode->TabIndex = 2;
			this->lblCurrentNode->Text = L"Nodo:";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->txtSolutionNode);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->txtSolOptima);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Location = System::Drawing::Point(536, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(154, 128);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Resultado";
			// 
			// txtSolutionNode
			// 
			this->txtSolutionNode->Location = System::Drawing::Point(101, 81);
			this->txtSolutionNode->Name = L"txtSolutionNode";
			this->txtSolutionNode->ReadOnly = true;
			this->txtSolutionNode->Size = System::Drawing::Size(40, 20);
			this->txtSolutionNode->TabIndex = 7;
			this->txtSolutionNode->Text = L"0";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(14, 84);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(81, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Nodo solución: ";
			// 
			// txtSolOptima
			// 
			this->txtSolOptima->Location = System::Drawing::Point(16, 43);
			this->txtSolOptima->Name = L"txtSolOptima";
			this->txtSolOptima->ReadOnly = true;
			this->txtSolOptima->Size = System::Drawing::Size(124, 20);
			this->txtSolOptima->TabIndex = 5;
			this->txtSolOptima->Text = L"0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(14, 27);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(85, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Solución óptima:";
			// 
			// IntegerTreeForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(704, 462);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->myPanel);
			this->MaximumSize = System::Drawing::Size(720, 500);
			this->MinimumSize = System::Drawing::Size(720, 500);
			this->Name = L"IntegerTreeForm";
			this->Text = L"Árbol Problema Entero";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: void updateNodeDetails(int currentNode){
		if (!lista_nodos->at(currentNode).sTableaux.acotado){
			this->txtProblemType->Text = "NO ACOTADO";
		}
		else if (lista_nodos->at(currentNode).sTableaux.integer_factible){
			this->txtProblemType->Text = "FACTIBLE";
		}
		else if (!lista_nodos->at(currentNode).sTableaux.factible){
			this->txtProblemType->Text = "INFACTIBLE";
		}
		else{
			this->txtProblemType->Text = "FACTIBLE NO ENTERO";
		}
		if (currentNode == 0){
			this->txtNewRestriction->Text = "";
		}
		else{
			int parent = lista_nodos->at(currentNode).parent;
			bool leftChild = (currentNode == lista_nodos->at(parent).leftChild);
			int num;
			int variable = -1;
			for (int i = 0; i < lista_nodos->at(parent).sTableaux.numVar; i++){
				if (variable == -1){
					if (lista_nodos->at(parent).sTableaux.integerVariable[i] && lista_nodos->at(parent).sTableaux.solution[i].denominator() != 1){
						variable = i;
						num = lista_nodos->at(parent).sTableaux.solution[i].numerator() / lista_nodos->at(parent).sTableaux.solution[i].denominator();
						if (lista_nodos->at(parent).sTableaux.solution[i] < 0) num--; //para que el redondeo vaya al numero menor en caso de negativo
						if (!leftChild) num++;
					}
				}
			}
			this->txtNewRestriction->Text = String::Concat("X", Convert::ToString(variable + 1), " ");
			if (leftChild) this->txtNewRestriction->Text += "<= ";
			else this->txtNewRestriction->Text += ">= ";
			this->txtNewRestriction->Text += Convert::ToString(num);
		}
		if (!lista_nodos->at(currentNode).sTableaux.acotado || !lista_nodos->at(currentNode).sTableaux.factible){
			this->txtPartialSolution->Text = "";
		}
		else{
			this->txtPartialSolution->Text = (- lista_nodos->at(currentNode).sTableaux.tableau[lista_nodos->at(currentNode).sTableaux.cont - 1].functionValue).print();
		}
	}
	private: System::Void cbViewTable_Click(System::Object^  sender, System::EventArgs^  e) {
		int curNode = System::Convert::ToInt16(this->txtCurrentNode->Text);
		TableauForm^ tableau_f = gcnew TableauForm(lista_nodos->at(curNode).sTableaux);
		tableau_f->parentForm = this;
		tableau_f->Show();
		this->Enabled = false;
	}
	private: System::Void node_Click(System::Object^  sender, System::EventArgs^  e) {
		CustomButton^ node = (CustomButton^)sender;
		this->txtCurrentNode->Text = node->Text;
		this->updateNodeDetails(System::Convert::ToInt16(this->txtCurrentNode->Text));
		this->myPanel->Invalidate(); //Force paint
	}
	private: void drawNode(Graphics ^ g, int currentNode){
		System::Drawing::SolidBrush^ ellipseBrush;
		if (lista_nodos->at(currentNode).sTableaux.integer_factible){
			ellipseBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Blue);
		}
		else if (!lista_nodos->at(currentNode).sTableaux.factible){
			ellipseBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Red);
		}
		else{
			ellipseBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);
		}
		CustomButton^ node;
		for (int i = 0; i < nodeVector.size(); i++){
			if (System::Convert::ToInt16(nodeVector.at(i)->Text) == currentNode){
				node = nodeVector.at(i);
				break;
			}
		}
		int x = node->Location.X;
		int y = node->Location.Y;
		RectangleF rect = RectangleF(x, y, _NODE_SIZE, _NODE_SIZE);
		StringFormat^ sf = gcnew StringFormat();
		sf->LineAlignment = StringAlignment::Center;
		sf->Alignment = StringAlignment::Center;
		Pen^ blackPen = gcnew Pen(Color::Black, 1.5f);
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 12);
		SolidBrush^ stringBrush;
		if (currentNode == System::Convert::ToInt16(this->txtCurrentNode->Text))
			stringBrush = gcnew SolidBrush(Color::Goldenrod);
		else
			stringBrush = gcnew SolidBrush(Color::White);
		g->FillEllipse(ellipseBrush, rect);
		g->DrawEllipse(blackPen, rect);
		g->DrawString(Convert::ToString(currentNode), drawFont, stringBrush, rect, sf);
		delete stringBrush;
		delete ellipseBrush;
		delete sf;
		delete blackPen;
	}
	private: void drawLine(Graphics ^ g, int x1, int y1, int x2, int y2){
		Pen^ blackPen = gcnew Pen(Color::Black, 1.5f);
		g->DrawLine(blackPen, x1, y1 + 24, x2, y2 + 24);
		delete blackPen;
	}
	private: System::Void myPanel_OnPaint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^ e){
		for (int i = 0; i < lista_nodos->size(); i++){
			drawNode(e->Graphics, i);
			if (lista_nodos->at(i).parent != -1){
				bool leftNode = (lista_nodos->at(lista_nodos->at(i).parent).leftChild == i);
				CustomButton^ node;
				CustomButton^ nodeParent;
				for (int j = 0; j < nodeVector.size(); j++){
					if (System::Convert::ToInt16(nodeVector.at(j)->Text) == i){
						node = nodeVector.at(j);
					}
					if (System::Convert::ToInt16(nodeVector.at(j)->Text) == lista_nodos->at(i).parent){
						nodeParent = nodeVector.at(j);
					}
				}
				if (leftNode){
					drawLine(e->Graphics, node->Location.X + _NODE_SIZE / 2, node->Location.Y - _NODE_SIZE, nodeParent->Location.X + _NODE_SIZE / 2 - 2, nodeParent->Location.Y -2);
				}
				else{
					drawLine(e->Graphics, node->Location.X + _NODE_SIZE / 2, node->Location.Y - _NODE_SIZE, nodeParent->Location.X + _NODE_SIZE / 2 + 2, nodeParent->Location.Y -2);
				}
			}
		}
	}
	private: System::Void myPanel_MouseClick(System::Object^  sender, MouseEventArgs^  e) {
		for (int i = 0; i < nodeVector.size(); i++){
			int x = nodeVector.at(i)->Location.X;
			int y = nodeVector.at(i)->Location.Y;
			if (e->X >= x && e->X <= x + _NODE_SIZE && e->Y >= y && e->Y <= y + _NODE_SIZE){
				node_Click(nodeVector.at(i), e);
			}
		}
	}
	};
}
