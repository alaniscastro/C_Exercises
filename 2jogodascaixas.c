#include <stdio.h>

void analisa_caixas(FILE *arq)
{
	int nlinhas, n, k = 1, soma, soma_parcial = 0, linha = 0, coluna = 0;
    fscanf(arq, "%d", &nlinhas);	
	int matriz [nlinhas][nlinhas];
    for(int i = 0; i < nlinhas; i++)
	{
		for(int j = 0; j < nlinhas; j++)
		{
			if (j<k)
			{
				fscanf(arq, "%d", &n);
		    	matriz[i][j] = n;
			}

			else
	        	matriz[i][j] = 0;
		}
		k++;
	}	
	soma = matriz[0][0]; 
	int soma_acima = soma;

	for (int i=1; i<nlinhas; i++)
	{
		for (int j=0; j<nlinhas; j++)
		{
			soma_parcial += matriz [i][j];

			if ((matriz[i][j] + soma_acima) >= soma)
			{
				soma = (matriz[i][j] + soma_acima);
				linha = i;
				coluna = j;
			}
		}
		soma_acima += soma_parcial;
		soma_parcial = 0;
	}

    printf("Resposta: fileira %d, caixa %d.", linha+1, coluna+1);
}

int main()
{
	FILE *arquivo_teste;
	char arq[11];
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", arq);
    arquivo_teste = fopen(arq, "r");
	if(arquivo_teste != NULL)
	{
        analisa_caixas(arquivo_teste);
	}
	else
	{
        printf("O arquivo não foi encontrado\n");
	}
    fclose(arquivo_teste);
	return 0;
}
