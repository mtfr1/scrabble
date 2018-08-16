#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bag.h"

void imprime_bag(bag_t *bag){
	node_t *aux = bag->inicio;
	while(aux != NULL){
		printf("%c\n", aux->valor);
		aux = aux->next;
	}
}

bag_t *cria_bag(){
	bag_t *bag = (bag_t*) malloc(sizeof(bag_t));
	bag->inicio = NULL;
	bag->num_elementos = 0;
	return bag;
}

int is_empty(bag_t *bag){
	if(bag->inicio == NULL) return 1;
	else return 0;
}

void push(bag_t *bag, char valor){
	node_t *novo = (node_t*) malloc(sizeof(node_t));
	novo->valor = valor;
	if(bag->inicio == NULL){
		bag->inicio = novo;
		novo->next = NULL;
	}
	else{
		novo->next = bag->inicio;
		bag->inicio = novo;
	}
	bag->num_elementos++; 
}

char pop(bag_t *bag){
	char c;
	if(!is_empty(bag)){
		node_t *aux = bag->inicio;
		bag->inicio = bag->inicio->next;
		bag->num_elementos--;
		c = aux->valor;
		free(aux);
		return c;
	}
	else{
		printf("A bag esta vazia!\n");
		return 1;
	}	
}

void preenche_bag(bag_t *bag){
	int i;
	for(i = 0; i < 14; i++){push(bag, 'A');}
	for(i = 0; i < 11; i++){push(bag, 'E');}
	for(i = 0; i < 10; i++){push(bag, 'I');}
	for(i = 0; i < 10; i++){push(bag, 'O');}
	for(i = 0; i < 8; i++){ push(bag, 'S');}
	for(i = 0; i < 7; i++){ push(bag, 'U');}
	for(i = 0; i < 6; i++){ push(bag, 'M');}
	for(i = 0; i < 6; i++){ push(bag, 'R');}
	for(i = 0; i < 5; i++){ push(bag, 'T');}
	for(i = 0; i < 5; i++){ push(bag, 'D');}
	for(i = 0; i < 5; i++){ push(bag, 'L');}
	for(i = 0; i < 4; i++){ push(bag, 'C');}
	for(i = 0; i < 4; i++){ push(bag, 'P');}
	for(i = 0; i < 4; i++){ push(bag, 'N');}
	//for(i = 0; i < 3; i++){ push(bag, ' ');}
	for(i = 0; i < 3; i++){ push(bag, 'B');}
	for(i = 0; i < 2; i++){ push(bag, 'F');}
	for(i = 0; i < 2; i++){ push(bag, 'G');}
	for(i = 0; i < 2; i++){ push(bag, 'H');}
	for(i = 0; i < 2; i++){ push(bag, 'V');}
	for(i = 0; i < 2; i++){ push(bag, 'J');}
	push(bag, 'Q');
	push(bag, 'X');
	push(bag, 'Z');
}

void randomize_bag(bag_t *bag){
	srand(time(0));
	char aux;
	int i, j, n;
	node_t *aux_it = bag->inicio;
	node_t *aux_it2 = bag->inicio;
	while(aux_it != NULL){
		n = rand()%bag->num_elementos;
		for(j = 0; j < n; j++){
			if(aux_it2 != NULL) aux_it2 = aux_it2->next;
		}
		aux = aux_it2->valor;
		aux_it2->valor = aux_it->valor;
		aux_it->valor = aux;
		aux_it = aux_it->next;
		aux_it2 = bag->inicio;
	}
}