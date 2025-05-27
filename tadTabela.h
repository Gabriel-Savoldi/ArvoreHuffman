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
	int simbolo;
	char palavra[30];
	union byte cod;
};
typedef struct registro Registro;


struct tabela{
	Registro *reg;
	int freq;
	struct tabela *prox;
};
typedef struct tabela Tabela;


void init(Tabela **T)
{
	*T=NULL;
}

char isEmpty(Tabela *T)
{
	return T == NULL;
}






