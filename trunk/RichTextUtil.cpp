#include "stdafx.h"
#include "RichTextUtil.h"

#define LESS_EQUAL
#define MORE_EQUAL

void RichText_setNormalMode(System::Windows::Forms::RichTextBox^ textBox){
	textBox->SelectionFont = (gcnew System::Drawing::Font(L"Arial Unicode MS", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	textBox->SelectionCharOffset = 0;
}
void RichText_setSubScriptMode(System::Windows::Forms::RichTextBox^ textBox){
	textBox->SelectionFont = (gcnew System::Drawing::Font(L"Arial Unicode MS", 6.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	textBox->SelectionCharOffset = -4;
}
void RichText_newLine(System::Windows::Forms::RichTextBox^ textBox){
	textBox->SelectedText = "\n";
	RichText_setNormalMode(textBox);
}
void RichText_test(System::Windows::Forms::RichTextBox^ textBox){

}
