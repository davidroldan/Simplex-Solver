#ifndef _INT_PFUNC
#define _INT_PFUNC
#include "DataTypes.h"
#include <vector>

bool searchNextActiveNode(vector<simplexTabTree> &lista, int &activeNode, fraction inf_c);
bool worseSolution(fraction sup_c, fraction a, bool maxMin);
void updateActiveNodes(vector<simplexTabTree> &lista, fraction sup_c, bool maxMin);
void updateInferiorCote(vector<simplexTabTree> lista, fraction &inf_c, bool maxMin);

#endif