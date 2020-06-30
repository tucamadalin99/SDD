#include<stdio.h>
#include<string>
#include<iostream>


struct angajat {
	int cod;
	char* nume;
	char* functie;
	float salariu;
	int varsta;
	int gradFunctie;
};

struct nod {
	angajat info;
	nod* next;
	nod* prev;
};

struct ListaDubla {
	nod* primul;
	nod* ultimul;
};

struct nodArb {
	nodArb* left;
	nodArb* right;
	angajat info;
};

angajat* citireFis(FILE* f) {
	int nr;
	angajat a;
	angajat* angVect = NULL;
	int i = 0;
	char buff[30];
	if (f != NULL) {
		fscanf(f, "%d", &nr);
		printf("S-au extras %d angajati\n", nr);
		angVect = (angajat*)malloc(sizeof(angajat) * nr);
		while (!feof(f)) {
			fscanf(f, "%d", &a.cod);
			fscanf(f, "%s", &buff);
			a.nume = (char*)malloc(sizeof(strlen(buff)) + 1);
			strcpy(a.nume, buff);
			fscanf(f, "%s", &buff);
			a.functie = (char*)malloc(sizeof(strlen(buff)) + 1);
			strcpy(a.functie, buff);
			fscanf(f, "%f", &a.salariu);
			fscanf(f, "%d", &a.varsta);
			fscanf(f, "%d", &a.gradFunctie);
			angVect[i] = a;
			i++;
		}
	}

	return angVect;
}


void inserareLDdeLaSfarsit(ListaDubla &list, angajat* av)
{
	angajat a;
	for (int i = 0; i < 10; i++) {
		a = av[i];
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = a;
		nou->next = NULL;
		nou->prev = list.ultimul;
		if (list.ultimul) {
			list.ultimul->next = nou;
			list.ultimul = nou;
		}
		else {
			list.ultimul = nou;
			list.primul = nou;
		}
	}


}

void afisare(ListaDubla &lista) {
	nod* cursor = lista.primul;
	printf("\nAfisare de la inceput\n");
	while (cursor) {
		printf("\n: Cod-> %d, Nume-> %s, Functie->%s, Salariu->%5.2f, Varsta->%d, Grad Functie-> %d\n",
			cursor->info.cod, cursor->info.nume, cursor->info.functie, cursor->info.salariu, cursor->info.varsta, cursor->info.gradFunctie);
		cursor = cursor->next;
	}
	printf("\nAfisare de la sfarsit\n");
	cursor = lista.ultimul;
	while (cursor) {
		printf("\n: Cod-> %d, Nume-> %s, Functie->%s, Salariu->%5.2f, Varsta->%d Grad Functie-> %d\n",
			cursor->info.cod, cursor->info.nume, cursor->info.functie, cursor->info.salariu, cursor->info.varsta, cursor->info.gradFunctie);
		cursor = cursor->prev;
	}
}

nodArb* cautare(nodArb* rad, int cheie) {
	if (rad != NULL) {
		if (cheie == rad->info.cod)
			return rad;
		else if (cheie < rad->info.cod)
			cautare(rad->left, cheie);
		else
			return cautare(rad->right, cheie);
	}
	else
		return NULL;
}

void stergereDupaNume(ListaDubla &lista, const char* nume) {
	nod* cursor = lista.primul;
	while (cursor && strcmp(cursor->info.nume, nume) != 0)
		cursor = cursor->next;
	if (cursor) {
		nod* aux = cursor;
		if (cursor->prev)
		{
			cursor->prev->next = cursor->next;
			if (cursor->next) {
				cursor->next->prev = cursor->prev;
			}
			else {
				lista.ultimul = cursor->prev;
			}
		}
		else {
			cursor->next->prev = NULL;
			lista.primul = cursor->next;
		}
		//free(cursor->info.functie);
		free(cursor->info.nume);
		free(cursor);
	}
}
void dezalocare(ListaDubla &lista) {
	nod* cursor = lista.primul;
	while (cursor) {
		nod* aux = cursor->next;
		free(cursor->info.functie);
		//free(cursor->info.nume);
		cursor = aux;
	}
	lista.primul = NULL;
	lista.ultimul = NULL;
}

nodArb* creare(angajat a, nodArb* st, nodArb* dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.cod = a.cod;
	nou->info.nume = (char*)malloc(sizeof(char)* (strlen(a.nume)) + 1);
	strcpy(nou->info.nume, a.nume);
	nou->info.functie = (char*)malloc(sizeof(char)* (strlen(a.functie)) + 1);
	strcpy(nou->info.functie, a.functie);
	nou->info.salariu = a.salariu;
	nou->info.varsta = a.varsta;
	nou->info.gradFunctie = a.gradFunctie;
	nou->left = st;
	nou->right = dr;
	return nou;
}

nodArb* inserare(angajat a, nodArb* rad) {
	nodArb* aux = rad;
	if (rad == NULL) {
		aux = creare(a, NULL, NULL);
		return aux;
	}
	else {
		while (true) {
			if (a.cod < aux->info.cod) {
				if (aux->left != NULL)
					aux = aux->left;
				else {
					aux->left = creare(a, NULL, NULL);
					return rad;
				}
			}

			else if (a.cod > aux->info.cod) {
				if (aux->right != NULL)
					aux = aux->right;
				else {
					aux->right = creare(a, NULL, NULL);
					return rad;
				}
			}
			else
				return rad;
		}
	}
		
}


void inordine(nodArb* rad) {
	if (rad != NULL) {
		inordine(rad->left);
		printf("\n: Cod-> %d, Nume-> %s, Functie->%s, Salariu->%5.2f, Varsta->%d Grad Functie-> %d\n",
			rad->info.cod, rad->info.nume, rad->info.functie, rad->info.salariu, rad->info.varsta, rad->info.gradFunctie);
		inordine(rad->right);
	}

}

void dezalocareArb(nodArb* rad) {
	if (rad != NULL) {
		nodArb* st = rad->left;
		nodArb* dr = rad->right;
		dezalocareArb(st);
		free(rad->info.nume);
		free(rad->info.functie);
		free(rad);
		dezalocareArb(dr);
	}
}

void copiereListaArb(ListaDubla &ls, nodArb** rad, int cheie) {
	nod* cursor = ls.primul;
	while (cursor) {
		if (cheie > cursor->info.cod) {
			*rad = inserare(cursor->info, *rad);
		}
		cursor = cursor->next;
	}
}

void convertArbVect(nodArb* rad, angajat* vect, int& nr) {
	if (rad != NULL) {
		vect[nr].cod = rad->info.cod;
		vect[nr].nume = (char*)malloc(sizeof(char)*(strlen(rad->info.nume) + 1));
		strcpy(vect[nr].nume, rad->info.nume);
		vect[nr].functie = (char*)malloc(sizeof(char)*(strlen(rad->info.functie) + 1));
		strcpy(vect[nr].functie, rad->info.functie);
		vect[nr].salariu = rad->info.salariu;
		vect[nr].varsta = rad->info.varsta;
		vect[nr].gradFunctie = rad->info.gradFunctie;
		nr++;
		nodArb* st = rad->left;
		nodArb* r = rad->right;
		convertArbVect(st, vect, nr);
		convertArbVect(r, vect, nr);
		
	}
}

void main()
{
	FILE* f;
	fopen_s(&f, "Angajati.txt", "r");
	int nr;

	angajat* angVect = citireFis(f);
	fclose(f);
	for (int i = 0; i < 10; i++) {
		printf("\n[%d]: Cod-> %d, Nume-> %s, Functie->%s, Salariu->%5.2f, Varsta->%d\n", i,
			angVect[i].cod, angVect[i].nume, angVect[i].functie, angVect[i].salariu, angVect[i].varsta, angVect[i].gradFunctie);
	}
	printf("Succes");

	ListaDubla lista;
	lista.primul = lista.ultimul = NULL;
	inserareLDdeLaSfarsit(lista, angVect);
	printf("\nAfisare lista inainte de stergere");
	afisare(lista);
//	printf("\nAfisare lista dupa stergere:\n");
	//stergereDupaNume(lista, "Toma");
	//afisare(lista);
	//printf("\nDezalocare memeorie");
	//dezalocare(lista);
	//afisare(lista);
	nodArb* rad = NULL;
	int cheie;
	printf("Criteriu copiere: ");
	scanf("%d", &cheie);
	copiereListaArb(lista, &rad, cheie);
	printf("\n--------------ARBORE----------------\n");
	inordine(rad);
	printf("\n---------------- CONVERSIE-ARBORE-VECTOR-----------------\n");
	angajat* convVect = (angajat*)malloc(sizeof(angajat) * 10);
	int n = 0;
	convertArbVect(rad, convVect, n);
	for (int i = 0; i < n; i++)
	{
		printf("\n[%d]: Cod-> %d, Nume-> %s, Functie->%s, Salariu->%5.2f, Varsta->%d,GradFunctie->%d\n", i,
			convVect[i].cod, convVect[i].nume, convVect[i].functie, convVect[i].salariu, convVect[i].varsta, convVect[i].gradFunctie);
	}
	for (int i = 0; i < n; i++)
	{
		free(convVect[i].nume);
	}
	free(convVect);
}