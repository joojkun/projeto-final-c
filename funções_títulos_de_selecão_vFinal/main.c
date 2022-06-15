// Projeto Final - Fundamentos de Programação
// Equipe:
// Ricardo Henrique Pires dos Reis
// Victor Gabriel Rodrigues da Silva
// Johnny Sarafim Pinto

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "desenhosFiguras.h"
#ifdef _WIN32 
    #include <Windows.h> 
    #define LIMPA "cls"
#else 
    #include <unistd.h> 
    #define LIMPA "clear"
#endif

#define LINHA 15
#define COLUNA 15
#define MORTO '.'
#define VIVO '0'
#define GERACOES 20

void titulo_Menu(void);
void titulo_Menu_Opcoes(int nm_pergunta, int nm_descricao);
void selecao_Menu_Modo(int *modo);
void selecao_Menu_Modo_Invasor(int *modo);
void selecao_Menu_Figura(int modo, char *figura, int tm_X, int tm_Y);
void perguntaCustomizarInicializacao(int *resposta);
void perguntaMudarCaracter(char *vivo, char *morto);
void perguntaTamanhoTabela(int *linha, int *coluna, int tm_X, int tm_Y);
void perguntaInicioLocalizacao(int *lcz_X, int *lcz_Y, int linha, int coluna, int tm_X, int tm_Y);
void perguntaNumeroGeracoes(int *num_geracoes);
void perguntaInserirInvasor(int *respostaInserir);
void perguntaCustomizarInicializacaoInvasor(int *respostaInv);
void perguntaInicioLocalizacaoInvasor(int *lczInv_X, int *lczInv_Y, int linha, int coluna, int tmInv_X, int tmInv_Y);
void perguntaInicioGeracaoInvasor(int num_geracoes, int *num_InvInicio);
void aviso_Erro(int tipoErro);
void telaCarregamento(void);
void descricaoModos(void);
void descricaoRegras(void);
void fim_de_Jogo(void);
int main(void) 
{
	int modo=0, modoInvasor=0, num_geracoes, num_InvInicio;
	int lcz_X, lcz_Y, lczInv_X, lczInv_Y;
	int tm_X=1, tm_Y=1, tmInv_X=1, tmInv_Y=1;
	int linha = LINHA, coluna = COLUNA;
	int resposta=0, respostaInserir=0, respostaInv=0;
	char **matriz, **invasor, figura[2], figuraInv[2];
	char vivo=VIVO, morto=MORTO;
	while (modo != 7) 
	{
		srand(time(NULL));
    	modo = 0, modoInvasor = 0;
	    figura[0] = 0;
	    system(LIMPA);
		matriz = (char**) malloc (linha*sizeof(char*));
		for (int a = 0; a < linha; a++) 
			matriz[a] = (char*) malloc (coluna*sizeof(char));
	    selecao_Menu_Modo(&modo);
	    if (modo == 5) 
		{
	    	descricaoModos();
	    	continue;
	    }
	    else if (modo == 6) 
		{
	    	descricaoRegras();
	    	continue;
	    }
	    else if (modo == 7) 
		{
	    	fim_de_Jogo();
	    	continue;
	    } 
		else
		{
			selecao_Menu_Figura(modo, figura, tm_X, tm_Y);
		    perguntaCustomizarInicializacao(&resposta);
			if(resposta==1)
			{
				perguntaMudarCaracter(&vivo, &morto);
				perguntaTamanhoTabela(&linha, &coluna, tm_X, tm_Y);
				perguntaInicioLocalizacao(&lcz_X, &lcz_Y, linha, coluna, tm_X, tm_Y);
			    perguntaNumeroGeracoes(&num_geracoes);
			}
			else
			{
				lcz_X= rand()%(linha-tm_X);
				lcz_Y= rand()&(coluna-tm_Y);
			}
			perguntaInserirInvasor(&respostaInserir);
			if(respostaInserir==1)
			{
				selecao_Menu_Modo_Invasor(&modoInvasor);
				perguntaCustomizarInicializacaoInvasor(&respostaInv);
				if(respostaInv==1)
				{
					perguntaInicioLocalizacaoInvasor(&lczInv_X, &lczInv_Y,
					linha, coluna, tmInv_X, tmInv_Y);
					perguntaInicioGeracaoInvasor(num_geracoes, &num_InvInicio);
				}
				else
				{
					lczInv_X= rand()%(linha-tmInv_X);
					lczInv_Y= rand()%(coluna-tmInv_X);
					num_InvInicio=1;
				}
				selecao_Menu_Figura(modoInvasor, figuraInv, tmInv_X, tmInv_Y);
			}
	    	telaCarregamento();
		}
	}
	system(LIMPA);
	return 0;
}



void titulo_Menu(void) 
{
	printf("*********************************************\n");
	printf("                 JOGO DA VIDA\n");
	printf("*********************************************\n\n\n\n");
	return;
}



void titulo_Menu_Modo_Opcao(int inicio) 
{
	printf("1) Vida Eterna.\n\n");
	printf("2) Osciladores.\n\n");
	printf("3) Naves Espaciais.\n\n");
	printf("4) Matusalém.\n\n");
	printf("5) Descrição dos modos de jogo.\n\n");
	if(inicio==1)
	{
		printf("6) Regras do jogo.\n\n");
		printf("7) Sair do jogo.\n\n");
	}
	return;
}



void titulo_Menu_Opcoes(int pergunta, int descricao) 
{
	if (pergunta == 0) 
	{
		if (descricao == 0)
			
    	printf("Modos:\n");
    	if (descricao == 1)
    	printf("Figuras:\n");
	    if (descricao == 2) 
		{
	    	printf("Opções de jogo:\n");
	    	printf("Digite 'S' para sim ou 'N' para não.\n");
	    }
		printf("---------------------------------------------\n\n");
	} 
	else 
	{
	    printf("Opções de jogo:\n");
	    if (descricao == 0)
	      printf("Digite um único caracter do teclado.\n");
	    if (descricao == 1)
	      printf("Digite o tamanho da tabela, considerando o tamanho mínimo de 15x15.\n");
	    if (descricao == 2)
	      printf("Digite as coordernadas da tabela em X e Y, sendo as coordenadas positivas.\n");
	    if (descricao == 3)
	    	printf("Digite o número de gerações, sabendo tem que ser positivo.\n");
	   	printf("---///---///---///---///---///---///---///---\n\n");
	}
	return;
}



void selecao_Menu_Modo(int *modo) 
{
	while (*modo < 1 || *modo > 8) 
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 0);
	    titulo_Menu_Modo_Opcao(1);
	    printf("Escolha o modo de jogo: ");
	    scanf("%d", modo);
	    if (*modo < 1 || *modo > 8)
	    	aviso_Erro(1);
	}
	system(LIMPA);
	return;
}



void selecao_Menu_Figura(int modo, char *figura, int tm_X, int tm_Y)
{
	while (figura[0] < 'A' || figura[0] > 'C') 
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 1);
	    titulo_Menu_Figura_Opcao(modo);
	    printf("Escolha a figura inicial para o jogo: ");
	    scanf("%s", figura);
	    figura[1] = '\0';
		if(modo==2 || modo==3)
		{
			if (figura[0] == 'a' || figura[0] == 'b')
	    		figura[0] -= 32;
	    	if (figura[0] < 'A' || figura[0] > 'B')
	    		aviso_Erro(2);
		}
		else
		{
			if (figura[0] >= 'a' && figura[0] <= 'c')
	    		figura[0] -= 32;
	    	if (figura[0] < 'A' || figura[0] > 'C')
	    		aviso_Erro(2);
		}
	}
	system(LIMPA);
	return;
}



void selecao_Menu_Modo_Invasor(int *modo) 
{
	while (*modo < 1 || *modo > 5) 
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 0);
	    titulo_Menu_Modo_Opcao(0);
	    printf("Escolha o modo de jogo: ");
	    scanf("%d", modo);
	    if (*modo < 1 || *modo > 5)
	      aviso_Erro(1);
	}
	system(LIMPA);
	return;
}



void perguntaCustomizarInicializacao(int *resposta)
{
	char resposta_Customizar[2];
	resposta_Customizar[1] = '@';
	while (resposta_Customizar[0] != 'S' && resposta_Customizar[0] != 'N') 
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja customizar algo no jogo? ");
	    scanf("%s", resposta_Customizar);
	    resposta_Customizar[1] = '\0';
	    if (resposta_Customizar[0] == 's' || resposta_Customizar[0] == 'n')
	    	resposta_Customizar[0] -= 32;
	    if (resposta_Customizar[0] != 'S' && resposta_Customizar[0] != 'N')
	    	aviso_Erro(3);
	}
	if (resposta_Customizar[0] == 'S') 
		*resposta=1;
	system(LIMPA);
	return;
}



void perguntaMudarCaracter(char *vivo, char *morto)
{
	char resposta_Mudar_Caracter[2];
	resposta_Mudar_Caracter[1] = '@';
	system(LIMPA);
	while (resposta_Mudar_Caracter[0] != 'S' && resposta_Mudar_Caracter[0] != 'N') 
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja mudar os caracteres da tabela padrão (0 e X)? ");
	    scanf("%s", resposta_Mudar_Caracter);
	    resposta_Mudar_Caracter[1] = '\0';
	    if (resposta_Mudar_Caracter[0] == 's' || resposta_Mudar_Caracter[0] == 'n')
	    	resposta_Mudar_Caracter[0] -= 32;
	    if (resposta_Mudar_Caracter[0] != 'S' && resposta_Mudar_Caracter[0] != 'N')
	    	aviso_Erro(3);
	}
	if (resposta_Mudar_Caracter[0] == 'S') 
	{
	    system(LIMPA);
	    titulo_Menu();
	    titulo_Menu_Opcoes(1, 0);
	    printf("\nEscolha o caracter para as células mortas: ");
	    scanf(" %c", vivo);
	    printf("\n\nEscolha o caracter para as células vivas: ");
	    scanf(" %c", morto);
	}
	system(LIMPA);
	return;
}



void perguntaTamanhoTabela(int *linha, int *coluna, int tm_X, int tm_Y)
{
	char resposta_Tamanho[2];
	resposta_Tamanho[1] = '@';
	while (resposta_Tamanho[0] != 'S' && resposta_Tamanho[0] != 'N') 
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja mudar o tamanho da tabela padrão? ");
	    scanf("%s", resposta_Tamanho);
	    resposta_Tamanho[1] = '\0';
	    if (resposta_Tamanho[0] == 's' || resposta_Tamanho[0] == 'n')
	    	resposta_Tamanho[0] -= 32;
	    if (resposta_Tamanho[0] != 'S' && resposta_Tamanho[0] != 'N')
	    	aviso_Erro(3);
	}
	if (resposta_Tamanho[0] == 'S') 
	{
	    *linha = 0, *coluna = 0;
	    system(LIMPA);
	    while (*linha < 9 || *coluna < 9) 
		{
	    	titulo_Menu();
	    	titulo_Menu_Opcoes(1, 1);
	    	printf("Escolha o comprimento da linha e da coluna (O mínimo é 9x9): ");
	    	scanf("%d %d", linha, coluna);
	    	if (*linha < 9 && *coluna < 9)
	        	aviso_Erro(4);
	    }
	}
	system(LIMPA);
	return;
}



void perguntaInicioLocalizacao(int *lcz_X, int *lcz_Y, int linha, int coluna, int tm_X, int tm_Y)
{
	*lcz_X = 0, *lcz_Y = 0;
	char resposta_Localizacao[2];
	resposta_Localizacao[1] = '@';
	while (resposta_Localizacao[0] != 'S' && resposta_Localizacao[0] != 'N') 
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja escolher o local inicial da figura? ");
	    scanf("%s", resposta_Localizacao);
	    resposta_Localizacao[1] = '\0';
	    if (resposta_Localizacao[0] == 's' || resposta_Localizacao[0] == 'n')
	    	resposta_Localizacao[0] -= 32;
	    if (resposta_Localizacao[0] != 'S' && resposta_Localizacao[0] != 'N')
	    	aviso_Erro(3);
	}
	if (resposta_Localizacao[0] == 'S') 
	{
		*lcz_X = 0, *lcz_Y = 0;
	    system(LIMPA);
	    while ((*lcz_X < 1 || *lcz_X > (linha-tm_X)) || 
		(*lcz_Y < 1 || *lcz_Y > (coluna-tm_Y)))
		{
	    	titulo_Menu();
	    	titulo_Menu_Opcoes(1, 2);
	    	printf("Escolha a localização X Y (O mínimo é 1x1 e"
			" o máximo é %dx%d): ", (linha-tm_X), (coluna-tm_Y));
	    	scanf("%d %d", lcz_X, lcz_Y);
	    	if ((*lcz_X < 1 || *lcz_X > (linha-tm_X)) || 
			(*lcz_Y < 1 || *lcz_Y > (coluna-tm_Y)))
	        	aviso_Erro(5);
		}
	}
	system(LIMPA);
	return;
}



void perguntaNumeroGeracoes(int *num_geracoes)
{
	char resposta_Geracoes[2];
	resposta_Geracoes[1] = '@';
	while (resposta_Geracoes[0] != 'S' && resposta_Geracoes[0] != 'N') 
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja escolher quantas gerações serão passadas na tela? ");
	    scanf("%s", resposta_Geracoes);
	    resposta_Geracoes[1] = '\0';
	    if (resposta_Geracoes[0] == 's' || resposta_Geracoes[0] == 'n')
	    	resposta_Geracoes[0] -= 32;
	    if (resposta_Geracoes[0] != 'S' && resposta_Geracoes[0] != 'N')
	    	aviso_Erro(3);
	}
	if (resposta_Geracoes[0] == 'S') 
	{
	    int *num_geracoes = 0;
	    system(LIMPA);
	    while (*num_geracoes < 1) 
		{
		    titulo_Menu();
	    	titulo_Menu_Opcoes(1, 3);
	    	printf("Digite o número de gerações a serem rodadas (O mínimo é 1): ");
	    	scanf("%d", num_geracoes);
	    	if (*num_geracoes < 1)
		   		aviso_Erro(5);
	    }
	}
	system(LIMPA);
	return;
}



void perguntaInserirInvasor(int *respostaInserir)
{
	char resposta_Invasor[2];
	resposta_Invasor[1] = '@';
	while (resposta_Invasor[0] != 'S' && resposta_Invasor[0] != 'N') 
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja adicionar um invasor na tabela? ");
	    scanf("%s", resposta_Invasor);
	    resposta_Invasor[1] = '\0';
	    if (resposta_Invasor[0] == 's' || resposta_Invasor[0] == 'n')
	      resposta_Invasor[0] -= 32;
	    if (resposta_Invasor[0] != 'S' && resposta_Invasor[0] != 'N')
	      aviso_Erro(3);
	}
	if (resposta_Invasor[0] == 'S') 
		*respostaInserir=1;
	system(LIMPA);
	return;
}



void perguntaCustomizarInicializacaoInvasor(int *respostaInv)
{
	char resposta_Customizar[2];
	resposta_Customizar[1] = '@';
	while (resposta_Customizar[0] != 'S' && resposta_Customizar[0] != 'N') 
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja customizar algo no jogo? ");
	    scanf("%s", resposta_Customizar);
	    resposta_Customizar[1] = '\0';
	    if (resposta_Customizar[0] == 's' || resposta_Customizar[0] == 'n')
	    	resposta_Customizar[0] -= 32;
	    if (resposta_Customizar[0] != 'S' && resposta_Customizar[0] != 'N')
	    	aviso_Erro(3);
	}
	if (resposta_Customizar[0] == 'S') 
		*respostaInv=1;
	system(LIMPA);
	return;
}



void perguntaInicioLocalizacaoInvasor(int *lczInv_X, int *lczInv_Y, int linha, int coluna, 
int tmInv_X, int tmInv_Y)
{
	*lczInv_X = 0, *lczInv_Y = 0;
	char resposta_Localizacao[2];
	resposta_Localizacao[1] = '@';
	while (resposta_Localizacao[0] != 'S' && resposta_Localizacao[0] != 'N') 
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja escolher o local inicial da figura? ");
	    scanf("%s", resposta_Localizacao);
	    resposta_Localizacao[1] = '\0';
	    if (resposta_Localizacao[0] == 's' || resposta_Localizacao[0] == 'n')
	    	resposta_Localizacao[0] -= 32;
	    if (resposta_Localizacao[0] != 'S' && resposta_Localizacao[0] != 'N')
	    	aviso_Erro(3);
	}
	if (resposta_Localizacao[0] == 'S') 
	{
	    system(LIMPA);
	    while ((*lczInv_X < 1 || *lczInv_X > (linha-tmInv_X)) || 
		(*lczInv_Y < 1 || *lczInv_Y > (coluna-tmInv_Y))) 
		{
	    	titulo_Menu();
	    	titulo_Menu_Opcoes(1, 2);
	    	printf("Escolha a localização X Y (O mínimo é 1x1 e"
			" o máximo é %dx%d): ",(linha-tmInv_X), (coluna-tmInv_Y));
	    	scanf("%d %d", lczInv_X, lczInv_Y);
	    	if ((*lczInv_X < 1 || *lczInv_X > (linha-tmInv_X)) || 
			(*lczInv_Y < 1 || *lczInv_Y > (coluna-tmInv_Y))) 
	        	aviso_Erro(5);
		}
	}
	system(LIMPA);
	return;
}



void perguntaInicioGeracaoInvasor(int num_geracoes, int *num_InvInicio)
{
	char resposta_Invasor[2];
	resposta_Invasor[1] = '@';
	while (resposta_Invasor[0] != 'S' && resposta_Invasor[0] != 'N') 
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0, 2);
	    printf("Deseja inserir um momento específico para adicionar\n"
		"o invasor na tabela? ");
	    scanf("%s", resposta_Invasor);
	    resposta_Invasor[1] = '\0';
	    if (resposta_Invasor[0] == 's' || resposta_Invasor[0] == 'n')
	      resposta_Invasor[0] -= 32;
	    if (resposta_Invasor[0] != 'S' && resposta_Invasor[0] != 'N')
	      aviso_Erro(3);
	}
	if (resposta_Invasor[0] == 'S') 
	{
	    system(LIMPA);
	    (*num_InvInicio) = 0;
	    while (*num_InvInicio < 1 || *num_InvInicio > num_geracoes) 
		{
		    titulo_Menu();
	    	titulo_Menu_Opcoes(1, 3);
	    	printf("Digite o número de gerações para aparecer\n"
			"o invasor (O mínimo é 1 e o máximo é %d): ", num_geracoes);
	    	scanf("%d", &(*num_InvInicio));
	    	if (*num_InvInicio < 1 || *num_InvInicio > num_geracoes)
		   		aviso_Erro(5);
	    }
	}
	system(LIMPA);
	return;
}



void aviso_Erro(int tipoErro) 
{
	system(LIMPA);
	titulo_Menu();
	if (tipoErro == 1) 
	{
    	titulo_Menu_Opcoes(0, 0);
    	printf("Digite o número novamente!!!\n"
			"O número precisa estar presente no menu de seleção!\n");
	} 
	else if (tipoErro == 2) 
	{
    	titulo_Menu_Opcoes(0, 1);
    	printf("Digite a letra novamente!!!\n"
			"A letra precisa estar presente no menu de seleção!\n");
	} 
	else if (tipoErro == 3) 
	{
    	titulo_Menu_Opcoes(0, 2);
    	printf("Digite a letra novamente!!!\n"
			"A letra precisa ser 'S' para sim ou 'N' para não!\n");
	} 
	else if (tipoErro == 4) 
	{
    	titulo_Menu_Opcoes(1, 1);
    	printf("Digite o tamanho novamente!!!\n"
			"O tamanho precisa estar entre os requisitos!\n");
	} 
	else if (tipoErro == 5) 
	{
    	titulo_Menu_Opcoes(1, 2);
    	printf("Digite o número novamente!!!\n"
			"O número precisa estar entre os requisitos!\n");
	}
  sleep(3);
  system(LIMPA);
  return;
}



void telaCarregamento(void) 
{
	int tempo = 0;
	system(LIMPA);
	for (int i = 0; i < 3; i++) 
	{
	    titulo_Menu();
	    printf("Preparando jogo\nCarregando.\n");
	    sleep(1);
	    system(LIMPA);
	    titulo_Menu();
	    printf("Preparando jogo\nCarregando..\n");
	    sleep(1);
	    system(LIMPA);
	    titulo_Menu();
	    printf("Preparando jogo\nCarregando...\n");
	    sleep(1);
	    system(LIMPA);
	}
}



void descricaoModos(void) 
{
	char continuar = 0;
	titulo_Menu();
	printf("Descrição dos modos de jogo:\n");
	printf("---------------------------------------------\n\n");
	printf("1°) Vida Eterna - Formações que não se alteram\n"
		"em gerações subsequentes a não ser que sejam\n"
		"perturbadas por outras células.\n\n");
	printf("2°) Osciladores - Formações periódicas com\n"
		"comportamento previsível.\n\n");
	printf("3°) Naves Espaciais - Formações que deslizam uma\n"
		"posição na diagonal a cada nova geração.\n\n");
	printf("4°) Matusalém - Formações que requerem um\n"
		"número grande de gerações para estabilizarem.\n\n");
	printf("Digite qualquer tecla para continuar:\n");
	scanf(" %c", &continuar);
	return;
}



void descricaoRegras(void) 
{
	char continuar = 0;
	titulo_Menu();
	printf("Regras de jogo:\n");
	printf("---------------------------------------------\n\n");
	printf("1° - Qualquer célula viva com menos de dois vizinhos\n"
	"vivos morre de solidão.\n\n");
	printf("2° - Qualquer célula viva com mais de três vizinhos\nvivos morre de "
    "superpopulação.\n\n");
	printf("3° - Qualquer célula com exatamente três vizinhos\n"
	"vivos se torna uma célula viva.\n\n");
	printf("4° - Qualquer célula com dois vizinhos vivos\n"
	"continua no mesmo estado para a próxima geração.\n\n");
	printf("Células vivas: %c\nCélulas mortas: %c\n\n\n", VIVO, MORTO);
	desenhoExemplo();
	printf("Digite qualquer tecla para continuar:\n");
	scanf(" %c", &continuar);
	return;
}



void fim_de_Jogo(void) 
{
	printf("*********************************************\n");
	printf("                  FIM DE JOGO\n");
	printf("*********************************************\n");
	sleep(3);
	return;
}