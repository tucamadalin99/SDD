#include <stdio.h>
#include <stdlib.h>
#include <string>

struct platforma {
	int nrAsigurare;
	float pretLicenta;
	char* denumire;
	int nrLuni;
	float* reduceriLuna;
};

struct heap {
	platforma* vect;
	int nrElem;
};

struct nodArb {
	platforma info;
	nodArb* left;
	nodArb* right;
};

nodArb *creare(platforma p, nodArb *st, nodArb *dr) {	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));	nou->info.nrAsigurare = p.nrAsigurare;	nou->info.pretLicenta = p.pretLicenta;	nou->info.denumire = (char*)malloc(sizeof(char)*(strlen(p.denumire) + 1));	strcpy(nou->info.denumire, p.denumire);	nou->info.nrLuni = p.nrLuni;	nou->info.reduceriLuna = (float*)malloc(sizeof(float) * nou->info.nrLuni);	for (int i = 0; i < nou->info.nrLuni; i++)		nou->info.reduceriLuna[i] = p.reduceriLuna[i];	nou->left = st;	nou->right = dr;	return nou;}


nodArb* inserareArb(platforma p, nodArb* rad) {
	nodArb* aux = rad;
	if (rad == NULL) {
		aux = creare(p, NULL, NULL);
		return aux;
	}
	else
		while (true) {
			if (p.nrAsigurare < aux->info.nrAsigurare)
				if (aux->left != NULL)
					aux = aux->left;
				else {
					aux->left = creare(p, NULL, NULL);
					return rad;
				}
			else if (p.nrAsigurare > aux->info.nrAsigurare)
				if (aux->right != NULL)
					aux = aux->right;
				else {
					aux->right = creare(p, NULL, NULL);
					return rad;
				}
			else
				return rad;
		}
}

nodArb* copiereHeapArb(heap& h, nodArb** rad, int n) {
	//*rad = NULL;
	platforma p;
	for (int i = 0; i < n; i++) {
		
		p.nrAsigurare = h.vect[i].nrAsigurare;
		p.denumire = (char*)malloc(sizeof(char)* (strlen(h.vect[i].denumire) + 1));
		strcpy(p.denumire, h.vect[i].denumire);
		p.pretLicenta = h.vect[i].pretLicenta;
		p.nrLuni = h.vect[i].nrLuni;
		p.reduceriLuna = (float*)malloc(sizeof(float) * p.nrLuni);		for (int j = 0; j < p.nrLuni; j++)			p.reduceriLuna[j] = h.vect[i].reduceriLuna[j];
		*rad = inserareArb(p, *rad);

	}
	return *rad;
}

void filtrare(heap h, int index) {			
	int iMin = index;
	int iStanga = 2 * index + 1;
	int iDreapta = 2 * index + 2;
	if (iStanga < h.nrElem && h.vect[iStanga].pretLicenta < h.vect[iMin].pretLicenta) {
		iMin = iStanga;
	}

	if (iDreapta < h.nrElem && h.vect[iDreapta].pretLicenta < h.vect[iMin].pretLicenta) {
		iMin = iDreapta;
	}

	if (index != iMin) {
		platforma temp = h.vect[index];
		h.vect[index] = h.vect[iMin];
		h.vect[iMin] = temp;
		filtrare(h, iMin);
	}
}

void traversareInordine(nodArb *rad) {	if (rad != NULL)	{		traversareInordine(rad->left);		printf("\nNrAsigurare->%d, PretLicenta->%5.2f, Denumire->%s, NrLuni->%d, Reducere->",			rad->info.nrAsigurare, rad->info.pretLicenta, rad->info.denumire, rad->info.nrLuni);		for (int j = 0; j < rad->info.nrLuni; j++)		{			printf("%5.2f ", rad->info.reduceriLuna[j]);		}
		traversareInordine(rad->right);	}}


void inserare(heap* h, platforma elem) {
	platforma *vNou = (platforma*)malloc(((*h).nrElem + 1) * sizeof(platforma));
	for (int i = 0; i < (*h).nrElem; i++) {
		vNou[i] = (*h).vect[i];
	}

	(*h).nrElem++;
	free((*h).vect);
	(*h).vect = vNou;
	(*h).vect[(*h).nrElem - 1] = elem;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--) {
		filtrare((*h), i);
	}
}

void afisare(heap h) {
	printf("\nElemente heap: ");
	for (int i = 0; i < h.nrElem; i++) {
		printf("\nNr.Asigurare: %d -> Pret licenta: %5.2f -> Denumire: %s -> Nr.Luni: %d -> Reduceri: "
			, h.vect[i].nrAsigurare, h.vect[i].pretLicenta, h.vect[i].denumire, h.vect[i].nrLuni);
		for (int j = 0; j < h.vect[i].nrLuni; j++) {
			printf("%5.2f ", h.vect[i].reduceriLuna[j]);
		}
	}
}

//void cautareSchimbare(heap* h, float pretNou) {
//	h->vect[0].pretLicenta = pretNou;
//	filtrare(*h, 0);
//}

void modificarePret(heap*h, int poz) {
	if (poz < h->nrElem) {
		float temp = h->vect[poz].pretLicenta;
		h->vect[poz].pretLicenta = h->vect[0].pretLicenta;
		h->vect[0].pretLicenta = temp;
		for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--) {
			filtrare((*h), i);
		}
	}
	else
		printf("\nNu exista elementul in heap");
	
}

void afisareArbFaraDesc(nodArb* rad, nodArb* st, nodArb* dr) {
	st = rad->left;
	dr = rad->right;
	if (rad != NULL) {
		if (st == NULL && dr != NULL) {
			traversareInordine(rad->right);
			printf("\nNrAsigurare->%d, PretLicenta->%5.2f, Denumire->%s, NrLuni->%d, Reducere->",				rad->info.nrAsigurare, rad->info.pretLicenta, rad->info.denumire, rad->info.nrLuni);			for (int j = 0; j < rad->info.nrLuni; j++)			{				printf("%5.2f ", rad->info.reduceriLuna[j]);			}
			traversareInordine(rad->right);
		}
		if (st != NULL && dr == NULL) {
			traversareInordine(rad->left);
			printf("\nNrAsigurare->%d, PretLicenta->%5.2f, Denumire->%s, NrLuni->%d, Reducere->",				rad->info.nrAsigurare, rad->info.pretLicenta, rad->info.denumire, rad->info.nrLuni);			for (int j = 0; j < rad->info.nrLuni; j++)			{				printf("%5.2f ", rad->info.reduceriLuna[j]);			}
			traversareInordine(rad->left);
		}
	}
	else
		printf("\nnu avem arbore");
}

void dezalocareHeap(heap h) {	if (h.nrElem > 0 && h.nrElem != NULL)	{		free(h.vect);	}}

void dezalocare(nodArb* rad) {
	if (rad != NULL) {
		//Post sa traversez cu orice ordine vreau
		nodArb* stanga = rad->left;//toti fii de stanga
		nodArb* dreapta = rad->right; // toti fii din dreapta ii salvam
		free(rad->info.denumire);
		free(rad->info.reduceriLuna);
		free(rad);
		dezalocare(stanga);
		dezalocare(dreapta);

	}
}



int main() {

	heap h;
	FILE* f = fopen("platforme.txt", "r");
	fscanf(f, "%d", &h.nrElem);
	char buff[30];
	h.vect = (platforma*)malloc(sizeof(platforma) * h.nrElem);
	for (int i = 0; i < h.nrElem; i++) {
		fscanf(f, "%d", &h.vect[i].nrAsigurare);
		fscanf(f, "%f", &h.vect[i].pretLicenta);
		fscanf(f, "%s", buff);
		h.vect[i].denumire = (char*)malloc((sizeof(char)) * (strlen(buff) + 1));
		strcpy(h.vect[i].denumire, buff);
		fscanf(f, "%d", &h.vect[i].nrLuni);
		h.vect[i].reduceriLuna = (float*)malloc(sizeof(float) * h.vect[i].nrLuni);
		for (int j = 0; j < h.vect[i].nrLuni; j++) {
			fscanf(f, "%f", &h.vect[i].reduceriLuna[j]);
		}
	}
	fclose(f);
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);

	afisare(h);
	//cautareSchimbare(&h, 500);
	modificarePret(&h, 15);
	modificarePret(&h, 4);
	printf("\nTraversare dupa schimbare:\n");
	afisare(h);
	nodArb* rad = NULL;
	rad = copiereHeapArb(h, &rad, 5);
	printf("\n INORDINE\n");
	traversareInordine(rad);
	dezalocareHeap(h);
	printf("\n INORDINE\n");
	traversareInordine(rad);
	nodArb* st = NULL;
	nodArb* dr = NULL;
	printf("\n------------------------\n");
	afisareArbFaraDesc(rad, st, dr);
	dezalocare(rad);
	
	

	return 0;
}