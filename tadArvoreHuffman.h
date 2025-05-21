struct tree{
	int freq,simbolo;
	struct tree *esq;
	struct tree *dir;
};
typedef struct tree Tree;

void init(Tree **raiz)
{
	*raiz=null;
}

void criaNo(Tree *esq,int simbolo,Tree **raiz,int freq,Tree *dir)
{
	*raiz = (Tree*) malloc(sizeof(Tree));
	(*raiz)->esq=esq;
	(*raiz)->dir=dir;
	(*raiz)->freq=freq
	(*raiz)->simbolo=simbolo;
}

char isEmpty(Tree *raiz)
{
	return raiz==null;
}


