#include <stdio.h>
#include <stdlib.h>
#include <string>

struct Laptop {
	char* producator;
	int RAM;
	float CPU;
};


Laptop creareLaptop(const char* prod, int ram, float CPU) {
	Laptop l;
	l.producator = (char*)malloc(sizeof(prod) + 1);
	strcpy(l.producator, prod);
	l.RAM = ram;
	l.CPU = CPU;
	return l;

}

struct Nod {
	Laptop info;
	Nod* prev;
	Nod* next;
};

struct Lista {
	Nod* prim;
	Nod* ultim;
};

void afisareLaptop(Laptop l) {
	printf("Producator: %s", l.producator);
	printf("\n");
	printf("RAM: %d GB\n", l.RAM);
	printf("CPU: %1.2 GHz\n", l.CPU);
}

void insertEnd(Lista &lst, Laptop l) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = l;
	nou->next = NULL;
	nou->prev = lst.ultim;
	if (lst.ultim) {
		lst.ultim->next = nou;
		lst.ultim = nou; 
	}
	else {
		lst.ultim = nou;
		lst.prim = nou; 
	}

}

void afisareListaIS(Lista lst) {
	Nod* cursor = lst.prim;
	while (cursor) {
		printf("\nProducator: %s, RAM: %d GB, CPU: %2.2f GHz", cursor->info.producator, cursor->info.RAM, cursor->info.CPU);
		cursor = cursor->next;
	}
}

void afisareListaSI(Lista lst) {
	Nod* cursor = lst.ultim;
	while (cursor) {
		printf("\nProducator: %s, RAM: %d GB, CPU: %2.2f GHz", cursor->info.producator, cursor->info.RAM, cursor->info.CPU);
		cursor = cursor->prev;
	}
}

void afisareInversFor(Lista lst) {
	for (Nod* c = lst.ultim; c != NULL; c = c->prev) {
		printf("\nProducator: %s, RAM: %d GB, CPU: %2.2f GHz", c->info.producator, c->info.RAM, c->info.CPU);
	}
}

void stergeLista(Lista& lst) {
	Nod* cursor = lst.prim;
	while (cursor) {
		Nod* aux = cursor->next;
		free(cursor->info.producator);
		free(cursor);
		cursor = aux;
	}
	lst.prim = NULL;
	lst.ultim = NULL;

	//printf("Lista dezalocata");
}

void stergeElemCautat(Lista& lst, const char* prod) {
	Nod* p = lst.prim;
	while (p && strcmp(p->info.producator, prod) != 0) {
		p = p->next;
	}
	if (p) {
		Nod* aux = p;
		if (p->prev) {
			p->prev->next = p->next;
			if (p->next) {
				p->next->prev = p->prev;
			}
			else {
				lst.ultim = p->prev;
			}
		}
		else {
			p->next->prev = NULL; 
			lst.prim = p->next;
		}
		free(p->info.producator);
		free(p);
	}
}


int main() {
	Lista lstDubla;
	lstDubla.prim = NULL;
	lstDubla.ultim = NULL;
	char buff[30] = "Lenovo";
	Laptop l1 = creareLaptop(buff, 8, 2.3);
	Laptop l2 = creareLaptop(buff, 16, 4.1);
	Laptop l3 = creareLaptop("Asus", 16, 4.1);

	insertEnd(lstDubla, l1);
	insertEnd(lstDubla, l2);
	insertEnd(lstDubla, l3);

	afisareListaIS(lstDubla);
	printf("\n------------SENS INVERS-----------\n");
	afisareListaSI(lstDubla);
	printf("\n------------ CU FOR -------------\n");
	afisareInversFor(lstDubla);
	//stergeLista(lstDubla);
	stergeElemCautat(lstDubla,"Lenovo");

	return 0;
}