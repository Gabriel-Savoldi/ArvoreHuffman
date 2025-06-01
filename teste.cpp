#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio2.h>
#include<ctype.h>

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

union bytes{
	unsigned char num; //8 bits ou 1 byte
	struct bits bits;
};



//funciona

void colocaCodHtab()
{
	
		union bytes a;
		int i,j;
		char cod[9];
		char aux[9];
		strcpy(aux,"00000000");
		strcpy(cod,"11001");
		if(strlen(cod) < 8) //completa o cod até ficar com 8 bits
		{
			for(i=strlen(cod)-1,j=7;i>=0;i--,j--)
			{
				aux[j]=cod[i];
			}
			strcpy(cod,aux);
		}
		printf("cod: %s\n\n",cod);
			
		a.num=0;
		for(i=0,j=7;i<8 ;i++,j--) // vai andar pelo codigo(string) somando na union os bits shiftando seu valor
		{
			if(cod[i]=='1')
			a.num = a.num + (1 << j);
		}
		
		printf("%d\n",a.bits.b0);
		printf("%d\n",a.bits.b1);
		printf("%d\n",a.bits.b2);
		printf("%d\n",a.bits.b3);
		printf("%d\n",a.bits.b4);
		printf("%d\n",a.bits.b5);
		printf("%d\n",a.bits.b6);
		printf("%d\n",a.bits.b7);	
	
}

void merda(int *m)
{
	m++;
	m++;
	m++;
}


int main()
{
	union bytes a;
	
//	testecaraio(aux);
	
	/*
	a.bits.b0=1;
	a.bits.b1=0;
	a.bits.b2=0;
	a.bits.b3=0;
	a.bits.b4=0;
	a.bits.b5=0;
	a.bits.b6=0;
	a.bits.b7=0;
	
	
	
	//     11001100
	
	a.num=0;
	a.num=a.num + ( 1 << 7); 
	a.num=a.num + (1 << 6);
	a.num=a.num + (1 << 3);
	a.num=a.num + (1 << 2);
	
	printf("num:\t %c\t%d\n\n",a.num,a.num);
	
	printf("%d\n",a.bits.b0);
	printf("%d\n",a.bits.b1);
	printf("%d\n",a.bits.b2);
	printf("%d\n",a.bits.b3);
	printf("%d\n",a.bits.b4);
	printf("%d\n",a.bits.b5);
	printf("%d\n",a.bits.b6);
	printf("%d\n",a.bits.b7);	
	
	printf("\n\n\n%d\n\n",strlen("00000000"));
	*/
	
	//colocaCodHtab();
	
	int m=10;
	merda(&m);
	printf("merda [%d]\n",m);
	
}
