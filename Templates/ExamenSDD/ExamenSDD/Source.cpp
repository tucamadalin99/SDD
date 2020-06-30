#include <stdio.h>
#include <stdlib.h>
#include <string>

struct factura {
	int cod;
	char* tipFactura;
	char* lunaFacturare;
	float pret;
	int zileScadenta;
};

struct heap {
	factura* vect;
	int nrElem;
};

struct nodArb {
	factura info;
	nodArb* left;
	nodArb* right;
};

struct nodSmp {
	nodSmp* next;
	factura info;
};


void filtrare(heap h, int index)
{
	int indexMin = index;
	int indexS = 2 * index + 1;
	int indexD = 2 * index + 2;
	if (indexS < h.nrElem && h.vect[indexS].zileScadenta < h.vect[indexMin].zileScadenta)
	{
		indexMin = indexS;
	}
	if (indexD < h.nrElem && h.vect[indexD].zileScadenta < h.vect[indexMin].zileScadenta)
	{
		indexMin = indexD;
	}
	if (index != indexMin)
	{
		factura temp = h.vect[index];
		h.vect[index] = h.vect[indexMin];
		h.vect[indexMin] = temp;
		filtrare(h, indexMin);
	}
}

void inserare(heap* h, factura elem)
{
	factura* vect1 = (factura*)malloc(sizeof(factura) * (*h).nrElem + 1);
	for (int i = 0; i < (*h).nrElem; i++)
		vect1[i] = (*h).vect[i];
	(*h).nrElem++;
	free((*h).vect);
	(*h).vect = vect1;

	(*h).vect[(*h).nrElem - 1] = elem;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--)
		filtrare((*h), i);
}

void afisareHeap(heap h)
{
	printf("\nElemenetele heapului sunt: \n");
	for (int i = 0; i < h.nrElem; i++)
	{
		printf("COD: %d -> Tip Factura:  %s -> Luna: %s -> Pret: %5.2f -> Zile scadenta: %d\n",
			h.vect[i].cod, h.vect[i].tipFactura, h.vect[i].lunaFacturare, h.vect[i].pret, h.vect[i].zileScadenta);
	}
}

void dezalocareHeap(heap& h) {
	if (h.nrElem > 0 && h.nrElem != NULL)
	{
		free(h.vect);
	}
}


nodArb* creare(factura p, nodArb* st, nodArb* dr) {	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));	nou->info.cod = p.cod;	nou->info.tipFactura = (char*)malloc(sizeof(char) * (strlen(p.tipFactura) + 1));	strcpy(nou->info.tipFactura, p.tipFactura);	nou->info.lunaFacturare = (char*)malloc(sizeof(char) * (strlen(p.lunaFacturare) + 1));	strcpy(nou->info.lunaFacturare, p.lunaFacturare);	nou->info.pret = p.pret;	nou->info.zileScadenta = p.zileScadenta;	nou->left = st;	nou->right = dr;	return nou;}

nodArb* inserareArb(factura p, nodArb* rad) {
	nodArb* aux = rad;
	if (rad == NULL) {
		aux = creare(p, NULL, NULL);
		return aux;
	}
	else
		while (true) {
			if (p.pret < aux->info.pret)
				if (aux->left != NULL)
					aux = aux->left;
				else {
					aux->left = creare(p, NULL, NULL);
					return rad;
				}
			else if (p.pret > aux->info.pret)
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
void stergeNod(heap h, int i)
{

	factura temp = h.vect[h.nrElem - 1];
	h.vect[i] = temp;

	h.nrElem--;

	filtrare(h, i);
}

void stergeDinHeap(heap h) {
	int i = 0;
	while (i < h.nrElem) {
		if (h.vect[i].zileScadenta < 3) stergeNod(h, i);
		else i++;
	}
}

nodArb* copiereHeapArb(heap& h, nodArb** rad, int n) {
	//*rad = NULL;
	factura fact;
	for (int i = 0; i < n; i++) {

		fact.cod = h.vect[i].cod;
		fact.tipFactura = (char*)malloc(sizeof(char) * (strlen(h.vect[i].tipFactura) + 1));
		strcpy(fact.tipFactura, h.vect[i].tipFactura);
		fact.lunaFacturare = (char*)malloc(sizeof(char) * (strlen(h.vect[i].lunaFacturare) + 1));
		strcpy(fact.lunaFacturare, h.vect[i].lunaFacturare);
		fact.pret = h.vect[i].pret;
		fact.zileScadenta = h.vect[i].zileScadenta;
		*rad = inserareArb(fact, *rad);

	}
	return *rad;
}

void traversareInordine(nodArb* rad) {	if (rad != NULL)	{		traversareInordine(rad->left);		printf("COD: %d -> Tip Factura:  %s -> Luna: %s -> Pret: %5.2f -> Zile scadenta: %d\n",
			rad->info.cod, rad->info.tipFactura, rad->info.lunaFacturare, rad->info.pret, rad->info.zileScadenta);
		traversareInordine(rad->right);	}}

nodSmp* inserareLs(nodSmp* cap, nodArb* f) {
	nodSmp* cursor = cap;
	nodSmp* nou;
	nou = (nodSmp*)malloc(sizeof(nodSmp));
	nou->info.cod = f->info.cod;
	nou->info.tipFactura = (char*)malloc(sizeof(char) * (strlen(f->info.tipFactura) + 1));
	strcpy(nou->info.tipFactura, f->info.tipFactura);
	nou->info.lunaFacturare = (char*)malloc(sizeof(char) * (strlen(f->info.lunaFacturare) + 1));
	strcpy(nou->info.lunaFacturare, f->info.lunaFacturare);
	nou->next = NULL;
	if (cap) {
		while (cursor->next) {
			cursor = cursor->next;
		}
		cursor->next = nou;
	}
	else {
		cap = nou;
	}

	return cap;
}


void inserareArbLista(nodArb*& rad, nodSmp*& capLista, float cheiePret) {

	if (rad != NULL) {
		inserareArbLista(rad->left, capLista, cheiePret);
		inserareLs(capLista, rad);
		inserareArbLista(rad->right, capLista, cheiePret);
	}
}


void parcurgereLs(nodSmp* cap) {
	nodSmp* cursor = cap;
	while (cursor) {
		printf("COD: %d -> Tip Factura:  %s -> Luna: %s -> Pret: %5.2f -> Zile scadenta: %d\n",
			cursor->info.cod, cursor->info.tipFactura, cursor->info.lunaFacturare, cursor->info.pret, cursor->info.zileScadenta);

		cursor = cursor->next;
	}
}


void dezalocareArb(nodArb* rad) {
	if (rad != NULL) {

		nodArb* stanga = rad->left;
		nodArb* dreapta = rad->right;
		free(rad->info.tipFactura);
		free(rad->info.lunaFacturare);
		free(rad);
		dezalocareArb(stanga);
		dezalocareArb(dreapta);

	}
}

void dezalocareLista(nodSmp* cap) {
	nodSmp* cursor = cap;
	while (cursor) {
		nodSmp* aux = cursor->next;
		free(cursor->info.tipFactura);
		free(cursor->info.lunaFacturare);
		cursor = aux;
	}
}

int main() {

	heap h;
	FILE* f = fopen("facturi.txt", "r");
	fscanf(f, "%d", &h.nrElem);
	char buff[30];
	h.vect = (factura*)malloc(sizeof(factura) * h.nrElem);
	for (int i = 0; i < h.nrElem; i++) {
		fscanf(f, "%d", &h.vect[i].cod);
		fscanf(f, "%s", buff);
		h.vect[i].tipFactura = (char*)malloc(sizeof(char) * (strlen(buff) + 1));
		strcpy(h.vect[i].tipFactura, buff);
		fscanf(f, "%s", buff);
		h.vect[i].lunaFacturare = (char*)malloc(sizeof(char) * (strlen(buff) + 1));
		strcpy(h.vect[i].lunaFacturare, buff);
		fscanf(f, "%f", &h.vect[i].pret);
		fscanf(f, "%d", &h.vect[i].zileScadenta);
	}
	fclose(f);
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	afisareHeap(h);
	//extragere(&h);
	//afisareHeap(h);
	nodArb* rad = NULL;
	rad = copiereHeapArb(h, &rad, 8);
	printf("\nExercitiul 3 - copierea unei parti primite ca parametru: \n");
	traversareInordine(rad);

	printf("Exercitiul 2- Extragerea elementelor cu mai putin de 3 zile scadenta: \n");
	stergeDinHeap(h);
	afisareHeap(h);
	printf("\nExercitiul 4 - inserarea arborelui intr-o lista simpla: \n");
	nodSmp* cap = NULL;
	inserareArbLista(rad, cap, 283);
	//traversareInordine(rad);
	parcurgereLs(cap);
	dezalocareHeap(h);
	traversareInordine(rad);
	dezalocareArb(rad);
	dezalocareLista(cap);

	return 0;
}