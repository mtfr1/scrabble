#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "hash.h"
#include "matriz.h"
#include "bag.h"
#include "scrabble.h"

void clear_screen(){
	system("clear");
}

void cria_mao(char *mao){
	int i;
	//char *mao = malloc(7*sizeof(char));
	for(i = 0; i < 7; i++){
		mao[i] = '*';
	}
}

void imprime_mao(char* mao){
	int i;
	for(i = 0; i < 7; i++){
		printf("%c ", mao[i]);
	}
	printf("\n");
	printf("           ");
	for(i = 0; i < 7; i++){
		printf("%d ", i);
	}
	printf("\t");
	return;
}

//funcoes essenciais
void preenche_mao(bag_t *bag, char *mao){
	int j;
	for(j = 0; j < 7; j++){
		if(!is_empty(bag) && mao[j] == '*') mao[j] = pop(bag);
	}
}
int jogada(){
	int j = 0;
	printf("\n");
	printf("Escolha sua jogada: 1. Formar uma palavra\n");
	printf("                    2. Trocar peças\n");
	printf("                    3. Passar a vez\n");
	while(j < 1 || j > 4){
		printf("Digite uma jogada:  ");
		scanf("%d", &j);
	}
	printf("\n");
	return j;
}
void trocar_mao(bag_t *bag, char *mao){
	int i;
	for(i = 0; i < 7; i++){
		if(mao[i] != '*'){ 
			push(bag, mao[i]);
			mao[i] = '*';
		}
	}
	randomize_bag(bag);
	preenche_mao(bag, mao);
}

void trocar_peca(bag_t *bag, char *mao){
	int i;
	printf("Digite o indice da peça que quer trocar: ");
	scanf("%d", &i);
	push(bag, mao[i]);
	mao[i] = '*';
	randomize_bag(bag);
	preenche_mao(bag, mao);
}

void colocar_letras(char *mao, int *pontos, char **matriz, tabela_t *tab, bag_t *bag){ //falta passar int de pontuaçao
	int n_letras;														//e substituir as letras usadas por '*'
	char vetor_jogada[7];
	int i;
	printf("Digite o número de letras que irá usar: ");
	scanf("%d", &n_letras);
	printf("Digite o indice das letras: ");
	for(i = 0; i < n_letras; i++){
		int k;
		scanf("%d", &k);
		vetor_jogada[i] = tolower(mao[k]); //substituir as pedras na mão por '*'
		mao[k] = '*';
		printf("%c", vetor_jogada[i]);
	}
	printf("\n");
	coloca_na_matriz(mao, vetor_jogada, pontos, n_letras, matriz, tab);
	preenche_mao(bag, mao);
}

void coloca_na_matriz(char *mao, char *vetor, int *pontos, int n_letras, char **matriz, tabela_t *tab){
	//vetor possui as pedras ja ordenadas
	char *palavra_completa =  calloc(16, sizeof(char));
	int i_inicial, j_inicial;
	int i_final, j_final;
	printf("Digite os indices i,j iniciais: ");
	scanf("%d %d", &i_inicial, &j_inicial);
	printf("Digite os indices i,j finais: ");
	scanf("%d %d", &i_final, &j_final);

	if(i_inicial == i_final){//i fixo, incrementar o j
		int j = j_inicial;
		int pos_vetor_original = 0;
		int indice = 0;
		while(j < j_final+1){
			if(matriz[i_inicial][j] == ' '){ 
				palavra_completa[indice] = vetor[pos_vetor_original];
				pos_vetor_original++;
			}
			else{
				palavra_completa[indice] = matriz[i_inicial][j];
			}
			j++;
			indice++;
		}
		palavra_completa[indice] = '\0';
		if(get(tab, palavra_completa)){
			int k = 0;
			for(j = j_inicial; j < j_final+1; j++){
				matriz[i_inicial][j] = palavra_completa[k];
				k++;
			}
			(*pontos) += conta_pontos(vetor, n_letras);
		}
		else{
			int k;
			printf("Palavra inválida!!\n");
			printf("Perdeu a vez!\n");
			for(k = 0; k < 7; k++){
				if(mao[k] == '*') mao[k] = toupper(vetor[k]);
			}
		}
	}
	
	else{ //j fixo, incrementar o i
		int i = i_inicial;
		int pos_vetor_original = 0;
		int indice = 0;
		while(i < i_final+1){
			if(matriz[i][j_inicial] == ' '){
				palavra_completa[indice] = vetor[pos_vetor_original];
				pos_vetor_original++;
			}
			else{
				palavra_completa[indice] = matriz[i][j_inicial];
			}
			i++;
			indice++;
		}
		palavra_completa[indice] = '\0';
		if(get(tab, palavra_completa)){
			int k = 0;
			for(i = i_inicial; i < i_final+1; i++){
				matriz[i][j_inicial] = palavra_completa[k];
				k++;
			}
			(*pontos) += conta_pontos(vetor, n_letras);
		}
		else{
			int k;
			printf("Palavra inválida!!\n");
			printf("Perdeu a vez!\n");
			for(k = 0; k < 7; k++){
				if(mao[k] == '*') mao[k] = toupper(vetor[k]);
			}
		}
	}
}

void god_mode(char **matriz){
	char c;
	int i, j;
	scanf(" %c %d %d", &c, &i, &j);
	matriz[i][j] = c;
}

int conta_pontos(char *vetor, int n_letras){ //vetor =  vetor_jogada;
	int *vetor_pontos = cria_vetor_pontos(); //n_letras = qnt de letras usadas na jogada;
	int pontos = 0;
	int i, j;
	for(i = 0; i < n_letras; i++){
		for(j = 0; j < 26; j++){
			if(j == (tolower(vetor[i]) - 'a')) pontos += vetor_pontos[j];
		}
	}
	return pontos;
}

int *cria_vetor_pontos(){
	int *vetor = malloc(26*sizeof(int));
	vetor[('a' - 'a')] = 1; vetor[('b' - 'a')] = 3; vetor[('c' - 'a')] = 2;
	vetor[('d' - 'a')] = 2; vetor[('e' - 'a')] = 1; vetor[('f' - 'a')] = 4;
	vetor[('g' - 'a')] = 4; vetor[('h' - 'a')] = 4; vetor[('i' - 'a')] = 1;
	vetor[('j' - 'a')] = 5; vetor[('k' - 'a')] = 0; vetor[('l' - 'a')] = 2;
	vetor[('m' - 'a')] = 1; vetor[('n' - 'a')] = 3; vetor[('o' - 'a')] = 1;
	vetor[('p' - 'a')] = 2; vetor[('q' - 'a')] = 6; vetor[('r' - 'a')] = 1;
	vetor[('s' - 'a')] = 1; vetor[('t' - 'a')] = 1; vetor[('u' - 'a')] = 1;
	vetor[('v' - 'a')] = 4; vetor[('x' - 'a')] = 8; vetor[('w' - 'a')] = 0;
	vetor[('y' - 'a')] = 0; vetor[('z' - 'a')] = 8;
	return vetor;
}

void imprime_placar_ordenado(jogador_t *jogador, int n_jogadores){
	jogador_t aux;
	int i, j;
	for(i = 0; i < n_jogadores; i++){
		for(j = 0; j < n_jogadores; j++){
			if(jogador[i].pontos > jogador[j].pontos){
				aux = jogador[i];
				jogador[i] = jogador[j];
				jogador[j] = aux;
			}
		}
	}
	printf("Pontuações finais:\n");
	for(i = 0; i < j; i++){
		printf("Jogador %d: %d\n", jogador[i].n_jogador+1, jogador[i].pontos);
	}
}