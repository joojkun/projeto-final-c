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
#include "game_config.h"
#include "evolui_geracoes.h"
#ifdef _WIN32
    #include <Windows.h>
    #define LIMPA "cls"
#else
    #include <unistd.h>
    #define LIMPA "clear"
#endif

int main(void)
{
	// Configurações da matriz de jogo
	MatrizConfig matCfg;
	matCfg.modo = 0; // Modo de início
	matCfg.figura= '@'; //Figura de início
	matCfg.linhas = 15; // Tamanho padrão matriz
	matCfg.colunas = 15;  // Tamanho padrão matriz
	matCfg.numGeracoes = 10; // Numero de gerações padrão
	matCfg.vivo = '0', matCfg.morto = '.'; // Caracteres vivo e morto padrão
	
	/* Enquanto o usuário não selecionar a opção de terminar o jogo (7 numérico),
	 o menu inicial será mostrado após cada simulação */
	while (matCfg.modo != 7)
	{
		srand(time(NULL));
		int resposta = 0, respostaInserir = 0, respostaInv = 0;
		matCfg.modo = 0, matCfg.modoInv = 0;
		matCfg.figura = '@', matCfg.figuraInv = '@';
		system(LIMPA);
		// Imprime menu
		selecao_Menu_Modo(&matCfg.modo);

		// Descrição dos modos de jogo
	  if (matCfg.modo == 5)
		{
	    	descricaoModos();
	    	continue;
		}
		// Descrição das regras
	  else if (matCfg.modo == 6)
		{
	    	descricaoRegras();
	    	continue;
		}
		// Encerra o jogo
	  else if (matCfg.modo == 7)
		{
	    	fim_de_Jogo();
	    	continue;
		}
		// Caso o usuário seleciona uma opção para iniciar o jogo
		else
		{
			// Caso o usuário que iniciar a matriz a partir de um arquivo .csv
			if (matCfg.modo == 4) 
			{
				matCfg.modo = 4;
			}
			// Caso o usuário deseje criar a matriz pelo próprio menu
			else {
				selecao_Menu_Figura(matCfg.modo, &matCfg.figura);
			}
			perguntaCustomizarInicializacao(&resposta);
			// Usuário deseja customizar jogo
			if(resposta == 1)
			{
				perguntaMudarCaracter(&matCfg.vivo, &matCfg.morto);
				perguntaTamanhoTabela(&matCfg.linhas, &matCfg.colunas);
				perguntaInicioLocalizacao(&matCfg.locX, &matCfg.locY, matCfg.linhas, matCfg.colunas);
				perguntaNumeroGeracoes(&matCfg.numGeracoes);
			}
			// Caso o usuário não deseje customizar onde a figura será colocada, ela será colocada em uma posição aleatória
			else
			{
				matCfg.locX = matCfg.linhas / 2;
				matCfg.locY = matCfg.colunas / 2;
			}
			perguntaInserirInvasor(&respostaInserir);
			// Usuário deseja inserir invasor
			if(respostaInserir == 1)
			{
				selecao_Menu_Modo_Invasor(&matCfg.modoInv);
        if (matCfg.modoInv != 4) {
				  selecao_Menu_Figura(matCfg.modoInv, &matCfg.figuraInv);
        }
				perguntaCustomizarInicializacaoInvasor(&respostaInv);
				if(respostaInv == 1)
				{
					perguntaInicioLocalizacaoInvasor(&matCfg.locXInv, &matCfg.locY, matCfg.linhas, matCfg.colunas);
					perguntaInicioGeracaoInvasor(matCfg.numGeracoes, &matCfg.inicioInv);
				}
				else
				{
					matCfg.locXInv = (matCfg.linhas / 2) + 4;
					matCfg.locYInv = (matCfg.colunas / 2);
					matCfg.inicioInv = 1;
				}
			}
		// Tela carregamento, iniciando a simulação
	    telaCarregamento();
		}
		simulaGeracoes(matCfg, matCfg.vivo, matCfg.morto);
		sleep(2);
		telaReinicio();
	}
	system(LIMPA);
	return 0;
}