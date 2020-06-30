#include<stdio.h>
#include<stdlib.h>
#include<string>

struct Gradinita {
	int cod;
	char*nume;
	char* adresa;
	int nrStrada;
	int nrCopii;
};


struct nodLS {
	Gradinita info;
	nodLS* next;
};

struct hashTable {
	nodLS** vector;
	int dim;
};

struct nodLista {
	nodLista* next;
	nodLista* prev;
	Gradinita info;
};

struct listaDubla {
	nodLista* prim;
	nodLista* ultim;
};

struct nodLP {
	nodLista* info;
	nodLP *next;
};



int hashFunction(const char* cheie, hashTable t) {
	int ascii = 0;
	for (int i = 0; i < strlen(cheie);  i++) {
		ascii += (int)cheie[i];
	}

	return ascii % t.dim;
}

int inserare(hashTable t, Gradinita g) {
	int poz;
	if (t.vector != NULL) {
		poz = hashFunction(g.nume, t);
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->info.cod = g.cod;
		nou->info.nume = (char*)malloc(sizeof(char) * (strlen(g.nume) + 1));
		strcpy(nou->info.nume, g.nume);
		nou->info.adresa = (char*)malloc(sizeof(char) * (strlen(g.adresa) + 1));
		strcpy(nou->info.adresa, g.adresa);
		nou->info.nrStrada = g.nrStrada;
		nou->info.nrCopii = g.nrCopii;
		nou->next = NULL;
		if (t.vector[poz] == NULL) {
			t.vector[poz] = nou;
		}
		else {
			//Colliziunee
			nodLS* cursor = t.vector[poz];
			while (cursor->next)
				cursor = cursor->next;
			cursor->next = nou;
		}
	}

	return poz;
}

void traversareHash(hashTable t) {
	if (t.vector != NULL) {
		for (int i = 0; i < t.dim; i++) {
			if (t.vector[i] != NULL) {
				printf("\nPozitie: %d\n", i);
				nodLS* cursor = t.vector[i];
				while (cursor) {
					printf("Cod: %d -> Denumire: %s -> Adresa: %s -> Nr.Strada: %d -> Nr.Copii: %d\n",
						cursor->info.cod, cursor->info.nume, cursor->info.adresa, cursor->info.nrStrada, cursor->info.nrCopii);
					cursor = cursor->next;
				}
			}
		}
	}
}

int cautareSchimbare(hashTable t, const char* nume, const char* numeNou) {
	int poz;
	int prevPoz;
	if (t.vector != NULL) {
		poz = hashFunction(nume, t);
		prevPoz = hashFunction(nume, t);
		nodLS* nou = t.vector[poz];
		nou->info.nume = (char*)malloc(sizeof(char) * strlen(numeNou) + 1);
		strcpy(nou->info.nume, numeNou);
		poz = hashFunction(numeNou, t);
		inserare(t, nou->info);
		if (t.vector[prevPoz]->next == NULL) {
			nodLS *temp = t.vector[prevPoz];
			free(temp->info.nume);
			free(temp);
			t.vector[prevPoz] = NULL;
		}
		else {
			nodLS* temp = t.vector[prevPoz];
			t.vector[prevPoz] = temp->next;
			temp->next = NULL;
			free(temp);
		}

		}
	return poz;
}

int stergere(hashTable tabela, const char* nume) {
	int pozitie;
	if (tabela.vector != NULL) {
		pozitie = hashFunction(nume, tabela);
		if (tabela.vector[pozitie] == NULL)
			return -1;
		else {
			if (strcmp(tabela.vector[pozitie]->info.nume, nume) == 0)
			{
				if (tabela.vector[pozitie]->next == NULL)
				{
					nodLS *temp = tabela.vector[pozitie];
					free(temp->info.nume);
					free(temp);
					tabela.vector[pozitie] = NULL;
				}
				else {
					nodLS *temp = tabela.vector[pozitie];
					tabela.vector[pozitie] = temp->next;
					free(temp->info.nume);
					free(temp);
				}
			}
			else
			{
				nodLS *temp = tabela.vector[pozitie];
				while (temp->next != NULL && strcmp(temp->next->info.nume, nume) != 0)
					temp = temp->next;
				nodLS *p = temp->next;
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
	return pozitie;
}

nodLS* cautareLista(hashTable t, const char* nume) {
	int poz;
	if (t.vector != NULL) {
		poz = hashFunction(nume, t);
		return t.vector[poz];
	}
}

void dezalocareHash(hashTable t) {
	if (t.vector != NULL) {
		for(int i = 0; i < t.dim; i++)
			if (t.vector[i] != NULL) {
				nodLS* cursor = t.vector[i];
				while (cursor) {
					nodLS* temp = cursor->next;
					free(cursor->info.nume);
					free(cursor->info.adresa);
					free(cursor);
					cursor = temp;
				}
			}
	}
}
void dezalocareListaDubla(listaDubla &lista)
{
	nodLista* cursor = lista.prim;
	while (cursor)
	{
		nodLista* aux = cursor->next;
		free(aux->info.nume);
		free(aux->info.adresa);
		aux = cursor;
	}
	lista.prim = NULL;
	lista.ultim = NULL;
}
 
void adaugListaDubla(listaDubla &ld, nodLS* cap) {
	nodLS* cursor = cap;
	while (cursor) {
		nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
		nou->info = cursor->info;
		nou->next = NULL;
		nou->prev = ld.ultim;
		if (ld.ultim) {
			ld.ultim->next = nou;
			ld.ultim = nou;
		}
		else {
			ld.ultim = nou;
			ld.prim = nou;
		}
		cursor = cursor->next;
	}

}

void afisareListaDubla(listaDubla ld) {
	nodLista* cursor = ld.prim;
	while (cursor) {
		printf("\nCod: %d -> Denumire: %s -> Adresa: %s -> Strada: %d -> Nr.Copii: %d",
			cursor->info.cod, cursor->info.nume, cursor->info.adresa, cursor->info.nrStrada, cursor->info.nrCopii);
		cursor = cursor->next;	
	}
}

int main() {
	hashTable t;
	t.dim = 101;
	t.vector = (nodLS**)malloc(sizeof(nodLS*) * t.dim);
	for (int i = 0; i < t.dim; i++) {
		t.vector[i] = NULL;
	}
	int nr;
	FILE* f = fopen("gradinite.txt", "r");
	fscanf(f, "%d", &nr);
	char buff[30];
	Gradinita g;
	for (int i = 0; i < nr; i++) {
		fscanf(f, "%d", &g.cod);
		fscanf(f, "%s", buff);
		g.nume = (char*)malloc(sizeof(char)*(strlen(buff) + 1));
		strcpy(g.nume, buff);
		fscanf(f, "%s", buff);
		g.adresa = (char*)malloc(sizeof(char)*(strlen(buff) + 1));
		strcpy(g.adresa, buff);
		fscanf(f, "%d", &g.nrStrada);
		fscanf(f, "%d", &g.nrCopii);
		inserare(t, g);

	}
	fclose(f);
	traversareHash(t);

	int rez = cautareSchimbare(t, "Tembelilor", "Pula");
	//stergere(t, "Zurli");
	char buff3[] = "Zurli";
	char buff2[] = "Dfsafaw";
	Gradinita g1 = { 2, buff3, buff2, 6, 150 };
	printf("Dupa schimbare: \n");
	traversareHash(t);

	printf("\n---------------------------------------------\n");
	inserare(t, g1);
	traversareHash(t);

	printf("\n---------------------------------------------\n");
	
	nodLS* cap = cautareLista(t, "Durli");
	nodLS* cursor = cap;
	while (cursor) {
		printf("\nCod: %d -> Denumire: %s -> Adresa: %s -> Strada: %d -> Nr.Copii: %d", cursor->info.cod, cursor->info.nume, cursor->info.adresa, cursor->info.nrStrada, cursor->info.nrCopii);
		cursor = cursor->next;
	}
	
	printf("\n Lista dubla:\n ");
	listaDubla ld;
	ld.prim = ld.ultim = NULL;
	adaugListaDubla(ld, cap);
	afisareListaDubla(ld);
	//dezalocareListaDubla(ld);
	//stergere(t, "Durli");
	//afisareListaDubla(ld);



	
	
	return 0;
}