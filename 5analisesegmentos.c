#include <stdio.h>

void analisaSegmento(FILE *arq)
{
	int qtdElementos, colunasMatriz = 1; 
    fscanf(arq, "%d", &qtdElementos);
	int matrizResposta[3][qtdElementos];
	
	for (int i = 0; i < 2; i++)
	{
		for (int b = 0; b < qtdElementos; b++)
		{
			matrizResposta[i][b] = 1;
		}
	}

	int vetor[qtdElementos];
	fscanf(arq, "%d", &vetor[0]);
	matrizResposta[2][0] = vetor[0];
	int vetorOrdenado[qtdElementos];
	vetorOrdenado[0] = vetor[0];

	for (int i = 1, j = 0; i < qtdElementos; i++)
	{
		fscanf(arq, "%d", &vetor[i]);
		if (vetor[i] != vetor[i-1])
		{
			colunasMatriz++;
			j++;
			matrizResposta[2][j] = vetor[i];
			vetorOrdenado[j] = vetor[i];
		}
		else
		{
			matrizResposta[1][j]++;
		}
	}

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
			if (matrizResposta[2][i] == vetorOrdenado[j])
			{
				matrizResposta[0][i] = j + 1;
			}		
		}
	}

	printf("Matriz:\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < colunasMatriz; j++)
		{
			printf("%d ", matrizResposta[i][j]);	
		}
		printf("\n");	
	}
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
        analisaSegmento(arquivo);
	}
	else
	{
        printf("O arquivo não foi encontrado\n");
	}
    fclose(arquivo);
	return 0;
}

