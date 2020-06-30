#include <stdio.h>
#include <stdlib.h>
#include <string>

struct gradinita {
	int cod;
	char* nume;
	char* strada;
	float suprafata;
	int nrCopii;
};


struct nodLS {
	gradinita info;
	nodLS* next;
};


struct nodDbl {
	gradinita infp;
	nodDbl* prev;
	nodDbl* next;
};

struct listaDubla {
	nodDbl* prim;
	nodDbl* ultim;
};




struct hashTable {
	nodLS** vector; //vector dinamic de pointeri la noduri
	int size;
};

int hash(hashTable t, const char* cheie) {
	int ascii = 0;
	for (int i = 0; i < strlen(cheie); i++) {
		ascii += (int)cheie[i];
	}
	return ascii % t.size;
}

int inserare(hashTable tabela, gradinita g) {
	int poz = -1;
	if (tabela.vector != NULL) { // Daca tabela nu e nula putem insera
		poz = hash(tabela, g.nume); // calculam pozitia elementului pe care vrem sa-l inseram
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->info.cod = g.cod;
		nou->info.nume = (char*)malloc(sizeof(char) * (strlen(g.nume) + 1));
		strcpy(nou->info.nume, g.nume);
		nou->info.strada = (char*)malloc(sizeof(char) * (strlen(g.strada) + 1));
		strcpy(nou->info.strada, g.strada);
		nou->info.suprafata = g.suprafata;
		nou->info.nrCopii = g.nrCopii;
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
					printf("COD: %d, NUME: %s, STRADA: %s, SUPRAFATA: %5.2f, NR.COPII: %d \n", cursor->info.cod, cursor->info.nume,
						cursor->info.strada, cursor->info.suprafata, cursor->info.nrCopii);
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
					free(temp->info.strada);
					free(temp);
					temp = temp2;
				}
			}
		free(tabela.vector);
	}
}

int stergere(hashTable tabela, const char* cod) {
	int poz;
	if (tabela.vector != NULL) {
		poz = hash(tabela, cod);
		if (tabela.vector[poz] == NULL)
			return -1;
		else
		{
			if (strcmp(tabela.vector[poz]->info.nume, cod) == 0) {
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
				while (temp->next != NULL && strcmp(temp->next->info.nume, cod))
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

nodDbl* inserareSfarsit(listaDubla&lst, hashTable t) {
	nodDbl* nou = NULL;
	for (int i = 0; i < t.size; i++) {
		nou = (nodDbl*)malloc(sizeof(nodDbl));
		nou->next = NULL;
		nou->prev = lst.ultim;
		if (t.vector[i]) {

			nodLS* cursor = t.vector[i];
			while (cursor) {
				nou->infp.cod = t.vector[i]->info.cod;
				nou->infp.nume = (char*)malloc(sizeof(char) * (strlen(t.vector[i]->info.nume) + 1));
				strcpy(nou->infp.nume, t.vector[i]->info.nume);
				nou->infp.strada = (char*)malloc(sizeof(char) * (strlen(t.vector[i]->info.strada) + 1));
				strcpy(nou->infp.strada, t.vector[i]->info.strada);
				nou->infp.suprafata = t.vector[i]->info.suprafata;
				nou->infp.nrCopii = t.vector[i]->info.nrCopii;
				cursor = cursor->next;
			}
			if (lst.ultim) {
				lst.ultim->next = nou;
				lst.ultim = nou;
			}
			else {
				lst.ultim = nou;
				lst.prim = nou;
			}
		}
	}
	return nou;
}
void afisareListaIS(listaDubla lst) {
	nodDbl *cursor = lst.prim;
	while (cursor) {
		printf("COD: %d, NUME: %s, STRADA: %s, SUPRAFATA: %5.2f, NR.COPII: %d \n", cursor->infp.cod, cursor->infp.nume,
			cursor->infp.strada, cursor->infp.suprafata, cursor->infp.nrCopii);
		cursor = cursor->next;
	}
}

//void insListB(nodListB** cap, listaDubla ld) {
//	nodListB* nou = (nodListB*)malloc(sizeof(nodListB));
//	nou->info = &ld;
//	nou->next = NULL;
//	nou->prev = (*cap)->prev;
//	if () {
//		ld.ultim->next = nou;
//		ld.ultim = nou;
//	}
//	else {
//		ld.ultim = nou;
//		ld.prim = nou;
//	}
//}

void insDubla(listaDubla &ls, gradinita g) {
	nodDbl* nou = (nodDbl*)malloc(sizeof(nodDbl));
	nou->infp = g;
	nou->next = NULL;
	nou->prev = ls.ultim;
	if (ls.ultim) {
		ls.ultim->next = nou;
		ls.ultim = nou;
	}
	else {
		ls.ultim = nou;
		ls.prim = nou;
	}
}
void rupereLista(nodDbl* cap, nodDbl** cap1, nodDbl** cap2, int cod) {
	nodDbl* cursor = cap;
	int sw = 0;
	while ((cursor != NULL)) {
		nodDbl* cursor2 = cursor->next;
		nodDbl* nou = (nodDbl*)malloc(sizeof(nodDbl));
		nou->infp.cod = cursor->infp.cod;
		nou->infp.nrCopii = cursor->infp.nrCopii;
		nou->infp.nume = (char*)malloc(sizeof(char)*(strlen(cursor->infp.nume) + 1));
		strcpy(nou->infp.nume, cursor->infp.nume);
		nou->infp.strada = (char*)malloc(sizeof(char)*(strlen(cursor->infp.strada) + 1));
		strcpy(nou->infp.strada, cursor->infp.strada);
		nou->infp.suprafata = cursor->infp.suprafata;
		nou->next = NULL;
		if (cursor->infp.cod == cod)
		{
			sw = 1;
		}
		if (sw == 0) {
			if (*cap1 == NULL) {
				nou->prev = NULL;
				*cap1 = nou;
			}
			else {
				nodDbl* cursor3 = *cap1;
				while (cursor3->next != NULL)
				{
					cursor3 = cursor3->next;
				}
				cursor3->next = nou;
				nou->prev = cursor3;
			}
		}
		else {
			if (*cap2 == NULL) {
				nou->prev = NULL;
				*cap2 = nou;
			}
			else {
				nodDbl* cursor3 = *cap2;
				while (cursor3->next != NULL)
				{
					cursor3 = cursor3->next;
				}
				cursor3->next = nou;
				nou->prev = cursor3;
			}

		}
	}
}

void schimbareCheie(hashTable t, const char* cheie, const char* cheieNou) {
	if (t.vector != NULL) {
		int poz = hash(t, cheie);
		gradinita g;
		nodLS* cautat = t.vector[poz];
		if (strcmp(t.vector[poz]->info.nume, cheie) == 0) {
			g.cod = cautat->info.cod;
			g.nume = (char*)malloc(sizeof(char) * (strlen(cheieNou) + 1));
			strcpy(g.nume, cheieNou);
			g.strada = (char*)malloc(sizeof(char) * (strlen(cautat->info.strada) + 1));
			strcpy(g.strada, cautat->info.strada);
			g.suprafata = cautat->info.suprafata;
			g.nrCopii = cautat->info.nrCopii;
			inserare(t, g);
			if (cautat->next == NULL) {
				free(cautat->info.nume);
				free(cautat->info.strada);
				free(cautat);
				t.vector[poz] = NULL;
			}
		}
		else {
			while (strcmp(cautat->next->info.nume, cheie) != 0) {
				cautat = cautat->next;
			}
			nodLS* sters = cautat->next;//elementul pe care il stergem
			
			cautat->next = sters->next;
			free(sters);

		}

	}
}



int main() {

	hashTable t;
	t.size = 101;
	t.vector = (nodLS**)malloc(sizeof(nodLS*) * t.size);
	for (int i = 0; i < t.size; i++) {
		t.vector[i] = NULL;
	}
	int nr = 0;
	nodDbl* cap = NULL;
	FILE* f = fopen("gradinite.txt", "r");
	gradinita g;
	char buff[60];
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++) {
		fscanf(f, "%d", &g.cod);
		fscanf(f, "%s", buff);
		g.nume = (char*)malloc((strlen(buff) + 1) * sizeof(char));
		strcpy(g.nume, buff);
		fscanf(f, "%s", buff);
		g.strada = (char*)malloc((strlen(buff) + 1) * sizeof(char));
		strcpy(g.strada, buff);
		fscanf(f, "%f", &g.suprafata);
		fscanf(f, "%d", &g.nrCopii);

		  inserare(t, g);
	}
	fclose(f);
	traversare(t);
	schimbareCheie(t, "Friky", "Muie");
	//stergere(t, "Zurli")
	printf("\n");
	traversare(t);
	printf("\n ------- LISTA DUBLA A ELEMENTELOR UNICE DIN TABELA --------------\n");
	listaDubla ld;
	ld.prim = NULL;
	ld.ultim = NULL;
	cap = inserareSfarsit(ld, t);
	afisareListaIS(ld);
	nodDbl* cap1 = NULL;
	nodDbl* cap2 = NULL;
	//rupereLista(cap, &cap1, &cap2, 3);

	return 0;
}