#ifndef _INIC_TABLEAU
#define _INIC_TABLEAU

#include "DataTypes.h"

void setInitialTableau(tableauData &tableau, System::Windows::Forms::DataGridView^ dataGrid, System::Windows::Forms::DataGridView^ dataGrid2, string *variableNames);
void setInitialTableauInteger(simplexTableaux &t1, simplexTableaux &t2, bool leftChild);
#endif