#include <stdio.h>
#include<stdlib.h>
#include <string>

struct Tigara {
	char* marca;
	int nicotina;
	float pret;
};

struct Nod {
	Nod* prev;
	Nod* next;
	Tigara info;
};

struct ListaDubla {
	Nod* first;
	Nod* last;
};

Tigara creare(const char* marca, int nic, float price) {
	Tigara t;
	t.marca = (char*)malloc(sizeof(strlen(marca)) + 1);
	strcpy(t.marca, marca);
	t.nicotina = nic;
	t.pret = price;
	return t;
}

void insertInListIS(ListaDubla& l, Tigara t) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = t;
	nou->next = l.first;
	nou->prev = NULL;

	if (l.first) {
		l.first->prev = nou;
		l.first = nou;
		//nou->prev = NULL;
	}
	else {
		l.first = nou;
		l.last = nou;
		
	}
}

void display(Tigara t) {
	printf("Brand: %s -> Nivel nicotina: %d mg -> Pret: %2.2f lei", t.marca, t.nicotina, t.pret);
}

void displayList(ListaDubla &l) {
	Nod* cursor = l.first;
	while (cursor) {
		printf("Brand: %s -> Nivel nicotina: %d mg -> Pret: %2.2f lei\n", cursor->info.marca, cursor->info.nicotina, cursor->info.pret);
		cursor = cursor->next;
	}
	cursor = l.last;
	printf("PARCURGERE INVERSA: \n");
	while (cursor) {
		printf("Brand: %s -> Nivel nicotina: %d mg -> Pret: %2.2f lei\n", cursor->info.marca, cursor->info.nicotina, cursor->info.pret);
		cursor = cursor->prev;
	}
}

void dezaloc(ListaDubla& l) {
	//PARCURGEM LISTA DEZALOCAM FIECARE NOD SI REFACEM LEGATURILE LA FIECARE ITERATIE
	Nod* p = l.first;
	while (p) {
		Nod* aux = p->next;
		//aux->next = p->next;
		free(p->info.marca);
		free(p);
		p = aux;
	}
	l.first = NULL;
	l.last = NULL;
}


int main() {

	ListaDubla lstDubla;
	lstDubla.first = NULL;
	lstDubla.last = NULL;
	insertInListIS(lstDubla, creare("Dunhill", 10, 23.00));
	insertInListIS(lstDubla, creare("Kent", 10, 23.00));
	displayList(lstDubla);
	dezaloc(lstDubla);
	return 0;
}