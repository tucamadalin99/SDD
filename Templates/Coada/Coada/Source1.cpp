#include <stdio.h>
#include <stdlib.h>
#include <string>
//LISTA DE LISTE SIMPLE dupa un criteriu
struct student {
	int varsta;
	char* nume;	
	float medie;
};

struct nodLS {
	student info;
	nodLS* next;
};

struct nodLP {
	nodLS* info;
	nodLP* next; 
};

void inserareLS(nodLS** cap, student s) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.varsta = s.varsta;
	nou->info.nume = (char*)malloc(sizeof(s.nume) + 1);
	strcpy(nou->info.nume, s.nume);
	nou->info.medie = s.medie;
	nou->info = s;
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nodLS* cursor = *cap;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = nou; 
	}

}

void traversare(nodLS* cap) {
	nodLS* cursor = cap;
	while (cursor) {
		printf(
			"Student varsta: %d, Nume: %s, Medie: %2.2f\n", cursor->info.varsta, cursor->info.nume, cursor->info.medie
		);
		cursor = cursor->next;
	}
}

void traversarePrincipala(nodLP* cap) {
	nodLP* cursor = cap;
	while (cursor) {
		printf("Sublista\n");
		traversare(cursor->info);
		cursor = cursor->next;
	}
}

void dezalocLS(nodLS* cap) {
	nodLS* cursor = cap;
	while (cursor) {
		nodLS* cursor2 = cursor->next;
		free(cursor->info.nume);
		free(cursor);
		cursor = cursor2;
	}
}

void dezalocLP(nodLP* cap) {
	nodLP* cursor = cap;
	while (cursor) {
		nodLP* cursor2 = cursor->next;
		dezalocLS(cursor->info);
		cursor = cursor2;
	}
}

void inserareLP(nodLP** cap, nodLS* capLS) {
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->info = capLS;
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nodLP* cursor = *cap;
		while (cursor->next) {
			cursor = cursor->next;
		}
		cursor->next = nou;
	}
}

void main() {

	int n;
	printf("NR STUDENTI: ");
	scanf("%d", &n);
	student s;
	char buff[30];
	nodLP* capLP = NULL;
	nodLS* capLSpar = NULL;
	nodLS* capLSimpar = NULL;
	for (int i = 0; i < n; i++) {
		printf("Varsta: ");
		scanf("%d", &s.varsta);
		printf("Nume: ");
		getchar();
		gets_s(buff, 30);
		s.nume = (char*)malloc(sizeof(buff) + 1);
		strcpy(s.nume, buff);
		printf("Medie: ");
		scanf("%f", &s.medie);
		if ((int)s.medie % 2 == 0) {
			inserareLS(&capLSpar, s);
		}
		else {
			inserareLS(&capLSimpar, s);
		}
	}

	inserareLP(&capLP, capLSpar);
	inserareLP(&capLP, capLSimpar);
	traversarePrincipala(capLP);
	dezalocLP(capLP);

}