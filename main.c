#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "matriz.h"
#include "bag.h"
#include "scrabble.h"

int main(){
	int jog;
	int pass = 0;
	int n_letras;
	int n_jogadores;
	int i;

	char vetor_jogada[7];
	
	tabela_t *tab = init_table();
	char **matriz = cria_matriz(15, 15);
	
	bag_t *bag = cria_bag();
	preenche_bag(bag);
	randomize_bag(bag);
	
	printf("Digite o numero de jogadores (2 a 4): ");
	scanf("%d", &n_jogadores);
	jogador_t jogador[n_jogadores];
	
	for(i = 0; i < n_jogadores; i++){
		jogador[i].pontos = 0;
		jogador[i].n_jogador = i;
		cria_mao(jogador[i].mao);
		preenche_mao(bag, jogador[i].mao);
	}
	
	i = 0;
	while(!is_empty(bag) && pass != n_jogadores*2){
		
		if(i >= n_jogadores) i = 0;
		clear_screen();
		imprime_matriz(matriz);
		printf("Jogador %d: ", i+1);
		imprime_mao(jogador[i].mao);
		printf("PONTUAÇÃO: %d\t\t PEÇAS NA BAG: %d\n", jogador[i].pontos, bag->num_elementos);
		
		jog = jogada();
		if(jog == 1){
			colocar_letras(jogador[i].mao, &jogador[i].pontos, matriz, tab, bag);
			pass = 0;
		}
		else if(jog == 2){
			int pecas;
			printf("Digite o numero de peças que deseja trocar (1 ou 7): ");
			scanf("%d", &pecas);
			if(pecas == 7){ 
				trocar_mao(bag, jogador[i].mao);
			}
			else if(pecas == 1){ 
				trocar_peca(bag, jogador[i].mao);
			}
			printf("Jogador %d: ", i+1);
			imprime_mao(jogador[i].mao);
			pass = 0;
		}
		else if(jog == 3){
			printf("Jogador %d passou a vez!\n", i+1);
			pass++;
		}
		else if(jog == 4){
			god_mode(matriz);
		}
		printf("\n");
		i++;
	}
	for(i = 0; i < n_jogadores; i++){
		jogador[i].pontos -= conta_pontos(jogador[i].mao, 7);
	}
	imprime_placar_ordenado(jogador, n_jogadores);

	return 0;
}

/* 
criar o vetor de pontuação por letra especificado no pdf
mudar parametros da funçao para receber um ponteiro para o int que guarda a pontuação
se get retornar 1 (a palavra existe) fazer o calculo dos pontos usando o vetor_jogada (que contém as letras usadas);

//FIM DE JOGO: while(!is_empty(bag) && pass != 4);
//3 tipos de jogadas -> colocar letras (verificar se a letra é valida -> hash)
//					 -> trocar mão (colocar as peças no saco -> randomizar saco -> comprar 7 pedras)
//					 -> passar (pass_total++, se o outro jogador nao passar -> pass_total = 0)

*/


/*CRIAR MATRIZ COM POSICOES ESPECIAS, VARRER AS POSICOES DA MATRIZ (SE I FIXO) VARRER DE J_I ATE J_F, (SE J FIXO) VARRER DE I_I ATE I_F
SE PASSAR EM CIMA DE UMA POSICAO ESPECIAL FAZER AS CONTAS*/