// SimplexSolver.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include "MainWindow.h"

using namespace SimplexSolver;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Habilitar los efectos visuales de Windows XP antes de crear ningún control
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Crear la ventana principal y ejecutarla
	Application::Run(gcnew MainWindow());
	return 0;
}
