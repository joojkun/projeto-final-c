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

void titulo_Menu(void);
void titulo_Menu_Modo(void);
void titulo_Menu_Figura(void);
void selecao_Menu_Modo(int *modo, int *continua);
void selecao_Menu_Figura(int modo, char *figura);
void aviso_Erro(int tipoErro);
void fim_de_Jogo(void);
int main(void) 
{
  int modo, continua=1;
  char figura[2];
  while(continua==1)
  {
    modo=0;
    figura[0]=0;
    //system("cls") para windows
    system("clear");
    selecao_Menu_Modo(&modo, &continua);
    if(continua==0)
    {
      fim_de_Jogo();
      continue;
    }
    selecao_Menu_Figura(modo, figura);
  }
  //system("cls") para windows
  system("clear");
  return 0;
}

void titulo_Menu(void)
{
  printf("******************************************\n");
  printf("               JOGO DA VIDA\n");
  printf("******************************************\n\n\n\n");
  return;
}

void titulo_Menu_Modo(void)
{
  printf("Modos de jogo:\n");
  printf("------------------------------------------\n\n");
  return;
}

void titulo_Menu_Modo_Opcao(void)
{
  for(int a=1; a<=4; a++)
  {
    printf("%d) MODO.\n\n", a);
  }
  return;
}

void titulo_Menu_Figura()
{
  printf("Figuras:\n");
  printf("------------------------------------------\n\n");
  return;
}

void titulo_Menu_Figura_Opcao(int modo)
{
  //Deixarei em comentário até todas as opções estarem confirmadas
  for(int a=1; a<=4; a++)
  {
    printf("%c) FIGURA.\n\n", a+64);
  }
  return;
}

void selecao_Menu_Modo(int *modo, int *continua)
{
  int tipoErro=0;
  while(*modo<1 || *modo>4)
  {
    titulo_Menu();
    titulo_Menu_Modo();
    titulo_Menu_Modo_Opcao();
    printf("Escolha o modo de jogo: ");
    scanf("%d", modo);
    if(*modo<1 || *modo>4)
    {
      tipoErro=1;
      aviso_Erro(tipoErro);
    }
    else if (*modo==4)
      *continua=0;
  }
  //system("cls") para windows
  system("clear");
  return;
}

void selecao_Menu_Figura(int modo, char *figura)
{
  int tipoErro=0;
  while(figura[0]<'A' || figura[0]>'C')
  {
    titulo_Menu();
    titulo_Menu_Figura();
    titulo_Menu_Figura_Opcao(modo);
    printf("Escolha a figura inicial para o jogo: ");
    scanf("%s", figura);
    figura[1]='\0';
    if(figura[0]>='a' && figura[0]<='c')
      figura[0]-=32;
    if(figura[0]<'A' || figura[0]>'C')
    {
      tipoErro=2;
      aviso_Erro(tipoErro);
    }
  }
  //system("cls") para windows
  system("clear");
  return;
}

void aviso_Erro(int tipoErro)
{
  //system("cls") para windows
  system("clear");
  titulo_Menu();
  if(tipoErro==1)
  {
    titulo_Menu_Modo();
    printf("Digite o número novamente!!!\nO número precisa estar presente no menu de seleção!\n");
  }
  else if(tipoErro==2)
  {
    titulo_Menu_Figura();
    printf("Digite a letra novamente!!!\nA letra precisa estar presente no menu de seleção!\n");
  }
  sleep(3);
  //system("cls") para windows
  system("clear");
  return;
}

void fim_de_Jogo(void)
{
  printf("******************************************\n");
  printf("               FIM DE JOGO\n");
  printf("******************************************\n");
  sleep(3);
  return;
}