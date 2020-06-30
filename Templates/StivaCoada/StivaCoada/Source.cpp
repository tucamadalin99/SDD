#include <stdio.h>
#include <stdlib.h>
#include <string>

//STIVA
// LIFO
// SE BAGA SI SE SCOATE DOAR DIN VARF
//VARF = CAP
//1. CREAZA STIVA
//2. CREAZA FUNCTIE PUSH SI POP

struct Carte {
	int cod;
	char* autor;
	float pret;

};

struct nodStiva {
	nodStiva* next; //CA LA LISTA SIMPLA!!
	Carte info;
};

struct nodLista { //PENTRU CONVERSIE IN LISTA SIMPLA
	nodLista* next;
	Carte info;
};

//PUSH: LA ADRESA VARFULUI, INSERAM O CARTE
void push(nodStiva** varf, Carte c) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->info = c;
	nou->next = NULL;
	if ((*varf) == NULL) {
		(*varf) = nou;
	}
	else {
		nou->next = (*varf);
		(*varf) = nou;
	}
	//END
}

//POP, LA ADRESA VARFULUI, EXTRAGEM O CARTE, O DEZALOCAM APOI PRELUCRAM INFO MAI DEPARTE
int pop(nodStiva** varf, Carte* info) {
	if (*varf == NULL)
		return 0;
	else {
		info->cod = (*varf)->info.cod;
		info->autor = (char*)malloc(sizeof(char) * (strlen((*varf)->info.autor) + 1));
		strcpy(info->autor, (*varf)->info.autor);
		info->pret = (*varf)->info.pret;
		nodStiva* popped = *varf;
		*varf = (*varf)->next;
		free(popped->info.autor);
		free(popped);
		return 1;
	}
}

void traverseStiva(nodStiva* varf) {
	nodStiva* c = varf;
	while (c) {
		printf("Cod carte: %d -> Autor: %s -> Pret: %2.2f\n", c->info.cod, c->info.autor, c->info.pret);
		c = c->next;
	}
}

void convArray(nodStiva** varf, Carte* vector, int* nr) { //int* pt ca intra cu val 0 si se modifica
	Carte c;
	while (pop(varf, &c) == 1) {
		vector[*nr] = c;
		(*nr)++;
	}

}

int main() {

	nodStiva* varf = NULL;
	int n;
	printf("Number of books: ");
	scanf("%d", &n);
	if (n <= 0) {
		printf("Stiva nu s-a initializat");
	}
	else {
		for (int i = 0; i < n; i++) {
			Carte c;
			printf("Cod: ");
			scanf("%d", &c.cod);
			printf("Autor: ");
			getchar();
			char buffer[30];
			gets_s(buffer, 30);
			int dim = strlen(buffer) + 1;
			c.autor = (char*)malloc(sizeof(dim));
			strcpy(c.autor, buffer);
			printf("Price: ");
			scanf("%f", &c.pret);
			push(&varf, c);
			printf("Cartea: %d a fost inserata.\n", c.cod);
		}

	}

	traverseStiva(varf);
	printf("Popping element: \n");
	Carte c2;
	pop(&varf, &c2);
	printf("Extras: Cod carte: %d -> Autor: %s -> Pret: %2.2f\n", c2.cod, c2.autor, c2.pret);

	int nr = 0;
	Carte* stivaConvVector = (Carte*)malloc(n * sizeof(Carte));
	convArray(&varf,stivaConvVector, &nr);
	for (int i = 0; i < nr; i++) {
		printf("Conversie: Cod carte: %d -> Autor: %s -> Pret: %2.2f\n", stivaConvVector[i].cod, stivaConvVector[i].autor, stivaConvVector[i].pret);
	}


	return 0;
}