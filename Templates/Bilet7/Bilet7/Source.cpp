#include <stdio.h>
#include <stdlib.h>
#include <string>


struct camera {
	int camera;
	float pretCamera;
	char* tipCamera;
	int etaj;
	char* platitor;
};

struct nodArb {
	nodArb* left;
	nodArb* right;
	camera info;
};

struct nodSmp {
	nodSmp* next;
	int info;
};

struct nodDbl {
	camera info;
	nodDbl* prev;
	nodDbl* next;
};

struct Lista {
	nodDbl* prim;
	nodDbl* ultim;
};


nodArb* creare(camera c, nodArb* st, nodArb* dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.camera = c.camera;
	nou->info.pretCamera = c.pretCamera;
	nou->info.tipCamera = (char*)malloc(sizeof(char)*(strlen(c.tipCamera) + 1));
	strcpy(nou->info.tipCamera, c.tipCamera);
	nou->info.etaj = c.etaj;
	nou->info.platitor = (char*)malloc(sizeof(char) * (strlen(c.platitor) + 1));
	strcpy(nou->info.platitor, c.platitor);
	nou->left = st;
	nou->right = dr;
	return nou;
}

nodArb* inserare(camera c, nodArb* radacina) {

	nodArb* aux = radacina;
	//Verificam cazurile
	if (radacina == NULL) {
		aux = creare(c, NULL, NULL);
		return aux;
	}
	else
		while (true) {
			if (c.camera < aux->info.camera)
				if (aux->left != NULL)//Daca exista fiu stang
					aux = aux->left; // M-am dus pe ramura stanga
				else
				{
					//Daca nu exista, atunci il creez eu
					aux->left = creare(c, NULL, NULL);
					return radacina;
				}
			else if (c.camera > aux->info.camera)
				if (aux->right != NULL)//Daca exista fiu dreapta
					aux = aux->right; //Ma duc pe dreapta
				else {
					//Daca nu exista, creez
					aux->right = creare(c, NULL, NULL);
					return radacina;
				}
			else
				return radacina; // Daca exista deja, e duplicat, ies direct

		}
}

void inordine(nodArb* rad) {
	if (rad != NULL) {
		inordine(rad->left);
		printf("Camera: %d -> Pret: %5.2f -> Tip: %s -> Etaj: %d -> Platitor: %s\n",
			rad->info.camera, rad->info.pretCamera, rad->info.tipCamera, rad->info.etaj, rad->info.platitor);
		inordine(rad->right);
	}
}

int extrageNrCamere(nodArb* rad, int &nr, int et) {
	if (rad != NULL) {
		extrageNrCamere(rad->left, nr, et);
		if (rad->info.etaj == et)
			nr++;
		extrageNrCamere(rad->right, nr, et);
	}

	return nr;
}

int max(int a, int b) { //Functie pentru determinare nr niveluri
	int max = a;
	if (a < b)
		max = b;
	return max;
}

int nrLvl(nodArb* rad) {
	if (rad != NULL)
		return 1 + max(nrLvl(rad->left), nrLvl(rad->right));
	else
		return 0;
}


nodSmp* inserareNrEtajLista(nodSmp* cap, nodArb* rad) {
	nodSmp* nou; 
	int nr = 0;
	int i = 1;
	while (i <= 4) {
		if (cap) {
			nou = (nodSmp*)malloc(sizeof(nodSmp));
			nou->next = NULL;
			nou->info = extrageNrCamere(rad, nr, i);
			nodSmp* cursor = cap;
			while (cursor->next != NULL)
				cursor = cursor->next;
			cursor->next = nou;
		}
		else {
			nou = (nodSmp*)malloc(sizeof(nodSmp));
			nou->next = NULL;
			nou->info = extrageNrCamere(rad, nr, i);
			cap = nou;
		}
		i++;
		nr = 0;
	}
	return cap;

}

void traversareLista(nodSmp* cap) {
	nodSmp* cursor = cap;
	while (cursor) {
		printf("%d ", cursor->info);
		cursor = cursor->next;
	}
}

void copiereInDbl(Lista &lst, nodArb* rad, float pret) {
	if (rad != NULL) {
		copiereInDbl(lst, rad->left, pret);
		if (rad->info.pretCamera > pret) {
			nodDbl* nou = (nodDbl*)malloc(sizeof(nodDbl));
			nou->info.camera = rad->info.camera;
			nou->info.pretCamera = rad->info.pretCamera;
			nou->info.tipCamera = (char*)malloc(sizeof(char) * (strlen(rad->info.tipCamera) + 1));
			strcpy(nou->info.tipCamera, rad->info.tipCamera);
			nou->info.etaj = rad->info.etaj;
			nou->info.platitor = (char*)malloc(sizeof(char) * (strlen(rad->info.platitor) + 1));
			strcpy(nou->info.platitor, rad->info.platitor);
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
		copiereInDbl(lst, rad->right, pret);
	}

}



void inserareDblCriteriu(nodArb* rad, Lista &lst, const char* payeeKey) {
	if (rad != NULL) {
		inserareDblCriteriu(rad->left, lst, payeeKey);
		if (strcmp(rad->info.platitor, payeeKey) == 0) {
			nodDbl* nou = (nodDbl*)malloc(sizeof(nodDbl));
			nou->info.camera = rad->info.camera;
			nou->info.pretCamera = rad->info.pretCamera;
			nou->info.tipCamera = (char*)malloc(sizeof(char) * (strlen(rad->info.tipCamera) + 1));
			strcpy(nou->info.tipCamera, rad->info.tipCamera);
			nou->info.etaj = rad->info.etaj;
			nou->info.platitor = (char*)malloc(sizeof(char) * (strlen(rad->info.platitor) + 1));
			strcpy(nou->info.platitor, rad->info.platitor);
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
		inserareDblCriteriu(rad->right, lst, payeeKey);
	}
}

void afisareListaIS(Lista lst) {
	nodDbl* cursor = lst.prim;
	while (cursor) {
		printf("Camera: %d -> Pret: %5.2f -> Tip: %s -> Etaj: %d -> Platitor: %s\n",
			cursor->info.camera, cursor->info.pretCamera, cursor->info.tipCamera, cursor->info.etaj, cursor->info.platitor);
		cursor = cursor->next;
	}
}

void dezalocareArb(nodArb* rad) {
	if (rad != NULL) {
		//Post sa traversez cu orice ordine vreau
		nodArb* stanga = rad->left;//toti fii de stanga
		nodArb* dreapta = rad->right; // toti fii din dreapta ii salvam
		//free(rad->info.nume);
		free(rad);
		dezalocareArb(stanga);
		dezalocareArb(dreapta);

	}
}

void dezalocareLista(Lista& lst) {
	nodDbl* cursor = lst.prim;
	while (cursor) {
		nodDbl* aux = cursor->next;
		free(cursor->info.tipCamera);
		free(cursor->info.platitor);
		free(cursor);
		cursor = aux;
	}
	lst.prim = NULL;
	lst.ultim = NULL;

	//printf("Lista dezalocata");
}




int main() {

	nodArb* rad = NULL;
	int n;
	FILE* f = fopen("camere.txt", "r");
	char buff[30];
	camera c;
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &c.camera);
		fscanf(f, "%f", &c.pretCamera);
		fscanf(f, "%s", buff);
		c.tipCamera = (char*)malloc(sizeof(char) *(strlen(buff) + 1));
		strcpy(c.tipCamera, buff);
		fscanf(f, "%d", &c.etaj);
		fscanf(f, "%s", buff);
		c.platitor = (char*)malloc(sizeof(char) * (strlen(buff) + 1));
		strcpy(c.platitor, buff);

		rad = inserare(c, rad);
	}
	fclose(f);
	printf("\nEX 1: Afisare Arbore\n");
	inordine(rad);
	int nr = 0;
	//nr = extrageNrCamere(rad, nr, 4);
	//printf("\n%d", nr);
	printf("\nEX 2: ");
	printf("Numarul de camere pe fiecare etaj: ");
	nodSmp* cap = NULL;
	cap = inserareNrEtajLista(cap, rad);
	traversareLista(cap);
	printf("\n");
	printf("\nEX 3: ");
	printf(" Copiere in lista camerele cu pretul mai mare decat cel primit ca parametru: \n");
	Lista lstDubla;
	lstDubla.prim = NULL;
	lstDubla.ultim = NULL;
	copiereInDbl(lstDubla, rad, 300);
	afisareListaIS(lstDubla);
	printf("\nEX 4: Inserarea unei camere in lista dubla dupa numele platitorului: \n");
	inserareDblCriteriu(rad, lstDubla, "Vadim");
	inserareDblCriteriu(rad, lstDubla, "Oana");
	dezalocareArb(rad);
	afisareListaIS(lstDubla);
	dezalocareLista(lstDubla);

	return 0;
}