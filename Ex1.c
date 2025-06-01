#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<conio2.h>

#include "tabela.h"
#include "layout.h"
#include "floresta.h"

#define TF 200

void criaFloresta(Floresta **f,Tabela *t)
 {
	initFloresta(&*f);
	while(t!=NULL)
	{
		inserirFloresta(NULL,&*f,t->reg.simb,t->freq,NULL);
		t=t->prox;
	}
 }

Tree * criaArvoreHuffman(Floresta **f)
{
	int podeInserir=0;
	Tree* dir, *esq;
	while(*f !=NULL)
	{
		esq=retiraFloresta(&*f);
		//exibirNo(esq);
		if(*f !=NULL)
		{
			dir=retiraFloresta(&*f);
			podeInserir=1;
			//exibirNo(dir);
		}
		if(podeInserir)
		inserirFloresta(esq,&*f,-1,(esq->freq + dir->freq),dir);
		
		podeInserir=0;
	}
	return esq;
}





void gravarFrase(Tabela **tab, int *simb){
	initTabela(&*tab);
    char letra, palavra[30], aux[2];
    int i=0;
    FILE *ptr = fopen("entradinha.txt", "r");
    letra = tolower(fgetc(ptr));
    while(!feof(ptr)){
    	
        if(letra == 32 || letra == 44 || letra == 46 || letra == '\0'){
        
    		aux[0] = letra;
            aux[1] = '\0';
            
            inserirTabela(&*tab, simb, aux, 0);
            if(i!=0){
                palavra[i] = '\0';
                
            	inserirTabela(&*tab, simb, palavra, 0);
       		}
            i = 0;
        }
		else
		{
			palavra[i] = letra;
			i++;
		}
        letra = tolower(fgetc(ptr)); 
    }
    if(i>3)
    {
		palavra[i-3]='\0';
    	inserirTabela(&*tab, simb, palavra, 0);
    }
    fclose(ptr);
}

void criarArqBin(Tabela *t)
{
	FILE * ptr=fopen("registro.dat","wb");
	while(t!=NULL)
	{
		fwrite(&(t->reg),sizeof(Registro),1,ptr);
		t=t->prox;
	}
	fclose(ptr);
}

void criarArqBinCodificado(Tabela *t,char frase[100])
{
	FILE * ptr=fopen("codificado.dat","wb");
	int i=0 , j=0;
	Tabela *tab;
	unsigned char au=0;
	char palavra[30],aux[2];
	aux[0]=' ';
	aux[1]='\0';
	
	while(frase[i]!= '\0')
	{
		
		if(frase[i]== ' ')
		{
			
			palavra[j]='\0';
			tab = buscaPalavra(t,palavra);
			if(tab!=NULL)
				fwrite(&tab->reg.cod.num,1,1,ptr);
			tab = buscaPalavra(t,aux);
			if(tab!=NULL)
				fwrite(&tab->reg.cod.num,1,1,ptr);
			j=0;
			
		}
		else
		{
			palavra[j]=frase[i];
		}
		
		j++;
		i++;
	}
	fclose(ptr);
}

void descobreCodHuf(Tree* arvh, Tree** achei, int simb, char codHuf[9], int pos) {
    if (arvh != NULL && *achei == NULL) {  

        if (arvh->simb == simb) {
            codHuf[pos] = '\0'; 
            *achei = arvh;       
            return;
        }
        codHuf[pos] = '0';
        descobreCodHuf(arvh->esq, achei, simb, codHuf, pos + 1);
        if (*achei == NULL) { 
            codHuf[pos] = '1';
            descobreCodHuf(arvh->dir, achei, simb, codHuf, pos + 1);
        }
    }
}

void colocaCodHtab(Tree* arvh,Tabela **t)
{
	Tabela *aux= *t;
	while(aux!=NULL)
	{
		int i,j;
		Tree *achei=NULL;
		Tabela* pos;
		char cod[9];
		char auxCod[9];
		strcpy(auxCod,"00000000");
		descobreCodHuf(arvh,&achei,aux->reg.simb,cod,0);
		if(strlen(cod) < 8)
		{
			for(i=strlen(cod)-1,j=7;i>=0;i--,j--)
			{
				auxCod[j]=cod[i];
			}
			strcpy(cod,auxCod);
		}		
		pos=buscaSimb(*t,achei->simb);
		
		pos->reg.cod.bi.b0 = cod[0]-48;
		pos->reg.cod.bi.b1 = cod[1]-48;
		pos->reg.cod.bi.b2 = cod[2]-48;
		pos->reg.cod.bi.b3 = cod[3]-48;
		pos->reg.cod.bi.b4 = cod[4]-48;
		pos->reg.cod.bi.b5 = cod[5]-48;
		pos->reg.cod.bi.b6 = cod[6]-48;
		pos->reg.cod.bi.b7 = cod[7]-48;
		
		aux = aux->prox;
	}
}

void executar(){
    char op;
    int simb=0;
    
    //cria a tabela
    Tabela *tab;
    gravarFrase(&tab,&simb);
   
    
    // cria e exibe a arvore;
    Floresta *flo;
    criaFloresta(&flo,tab);
    exibirFlo(flo);
	Tree *arvh;
    arvh = criaArvoreHuffman(&flo);
    printf("\n* * * ARVORE DE HUFFMAN * * *\n");
    exibirArvH(arvh,1);
    
    
    //usa a arvore para fazer o cod de huffman e coloca na tabela exibe tabela
    colocaCodHtab(arvh,&tab);
    exibirTabela(tab);
    
    //minha frase é "tentar e errar e aprender e viver";
    
    
    
    
    criarArqBin(tab);
    criarArqBinCodificado(tab,"tentar e errar e aprender e viver");
   
}

int main(){
    executar();
    return 0;
}
