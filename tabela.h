#include<string.h>
#include<stdio.h>
#include<conio2.h>

struct bits
{
 unsigned char b7:1;
 unsigned char b6:1;
 unsigned char b5:1;
 unsigned char b4:1;
 unsigned char b3:1;
 unsigned char b2:1;
 unsigned char b1:1;
 unsigned char b0:1;
};

union byte
{
 struct bits bi;
 unsigned char num;
};

struct registro{
	int simb;
	char palavra[30];
	union byte cod;
};
typedef struct registro Registro;

struct tabela{
	Registro reg;
	int freq;
	struct tabela *prox;
};
typedef struct tabela Tabela;


void initTabela(Tabela **T)
{
	*T=NULL;
}

char isEmpty(Tabela *T)
{
	return T == NULL;
}



Tabela * buscaSimb(Tabela *t,int simb)
{
	while(t!= NULL && t->reg.simb!=simb)
		t=t->prox;
	return t;
}


Tabela * buscaPalavra(Tabela *t,char palavra[30])
{
	while(t!= NULL && stricmp(t->reg.palavra,palavra)!=0)
		t=t->prox;
	return t;
}

Tabela* criarLinhaTabela(int simb,char palavra[30],unsigned char cod)
{
	Tabela *t=(Tabela*) malloc(sizeof(Tabela));
	t->reg.cod.num= cod;
	strcpy(t->reg.palavra,palavra);
	t->reg.simb=simb;
	t->prox=NULL;
	
	//printf("criando: simb = [%d]   palavra = [%s]   cod = [%d]\n",simb,palavra,cod);
	return t;
}


void inserirTabela(Tabela** t,int *simb, char palavra[30], unsigned char cod)
{
	Tabela* aux=buscaPalavra(*t,palavra);
	
	if(aux==NULL)
	{
		aux = criarLinhaTabela(*simb,palavra,cod);
		*simb= *simb +1;
		aux->freq=1;
		aux->prox=*t;
		*t=aux;
	}
	else
	{
		aux->freq++; 
	}
}

void exibirTabela(Tabela* t)
{
	printf("\n * * * T A B E L A * * * \n");
	printf("Freq.\tSimb.\tPalavr.\tCod\n");
	
	while(t!=NULL)
	{
		printf("%d\t%d\t[%s]\t",t->freq,t->reg.simb,t->reg.palavra);
		
		printf("%d",t->reg.cod.bi.b0);
		printf("%d",t->reg.cod.bi.b1);
		printf("%d",t->reg.cod.bi.b2);
		printf("%d",t->reg.cod.bi.b3);
		printf("%d",t->reg.cod.bi.b4);
		printf("%d",t->reg.cod.bi.b5);
		printf("%d",t->reg.cod.bi.b6);
		printf("%d\n",t->reg.cod.bi.b7);	
		
		t=t->prox;
	}	
}


/*
// Lê bytes de um arquivo e exibe os bits individuais na tela.
void montarbytes(){
	FILE * ptr = fopen("codigo.dat", "rb");
	Byte b;
	fread(&b.cod, sizeof(char), 1, ptr);
	while(!feof(ptr)){
		printf("%d", b.bit.b0);
		printf("%d", b.bit.b1);
		printf("%d", b.bit.b2);
		printf("%d", b.bit.b3);
		printf("%d", b.bit.b4);
		printf("%d", b.bit.b5);
		printf("%d", b.bit.b6);
		printf("%d", b.bit.b7);
		fread(&b.cod, sizeof(char), 1, ptr);
	}
	fclose(ptr);
}

*/

/*
// Exibe a tabela de símbolos formatada em colunas com bordas na tela, usando caracteres gráficos.
void exibirTab(Tabela *tab, int ci, int li){
	int i, j, vetor[4], aux;
	vetor[0] = ci + 20;
	for(i=1;i<4;i++)
		vetor[i] = vetor[i-1] + 20;
	if(tab->freq == 0)
		vetor[3] = vetor[2];

	gotoxy(ci, li);
	printf("%c", 201); //canto esquerdo superior

	for(i = ci + 1; i < vetor[3]; i++){
		gotoxy(i, li);
		if(i == vetor[0] || i == vetor[1] || i == vetor[2] || i == vetor[3])
			printf("%c", 203);
		else
			printf("%c", 205);

	}

	gotoxy(vetor[3], li);
	printf("%c", 187); //canto direito superior

	i = li+1;

	gotoxy(ci, i);
	printf("%c", 186); //borda esq
	gotoxy(vetor[0], i);
	printf("%c", 186);
	gotoxy(vetor[1], i);
	printf("%c", 186);
	gotoxy(vetor[2], i);
	printf("%c", 186);
	gotoxy(vetor[3], i);
	printf("%c", 186); //borda dir

	aux = strlen("Palavra")/2;
	gotoxy((ci[0] + vetor[0])/2 -aux, i);
	printf("PALAVRA");

	aux = strlen("Simbolo")/2;
	gotoxy((vetor[0] + vetor[1])/2 -aux, i);
	printf("SIMBOLO");

	aux = strlen("Codigo")/2;
	gotoxy((vetor[1] + vetor[2])/2 -aux, i);
	printf("CODIGO");

	if(vetor[2] != vetor[3]){
		aux = strlen("Simbolo")/2;
		gotoxy((vetor[0] + vetor[1])/2 -aux, i);
		printf("SIMBOLO");
	}

	i++

	gotoxy(ci, i);
	printf("%c", 204); //div esq

	for(j = ci + 1; j < vetor[3]; j++){
		gotoxy(j,i);
		if(j == vetor[0] || j == vetor[1] || j == vetor[2] || j == vetor[3])
			printf("%c", 206); //div col
		else
			printf("%c", 206); // linha hor


	}

	gotoxy(vet[3], i);
	printf("%c", 185);

	while(tab != NULL){
		i++;
		gotoxy(ci, i);
		printf("%c", 186); //borda esq
		gotoxy(vetor[0], i);
		printf("%c", 186); //divisoria
		gotoxy(vetor[1], i);
		printf("%c", 186);
		gotoxy(vetor[2], i);
		printf("%c", 186);
		gotoxy(vetor[3], i); //borda dir
		printf("%c", 186);

		if(tab->reg.palavra[0] == ''){
			aux = strlen("'Espaco'")/2;
			gotoxy((i+vetor[0])/2 -aux, i);
			printf("'Espaco'");

		}
		else{
			aux = strlen(tab->reg.palavra)/2;
			gotoxy((ci+vetor[0])/2 -aux, i);
			printf("%s", tab->reg.palavra);
		}

		gotoxy((vetor[0] + vetor[1])/2 -1, i);
		printf("%d", tab->reg.simb);
		aux = strlen(tab->reg.cod);
		gotoxy((vetor[1] + vetor[2])/2 -aux, i);
		printf("%s", tab->reg.cod);

		if(vetor[2] != vetor[3]){
			gotoxy((vetor[2] + vetor[3])/2 -1, i);
			printf("%d", tab->freq);
		}

		i++;
		gotoxy(ci, i);
		printf("%c", 204);

		for (j = ci + 1; j < vetor[3]; j++) {
            gotoxy(j, i);
            if (j == vetor[0] || j == vetor[1] || j == vetor[2] || j == vetor[3])
                printf("%c", 206); // Divisões de colunas
            else
                printf("%c", 205); // Li horizontal
        }

        gotoxy(vetor[3], i);
        printf("%c", 185); // Div dir

        // Próximo elemento da pilha
        t = t->prox; 
	}

	// Base da caixa
    gotoxy(ci, i);
    printf("%c", 200); // Canto inferior esquerdo

    for (j = ci + 1; j < vetor[3]; j++) {
        gotoxy(j, i);
        if (j == vetor[0] || j == vetor[1] || j == vetor[2] || j == vetor[3])
            printf("%c", 202); // Div de colunas
        else
            printf("%c", 205); // Li horizontal
    }

    gotoxy(vetor[3], i);
    printf("%c", 188); // Canto inferior direito
}

*/
//
// MUITO TRABALHO ARRUMAR DAI EU FIZ NO MEU DIRETO ALI 
 
/*
void inserirTabelaOrdenado(Tabela **tab, Registro reg){
	Tabela *aux, *ant, *nova;
	nova = (Tabela*)malloc(sizeof(Tabela));
	nova -> prox = NULL;
	nova -> reg = reg;
	if(*tab==NULL)
		*tab = nova;
	else{
		if(tab.freq>(*tab)->reg.freq){
			nova->prox = *tab;
			*tab = nova;
		}
		else{
			ant = aux = *tab;
			while(aux!=NULL && reg.freq<=aux->reg.freq){
				ant =aux;
				aux = aux->prox;
			}
			ant->prox = nova;
			nova->prox = aux;
		}
	}
}
*/

// Busca uma entrada na tabela pelo símbolo.
/*
char BuscarSimbolo(Tabela *tab,int simb,Tabela **aux){
	*aux=tab;
	while(*aux!=NULL && (*aux)->reg.simb!=simb)
		*aux = (*aux)->prox;
	if(*aux!=NULL)
		return 1;
	return 0;
}

void excluirTab(Tabela **tab){
	Tabela *aux;
	while(*tab!=NULL){
		aux = *tab;
		*tab = aux->prox;
		free (aux);
	}
}
*/

//FALTA exibir tabela
