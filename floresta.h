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
	Tree info;
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

Floresta *novaCaixa(int freq, int simb)
{
	Floresta *f = (Floresta *)malloc(sizeof(Floresta));
	f->info.esq = f->info.dir = NULL;
	f->info.freq=freq;
	f->info.simbolo=simb;
}

void inserir(Floresta **lista, int freq, int simb)
{
	Floresta *aux = novaCaixa(freq, simb);

	if (*lista == NULL || aux->info.freq<(*lista)->info.freq)
	{
		aux->prox=(*lista);
		*lista=aux;
	}
	else
	{
		Floresta *ant=*lista;
		while(ant->prox!=null && ant->prox->info.freq<aux->info.freq)
		{
			ant=ant->prox;
		}
		aux->prox=ant->prox;
		ant->prox=aux;
	}
}


void retira(Floresta **lista,Floresta *retorno)
{
	retorno=*lista;
	*lista= (*lista)->prox;
}



