/****************
LAED1 - Problema da Mochila
Alunos(as): Alanis Viana Castro e Matheus Freire Henrique Fonseca
Data: 05/07/2021
****************/

#include <stdio.h>

int analisaMochilas(FILE *arq)
{
	int numeroMochilas, numeroArtigos, pesoMaximo = 0;

	//criando um vetor para armazenar a capacidade das mochilas
    fscanf(arq, "%d", &numeroMochilas);
	int capacidadeMochilas[numeroMochilas];
    for(int i = 0; i < numeroMochilas; i++)
	{
		fscanf(arq, "%d", &capacidadeMochilas[i]);
		pesoMaximo += capacidadeMochilas[i];
	}

	//criando uma matriz para armazenar o peso e os valores dos artigos
    fscanf(arq, "%d", &numeroArtigos);
	int matrizArtigos[numeroArtigos][2];
    for(int i = 0; i < numeroArtigos; i++)
	{
		for (int j=0; j<2; j++)
		{
			fscanf(arq, "%d", &matrizArtigos[i][j]);
		}
	}

	//criando uma matriz para guardar quais itens estão em cada mochila
	int artigosEscolhidos[numeroArtigos][numeroMochilas];
    for(int i = 0; i < numeroArtigos; i++)
	{
		for (int j=0; j<numeroMochilas; j++)
		{
			fscanf(arq, "%d", &artigosEscolhidos[i][j]);
		}
	}

	//criando e inicializando um vetor para armazenar quanto de peso há em cada mochila
	int pesoMochilas[numeroMochilas];
	for (int i = 0; i<numeroMochilas; i++)
	{
		pesoMochilas[i] = 0;
	}

	//testando viabilidade e já guardando quanto de peso há em cada mochila
	int viavel = 0;
	for (int i = 0; (i<numeroMochilas) && (viavel == 0); i++)
	{
		for (int j = 0; j<numeroArtigos; j++)
		{
			if (artigosEscolhidos[j][i] == 1)
			{
				pesoMochilas[i] += matrizArtigos[j][0];
			}
		}
		if (pesoMochilas[i] > capacidadeMochilas[i])
			viavel ++;
	}
	if (viavel != 0)
	{
		printf("Solucao inviavel.\n");
		return 0;
	}

	//ordenando a matriz dos artigos pelo de maior relação valor/peso e também a que guarda quais itens estão em cada mochila
	float relacaoPesoValor, novaRelacao;
	int auxiliar = 0;
	for (int i = 1; i<numeroArtigos; i++)
	{
		relacaoPesoValor = ((matrizArtigos[i-1][1])/(matrizArtigos[i-1][0]));
		for (int j = i; j<numeroArtigos; j++)
		{
			novaRelacao = ((matrizArtigos[j][1])/(matrizArtigos[j][0]));

			if (novaRelacao > relacaoPesoValor)
			{
				for (int b = 0; b<numeroMochilas; b++)
				{
					auxiliar = artigosEscolhidos[j][b];
					artigosEscolhidos[j][b] = artigosEscolhidos[i-1][b];
					artigosEscolhidos[i-1][b] = auxiliar;
				}

				for (int b = 0; b<2; b++)
				{
					auxiliar = matrizArtigos[j][b];
					matrizArtigos[j][b] = matrizArtigos[i-1][b];
					matrizArtigos[i-1][b] = auxiliar;
				}
			}
		}
	}
	int pesoRestante = pesoMaximo;
	//procura o melhor caso
	int melhores[numeroArtigos];
	for (int i = 0; i<numeroArtigos; i++)
	{
		if (matrizArtigos[i][0] <= pesoRestante)
		{
			pesoRestante -= matrizArtigos[i][0];
			melhores[i] = 1;
		}
		else
			melhores[i] = 0;

			//printf("primeiro %d \n",melhores[i]);
	}

	//compara o melhor caso com o dado
	int checaDesigual = 0;
	for (int i = 0; i<numeroArtigos; i++)
	{   //printf("checa %d ",checaDesigual);
	    //printf("melhores %d ",melhores[i]);
	  //  printf("escolhidos %d ",artigosEscolhidos[i][0]);
	//     printf("escolhidos2  %d \n",artigosEscolhidos[i][1]);
	    if(numeroMochilas==1){
            if ((melhores[i] == artigosEscolhidos[i][0])){}
            else{
                    checaDesigual++;

            }
	    }else{
		if ((melhores[i] == artigosEscolhidos[i][0]) || (melhores[i] == artigosEscolhidos[i][1])){}
		else{
			checaDesigual++;
        }
	    }
	}

	if (checaDesigual == 0)
		printf("Solucao otima.\n");
    else{
        int somaescolhidos = 0, somaotima = 0;
        for (int i = 0; i<numeroArtigos; i++)
        {
	    if (melhores[i] == 1){
            somaotima += matrizArtigos [i][1];
	    }
        }
        for (int i = 0; i<numeroArtigos; i++)
        {
        if(numeroMochilas==1){
            if (artigosEscolhidos[i][0] == 1){
            somaescolhidos += matrizArtigos [i][1];
            }
            }else{
        if((artigosEscolhidos[i][0] == 1) || (artigosEscolhidos[i][1] == 1)){
            somaescolhidos += matrizArtigos [i][1];
	    }
	    }
        }
        if(somaescolhidos>somaotima){
            printf("Solucao otima.\n");
        }
        else{
            printf("Solucao viavel mas nao otima.\n");
        }


	/*else
	{
		checaDesigual = 0;
		auxiliar = 0;
			for (int i = 1; i<numeroArtigos; i++)
			{
				int maior =  matrizArtigos[i-1][1];
				for (int j = i; j<numeroArtigos; j++)
				{
					if (matrizArtigos[j][1] > maior)
					{
						for (int b = 0; b<numeroMochilas; b++)
						{
							auxiliar = artigosEscolhidos[j][b];
							artigosEscolhidos[j][b] = artigosEscolhidos[i-1][b];
							artigosEscolhidos[i-1][b] = auxiliar;
						}

						for (int b = 0; b<2; b++)
						{
							auxiliar = matrizArtigos[j][b];
							matrizArtigos[j][b] = matrizArtigos[i-1][b];
							matrizArtigos[i-1][b] = auxiliar;
						}
					}
				}
			}

			//procura o melhor caso
			int melhores[numeroArtigos];
			for (int i = 0; i<numeroArtigos; i++)
			{
				if (matrizArtigos[i][0] <= pesoMaximo)
				{
					pesoMaximo -= matrizArtigos[i][0];
					melhores[i] = 1;
				}
				else
					melhores[i] = 0;

						printf("segundo %d \n",melhores[i]);
			}

			//compara o melhor caso com o dado
			int checaDesigual = 0;
			for (int i = 0; i<numeroArtigos; i++)
			{
				if ((melhores[i] == artigosEscolhidos[i][0]) || (melhores[i] == artigosEscolhidos[i][1])){}
				else
					checaDesigual++;
			}
			if (checaDesigual == 0)
		printf("Solucao otima.\n");
	else
		printf("Solucao viavel mas nao otima.\n");
	}*/
}
return 1;
}

int main()
{
	FILE *arquivo;
	char arq[15];
    printf("Digite o nome do arquivo: ");
    scanf("%s", arq);
    arquivo = fopen(arq, "r");
	if(arquivo != NULL)
	{
        analisaMochilas(arquivo);
	}
	else
	{
        printf("O arquivo não foi encontrado\n");
	}
    fclose(arquivo);
	return 0;
}
