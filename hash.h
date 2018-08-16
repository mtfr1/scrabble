#define HASH_H

typedef struct celula{
	char str[50];
	int key;
	struct celula *next; //lista para caso haja colisão
}celula_t;

typedef struct{
	int tamanho; //tamanho do vetor (primo mais proximo do nº de palavras)
	celula_t **vetor;
}tabela_t;

tabela_t *cria_tabela(int tamanho);
unsigned long hash(char *str);
void put(tabela_t *tab, char *str); //insere uma chave na tabela hash
tabela_t *init_table();
int get(tabela_t *tab, char *str); //verifica se uma chave existe na tabela