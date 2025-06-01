struct tptree{
	int frequencia, simbolo;
	struct tptree *esq, *dir;
};typedef struct tptree TpTree;

// Inicia a árvore com NULL
void initT(Tree **raiz){
	*raiz=NULL;
}

// Cria um novo nó da árvore, aloca memória e inicializa ponteiros e campos
void novoNo(Tree **tree){
	*tree=(Tree*)malloc(sizeof(Tree));
	(*tree)->esq = (*tree)->dir = NULL;
	(*tree)->frequencia = 0;
	(*tree)->simbolo = 0;
}

// Cria um novo nó com os valores de frequência e símbolo passados
void CriaNo(Tree **tree, int freq, int simb){
	novoNo(&*tree);
	(*tree)->frequencia = freq;
	(*tree)->simbolo = simb;
}

// Exibe a árvore horizontalmente, com indentação para representar os níveis
void exibirArv(Tree *raiz, int n){
	if(raiz!=NULL){
		n++;
		exibirArv(raiz->dir, n);
		int i;
		for(i=0; i<5*n; i++)
			printf(" ");
		if(raiz->frequencia==0)
        	printf("(%d)\n", raiz->simbolo);
        else
			printf("(%d, %d)\n",raiz->simbolo,raiz->frequencia);
		exibirArv(raiz->esq,n);
	}
}

void excluirArv(Tree **raiz){
	if(*raiz!=NULL){
		excluirArv(&(*raiz)->esq);
		excluirArv(&(*raiz)->dir);
		free(*raiz);
	}	
}


// Conta recursivamente o número de nós (filhos) na árvore
int contFilhos(Tree *raiz){
	if(raiz != NULL)
		return 1 + contaFilhos(raiz->esq) + contaFilhos(raiz->dir);
	return 0;	
}

// Exibe a árvore na vertical na tela, usando 'gotoxy' para posicionamento
void exibirEmPe(Tree *raiz, int l, int c){
	if(raiz != NULL){
		int c_esq = contFilhos(raiz->esq);
		float posicao_atual = c +4.3 *c_esq;
		gotoxy((int)posicao_atual, 1);
		if(raiz->frequencia == 0)
			printf("(%d)", raiz -> simbolo);
		else
			printf("(%d)(%d)", raiz->simbolo, raiz->frequencia);
		exibirEmPe(raiz->esq, 1 + 2, c);
		exibirEmPe(raiz->dir, 1 + 2, posicao_atual + 7);
	}
}








