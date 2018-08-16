#define SCRABBLE_H

typedef struct{
	//char nome[14];
	char mao[7];
	int pontos;
	int n_jogador;
}jogador_t;

void clear_screen();

void cria_mao(char *mao);

void preenche_mao(bag_t *bag, char *mao);
void trocar_mao(bag_t *bag, char *mao);
void trocar_peca(bag_t *bag, char *mao);

void imprime_mao(char* mao);

int jogada();
void colocar_letras(char *mao, int *pontos, char **matriz, tabela_t *tab, bag_t *bag);
void coloca_na_matriz(char *mao, char *vetor, int *pontos, int n_letras, char **matriz, tabela_t *tab);
int conta_pontos(char *vetor, int n_letras);
int *cria_vetor_pontos();

void imprime_placar_ordenado(jogador_t *jogador, int j);

void god_mode(char **matriz);