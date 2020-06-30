#include<stdio.h>
#include<stdio.h>
#include<string>

struct librarie {
	int cod;
	char* nume;
	int nrCarti;
};


struct nodArb{
	nodArb*left;
	nodArb*right;
	librarie info;
};

nodArb* creare(librarie l, nodArb* st, nodArb* dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.cod = l.cod;
	nou->info.nume = (char*)malloc(sizeof(strlen(l.nume) + 1));
	strcpy(nou->info.nume, l.nume);
	nou->info.nrCarti = l.nrCarti;
	nou->left = st;
	nou->right = dr;
	return nou;
}

nodArb* inserare(librarie s, nodArb* radacina) {

	nodArb* aux = radacina;
	//Verificam cazurile
	if (radacina == NULL) {
		aux = creare(s, NULL, NULL);
		return aux;
	}
	else
		while (true) {
			if (strlen(s.nume) < strlen(aux->info.nume))
				if (aux->left != NULL)//Daca exista fiu stang
					aux = aux->left; // M-am dus pe ramura stanga
				else
				{
					//Daca nu exista, atunci il creez eu
					aux->left = creare(s, NULL, NULL);
					return radacina;
				}
			else if (strlen(s.nume) > strlen(aux->info.nume))
				if (aux->right != NULL)//Daca exista fiu dreapta
					aux = aux->right; //Ma duc pe dreapta
				else {
					//Daca nu exista, creez
					aux->right = creare(s, NULL, NULL);
					return radacina;
				}
			else
				return radacina; // Daca exista deja, e duplicat, ies direct

		}
}

void inordine(nodArb* rad) { //SRD
	if (rad != NULL) {
		inordine(rad->left); //apel pe stanga
		printf("\n Cod: %d, Nume: %s, Nr. carti: %d", rad->info.cod, rad->info.nume, rad->info.nrCarti);//radacina
		inordine(rad->right);//apel pe dreapta
	}

}



int main() {

	FILE* f = fopen("librarii.txt", "r");
	nodArb* rad = NULL;
	int n;
	fscanf(f, "%d", &n);
	librarie l;
	char buff[20];
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &l.cod);
		fscanf(f, "%s", buff);
		l.nume = (char*)malloc(sizeof(char) * (strlen(buff) + 1));
		strcpy(l.nume, buff);
		fscanf(f, "%d", &l.nrCarti);
		rad = inserare(l, rad);
	}
	fclose(f);
	inordine(rad);



	return 0;
}