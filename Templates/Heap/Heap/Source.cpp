#include <stdio.h>
#include <stdlib.h>
#include <string>

struct heap2 {
	int* vect;
	int nrElem;
};


struct student {
	int varsta;
	char* nume;
	float medie;
};

struct heap {
	student* vect;
	int nrElem;
};

void filtrare(heap h, int index) {
	//PENTRU A ADUCE MEREU MAXIMUL DIN ELEMENTE PE PRIMA POZITIE
	int iMax = index; //presupun ca radacina e maxima
	int iStanga = 2 * index + 1;
	int iDreapta = 2 * index + 2;
	if (iStanga < h.nrElem && h.vect[iStanga].varsta > h.vect[iMax].varsta) {
		iMax = iStanga;
	}

	if (iDreapta < h.nrElem && h.vect[iDreapta].varsta > h.vect[iMax].varsta) {
		iMax = iDreapta;
	}

	if (index != iMax) {
		student temp = h.vect[index];
		h.vect[index] = h.vect[iMax];
		h.vect[iMax] = temp;
		filtrare(h, iMax);
	}
}


void inserare(heap*h, student elem) {
	student *vNou = (student*)malloc(((*h).nrElem + 1) * sizeof(student));//ALOCAM MEMORIE PENTRU VECTOR + 1 spatiu
	for (int i = 0; i < (*h).nrElem; i++) {
		vNou[i] = (*h).vect[i];//copiem tot ce era in vechiul vector
	}

	(*h).nrElem++;//incrementam n
	free((*h).vect);//stergem referinta heap-ului la vechiul vector
	(*h).vect = vNou;//setam referinta la noul vector
	(*h).vect[(*h).nrElem - 1] = elem; //adaugam elementul pe ultima pozitie in arbore

	//Refiltram sa il pozitionam unde ii este locul
	for (int i = ((*h).nrElem - 1)/2; i >= 0; i--) { // pornim de la -1 n/2 si decrementam pana ajungem la 0(radacina)
		filtrare((*h), i);
	}
}

void extragere(heap* h, student* elem) {
	student* vNou = (student*)malloc(sizeof(student) * ((*h).nrElem - 1));
	//scadem vectorul cu -1 pozitie
	student temp = (*h).vect[0];
	(*h).vect[0] = (*h).vect[(*h).nrElem - 1]; //interschimbam ultimul nod cu primul
	(*h).vect[(*h).nrElem - 1] = temp;

	*elem = (*h).vect[(*h).nrElem - 1]; // ii dam ultima radacina

	for (int i = 0; i < (*h).nrElem - 1; i++) {
		vNou[i] = (*h).vect[i];
	}

	(*h).nrElem--; // scadem dimens cu 1
	free((*h).vect); // taiem legatura cu nodul sters
	(*h).vect = vNou; // dam noul vector cu elementul sters
	//refiltram
	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--) { // pornim de la -1 n/2 si decrementam pana ajungem la 0(radacina)
		filtrare((*h), i);
	}

}

void afisare(heap h) {
	printf("\nElementele heap: ");
	for (int i = 0; i < h.nrElem; i++)
		printf("Varsta: %d, Nume: %s, Media: %2.2f ", h.vect[i].varsta, h.vect[i].nume, h.vect[i].medie);
}

int main() {

	heap h;
	printf("Nr. elemente: ");
	scanf("%d", &h.nrElem);
	h.vect = (student*)malloc(sizeof(student) * h.nrElem);

	for (int i = 0; i < h.nrElem; i++) {
		printf("\n Element %d: ", i+1);
		printf("Varsta: ");
		scanf("%d", &h.vect[i].varsta);
		char buff[30];
		getchar();
		printf("Nume: ");
		gets_s(buff, 30);
		h.vect[i].nume = (char*)malloc(sizeof(buff) + 1);
		strcpy(h.vect[i].nume, buff);
		printf("Media : ");
		scanf("%f", &h.vect[i].medie);
	}

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}

	afisare(h);
	char buff[30] = "Daniel";
	student s = { 23, buff, 8.3f };

	inserare(&h, s);

	afisare(h);
	student s1;
	extragere(&h, &s1);
	printf("Element extras:\n");
	printf("Varsta: %d, Nume: %s, Medie: %2.2f", s1.varsta, s1.nume, s1.nume);
	afisare(h);

	return 0;
}