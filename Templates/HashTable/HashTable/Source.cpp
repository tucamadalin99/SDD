#include <stdio.h>
#include <stdlib.h>
#include <string>
struct student {
	int cod;
	char* nume;
	float medie;
};

struct nodLS {
	student info;
	nodLS* next;
};

struct hashTable {
	nodLS** vector; //vector dinamic de pointeri la noduri
	int size;
};

int hashFunction(int cheie, hashTable tabela) {
	return cheie % tabela.size;
}

int inserare(hashTable tabela, student s) {
	int poz = -1;
	if (tabela.vector != NULL) { // Daca tabela nu e nula putem insera
		poz = hashFunction(s.cod, tabela); // calculam pozitia elementului pe care vrem sa-l inseram
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->info.cod = s.cod;
		nou->info.nume = (char*)malloc(sizeof(strlen(s.nume)) + 1);
		strcpy(nou->info.nume, s.nume);
		nou->info.medie = s.medie;
		nou->next = NULL;
		if (tabela.vector[poz] == NULL) {
			tabela.vector[poz] = nou; //Daca pozitia din vector e o lista goala, introducem
		}
		else {
			//S-a produs o coliziune
			nodLS* cursor = tabela.vector[poz]; // Capul listei unde s-a realizat coliziune
			while (cursor->next)
				cursor = cursor->next;
			cursor->next = nou;

		}
	}
	return poz;
}

void traversare(hashTable tabela) {
	if (tabela.vector != NULL) {
		//Tabela are elemente
		for (int i = 0; i < tabela.size; i++) {
			//FOLOSIM FOR DEOARECE ESTE UN VECTOR(DE LISTE)
			if (tabela.vector[i] != NULL) {
				printf("\nPozitie: %d ", i); // i-ul este chiar rezultatul hash-ului apelat anterior
				//VERIFICAM DACA PE POZITIA DIN VECTOR EXISTA O LISTA
				nodLS* cursor = tabela.vector[i];
				while (cursor) {
					printf("COD: %d, NUME: %s, MEDIE: %2.2f ", cursor->info.cod, cursor->info.nume, cursor->info.medie);
					cursor = cursor->next;
				}
			}

			//printf("\n");
		}
	}
}

void dezalocare(hashTable tabela) {
	if (tabela.vector != NULL) {
		for (int i = 0; i < tabela.size; i++)
			if (tabela.vector[i] != NULL) {
				nodLS* temp = tabela.vector[i];
				while (temp) {
					nodLS* temp2 = temp->next;
					free(temp->info.nume);
					free(temp);
					temp = temp2;
				}
			}
		free(tabela.vector);
	}
}

int stergere(hashTable tabela, int cod) {
	int poz = -1;
	if (tabela.vector != NULL) {
		poz = hashFunction(cod, tabela);
		if (tabela.vector[poz] == NULL)
			return -1;
		else
		{
			if (tabela.vector[poz]->info.cod == cod) {
				if (tabela.vector[poz]->next == NULL) {//IN CAZ IN CARE E PRIMUL
					nodLS* temp = tabela.vector[poz];
					free(temp->info.nume);
					free(temp);
					tabela.vector[poz] = NULL; //Trebuie sa nu mai pointeze daca e primul element ca nu mai e nicio lista
				}
				else {//DACA ARE CEVA DUPA EL
					nodLS* temp = tabela.vector[poz];
					tabela.vector[poz] = temp->next;// SARIM PESTE ELEMENTUL PE CARE IL STERGEM
					free(temp->info.nume);
					free(temp);
				}
			}
			else {
				nodLS* temp = tabela.vector[poz];
				while (temp->next != NULL && temp->next->info.cod != cod) 
					temp = temp->next;
				nodLS* p = temp->next; //elementul pe care il stergem
				if (p->next != NULL) {
					temp->next = p->next;
					free(p->info.nume);
					free(p);
				}
				else {
					temp->next = NULL;
					free(p->info.nume);
					free(p);
				}
			}
		}
	}
	return poz;
}

int main() {

	hashTable tabela;
	tabela.size = 101;
	tabela.vector = (nodLS**)malloc(tabela.size * sizeof(nodLS*));
	for (int i = 0; i < tabela.size; i++) {
		tabela.vector[i] = NULL;
	}

	int n;
	printf("Numar studenti: ");
	scanf("%d", &n);
	char buffer[30];
	student s;
	for (int i = 0; i < n; i++) {
		printf("Cod: ");
		scanf("%d", &s.cod);
		printf("Nume: ");
		getchar();
		gets_s(buffer, 30);
		s.nume = (char*)malloc(sizeof(buffer) + 1);
		strcpy(s.nume, buffer);
		printf("Medie: ");
		scanf("%f", &s.medie);

		inserare(tabela, s);
	}
	traversare(tabela);
	
	stergere(tabela, 305);
	printf("\n----- DUPA STERGERE: ");
	traversare(tabela);
	//dezalocare(tabela);
	printf("Tabela dezalocata!\n");


	return 0;
}