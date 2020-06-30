// CITIRE LISTA DUBLA
struct x {
		int
		char*
		char*
		float
		int
		int
};

struct nod {
	x info;
	nod* next;
	nod* prev;
};

struct ListaDubla {
	nod* primul;
	nod* ultimul;
};

x* citireFis(FILE* f) {
	int nr;
	angajat a;
	angajat* angVect = NULL;
	int i = 0;
	char buff[30];
	if (f != NULL) {
		fscanf(f, "%d", &nr);
		printf("S-au extras %d angajati\n", nr);
		angVect = (angajat*)malloc(sizeof(angajat) * nr);
		while (!feof(f)) {
			fscanf(f, "%d", &a.cod);
			fscanf(f, "%s", &buff);
			a.nume = (char*)malloc(sizeof(strlen(buff)) + 1);
			strcpy(a.nume, buff);
			fscanf(f, "%s", &buff);
			a.functie = (char*)malloc(sizeof(strlen(buff)) + 1);
			strcpy(a.functie, buff);
			fscanf(f, "%f", &a.salariu);
			fscanf(f, "%d", &a.varsta);
			fscanf(f, "%d", &a.gradFunctie);
			angVect[i] = a;
			i++;
		}
	}

	return angVect;
}
oid inserareLDdeLaSfarsit(ListaDubla &list, angajat* av)
{
	angajat a;
	for (int i = 0; i < 10; i++) {
		a = av[i];
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = a;
		nou->next = NULL;
		nou->prev = list.ultimul;
		if (list.ultimul) {
			list.ultimul->next = nou;
			list.ultimul = nou;
		}
		else {
			list.ultimul = nou;
			list.primul = nou;
		}
	}


}

void afisare(ListaDubla &lista) {
	nod* cursor = lista.primul;
	printf("\nAfisare de la inceput\n");
	while (cursor) {
		printf("\n: Cod-> %d, Nume-> %s, Functie->%s, Salariu->%5.2f, Varsta->%d, GradFunctie->%d\n",
			cursor->info.cod, cursor->info.nume, cursor->info.functie, cursor->info.salariu, cursor->info.varsta, cursor->info.gradFunctie);
		cursor = cursor->next;
	}
	printf("\nAfisare de la sfarsit\n");
	cursor = lista.ultimul;
	while (cursor) {
		printf("\n: Cod-> %d, Nume-> %s, Functie->%s, Salariu->%5.2f, Varsta->%d, GradFunctie->%d\n",
			cursor->info.cod, cursor->info.nume, cursor->info.functie, cursor->info.salariu, cursor->info.varsta, cursor->info.gradFunctie);
		cursor = cursor->prev;
	}
}
void main()
{
	FILE* f;
	fopen_s(&f, "angajati.txt", "r");
	int nr;

	angajat* angVect = citireFis(f);
	fclose(f);
	for (int i = 0; i < 10; i++) {
		printf("\n[%d]: Cod-> %d, Nume-> %s, Functie->%s, Salariu->%5.2f, Varsta->%d,GradFunctie->%d\n", i,
			angVect[i].cod, angVect[i].nume, angVect[i].functie, angVect[i].salariu, angVect[i].varsta, angVect[i].gradFunctie);
	}
	printf("Succes");

	ListaDubla lista;
	lista.primul = lista.ultimul = NULL;
	inserareLDdeLaSfarsit(lista, angVect);
	afisare(lista);
}
/////////////////////////////


// CITIRE HASHTABLE
struct gradinita {
	int cod;
	char* nume;
	char* strada;
	float suprafata;
	int nrCopii;
};


struct nodLS {
	gradinita info;
	nodLS* next;
};


struct nodDbl {
	gradinita infp;
	nodDbl* prev;
	nodDbl* next;
};

struct listaDubla {
	nodDbl* prim;
	nodDbl* ultim;
};




struct hashTable {
	nodLS** vector; //vector dinamic de pointeri la noduri
	int size;
};

int hash(hashTable t, const char* cheie) {
	int ascii = 0;
	for (int i = 0; i < strlen(cheie); i++) {
		ascii += (int)cheie[i];
	}
	return ascii % t.size;
}

int inserare(hashTable tabela, gradinita g) {
	int poz = -1;
	if (tabela.vector != NULL) { // Daca tabela nu e nula putem insera
		poz = hash(tabela, g.nume); // calculam pozitia elementului pe care vrem sa-l inseram
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->info.cod = g.cod;
		nou->info.nume = (char*)malloc(sizeof(char) * (strlen(g.nume) + 1));
		strcpy(nou->info.nume, g.nume);
		nou->info.strada = (char*)malloc(sizeof(char) * (strlen(g.strada) + 1));
		strcpy(nou->info.strada, g.strada);
		nou->info.suprafata = g.suprafata;
		nou->info.nrCopii = g.nrCopii;
		nou->next = NULL;
		if (tabela.vector[poz] == NULL) {
			tabela.vector[poz] = nou; //Daca pozitia din vector e o lista goala, introducem
		}
		else {
			//S-a produs o coliziune
			nodLS* cursor = tabela.vector[poz]; // Capul listei unde s-a realizat coliziune
			while (cursor->next)
				cursor = cursor->next;
			cursor->next = nou;

		}
	}
	return poz;
}

void traversare(hashTable tabela) {
	if (tabela.vector != NULL) {
		//Tabela are elemente
		for (int i = 0; i < tabela.size; i++) {
			//FOLOSIM FOR DEOARECE ESTE UN VECTOR(DE LISTE)
			if (tabela.vector[i] != NULL) {
				printf("\nPozitie: %d ", i); // i-ul este chiar rezultatul hash-ului apelat anterior
				//VERIFICAM DACA PE POZITIA DIN VECTOR EXISTA O LISTA
				nodLS* cursor = tabela.vector[i];
				while (cursor) {
					printf("COD: %d, NUME: %s, STRADA: %s, SUPRAFATA: %5.2f, NR.COPII: %d \n", cursor->info.cod, cursor->info.nume,
						cursor->info.strada, cursor->info.suprafata, cursor->info.nrCopii);
					cursor = cursor->next;
				}
			}

			//printf("\n");
		}
	}
}



void dezalocare(hashTable tabela) {
	if (tabela.vector != NULL) {
		for (int i = 0; i < tabela.size; i++)
			if (tabela.vector[i] != NULL) {
				nodLS* temp = tabela.vector[i];
				while (temp) {
					nodLS* temp2 = temp->next;
					free(temp->info.nume);
					free(temp->info.strada);
					free(temp);
					temp = temp2;
				}
			}
		free(tabela.vector);
	}
}

int stergere(hashTable tabela, const char* cod) {
	int poz;
	if (tabela.vector != NULL) {
		poz = hash(tabela, cod);
		if (tabela.vector[poz] == NULL)
			return -1;
		else
		{
			if (strcmp(tabela.vector[poz]->info.nume, cod) == 0) {
				if (tabela.vector[poz]->next == NULL) {//IN CAZ IN CARE E PRIMUL
					nodLS* temp = tabela.vector[poz];
					free(temp->info.nume);
					free(temp);
					tabela.vector[poz] = NULL; //Trebuie sa nu mai pointeze daca e primul element ca nu mai e nicio lista
				}
				else {//DACA ARE CEVA DUPA EL
					nodLS* temp = tabela.vector[poz];
					tabela.vector[poz] = temp->next;// SARIM PESTE ELEMENTUL PE CARE IL STERGEM
					free(temp->info.nume);
					free(temp);
				}
			}
			else {
				nodLS* temp = tabela.vector[poz];
				while (temp->next != NULL && strcmp(temp->next->info.nume, cod))
					temp = temp->next;
				nodLS* p = temp->next; //elementul pe care il stergem
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
	return poz;
}


int main() {

	hashTable t;
	t.size = 101;
	t.vector = (nodLS**)malloc(sizeof(nodLS*) * t.size);
	for (int i = 0; i < t.size; i++) {
		t.vector[i] = NULL;
	}
	int nr = 0;
	nodDbl* cap = NULL;
	FILE* f = fopen("gradinite.txt", "r");
	gradinita g;
	char buff[60];
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++) {
		fscanf(f, "%d", &g.cod);
		fscanf(f, "%s", buff);
		g.nume = (char*)malloc((strlen(buff) + 1) * sizeof(char));
		strcpy(g.nume, buff);
		fscanf(f, "%s", buff);
		g.strada = (char*)malloc((strlen(buff) + 1) * sizeof(char));
		strcpy(g.strada, buff);
		fscanf(f, "%f", &g.suprafata);
		fscanf(f, "%d", &g.nrCopii);

		inserare(t, g);
	}
	fclose(f);
	traversare(t);
////////////////////////

// CITIRE HEAP
	truct x{
		int x;
		float x;
		char* x;
		int x;
		float* x;
	};

	struct heap {
		x* vect;
		int nrElem;
	};

	void filtrare(heap h, int index)
	{
		int indexMin = index;
		int indexS = 2 * index + 1;
		int indexD = 2 * index + 2;
		if (indexS < h.nrElem && h.vect[indexS].pretLicenta < h.vect[indexMin].pretLicenta)
		{
			indexMin = indexS;
		}
		if (indexD < h.nrElem && h.vect[indexD].pretLicenta < h.vect[indexMin].pretLicenta)
		{
			indexMin = indexD;
		}
		if (index != indexMin)
		{
			platforma temp = h.vect[index];
			h.vect[index] = h.vect[indexMin];
			h.vect[indexMin] = temp;
			filtrare(h, indexMin);
		}
	}

	void inserare(heap *h, platforma elem)
	{
		platforma *vect1 = (platforma*)malloc(sizeof(platforma)*(*h).nrElem + 1);
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
		printf("\nElemenetele heapului sunt: ");
		for (int i = 0; i < h.nrElem; i++)
		{
			printf("\nNrAsigurare->%d, PretLicenta->%5.2f, Denumire->%s, NrLuni->%d, Reducere->",
				h.vect[i].nrAsigurare, h.vect[i].pretLicenta, h.vect[i].denumire, h.vect[i].nrLuni);
			for (int j = 0; j < h.vect[i].nrLuni; j++)
			{
				printf("%5.2f ", h.vect[i].reduceriLuna[j]);
			}
		}
	}
	void dezalocareHeap(heap h) {
		if (h.nrElem > 0 && h.nrElem != NULL)
		{
			free(h.vect);
		}
	}
	void main() {
		heap h;
		FILE* f = fopen("heapplatforma.txt", "r");
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
		afisareHeap(h);
///////////////////////
// CITIRE ABC
		struct librarie {
			int cod;
			char* name;
			int nrCarti;
		};

		struct nodArb {
			nodArb* left;
			nodArb* right;
			librarie info;
		};

		nodArb *creare(librarie s, nodArb *st, nodArb *dr)
		{
			nodArb *nou = (nodArb*)malloc(sizeof(nodArb));
			nou->info.cod = s.cod;
			nou->info.name = (char*)malloc((strlen(s.name) + 1) * sizeof(char));
			strcpy(nou->info.name, s.name);
			nou->info.nrCarti = s.nrCarti;
			nou->left = st;
			nou->right = dr;
			return nou;
		}

		nodArb *inserare(librarie s, nodArb *rad)
		{
			nodArb *aux = rad;
			if (rad == NULL)
			{
				aux = creare(s, NULL, NULL);
				return aux;
			}
			else
				while (true)
				{
					if (strlen(s.name) < strlen(aux->info.name))
						if (aux->left != NULL)
							aux = aux->left;
						else
						{
							aux->left = creare(s, NULL, NULL);
							return rad;
						}
					else
						if (strlen(s.name) > strlen(aux->info.name))
							if (aux->right != NULL)
								aux = aux->right;
							else
							{
								aux->right = creare(s, NULL, NULL);
								return rad;
							}
						else
							return rad;
				}
		}

		void inordine(nodArb *rad)
		{
			if (rad != NULL)
			{
				inordine(rad->left);
				printf("\nCod=%d, Nume=%s, NrCarti=%d", rad->info.cod, rad->info.name, rad->info.nrCarti);
				inordine(rad->right);
			}
		}


		struct librarie {
			int cod;
			char* name;
			int nrCarti;
		};

		struct nodArb {
			nodArb* left;
			nodArb* right;
			librarie info;
		};

		nodArb *creare(librarie s, nodArb *st, nodArb *dr)
		{
			nodArb *nou = (nodArb*)malloc(sizeof(nodArb));
			nou->info.cod = s.cod;
			nou->info.name = (char*)malloc((strlen(s.name) + 1) * sizeof(char));
			strcpy(nou->info.name, s.name);
			nou->info.nrCarti = s.nrCarti;
			nou->left = st;
			nou->right = dr;
			return nou;
		}

		nodArb *inserare(librarie s, nodArb *rad)
		{
			nodArb *aux = rad;
			if (rad == NULL)
			{
				aux = creare(s, NULL, NULL);
				return aux;
			}
			else
				while (true)
				{
					if (strlen(s.name) < strlen(aux->info.name))
						if (aux->left != NULL)
							aux = aux->left;
						else
						{
							aux->left = creare(s, NULL, NULL);
							return rad;
						}
					else
						if (strlen(s.name) > strlen(aux->info.name))
							if (aux->right != NULL)
								aux = aux->right;
							else
							{
								aux->right = creare(s, NULL, NULL);
								return rad;
							}
						else
							return rad;
				}
		}

		void inordine(nodArb *rad)
		{
			if (rad != NULL)
			{
				inordine(rad->left);
				printf("\nCod=%d, Nume=%s, NrCarti=%d", rad->info.cod, rad->info.name, rad->info.nrCarti);
				inordine(rad->right);
			}
		}

		void main() {

			int n;

			FILE* f = fopen("librarii.txt", "r");

			//printf("Nr. libarrii: ");
			fscanf(f, "%d", &n);

			nodArb *rad = NULL;
			librarie l;
			char buffer[20];

			for (int i = 0; i < n; i++)
			{
				//printf("\nCod: ");
				fscanf(f, "%d", &l.cod);
				//printf("\nNume: ");
				fscanf(f, "%s", buffer);
				l.name = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
				strcpy(l.name, buffer);
				//printf("\nMedie: ");
				fscanf(f, "%d", &l.nrCarti);

				rad = inserare(l, rad);

			}
			fclose(f);

			printf("\n----------------\n");
			inordine(rad);
		}

///////////////////////

// CITIRE STIVA
		struct Carte {
			int cod;
			char* autor;
			float pret;

		};

		struct nodStiva {
			nodStiva* next; //CA LA LISTA SIMPLA!!
			Carte info;
		};

		struct nodLista { //PENTRU CONVERSIE IN LISTA SIMPLA
			nodLista* next;
			Carte info;
		};

		//PUSH: LA ADRESA VARFULUI, INSERAM O CARTE
		void push(nodStiva** varf, Carte c) {
			nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
			nou->info = c;
			nou->next = NULL;
			if ((*varf) == NULL) {
				(*varf) = nou;
			}
			else {
				nou->next = (*varf);
				(*varf) = nou;
			}
			//END
		}

		//POP, LA ADRESA VARFULUI, EXTRAGEM O CARTE, O DEZALOCAM APOI PRELUCRAM INFO MAI DEPARTE
		int pop(nodStiva** varf, Carte* info) {
			if (*varf == NULL)
				return 0;
			else {
				info->cod = (*varf)->info.cod;
				info->autor = (char*)malloc(sizeof(char) * (strlen((*varf)->info.autor) + 1));
				strcpy(info->autor, (*varf)->info.autor);
				info->pret = (*varf)->info.pret;
				nodStiva* popped = *varf;
				*varf = (*varf)->next;
				free(popped->info.autor);
				free(popped);
				return 1;
			}
		}

		void traverseStiva(nodStiva* varf) {
			nodStiva* c = varf;
			while (c) {
				printf("Cod carte: %d -> Autor: %s -> Pret: %2.2f\n", c->info.cod, c->info.autor, c->info.pret);
				c = c->next;
			}
		}

		int main() {

			nodStiva* varf = NULL;
			char buff[30];
			FILE* f = fopen("text.txt", "r");
			int n;
			fscanf(f, "%d", &n);
			if (n <= 0) {
				printf("Stiva nu s-a initializat");
			}
			else {
				for (int i = 0; i < n; i++) {
					Carte c;
		
					fscanf("%d", &c.cod);
	
					fscanf(f, "%s", buff);
					c.autor = (char*)malloc(sizeof(char) * (strlen(buff) + 1));
					strcpy(c.autor, buff);

					fscanf(f, "%f", &c.pret);
					push(&varf, c);
					printf("Cartea: %d a fost inserata.\n", c.cod);
				}

			}

			traverseStiva(varf);
	
///////////////////////

// CITIRE COADA
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
			else if (*vf == NULL) {
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

		int main() {
			FILE* f = fopen("text.txt", "r");
			int n;

			fscanf(f, "%d", &n);
			nodCoada* vf = NULL;
			nodCoada* last = NULL;
			student s;
			char buff[30];
			for (int i = 0; i < n; i++) {

				fscanf(f, "%d", &s.varsta);
				char buff[30];
				fscanf(f, "%s", buff);
				s.nume = (char*)malloc(sizeof(char) * (strlen(buff)) + 1));
				strcpy(s.nume, buff);
				fscanf("%f", &s.medie);
				put(&vf, &last, s);
			}
			printf("Afisare coada:\n");
			traverse(vf);
		}

///////////////////////


//CITIRE LISTA SIMPLA

		struct test {
			int a;
			float b;
			char* n;
			char* s;
		};

		struct nodSmp {
			nodSmp* next;
			test info;
		};


		nodSmp* inserareLs(nodSmp* cap, test t) {
			nodSmp* cursor = cap;
			nodSmp* nou;
			nou = (nodSmp*)malloc(sizeof(nodSmp));
			nou->info.a = t.a;
			nou->info.b = t.b;
			nou->info.n = (char*)malloc(sizeof(char) * (strlen(t.n) + 1));
			strcpy(nou->info.n, t.n);
			nou->info.s = (char*)malloc(sizeof(char) * (strlen(t.s) + 1));
			strcpy(nou->info.s, t.s);
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

		void parcurgereLs(nodSmp* cap) {
			nodSmp* cursor = cap;
			while (cursor) {
				printf("a: %d, b: %5.2f, n: %s, s: %s\n", cursor->info.a, cursor->info.b, cursor->info.n, cursor->info.s);
				cursor = cursor->next;
			}
		}

		int main() {
			nodSmp* cap = NULL;
			char buff[30];
			test t;
			FILE* f = fopen("Text.txt", "r");
			int nr = 0;
			fscanf(f, "%d", &nr);
			for (int i = 0; i < nr; i++) {
				fscanf(f, "%d", &t.a);
				fscanf(f, "%f", &t.b);
				fscanf(f, "%s", buff);
				t.n = (char*)malloc(sizeof(char) * (strlen(buff) + 1));
				strcpy(t.n, buff);
				fscanf(f, "%s", buff);
				t.s = (char*)malloc(sizeof(char) * (strlen(buff) + 1));
				strcpy(t.s, buff);
				inserareLs(cap, t);

				cap = inserareLs(cap, t);
			}

			parcurgereLs(cap);

			return 0;
		}

////////////////////////////////