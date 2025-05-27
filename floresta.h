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

void init(Floresta **lista)
{
	*lista = NULL;
}

char isEmpty(Floresta *lista)
{
	return lista == NULL;
}

Tree* novaArvore(Tree *esq, int simb, int freq, Tree *dir)
{
	Tree *no = (Tree*)malloc(sizeof(Tree));
	no->esq = esq;
	no->dir = dir;
	no->freq=freq;
	no->simbolo=simb;
	
	return  no;
}

Floresta * novaFloresta(Tree* esq, int simb,int freq,Tree *dir)
{
	Floresta *f = (Floresta *) malloc(sizeof(Floresta));
	f->info = novaArvore(esq,simb,freq,dir);
	f->prox=NULL;
	return f;
}

void inserir(Tree *esq,Floresta **lista,int simb, int freq, Tree* dir)
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
		Floresta *ant=*lista;
		while(ant->prox!=null && ant->prox->info->freq < aux->info->freq)
		{
			ant=ant->prox;
		}
		aux->prox=ant->prox;
		ant->prox=aux;
	}
}


Tree* retira(Floresta **lista)
{
	Tree *aux = (*lista)->info;
	Floresta *rm = *lista;
	*lista= (*lista)->prox;
	free(*lista);
	return aux;
}



