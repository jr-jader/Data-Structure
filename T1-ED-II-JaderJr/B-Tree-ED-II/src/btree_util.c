#include "btree_util.h"

node_position _node_position_new(node_t *node, int index) {
	// Apenas retorna um node_position com os valores informados
	node_position node_pos = {.node = node, .index = index};
	return node_pos;
}

pair_t* _pair_new(int key, void *value) {
	pair_t *p = malloc(sizeof(pair_t));
	assert(p != NULL);

	p->key = key;
	p->value = value;

	return p;
}

pair_t* _pair_copy(pair_t *p) {
	// Apenas crie um novo pair_t com os mesmos valores que o antigo
	pair_t *new = _pair_new(p->key, p->value);
	return new;
}

node_t* _node_new(int order, bool is_leaf) {
	node_t *n = malloc(sizeof(node_t));
	assert(n != NULL);

	n->n_keys = 0;
	n->is_leaf = is_leaf;
	n->keys = malloc((2*order-1) * sizeof(pair_t));
	n->children = malloc((2*order) * sizeof(node_t*));

	return n;
}

bool _node_find_key(node_t *node, int key, int *pos) {
	*pos = 0;

	// Encontra a posição cuja chave é imediatamente maior ou igual à key
	// (respeitando o número de chaves ativas no nó)
	while ((*pos) < node->n_keys && key > node->keys[(*pos)]->key) {
		(*pos)++;
	}

	// A chave foi encontrada apenas se a posição (*pos)
	// pertence ao nó e se a chave está nessa posição
	return (*pos) < node->n_keys && key == node->keys[(*pos)]->key;
}

void _node_deslocate_keys_up(node_t *to, node_t *from, int beg, int end, int padding_to, int padding_from) {
	
	int j;
	for (j = beg; j < end; j++) {
		to->keys[j + padding_to] = from->keys[j + padding_from];

	}
}

void _node_deslocate_keys_down(node_t *to, node_t *from, int beg, int end, int padding_to, int padding_from) {

	int j;
	for (j = beg; j > end; j--) {
		to->keys[j + padding_to] = from->keys[j + padding_from];
	}
}

void _node_deslocate_children_up(node_t *to, node_t *from, int beg, int end, int padding_to, int padding_from) {
	int j;
	
	for (j = beg; j < end; j++) {
		to->children[j + padding_to] = from->children[j + padding_from];
	
	}
}

void _node_deslocate_children_down(node_t *to, node_t *from, int beg, int end, int padding_to, int padding_from) {

	int j;
	for (j = beg; j > end; j--) {
		to->children[j + padding_to] = from->children[j + padding_from];
	   
	}
}

node_position _node_find_max(node_t *node) {
	assert(node != NULL);

	if (node->is_leaf) {
		return _node_position_new(node, node->n_keys-1);
	}
	else {
		return _node_find_max(node->children[node->n_keys]);
	}
}

node_position _node_find_min(node_t *node) {
	assert(node != NULL);

	if (node->is_leaf) {
		return _node_position_new(node, 0);
	}
	else {
		return _node_find_max(node->children[0]);
	}
}

void _node_delete(node_t *node) {
	free(node->children);
	free(node->keys);
	free(node);
}
