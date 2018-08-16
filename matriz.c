#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

char **cria_matriz(int l, int c){
	int i, j;
	char **matriz = malloc(l*sizeof(char*));
	for(i = 0; i < l; i++){
		matriz[i] = malloc(c*sizeof(char));
	}
	for(i = 0; i < l; i++){
		for(j = 0; j < c; j++){
			matriz[i][j] = ' ';
		}
	}
	return matriz;
}

void imprime_matriz(char **matriz){
	int i, j;
	for(i = 0; i < 15; i++){
		if(i == 0){
			for(j = 0; j < 15; j++){
				if(j == 0){
					printf("\t     ");
				}
				printf("%2d  ", j);
			}
			printf("\n");
			for(j = 0; j < 15; j++){
				if(j == 0){
					printf("\t    |");
				}
				printf("---|");
			}
			printf("\n");
		}
		for(j = 0; j < 15; j++){
			if(j == 0){
				printf("\t%2d  |", i);
			}
			if(matriz[i][j] == ' '){
				printf("   |");
			}
			else{
				printf(" %c |", matriz[i][j]);
			}
		}
		printf("\n");
		for(j = 0; j < 15; j++){
			if(j == 0){
				printf("\t    |");
			}
			printf("---|");
		}
		printf("\n");
	}
	printf("\n");
}
