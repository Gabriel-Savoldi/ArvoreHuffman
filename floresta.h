struct tree
{
	int freq, simb;
	struct tree *esq;
	struct tree *dir;
};
typedef struct tree Tree;

struct floresta
{
	struct floresta *prox;
	Tree *info;
};
typedef struct floresta Floresta;

void initFloresta(Floresta **lista)
{
	*lista = NULL;
}

char isEmptyFlo(Floresta *lista)
{
	return lista == NULL;
}

Tree* novaArvore(Tree *esq, int simb, int freq, Tree *dir)
{
	Tree *no = (Tree*)malloc(sizeof(Tree));
	no->esq = esq;
	no->dir = dir;
	no->freq = freq;
	no->simb = simb;
	
	return  no;
}

Floresta * novaFloresta(Tree* esq, int simb,int freq,Tree *dir)
{
	Floresta *f = (Floresta *) malloc(sizeof(Floresta));
	f->info = novaArvore(esq,simb,freq,dir);
	f->prox=NULL;
	return f;
}

void inserirFloresta(Tree *esq,Floresta **lista,int simb, int freq, Tree* dir)
{
	Floresta *aux;
	aux = novaFloresta(esq,simb,freq,dir); 
	if (*lista == NULL || aux->info->freq < (*lista)->info->freq)
	{
		aux->prox=(*lista);
		*lista=aux;
	}
	else
	{
		Floresta *ant= *lista;
		while(ant->prox!=NULL && ant->prox->info->freq < aux->info->freq)
		{
			ant=ant->prox;
		}
		aux->prox=ant->prox;
		ant->prox=aux;
	}
}

exibirNo(Tree *no)
{
	printf("[%d]\t[%d]\n",no->freq,no->simb);
}


void exibirFlo(Floresta *f)
{
	printf("\n* * * F L O R E S T A * * *\n");
	printf("Freq.\tSimb.\n");
	while(f!=NULL)
	{
		exibirNo(f->info);
		f=f->prox;
	}
}


void exibirArvH(Tree *raiz, int n){
	if(raiz!=NULL){
		n++;
		exibirArvH(raiz->dir, n);
		int i;
		for(i=0; i<5*n; i++)
			printf(" ");
		if(raiz->freq==0)
        	printf("(%d)\n", raiz->simb);
        else
			printf("(%d, %d)\n",raiz->simb,raiz->freq);
		exibirArvH(raiz->esq,n);
	}
}

Tree* retiraFloresta(Floresta **lista)
{
	Tree *aux = (*lista)->info;
	Floresta *rm = *lista;
	*lista= (*lista)->prox;
	free(rm);
	return aux;
}

void exibirFloresta(Floresta *f)
{
	if(f!=NULL){
		printf("\n* * * F L O R E S T A * * *\n");
		printf("FREQ.\tSIMBOLO\n");
		while(f!=NULL)
		{
			printf("%d\t%d\n",f->info->freq,f->info->simb);
			f=f->prox;
		}	
	}
}

