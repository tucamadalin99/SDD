#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;


struct librarie {
	int cod;
	char* name;
	int nrCarti;
};

struct nodArb {
	nodArb* left;
	nodArb* right;
	librarie info;
};

nodArb *creare(librarie s, nodArb *st, nodArb *dr)
{
	nodArb *nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.cod = s.cod;
	nou->info.name = (char*)malloc((strlen(s.name) + 1) * sizeof(char));
	strcpy(nou->info.name, s.name);
	nou->info.nrCarti = s.nrCarti;
	nou->left = st;
	nou->right = dr;
	return nou;
}

nodArb *inserare(librarie s, nodArb *rad)
{
	nodArb *aux = rad;
	if (rad == NULL)
	{
		aux = creare(s, NULL, NULL);
		return aux;
	}
	else
		while (true)
		{
			if (strlen(s.name) < strlen(aux->info.name))
				if (aux->left != NULL)
					aux = aux->left;
				else
				{
					aux->left = creare(s, NULL, NULL);
					return rad;
				}
			else
				if (strlen(s.name) > strlen(aux->info.name))
					if (aux->right != NULL)
						aux = aux->right;
					else
					{
						aux->right = creare(s, NULL, NULL);
						return rad;
					}
				else
					return rad;
		}
}

void inordine(nodArb *rad)
{
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nCod=%d, Nume=%s, NrCarti=%d", rad->info.cod, rad->info.name, rad->info.nrCarti);
		inordine(rad->right);
	}
}


//void postordine(nodArb *rad)
//{
//	if (rad != NULL)
//	{
//		postordine(rad->left);
//		postordine(rad->right);
//		printf("\nCod=%d, Nume=%s, Medie=%5.2f, BF=%d", rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
//	}
//}
void afiseazaLib(librarie l){
	printf("%d %s %d\n", l.cod, l.name, l.nrCarti);
}

//int numaraFrunze(nodArb* rad) {
//	if (rad == NULL)
//		return 0;
//		if (rad->left == NULL && rad->right == NULL)
//			return 1;
//		else
//		numaraFrunze(rad->left) + numaraFrunze(rad->right);
//
//}

void numaraFrunze(nodArb* rad, int*nr) {

	if (rad) {
		numaraFrunze(rad->left, nr);
		if (rad->left == NULL && rad->right == NULL) {
			(*nr)++;
		}
		numaraFrunze(rad->right, nr);
	}

}

void inserareFrunze(nodArb* rad, int &nr, int* &vect) {
	if (rad) {
		inserareFrunze(rad->left, nr, vect);
		if (rad->left == NULL && rad->right == NULL) {
			vect[nr--] = strlen(rad->info.name);
			//printf("%d ", strlen(rad->info.nume));
		}
		inserareFrunze(rad->right, nr, vect);

	}
}



nodArb* copiereCriteriu(nodArb* rad, int nrCarti, nodArb*& nou) {
	//if (nrCarti > rad->info.nrCarti) {
	if (rad != NULL) {
		copiereCriteriu(rad->left, nrCarti, nou); //FARA SA IL PUI IN IF DEOARECE TREBUIE SA PARCURGA TOT ARBORELE
		if (nrCarti < rad->info.nrCarti) { //TRATEZI DOAR RADACINA NU SI NODURILE
			nou = inserare(rad->info, nou);
		}
		copiereCriteriu(rad->right, nrCarti, nou);
	}
	//}
	
	return nou;
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

nodArb* stergeNod(nodArb* rad, int cheie) { //Stergere dupa cheie
	if (rad == NULL)
		return NULL;
	else
		if (rad->info.cod == cheie) {
			rad = stergeRad(rad);
			return rad;
		}
		else {
			nodArb* aux = rad;
			while (true) {
				if (cheie < aux->info.cod) {
					//Cautam pe stanga
					if (aux->left == NULL)
						break;
					else if (aux->left->info.cod == cheie) {
						//Daca l-am gasit pe stanga primul fiu de stanga
						aux->left = stergeRad(aux->left);
					}
					else
						aux = aux->left;//mergem in continuare pe stang;
				}
				else if (cheie > aux->info.cod) {
					if (aux->right == NULL)
						break;
					else if (aux->right->info.cod == cheie)
						aux->right = stergeRad(aux->right);
					else aux = aux->right;
				}
			}
			return rad;
		}

}

void dezalocare(nodArb* rad) {
	if (rad != NULL) {
		//Post sa traversez cu orice ordine vreau
		nodArb* stanga = rad->left;//toti fii de stanga
		nodArb* dreapta = rad->right; // toti fii din dreapta ii salvam
		free(rad->info.name);
		free(rad);
		dezalocare(stanga);
		dezalocare(dreapta);

	}
}


void main() {

	int n;

	FILE* f = fopen("librarii.txt", "r");

	//printf("Nr. libarrii: ");
	fscanf(f, "%d", &n);

	nodArb *rad = NULL;
	librarie l;
	char buffer[20];

	for (int i = 0; i < n; i++)
	{
		//printf("\nCod: ");
		fscanf(f, "%d", &l.cod);
		//printf("\nNume: ");
		fscanf(f, "%s", buffer);
		l.name = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(l.name, buffer);
		//printf("\nMedie: ");
		fscanf(f, "%d", &l.nrCarti);

		rad = inserare(l, rad);

	}
	fclose(f);

	printf("\n----------------\n");
	inordine(rad);

	nodArb* arb2 = NULL;
	arb2 = copiereCriteriu(rad, 210, arb2);
	printf("\n----------------\n");
	inordine(arb2);
	rad = stergeNod(rad, 3);
	printf("\n----------------\n");
	inordine(rad);
	printf("\n----------------\n");
	int nr = 0;
	numaraFrunze(rad, &nr);
	int* vect = (int*)malloc(sizeof(int) * nr);
	inserareFrunze(rad, nr, vect);
	numaraFrunze(rad, &nr);
	for (int i = 1; i <= nr; i++) {
		printf("%d ", vect[i]);
	}
	printf("\n%d", nr);

	dezalocare(rad);
	dezalocare(arb2);
	
	


}