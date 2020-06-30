#include<stdio.h>
#include <stdlib.h>
#include <string>

struct aparat {
	float pret;
	char* firma;
	char* model;
	int consumEnergie;
};

struct nodArb{
	aparat info;
	nodArb* left;
	nodArb* right;
};



nodArb* creare(aparat s, nodArb* st, nodArb* dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.pret = s.pret;
	nou->info.firma = (char*)malloc(sizeof(char)  * (strlen(s.firma) + 1));
	strcpy(nou->info.firma, s.firma);
	nou->info.model = (char*)malloc(sizeof(char) * (strlen(s.model) + 1));
	strcpy(nou->info.model, s.model);
	nou->info.consumEnergie = s.consumEnergie;
	nou->left = st;
	nou->right = dr;
	return nou;
}

float extragePretRad(nodArb* rad, float& pret) {
	if (rad != NULL) {
		pret = rad->info.pret;
		return pret;
	}
	
	return 0;
}

float cautaMinPret(nodArb* rad, float& pret) {
	if (rad != NULL) {
		cautaMinPret(rad->left, pret);
		if (rad->info.pret < pret) {
			pret = rad->info.pret;
		}
		cautaMinPret(rad->right, pret);
		return pret;
	}
	return 0;
}

nodArb* inserare(aparat s, nodArb* radacina) {

	nodArb* aux = radacina;
	//Verificam cazurile
	if (radacina == NULL) {
		aux = creare(s, NULL, NULL);
		return aux;
	}
	else
		while (true) {
			if (s.pret< aux->info.pret)
				if (aux->left != NULL)//Daca exista fiu stang
					aux = aux->left; // M-am dus pe ramura stanga
				else
				{
					//Daca nu exista, atunci il creez eu
					aux->left = creare(s, NULL, NULL);
					return radacina;
				}
			else if (s.pret > aux->info.pret)
				if (aux->right != NULL)//Daca exista fiu dreapta
					aux = aux->right; //Ma duc pe dreapta
				else {
					//Daca nu exista, creez
					aux->right = creare(s, NULL, NULL);
					return radacina;
				}
			else
				return radacina; // Daca exista deja, e duplicat, ies direct

		}
}

void preordine(nodArb* rad) { //RSD
	if (rad != NULL) {//Daca exista radacina
		printf("\n Pret: %5.2f -> Firma: %s -> Model: %s -> Consum: %d kW\n", rad->info.pret, rad->info.firma, rad->info.model, rad->info.consumEnergie);
		preordine(rad->left);
		preordine(rad->right);
	}
}

nodArb* stergeRad(nodArb* rad) {
	nodArb* aux = rad;
	if (aux->left != NULL) { // Verificam daca are subarbore stang
		rad = aux->left; // Noua radacina devine fiul de stanga
		if (aux->right != NULL) {
			nodArb* temp = aux->left; //Determinam max din arborele stang ca sa legam
			while (temp->right != NULL)
				temp = temp->right;

			temp->right = aux->right;
		}
	}
	else if (aux->right != NULL)
		rad = aux->right;
	else
		rad = NULL;
	//	free(aux->info.nume);
	free(aux);
	return rad;
}

nodArb* extrageAparat(nodArb* rad, float pret) {
	aparat a;
	nodArb* extras = (nodArb*)malloc(sizeof(nodArb));
	if (rad != NULL) {
		if (rad->info.pret == pret) {
			extras->info.firma = (char*)malloc(sizeof(char) * (strlen(rad->info.firma) + 1));
			strcpy(extras->info.firma, rad->info.firma);
			extras->info.model = (char*)malloc(sizeof(char) * (strlen(rad->info.model) + 1));
			strcpy(extras->info.model, rad->info.model); 
				extras->info.pret = rad->info.pret;
				extras->info.consumEnergie = rad->info.consumEnergie;
			extras->left = NULL;
			extras->right = NULL;
			//rad = stergeRad(rad);
			return extras;
		}
		extrageAparat(rad->left, pret);
		if (rad->info.pret == pret) {
			extras->info.firma = (char*)malloc(sizeof(char) * (strlen(rad->info.firma) + 1));
			strcpy(extras->info.firma, rad->info.firma);
			extras->info.model = (char*)malloc(sizeof(char) * (strlen(rad->info.model) + 1));
			strcpy(extras->info.model, rad->info.model);
			extras->info.pret = rad->info.pret;
			extras->info.consumEnergie = rad->info.consumEnergie;
			extras->left = NULL;
			extras->right = NULL;
			//rad = stergeRad(rad);
			return extras;
		}
		extrageAparat(rad->right, pret);
	}
	return NULL;
}

nodArb* stergeNod(nodArb* rad, float pret) { //Stergere dupa cheie
	nodArb* extras = (nodArb*)malloc(sizeof(nodArb));
	if (rad == NULL)
		return NULL;
	else
		if (rad->info.pret == pret) {
			extras->info = rad->info;
			extras->left = NULL;
			extras->right = NULL;
			rad = stergeRad(rad);
			return extras;
		}
		else {
			nodArb* aux = rad;
			while (true) {
				if (pret < aux->info.pret) {
					//Cautam pe stanga
					if (aux->left == NULL)
						break;
					else if (aux->left->info.pret == pret) {
						//Daca l-am gasit pe stanga primul fiu de stanga
						aux->left = stergeRad(aux->left);
					}
					else
						aux = aux->left;//mergem in continuare pe stang;
				}
				else if (pret > aux->info.pret) {
					if (aux->right == NULL)
						break;
					else if (aux->right->info.pret == pret)
						aux->right = stergeRad(aux->right);
					else aux = aux->right;
				}
			}
			return extras;
		}

}

float cautaPretMax(nodArb* rad, float &pret) {
	if (rad != NULL) {
		cautaPretMax(rad->left, pret);
		if (rad->info.pret > pret) {
			pret = rad->info.pret;
		}
		cautaPretMax(rad->right, pret);

		return pret;
	}
	return 0;
}

void dezalocare(nodArb* rad) {
	if (rad != NULL) {
		//Post sa traversez cu orice ordine vreau
		nodArb* stanga = rad->left;//toti fii de stanga
		nodArb* dreapta = rad->right; // toti fii din dreapta ii salvam
		//free(rad->info.nume);
		free(rad->info.firma);
		free(rad->info.model);
		free(rad);
		dezalocare(stanga);
		dezalocare(dreapta);

	}
}

int main() {
	int n;

	FILE* f = fopen("aparate.txt", "r");

	//printf("Nr. libarrii: ");
	fscanf(f, "%d", &n);

	nodArb *rad = NULL;
	aparat a;
	char buffer[20];

	for (int i = 0; i < n; i++)
	{
		//printf("\nCod: ");
		fscanf(f, "%f", &a.pret);
		//printf("\nNume: ");
		fscanf(f, "%s", buffer);
		a.firma = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(a.firma, buffer);
		fscanf(f, "%s", buffer);
		a.model = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(a.model, buffer);
		fscanf(f, "%d", &a.consumEnergie);

		rad = inserare(a, rad);

	}
	fclose(f);

	printf("\n----------------\n");
	preordine(rad);
	printf("\n----------------\n");
	float pret = 0; extragePretRad(rad, pret);
	pret = cautaMinPret(rad, pret);
	printf("Cel mai mic pret din arbore: %5.2f\n", pret);
	float pretMax = 0;
	pretMax = cautaPretMax(rad, pretMax);
	printf("Cel mai mare pret din arbore: %5.2f\n", pretMax);
	//aparat sters;
	nodArb* sters = NULL;
	//sters = extrageAparat(rad, pretMax);
	sters = stergeNod(rad, pret);
	preordine(sters);
	//printf("\n Pret: %5.2f -> Firma: %s -> Model: %s -> Consum: %d kW\n", sters.pret, sters.firma, sters.model, sters.consumEnergie);*/
	printf("\n Arbore cu element extras: \n");
	preordine(rad);

	return 0;
}