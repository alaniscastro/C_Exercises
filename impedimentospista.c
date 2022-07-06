/*LAED1 - Projeto (Parte II) - Detecção de impedimentos na pista

Alunos(as): Alanis Viana Castro e Matheus Freire Henrique Fonseca

Data: 12/08/2021*/

#include <stdio.h>
#include <stdlib.h>
#define INICIOARRANJO   1
#define MAXTAM          1000

//funcoes Ziviani
typedef int TipoChave;
typedef int TipoApontador;
typedef int TipoResultado;

typedef struct {
	TipoChave Chave;
	TipoResultado Resultado;	
} TipoItem;

typedef struct {
	TipoItem Item[MAXTAM];
	TipoApontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista) //torna a lista vazia
{ 
	Lista -> Primeiro = INICIOARRANJO;
	Lista -> Ultimo = Lista -> Primeiro;
}

int Vazia(TipoLista Lista) //retorna se a lista está ou não vazia
{
	return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista) //insere um item na lista
{ 
	if (Lista -> Ultimo > MAXTAM)
		printf("Lista esta cheia\n");
	else 
	{ 
		Lista -> Item[Lista -> Ultimo - 1] = x;
        Lista -> Ultimo++;
	}
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item) //retira um item da lista
{
	int Aux;
	if (Vazia(*Lista) || p >= Lista -> Ultimo) 
	{ 
		printf(" Erro!\nPosicao nao existe\n");
		return;
	}
	*Item = Lista -> Item[p - 1];
	Lista -> Ultimo--;
	for (Aux = p; Aux < Lista -> Ultimo; Aux++)
    	Lista -> Item[Aux - 1] = Lista -> Item[Aux];
}

void Imprime(TipoLista Lista) //imprime toda a lista
{ 
	int Aux;
	for (Aux = Lista.Primeiro - 1; Aux <= (Lista.Ultimo - 2); Aux++)
	    printf("%d: %d\n", Lista.Item[Aux].Chave, Lista.Item[Aux].Resultado);
}
//fim das funções do Ziviani

void checaImpedimento (TipoLista Lista) //checa se há impedimento da pista
{ 
	int aux;
	for (aux = Lista.Primeiro - 1; aux <= (Lista.Ultimo - 2); aux++)
	{
		if (Lista.Item[aux].Resultado == 2)
		{
			printf("Resultado: Pista com impedimento.\n");
			return;
		}
	}	    
	printf("Resultado: Pista sem impedimento.\n");
}


int analisaSegmento(FILE *arq)
{
	int qtdElementos, colunasMatriz = 1;
	fscanf(arq, "%d", &qtdElementos);
    int matrizResposta[2][qtdElementos];

	int vetor[qtdElementos];
	fscanf(arq, "%d", &vetor[0]);
	matrizResposta[1][0] = vetor[0];
	int vetorOrdenado[qtdElementos];
	vetorOrdenado[0] = vetor[0];

	for (int i = 1, j = 0; i < qtdElementos; i++)
	{
		fscanf(arq, "%d", &vetor[i]);
		if (vetor[i] != vetor[i-1])
		{
			colunasMatriz++;
			j++;
			matrizResposta[1][j] = vetor[i];
			vetorOrdenado[j] = vetor[i];
		}
	}

	//tirando elemenentos repetidos do vetor ordenado
	int aux = colunasMatriz;
	for(int i = 0; i < aux; i++)
    {
        for(int j = i + 1; j < aux;)
        {
            if(vetorOrdenado[j] == vetorOrdenado[i])
            {
                for(int k = j; k < aux; k++ )
				{
                    vetorOrdenado[k] = vetorOrdenado[k + 1];
				}
                aux--;
            }
            else
            {
                j++;
            }
		}
    }
	
	//ordenando o vetor ordenado
	int aux2;
	for (int i = 0; i < aux; i++)
	{
    	for(int j = i + 1; j < aux; j++)
        {
            if (vetorOrdenado[i] > vetorOrdenado[j])
            {
                aux2 = vetorOrdenado[i];
                vetorOrdenado[i] = vetorOrdenado[j];
                vetorOrdenado[j] = aux2;
            }
        }
	}

	for (int i = 0; i< colunasMatriz; i++)
	{
		for (int j = 0; j < aux; j++)
		{
			if (matrizResposta[1][i] == vetorOrdenado[j])
			{
				matrizResposta[0][i] = j + 1;
			}
		}
	}

	int vetorbuscado[5]={1,3,2,3,1};

	//compara os vetores
	int i = 0, j = 0, sinalizador = 0;
	while(i < colunasMatriz)
	{
		if(matrizResposta[0][i]==vetorbuscado[j])
		{
		    i++;
		    j++;
		}
		else if(matrizResposta[0][i] == vetorbuscado[0])
		{
			j=1;i++;
		}
		else
		{
		    i++;
		    j=0;
	    }
		if(j==5)
		{
		    sinalizador=1;
		}
	}

	if(sinalizador == 1)
	    return 1;
	else //tentando diferenciar, usando o comparador novamente
	{
    	sinalizador=0;
    	if((matrizResposta[0][0] == matrizResposta[0][colunasMatriz-1]) && (matrizResposta[0][1] == matrizResposta[0][colunasMatriz-2]))
       		sinalizador = 1;
		else
 	       sinalizador = 0;

     if(sinalizador == 1) //pista interrompida
		return 2;
     else //padrao não reconhecido
        return 3;
   }
}

void listaResultados (FILE *arq)
{	
	TipoLista lista;
	TipoItem item;

	FLVazia(&lista);
	int linhas;
	fscanf(arq, "%d", &linhas);
	for (int i = 0; i < linhas; i++) //insere cada chave e resultado na lista
	{
		item.Chave = i + 1;
		item.Resultado = analisaSegmento(arq);	
  		Insere(item, &lista);
    }
	checaImpedimento(lista);		
}

int main()
{
	FILE *arquivo;
	char arq[15];
    printf("Digite o nome do arquivo: ");
    scanf("%s", arq);
    arquivo = fopen(arq, "r");
	//arquivo = fopen("teste.txt", "r");
	if(arquivo != NULL)
	{
        listaResultados(arquivo);
	}
	else
	{
        printf("O arquivo não foi encontrado\n");
	}
    fclose(arquivo);
	return 0;
}
