#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arvore.h"
#include "tabela.h"
#include "layout.h"

#define TF 200

char Menu(){
	int c,l;
	char op;
	do
	{
		LayoutMenu();
		gotoxy(25,3);
		printf("#  #  MENU  #  #");
		c=3;
		l=7;
		gotoxy(c,l);
		printf("[A] - Exibir tabela de palavras");
		l+=3;
		gotoxy(c,l);
		printf("[B] - Exibir arvore");
		l+=3;
		gotoxy(c,l);
		printf("[C] - Ver frase decodificada");
		l+=3;
		gotoxy(c,l);
		printf("[D] - Ver frase codificada");
		l+=3;
		gotoxy(c,l);
		printf("[E] - Exibir arvore em pe");
		l+=3;
		gotoxy(c,l);
		printf("[ESC] - Sair");
		l=27;
		gotoxy(c,l);
		printf("OPCAO: ");
		fflush(stdin);
		op=toupper(getche());
	}while(op!='A' && op!='B' && op!='C' && op!='D'  && op!='E' && op!=27 );
	return op;
}

// Lê os registros do arquivo e monta a tabela de palavras
void montarTab(Tabela *tab){
    FILE *ptr = fopen("registro.dat","rb");
    Registro reg;
    fread(&reg, sizeof(Registro), 1, ptr);
    while(!feof){
        inserirTabela(&*tab, reg.simb, reg.palavra, reg.cod);
        fread(&reg, sizeof(Registro), 1, ptr);
    }
    fclose(ptr);

}

// Constrói a árvore de Huffman a partir da tabela de códigos
void MontarArv(Tree **raiz, Tabela *tab){
    int i;
    Tree aux;
    novoNo(&*raiz);
    while(tab!=NULL){
        aux=*raiz;
        for(i=0;i<strlen(tab->reg.cod); i++){
            if(tab->reg.cod[i]=='0')
                if(aux->esq==NULL)
                    novoNo(&(aux->esq));
                aux = aux->esq;
            else{
                if(aux->dir==NULL)
                    novoNo(&(aux->dir));
                aux = aux->dir;
        
            }
        }
        aux->simbolo = tab->reg.simb;
        tab = tab-> prox;

    }
}

// Converte um byte (8 bits) em uma string binária de 8 caracteres
void pegarCodigo(char cod[],Byte b){
	cod[0]=b.bit.b7+48;
	cod[1]=b.bit.b6+48;
	cod[2]=b.bit.b5+48;
	cod[3]=b.bit.b4+48;
	cod[4]=b.bit.b3+48;
	cod[5]=b.bit.b2+48;
	cod[6]=b.bit.b1+48;
	cod[7]=b.bit.b0+48;
}

// Remove espaços em branco do final da string/frase
void remove(char frase[]){
	int i;
	for(i=strlen(frase)-1;frase[i]==' ';i--);
	frase[i+1]='\0';
}

// Lê o arquivo binário de código e decodifica a mensagem usando a árvore de Huffman
void decodificarHuffman(Tree *raiz, Tabela *tab, char  frase[TF]){
	Tree *aux;
	Tabela *tabAux;
	char codigo[TF];
	int i;
	FILE *ptr=fopen("codigo.dat","rb");
	byte Byte;
	codigo[8]='\0';
	fread(&Byte,sizeof(char),1,ptr);
	aux=raiz;
	while(!feof(ptr)){
		pegarCodigo(codigo, Byte);
		printf("%s  ",codigo);
		for(i=0;i<8;i++){
			if(codigo[i]=='0')
				aux = aux->esq;
			else
				aux = aux->dir;
			if(aux->esq == NULL && aux->dir ==NULL){
				BuscarSimbolo(tab, aux->simbolo , &tabAux);
				strcat(frase, tabAux->reg.palavra);
				aux = raiz;
			}
		}
		fread(&Byte,sizeof(char),1,ptr);
	}
	remove(frase);
	printf("\n\n%s",frase);
    fclose(ptr);
}

void executar(){
	char op,frase[TFL];
	Tabela *tab;
	Tree *raiz;
	init(&tab);
	initT(&raiz);
	montarTab(&tab);
	montarArv(&raiz,tab);
	strcpy(frase,"");
	decodificarHuffman(raiz,tab,frase);
	do{
		op=Menu();
		switch(op){
			case 'A':
				system("cls");
				exibirTabela(tab,1,1); //falta fazer
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
			case 'B':
				system("cls");
				exibirArv(raiz,-1);
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
			case 'C':
				system("cls");
				printf("A frase decodificada foi:\n %s\n ",frase);
				teste();
				exibirTabela(tab,1,4); //aqui
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
			case 'D':
				system("cls");
				teste();
				exibirTabela(tab,1,4); //aqui
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
			case 'E':
				system("cls");
				exibirEmPe(raiz,1,1);
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
		}
			
	}while(op!=27);
	excluirTab(&tab);
	excluirArv(&raiz);
}


int main(){
	executar();
	return 0;
}

