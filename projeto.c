#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int ehprimo(int x);
int mdc(int a, int b);
int RSA(long int num, long int v, long int k);
int combinacaol(long int a, long int b, int quocientes[], int resposta[]);

int main()
{
	long int p, q, n, d, e, totiente, i = 0, resposta1, publica1, publica2, privada1, privada2, privada3, aux, j = 0, teste1;
	int quocientes[100000], resposta[100000], teste2, auxd;
	char frase[5000], caract[10];

	system("clear");
	system("setterm -foreground blue ");
	system("figlet RSA ENCRYPTION");


	printf("[1] - GERAR CHAVES PUBLICA E PRIVADA\n");
	printf("[2] - CODIFICAR\n");
	printf("[3] - DECODIFICAR\n");
	system("setterm -foreground white");
	printf("\n");
	printf("RSA > ");
	scanf("%ld", &resposta1);

	if (resposta1 == 1) 
	{	
		printf("RSA > DIGITE SEUS DOIS PRIMOS: ");
		scanf("%ld%ld", &p, &q);

		if (ehprimo(p) != 1 || ehprimo(q) != 1)
		{
			printf("Voce digitou algum numero nao primo, entre com primos!\n");
			return 0;
		}
		else
		{
			n = p * q;
			totiente = (p - 1) * (q - 1);
			printf("\nφ(n) = %ld\n", totiente);
			printf("DIGITE UM VALOR PARA 'e', (1 < e < %ld)\n\n", totiente);
			printf("RSA > O MDC(%ld, e) deve ser igual a 1, ou seja, devem ser primos entre si!: ", totiente);

			for (;;)
			{
				scanf("%ld", &e);
				if (e >= totiente || e <= 1)
				{
					printf("O valor de 'e' deve ser entre 1 e %ld, digite um outro 'e': ", totiente);
				}
				else if (mdc(totiente, e) == 1)
				{
					system("clear");
					system("setterm -foreground green");
					printf("Valor de 'e' valido!\n\n");
					break;
				}
				else
				{
					printf("O mdc nao eh 1, digite um outro 'e': ");
				}

			}
			auxd = combinacaol(totiente, e, quocientes, resposta);
			if (auxd < 0)
			{
				for (;;)
				{
					auxd = auxd + totiente;
					if (auxd >= 0)
					{
						break;
					}
				}
			}
			d = auxd;

			system("setterm -foreground cyan");
			printf("Suas chaves publicas sao: %ld e %ld\n", n, e);
			printf("Suas chaves privadas sao: %ld, %ld e %ld\n", p, q, d);
		}
	}
	else if (resposta1 == 2)
	{
		printf("RSA > DIGITE AS CHAVES PUBLICAS: ");
		scanf("%ld%ld", &publica1, &publica2);

		printf("RSA > DIGITE A MENSAGEM A SER CODIFICADA: ");
		getchar();
		scanf("%[^\n]s", frase);
		system("clear");
		printf("SUA MENSAGEM CODIFICADA:\n");
		for (i = 0; i < strlen(frase); i++)
		{
			if (frase[i] != 32)
			{	
				printf("%d ", RSA(frase[i], publica2, publica1));
			}
		}
		printf("\n"); 

	}
	else if (resposta1 == 3)
	{
		printf("DIGITE OS NUMEROS PRIMOS: ");
		scanf("%ld%ld", &privada1, &privada2);
		printf("DIGITE O VALOR DE d: ");
		scanf("%ld", &privada3);
		printf("DIGITE O CODIGO A SER DESCRIPTOGRAFADO: ");
		n = privada1 * privada2;
		for (;;)
		{
			scanf("%ld", &teste1);
			if (teste1 == -9999)
			{
				break;
			}
			printf("%d", RSA(teste1, privada3, n));
		}


	}
	else
	{

	}
}

int ehprimo(int x)
{
	int i = 0, cont = 0;
	if ((x % 2 == 0 && x != 2) || x == 1)
	{
		return 0;
	}
	else
	{	

		for (i = 3; i <= sqrt(x); i++)
		{
			if (x % i == 0)
			{
				cont++;
			}
		}
		
		if (cont == 0)
		{
			return 1;
		}
		
		return 0;
	}	
}

int mdc(int a, int b)
{
	int resto;

	if (b == 0)
	{
		return a;
	}
	else
	{
		return mdc(b, a % b);
	}
}
int RSA(long int num, long int v, long int k)
{
	return (int)(pow(num, v)) % k;
}
int combinacaol(long int a, long int b, int quocientes[], int resposta[])
{
	int i = 0, aux, j, r, tam = 0;
	while (b != 0)
	{
		quocientes[i] = a / b;
		i++;
		r = a % b;
		a = b;
		b = r;
		
	}
	resposta[0] = 1;
	for (j = i-2; j >= 0; j--)
	{
		if (tam == 0)
		{
			resposta[tam+1] = quocientes[j] * resposta[tam];
			tam++;
		}
		else
		{
			resposta[tam+1] = (quocientes[j] * resposta[tam]) + (resposta[tam-1]);
			tam++;
		}
	}
	if (tam % 2 == 0)
	{
		return resposta[tam];
	}
	else
	{
		return -resposta[tam];	
	}
}