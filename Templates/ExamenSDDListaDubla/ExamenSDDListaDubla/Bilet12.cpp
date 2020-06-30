#include <stdio.h>
#include <stdlib.h>
#include <string>

struct Angajat {
	int cod;
	char* nume;
	char* functie;
	float salariu;
	int varsta;
};

struct nod {
	Angajat info;
	nod* prev;
	nod* next;
};

struct ListaDubla {
	nod* first;
	nod* last;
};

Angajat* citireFis(FILE* f) {
	int nr;
	Angajat a;
	Angajat* angVect = NULL;
	int i = 0;
	char buff[30];
	if (f != NULL) {
		fscanf(f, "%d", &nr);
		printf("S-au extras %d angajati\n", nr);
		angVect = (Angajat*)malloc(sizeof(Angajat) * nr);
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
			angVect[i] = a;
			i++;
		}
	}

	return angVect;
}

void inserareSf(ListaDubla& ld, Angajat* av) {
	Angajat a;
	for (int i = 0; i < 10; i++) {
		a = av[i];
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = a;
		nou->next = NULL;
		nou->prev = ld.last;
		if (ld.last) {
			ld.last->next = nou;
			ld.last = nou;
		}
		else {
			ld.last = nou;
			ld.first = nou;
		}
	}
	
}

void traversInceput(ListaDubla ld) {
	nod* cursor = ld.first;
	while (cursor) {
		printf("\nCod-> %d, Nume-> %s, Functie->%s, Salariu->%5.2f, Varsta->%d\n", 
			cursor->info.cod, cursor->info.nume, cursor->info.functie, cursor->info.salariu, cursor->info.varsta);
		cursor = cursor->next;
	}
	printf("\n------------ SENS INVERS ---------------\n");
	cursor = ld.last;
	while (cursor) {
		printf("\nCod-> %d, Nume-> %s, Functie->%s, Salariu->%5.2f, Varsta->%d\n",
			cursor->info.cod, cursor->info.nume, cursor->info.functie, cursor->info.salariu, cursor->info.varsta);
		cursor = cursor->prev;
	}
}

void stergeByNume(ListaDubla& ld, const char* nume) {
	nod* cursor = ld.first;
	while (cursor) {
		cursor = cursor->next;
		
	}
}

int main() {
	FILE* f;
	ListaDubla ld;
	ld.first = NULL;
	ld.last = NULL;
	fopen_s(&f, "Angajati.txt", "r");
	Angajat* angVect = citireFis(f);
	fclose(f);
	for (int i = 0; i < 10; i++) {
		printf("\n[%d]: Cod-> %d, Nume-> %s, Functie->%s, Salariu->%5.2f, Varsta->%d\n", i,
			angVect[i].cod, angVect[i].nume, angVect[i].functie, angVect[i].salariu, angVect[i].varsta);
	}
	inserareSf(ld, angVect);
	printf("Succes\n");
	traversInceput(ld);
	stergeByNume(ld, "Dardala");
	traversInceput(ld);

	return 0;
}