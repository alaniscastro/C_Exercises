#include <stdio.h>
#include <string.h>

void permuta(char *mensagem, int letras)
{
	char letra;
	int j, cont = 0;
	int jpar = letras-2;
	int jimpar = letras-1;

	for (int i = 0; i < (letras/2);)
	{
		if (i%2==0)
		{
			j = jpar;
			jpar -= 4;
			cont++;
		}
		else
		{
			j = jimpar;
			jimpar -= 4;
			cont++;
		}
		letra = mensagem[i];
		mensagem[i] = mensagem[j];
		mensagem[j] = letra;
		if (cont == 2)
		{
			i += 3;
			cont = 0; 
		}
		else
			i++;
	}
}

void reflete(char *mensagem, int letras)
{
	char letra;
	for (int i = 0; i < letras - 1; i+=2)
	{
		letra = mensagem[i];
		mensagem[i] = mensagem[i + 1];
		mensagem[i + 1] = letra;
	}
}

void cifra(char *mensagem, int letras)
{
	for (int i = 0; i < letras; i++)
	{
		if (mensagem[i] == '#')
		{
			if (i==(letras - 1))
			{
				mensagem[i]='\0';
			}
			mensagem[i] = ' ';
		}
		else
		{
			if (((mensagem[i]>=65) && (mensagem[i]<=69)) || ((mensagem[i]>=97) && (mensagem[i]<=101)))
			{
				mensagem[i] = mensagem[i] + 26;
			}
			mensagem[i] = mensagem[i] - 5;
		}
	}
}

int main()
{
	char arq[15];
	int letras = 0;
	char mensagem[1000];

	printf("Digite o nome do arquivo: ");
	scanf("%s", arq);
	FILE *arquivo = fopen(arq, "r");

	printf("\n--------------------\n");
	printf("Mensagem codificada: ");
	printf("\n--------------------\n");

	fscanf(arquivo, "%s", mensagem);
	printf("%s", mensagem);
	letras = strlen(mensagem);

	permuta(mensagem, letras);
	reflete(mensagem, letras);
	cifra(mensagem, letras);

	printf("\n\n----------------------\n");
	printf("Mensagem decodificada: ");
	printf("\n----------------------\n");

	printf("%s", mensagem);
	fclose(arquivo);
	return 0;
}

