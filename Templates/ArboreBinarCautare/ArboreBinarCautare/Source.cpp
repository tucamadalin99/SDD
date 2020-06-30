#include <stdio.h>
#include <stdlib.h>
#include <string>

struct student {
	int cod;
	char* nume;
	float medie;
};

struct nodArb {
	int BF; //daca ia val > 2 e dezechilibrat
	student info;
	nodArb* left;
	nodArb* right;
};


nodArb* creare(student s, nodArb* st, nodArb* dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.cod = s.cod;
	nou->info.nume = (char*)malloc(sizeof(strlen(s.nume) + 1));
	strcpy(nou->info.nume, s.nume);
	nou->info.medie = s.medie;
	nou->left = st;
	nou->right = dr;
	return nou;
}

nodArb* inserare(student s, nodArb* radacina) {

	nodArb* aux = radacina;
	//Verificam cazurile
	if (radacina == NULL) {
		aux = creare(s, NULL, NULL);
		return aux;
	}
	else
		while (true) {
			if (s.cod < aux->info.cod)
				if (aux->left != NULL)//Daca exista fiu stang
					aux = aux->left; // M-am dus pe ramura stanga
				else
				{
					//Daca nu exista, atunci il creez eu
					aux->left = creare(s, NULL, NULL);
					return radacina;
				}
			else if (s.cod > aux->info.cod)
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
		printf("\n Cod: %d, Nume: %s, Medie: %2.2f, BF=%d", rad->info.cod, rad->info.nume, rad->info.medie, rad->BF);
		preordine(rad->left);
		preordine(rad->right);
	}
}

void inordine(nodArb* rad) { //SRD
	if (rad != NULL) {
		inordine(rad->left); //apel pe stanga
		printf("\n Cod: %d, Nume: %s, Medie: %2.2f", rad->info.cod, rad->info.nume, rad->info.medie);//radacina
		inordine(rad->right);//apel pe dreapta
	}

}

void postordine(nodArb* rad) { //SDR

	if (rad != NULL) {
		postordine(rad->left);
		postordine(rad->right);
		printf("\n Cod: %d, Nume: %s, Medie: %2.2f", rad->info.cod, rad->info.nume, rad->info.medie);//radacina
	}

}

nodArb* cautare(nodArb* rad, int cheie) {
	if (rad != NULL) {
		//Daca exista arborele
		if (cheie == rad->info.cod)
			return rad;
		else
			if (cheie < rad->info.cod)
				cautare(rad->left, cheie);
			else
				return cautare(rad->right, cheie);
	}
	else
		return NULL;
}

void dezalocare(nodArb* rad) {
	if (rad != NULL) {
		//Post sa traversez cu orice ordine vreau
		nodArb* stanga = rad->left;//toti fii de stanga
		nodArb* dreapta = rad->right; // toti fii din dreapta ii salvam
		//free(rad->info.nume);
		free(rad);
		dezalocare(stanga);
		dezalocare(dreapta);

	}
}

int max(int a, int b) { //Functie pentru determinare nr niveluri
	int max = a;
	if (a < b)
		max = b;
	return max;
}

int nrLvl(nodArb* rad) {
	if (rad != NULL)
		return 1 + max(nrLvl(rad->left), nrLvl(rad->right));
	else
		return 0;
}

void calculBF(nodArb* rad) {
	if (rad != NULL) {
		rad->BF = nrLvl(rad->right) - nrLvl(rad->left);
		calculBF(rad->left);
		calculBF(rad->right);
	}
}

void conversieVect(nodArb* rad, student* vect, int* nr) {
	/*if (rad != NULL) {
		vect[*nr] = rad->info;
		(*nr)++;
		conversieVect(rad->left, vect, nr);
		conversieVect(rad->right, vect, nr);
	}*/
	if (rad != NULL) {
		vect[*nr].cod = rad->info.cod;
		vect[*nr].nume = (char*)malloc(sizeof(char) * strlen(rad->info.nume) + 1);
		strcpy(vect[*nr].nume, rad->info.nume);
		vect[*nr].medie = rad->info.medie;
		(*nr)++;
		nodArb* stanga = rad->left;//toti fii de stanga
		nodArb* dreapta = rad->right; // toti fii din dreapta ii salvam
		//free(rad->info.nume);
		free(rad);
		conversieVect(stanga, vect, nr);
		conversieVect(dreapta, vect, nr);
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

int main() {
	
	int n;
	printf("Nr studenti: ");

	FILE* f = fopen("studenti.txt", "r");
	fscanf(f, "%d", &n);


	nodArb* rad = NULL;
	student s;
	char buffer[30];
	for (int i = 0; i < n; i++) {
		//printf("Cod: ");
		fscanf(f, "%d", &s.cod);
		//printf("Nume: ");
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(s.nume, buffer);
		//printf("Medie: ");
		fscanf(f, "%f", &s.medie);

		rad = inserare(s, rad);
		calculBF(rad);//la fiecare inserare calculam balance factor
	}
	fclose(f);

	printf("\nPreordine: \n");
	preordine(rad);
	printf("\nInordine: \n");
	inordine(rad);
	printf("\nPost ordine: \n");
	postordine(rad);
	nodArb* cautat = cautare(rad, 3);
	if (cautat != NULL) {
		printf("\nStudentul cautat se numeste: %s\n", cautat->info.nume);
	}
	else
		printf("Nu exista\n");

	printf("Inaltimea este: %d", nrLvl(rad));
	printf("\n Inaltime stanga: %d", nrLvl(rad->left));
	printf("\n Inaltime dreapta: %d", nrLvl(rad->right));

	//student* vect = (student*)malloc(sizeof(student) * n);
	//int nr = 0;
	//conversieVect(rad, vect, &nr);
	//printf("\nVector:");
	//for(int i = 0; i < nr; i++) {
	//	printf("\n Cod: %d, Nume: %s, Medie: %2.2f", vect[i].cod, vect[i].nume, vect[i].medie);
	//}
	//for (int i = 0; i < nr; i++)
	//	free(vect[i].nume);
	//free(vect);
	////dezalocare(rad);
	rad = stergeNod(rad, 7);
	inordine(rad);
	preordine(rad);

	dezalocare(rad);
	return 0;
}