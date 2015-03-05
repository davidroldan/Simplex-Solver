#include "stdafx.h"
#include "IntegerProblemFunctions.h"

bool searchNextActiveNode(vector<simplexTabTree> &lista, int &activeNode, fraction inf_c){
	for (int i = 0; i < lista.size(); i++){
		if (lista.at(i).activeNode){
			if (-lista.at(i).sTableaux.tableau[lista.at(i).sTableaux.cont - 1].functionValue == inf_c){
				activeNode = i;
				return true;
			}
		}
	}
	return false;
	/*while (!lista.at(activeNode).activeNode){
		activeNode = lista.at(activeNode).parent;
		if (activeNode == -1) return false;
	}
	return true;*/
}

bool worseSolution(fraction sup_c, fraction a, bool maxMin){
	if (maxMin){
		if (a > sup_c) return false;
	}
	else{
		if (a < sup_c) return false;
	}
	return true;
}

void updateActiveNodes(vector<simplexTabTree> &lista, fraction sup_c, bool maxMin){
	for (int i = 0; i < lista.size(); i++){
		if (lista.at(i).activeNode){
			fraction optimo = - lista.at(i).sTableaux.tableau[lista.at(i).sTableaux.cont - 1].functionValue;
			if (worseSolution(sup_c, optimo, maxMin)){
				lista.at(i).activeNode = false;
			}
		}
	}
}

void updateInferiorCote(vector<simplexTabTree> lista, fraction &inf_c, bool maxMin){
	bool inf = false;
	for (int i = 0; i < lista.size(); i++){
		if (lista.at(i).activeNode){
			fraction optimo = -lista.at(i).sTableaux.tableau[lista.at(i).sTableaux.cont - 1].functionValue;
			if (!inf){
				inf = true;
				inf_c = optimo;
			}
			else{
				if (maxMin){
					if (optimo > inf_c) inf_c = optimo;
				}
				else{
					if (optimo < inf_c) inf_c = optimo;
				}
			}
		}
	}
}