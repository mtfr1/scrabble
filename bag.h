#define BAG_H

typedef struct node_t{
	char valor;
	struct node_t *next;
}node_t;

typedef struct{
	int num_elementos;
	node_t *inicio;
}bag_t;

void imprime_bag(bag_t *bag);
bag_t *cria_bag();
int is_empty(bag_t *bag);
void push(bag_t *bag, char valor);
char pop(bag_t *bag);
void preenche_bag(bag_t *bag);
void randomize_bag(bag_t *bag);