#include <stdio.h>
#include <stdlib.h>
#include <string>


struct student {
	int varsta;
	char* nume;
	float medie;
	//int nrNode;
	//int* note;
};

struct nodCoada {
	student info;
	nodCoada* next;
};

void put(nodCoada** vf, nodCoada** last, student s) {
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->info = s;
	nou->next = NULL;
	if (*vf == NULL && *last == NULL) {
		*vf = nou;
		*last = nou;
	}
	else {
		(*last)->next = nou;
		(*last) = nou;
	}
}

int get(nodCoada** vf, nodCoada** last, student* s) {
	if (*vf != NULL && *last != NULL) {
		s->varsta = (*vf)->info.varsta;
		s->nume = (char*)malloc(sizeof(strlen((*vf)->info.nume)) + 1);
		strcpy(s->nume, (*vf)->info.nume);
		s->medie = (*vf)->info.medie;
		nodCoada* temp = *vf;
		*vf = (*vf)->next;
		free(temp->info.nume);
		free(temp);
		return 0;
	}
	else if(*vf == NULL) {
		*last = NULL;
		return -1;
	}
}

void traverse(nodCoada* vf) {
	nodCoada* cursor = vf;
	while (cursor) {
		printf(
			"Student varsta: %d, Nume: %s, Medie: %2.2f\n", cursor->info.varsta, cursor->info.nume, cursor->info.medie
		);
		cursor = cursor->next;
	}
}

void convArray(nodCoada** vf, nodCoada** last, student* vect, int* nr) {
	student s;
	while (get(vf, last, &s) == 0)
	{
		vect[*nr] = s;
		(*nr)++;
	}
}


int main() {

	int n;
	printf("NR STUDENTI:");
	scanf("%d", &n);
	nodCoada* vf = NULL;
	nodCoada* last = NULL;
	student s;
	for (int i = 0; i < n; i++) {
		printf("Varsta: ");
		scanf("%d", &s.varsta);
		char buff[30];
		getchar();
		printf("Nume: ");
		gets_s(buff, 30);
		s.nume = (char*)malloc(sizeof(strlen(buff)) + 1);
		strcpy(s.nume, buff);
		printf("Medie: ");
		scanf("%f", &s.medie);
		put(&vf, &last, s);
	}
	printf("Afisare coada:\n");
	traverse(vf);

	student* vect = (student*)malloc(n * sizeof(student));
	int nr = 0;
	printf("Conversie vector\n");
	convArray(&vf, &last, vect, &nr);
	for (int i = 0; i < nr; i++) {
		printf("Student varsta: %d, Nume: %s, Medie: %2.2f\n", vect[i].varsta, vect[i].nume, vect[i].medie);
	}

	//DEZALOC VECTOR
	for (int i = 0; i < nr; i++) {
		free(vect[i].nume);
	}
	free(vect);
	//DEZALOCARE COADA
	student sters;
	while (get(&vf, &last, &sters) == 0)
		free(sters.nume);


	return 0;
}