//Projeto Final - Fundamentos de Programação
//Equipe: 
//Ricardo Henrique Pires dos Reis
//Victor Gabriel Rodrigues da Silva
//Johnny Sarafim Pinto

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h> //Para Linux
//#include <windows.h> //Para Windows

#define MORTO '0'
#define VIVO 'X'

void titulo_Menu(void);
void titulo_Menu_Opcoes(int nm_pergunta, int nm_descricao);
void selecao_Menu_Modo(int *modo);
void selecao_Menu_Figura(int modo, char *figura);
void perguntaCustomizarInicializacao(int modo, char *figura);
void perguntaMudarCaracter(int modo, char *figura);
void perguntaTamanhoTabela(int modo, char *figura);
void perguntaInicioLocalizacao(int modo, char *figura);
void perguntaNumeroGeracoes(int modo, char *figura);
void aviso_Erro(int tipoErro);
void telaCarregamento(void);
void descricaoRegras(void);
void desenhoExemplo(void);
void apagaTela(void);
void fim_de_Jogo(void);
int main(void) 
{
	int modo, vd_eterna;
	int num_modos=1, num_figuras=1;
	char figura[2];
	while(modo!=6)
	{
    	modo=0;
    	vd_eterna=0;
    	figura[0]=0;
    	apagaTela();
    	selecao_Menu_Modo(&modo);
		if(modo==5)
		{
			descricaoRegras();
			continue;
		}
    	if(modo==6)
    	{
    		fim_de_Jogo();
    		continue;
    	}
    	selecao_Menu_Figura(modo, figura);
    	perguntaCustomizarInicializacao(modo, figura);
    	telaCarregamento();
	}
	apagaTela();
	return 0;
}



void titulo_Menu(void)
{
	printf("*********************************************\n");
	printf("                 JOGO DA VIDA\n");
	printf("*********************************************\n\n\n\n");
	return;
}



void titulo_Menu_Modo_Opcao(void)
{
	//Deixarei em comentário até todas as opções estarem confirmadas
	for(int a=1; a<=6; a++)
	{
		printf("%d) MODO.\n\n", a);
	}
	return;
}



void titulo_Menu_Figura_Opcao(void)
{
	//Deixarei em comentário até todas as opções estarem confirmadas
	for(int a=1; a<=3; a++)
	{
		printf("%c) FIGURA.\n\n", a+64);
	}
	return;
}



void titulo_Menu_Opcoes(int pergunta, int descricao)
{
	if(pergunta==0)
	{
		if(descricao==0)
			printf("Modos:\n");
		if(descricao==1)
			printf("Figuras:\n");
		if(descricao==2)
		{
			printf("Opções de jogo:\n");
			printf("Digite 'S' para sim ou 'N' para não\n");
		}
		printf("---------------------------------------------\n\n");
	}
	else
	{
		printf("Opções de jogo:\n");
		if(descricao==0)
			printf("Digite um único caracter do teclado\n");
		if(descricao==1)
			printf("Digite o tamanho da tabela, considerando o tamanho da figura\n");
		if(descricao==2)
			printf("Digite as coordernadas da tabela em X e Y, sendo as coordenadas positivas\n");
		if(descricao==3)
			printf("Digite o número de gerações, sabendo tem que ser positivo\n");
		printf("---///---///---///---///---///---///---///---\n\n");
	}
	return;
}



void selecao_Menu_Modo(int *modo)
{
	while(*modo<1 || *modo>6)
	{
		titulo_Menu();
	    titulo_Menu_Opcoes(0,0);
	    titulo_Menu_Modo_Opcao();
	    printf("Escolha o modo de jogo: ");
	    scanf("%d", modo);
	    if(*modo<1 || *modo>6)
	    	aviso_Erro(1);
	}
		apagaTela();
		return;
}



void selecao_Menu_Figura(int modo, char *figura)
{
	while(figura[0]<'A' || figura[0]>'C')
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0,1);
		titulo_Menu_Figura_Opcao();
	    printf("Escolha a figura inicial para o jogo: ");
	    scanf("%s", figura);
	    figura[1]='\0';
	    if(figura[0]>='a' && figura[0]<='c')
	    	figura[0]-=32;
	    if(figura[0]<'A' || figura[0]>'C')
	    	aviso_Erro(2);
	}
	apagaTela();
	return;
}



void perguntaCustomizarInicializacao(int modo, char *figura)
{
	char resposta_Customizar[2];
	resposta_Customizar[1]='@';
	while(resposta_Customizar[0]!='S' && resposta_Customizar[0]!='N')
	{
    	titulo_Menu();
    	titulo_Menu_Opcoes(0,2);
    	printf("Deseja customizar algo no jogo? ");
    	scanf("%s", resposta_Customizar);
    	resposta_Customizar[1]='\0';
    	if(resposta_Customizar[0]=='s' || resposta_Customizar[0]=='n')
    	resposta_Customizar[0]-=32;
    	if(resposta_Customizar[0]!='S' && resposta_Customizar[0]!='N')
    		aviso_Erro(3);
	}
	if(resposta_Customizar[0]=='S')
	{
		perguntaMudarCaracter(modo, figura);
    	perguntaTamanhoTabela(modo, figura);
    	perguntaInicioLocalizacao(modo, figura);
    	if(modo!=1)
	    	perguntaNumeroGeracoes(modo, figura);
	}
	apagaTela();
	return;
}



void perguntaMudarCaracter(int modo, char *figura)
{
	char resposta_Mudar_Caracter[2];
	resposta_Mudar_Caracter[1]='@';
	apagaTela();
	while(resposta_Mudar_Caracter[0]!='S' && resposta_Mudar_Caracter[0]!='N')
	{
    	titulo_Menu();
    	titulo_Menu_Opcoes(0,2);
    	printf("Deseja mudar os caracteres da tabela padrão (0 e X)? ");
    	scanf("%s", resposta_Mudar_Caracter);
		resposta_Mudar_Caracter[1]='\0';
		if(resposta_Mudar_Caracter[0]=='s' || resposta_Mudar_Caracter[0]=='n')
    	resposta_Mudar_Caracter[0]-=32;
    	if(resposta_Mudar_Caracter[0]!='S' && resposta_Mudar_Caracter[0]!='N')
    		aviso_Erro(3);
	}
	if(resposta_Mudar_Caracter[0]=='S')
	{
		char teste1 , teste2;
    	apagaTela();
    	titulo_Menu();
    	titulo_Menu_Opcoes(1,0);
    	printf("\nEscolha o caracter para as células mortas: ");
    	scanf(" %c", &teste1);
    	printf("\n\nEscolha o caracter para as células vivas: ");
    	scanf(" %c", &teste2);
	}
	apagaTela();
	return;
}



void perguntaTamanhoTabela(int modo, char *figura)
{
	char resposta_Tamanho[2];
	resposta_Tamanho[1]='@';
	while(resposta_Tamanho[0]!='S' && resposta_Tamanho[0]!='N')
	{
	    titulo_Menu();
	    titulo_Menu_Opcoes(0,2);
	    printf("Deseja mudar o tamanho da tabela padrão? ");
	    scanf("%s", resposta_Tamanho);
	    resposta_Tamanho[1]='\0';
	    if(resposta_Tamanho[0]=='s' || resposta_Tamanho[0]=='n')
	    	resposta_Tamanho[0]-=32;
	    if(resposta_Tamanho[0]!='S' && resposta_Tamanho[0]!='N')
	    	aviso_Erro(3);
	}
	if(resposta_Tamanho[0]=='S')
	{
	    int teste1=0, teste2=0;
	    apagaTela();
	    while(teste1<1)
	    {
	    	titulo_Menu();
	    	titulo_Menu_Opcoes(1,1);
	    	printf("Escolha o comprimento da linha (O mínimo é 1): ");
	    	scanf("%d", &teste1);
	    	if(teste1<1)
	    		aviso_Erro(4);
	    }
	    while(teste2<1)
	    {
	    	apagaTela();
	    	titulo_Menu();
	    	titulo_Menu_Opcoes(1,1);
	    	printf("Escolha o comprimento da coluna (O mínimo é 1): ");
	    	scanf("%d", &teste2);
	    	if(teste1<1)
	        	aviso_Erro(4);
		}
	}
	apagaTela();
	return;
}



void perguntaInicioLocalizacao(int modo, char *figura)
{
	int teste1=0, teste2=0;
	char resposta_Localizacao[2];
	resposta_Localizacao[1]='@';
	while(resposta_Localizacao[0]!='S' && resposta_Localizacao[0]!='N')
	{
    	titulo_Menu();
    	titulo_Menu_Opcoes(0,2);
    	printf("Deseja escolher o local inicial da figura? ");
    	scanf("%s", resposta_Localizacao);
    	resposta_Localizacao[1]='\0';
    	if(resposta_Localizacao[0]=='s' || resposta_Localizacao[0]=='n')
    		resposta_Localizacao[0]-=32;
    	if(resposta_Localizacao[0]!='S' && resposta_Localizacao[0]!='N')
      		aviso_Erro(3);
	}
	if(resposta_Localizacao[0]=='S')
	{
    	apagaTela();
    	while(teste1<1 || teste1>5)
    	{
    		titulo_Menu();
    		titulo_Menu_Opcoes(1,2);
    		printf("Escolha a localização X (O mínimo é 1 e o máximo é 5): ");
    		scanf("%d", &teste1);
    		if(teste1<1 || teste1>5)
			aviso_Erro(5);
    	}
    }
    while(teste2<1 || teste2>5)
    {
    	apagaTela();
    	titulo_Menu();
    	titulo_Menu_Opcoes(1,2);
    	printf("Escolha a localização Y (O mínimo é 1 e o máximo é 5): ");
    	scanf("%d", &teste2);
    	if(teste2<1 || teste2>5)
        	aviso_Erro(5);
	}
	apagaTela();
	return;
}



void perguntaNumeroGeracoes(int modo, char *figura)
{
	char resposta_Geracoes[2];
	resposta_Geracoes[1]='@';
	while(resposta_Geracoes[0]!='S' && resposta_Geracoes[0]!='N')
	{
    	titulo_Menu();
    	titulo_Menu_Opcoes(0,2);
    	printf("Deseja escolher quantas gerações serão passadas na tela? ");
    	scanf("%s", resposta_Geracoes);
    	resposta_Geracoes[1]='\0';
    	if(resposta_Geracoes[0]=='s' || resposta_Geracoes[0]=='n')
    		resposta_Geracoes[0]-=32;
		if(resposta_Geracoes[0]!='S' && resposta_Geracoes[0]!='N')
    		aviso_Erro(3);
	}
	if(resposta_Geracoes[0]=='S')
	{
    	int teste1=0;
    	apagaTela();
    	while(teste1<1)
		{
    		titulo_Menu();
    		titulo_Menu_Opcoes(1,3);;
    		printf("Digite o número de gerações a serem rodadas (O mínimo é 1): ");
    		scanf("%d", &teste1);
    		if(teste1<1)
        	aviso_Erro(5);
		}
	}
	apagaTela();
	return;
}



void aviso_Erro(int tipoErro)
{
	apagaTela();
	titulo_Menu();
	if(tipoErro==1)
	{
    	titulo_Menu_Opcoes(0,0);
    	printf("Digite o número novamente!!!\nO número precisa estar presente no menu de seleção!\n");
  	}
  	else if(tipoErro==2)
  	{
    	titulo_Menu_Opcoes(0,1);
    	printf("Digite a letra novamente!!!\nA letra precisa estar presente no menu de seleção!\n");
  	}
  	else if(tipoErro==3)
  	{
    	titulo_Menu_Opcoes(0,2);
    	printf("Digite a letra novamente!!!\nA letra precisa ser 'S' para sim ou 'N' para não!\n");
  	}
  	else if(tipoErro==4)
  	{
    	titulo_Menu_Opcoes(1,1);
    	printf("Digite o tamanho novamente!!!\nO tamanho precisa estar entre os requisitos!\n");
  	}
  	else if(tipoErro==5)
  	{
    	titulo_Menu_Opcoes(1,2);
    	printf("Digite o número novamente!!!\nO número precisa estar entre os requisitos!\n");
  	}
  	sleep(3);
  	apagaTela();
  	return;
}



void telaCarregamento (void)
{
	int tempo=0;
	apagaTela();
	for(int i=0; i<3; i++)
	{
    	titulo_Menu();
    	printf("Preparando jogo\nCarregando.\n");
    	sleep(1);
    	apagaTela();
    	titulo_Menu();
    	printf("Preparando jogo\nCarregando..\n");
    	sleep(1);
    	apagaTela();
    	titulo_Menu();
    	printf("Preparando jogo\nCarregando...\n");
    	sleep(1);
    	apagaTela();
	}
}



void descricaoRegras(void)
{
	char continuar=0;
	titulo_Menu();
	printf("Regras de jogo:\n");
	printf("---------------------------------------------\n\n");
	printf("1° - Qualquer célula viva com menos de dois vizinhos\nvivos morre de solidão.\n");
	printf("2° - Qualquer célula viva com mais de três vizinhos\nvivos morre de superpopulação.\n");
	printf("3° - Qualquer célula com exatamente três vizinhos\nvivos se torna uma célula viva.\n");
	printf("4° - Qualquer célula com dois vizinhos vivos\ncontinua no mesmo estado para a próxima geração.\n\n");
	printf("Células vivas: %c\nCélulas mortas: %c\n\n\n", VIVO, MORTO);
	desenhoExemplo();
	printf("Digite qualquer tecla para continuar:\n");
	scanf(" %c", &continuar);
	return;
}



void desenhoExemplo(void)
{
	printf("%c %c %c %c %c		%c %c %c %c %c\n%c %c %c %c %c		%c %c %c %c %c\n", MORTO, MORTO, MORTO, MORTO, VIVO, MORTO, MORTO, VIVO, VIVO, MORTO, MORTO, VIVO, VIVO, VIVO, MORTO, MORTO, VIVO, MORTO, VIVO, VIVO);
	printf("%c %c %c %c %c  -->  %c %c %c %c %c\n", MORTO, VIVO, MORTO, VIVO, MORTO, VIVO, VIVO, MORTO, VIVO, VIVO);
	printf("%c %c %c %c %c		%c %c %c %c %c\n%c %c %c %c %c		%c %c %c %c %c\n\n", VIVO, MORTO, MORTO, VIVO, MORTO, MORTO, MORTO, MORTO, VIVO, MORTO, MORTO, MORTO, VIVO, MORTO, MORTO, MORTO, MORTO, MORTO, MORTO, MORTO);	
}



void apagaTela(void)
{
	//system("cls"); //para Windows
    system("clear"); //para Linux
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