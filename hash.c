#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

tabela_t *cria_tabela(int tamanho){
	tabela_t *tab = malloc(sizeof(tabela_t));
	tab->vetor = (celula_t**) malloc(tamanho*sizeof(celula_t*));
	tab->tamanho = tamanho;
	int i;
	for(i = 0; i < tamanho; i++){
		tab->vetor[i] = NULL;
	}

	return tab;
}

unsigned long hash(char *str){
	unsigned long hash = 5381;
	int c;
	while (c = *str++){
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

void put(tabela_t *tab, char *str){
	int key = (hash(str)) % tab->tamanho;
	celula_t *entry = malloc(sizeof(celula_t));
	entry->key = key;
	strcpy(entry->str, str);
	entry->next = NULL;

	celula_t *aux = tab->vetor[key];
	if(aux == NULL){
		tab->vetor[key] = entry;
	}
	else{
		while(aux->next != NULL){
			aux = aux->next;
		}
		aux->next = entry;
	}
}

tabela_t *init_table(){
	FILE *fp = fopen("palavras_comp.txt", "r");
	tabela_t *tab = cria_tabela(1000000);
	char entry[50];
	while(fscanf(fp, "%s", entry) != EOF){
		put(tab, entry);
	}
	return tab;
}

int get(tabela_t *tab, char *str){
	int key = (hash(str)) % tab->tamanho;
	celula_t *aux = tab->vetor[key];
	while(aux != NULL){
		if(strcmp(aux->str, str) == 0) return 1;
		aux = aux->next;
	}
	return 0;
}
