#include "btree.h"

BTree* btree_new(int order) {
	BTree* bt = malloc(sizeof(BTree));
	assert(bt != NULL);

	// Após alocar, temos que inicializar a B-Tree
	btree_init(bt, order);

	return bt;
}

void btree_init(BTree *bt, int order) {
	assert(bt != NULL);

	bt->order = order;
	bt->root = _node_new(order, TRUE);
}

node_position btree_find(BTree* bt, int key) {
	assert(bt != NULL);

	return _btree_find_node(bt->root, key);
}

node_position _btree_find_node(node_t* node, int key) {
	assert(node != NULL);

	int pos;
	if (_node_find_key(node, key, &pos)) {
		// Se a chave foi encontrada nesse nó,
		// retorne um meio de acessá-la
		return _node_position_new(node, pos);
	}
	else {
		// Se a chave não foi encontrada
		if (node->is_leaf) {
			// e o nó atual é uma folha,
			// então key não pertence à B-Tree
			return _node_position_new(NULL, -1);
		}
		else {
			// e o nó atual possui filhos,
			// então devemos explor o filho na posição pos
			return _btree_find_node(node->children[pos], key);
		}
	}
}

node_position btree_insert(BTree* bt, int key, void *value) {
	assert(bt != NULL);

	node_t *root = bt->root;

	// Esse pair será enviado durante as chamadas recursivas de inserção,
	// e é o que realmente será inserido na B-Tree
	pair_t *pair = _pair_new(key, value);

	if (root->n_keys == 2*bt->order -1) {

		node_t *new_root = _node_new(bt->order, FALSE);
		new_root->children[0] = root;

		_btree_split(new_root, 0, bt->order);
		bt->root = new_root;

		// Podemos prosseguir com a inserção
		return _btree_insert_nonfull(new_root, pair, bt->order);
	}
	else {

		return _btree_insert_nonfull(root, pair, bt->order);
	}
}

void _btree_split(node_t *node, int pos, int order) {
	// Para mais informações, consulte a documentação,
	// em especial o pseudo-código B-Tree-Split-Child

	node_t *y = node->children[pos];
	assert(y != NULL);

	node_t *z = _node_new(order, y->is_leaf);
	z->n_keys = order-1;

	_node_deslocate_keys_up(z, y, 0, order-1, 0, order);

	if (!y->is_leaf) {
		
		_node_deslocate_children_up(z, y, 0, order, 0, order);
	}
	y->n_keys = order-1;

	_node_deslocate_children_down(node, node, node->n_keys, pos, 1, 0);

	node->children[pos+1] = z;

	_node_deslocate_keys_down(node, node, node->n_keys-1, pos-1, 1, 0);

	node->keys[pos] = y->keys[order-1];

	node->n_keys++;
}

node_position _btree_insert_nonfull(node_t * node, pair_t *pair, int order) {

	int pos = node->n_keys - 1;
	if (node->is_leaf) {

		while (pos >= 0 && pair->key < node->keys[pos]->key) {
			node->keys[pos+1] = node->keys[pos];
			pos--;
		}

		if (pos >= 0 && pair->key == node->keys[pos]->key) {

			pos++;
			while (pos != node->n_keys) {
				node->keys[pos] = node->keys[pos+1];
				pos++;
			}

			return _node_position_new(NULL, -1);
		}
		else {
			pos++;

			node->keys[pos] = pair;
			node->n_keys++;
			return _node_position_new(node, pos);
		}
	}
	else {
		while (pos >= 0 && pair->key < node->keys[pos]->key) {
			pos--;
		}
		if (pos >= 0 && pair->key == node->keys[pos]->key) {

			return _node_position_new(NULL, -1);
		}
		else {
			pos++;

			if (node->children[pos]->n_keys == 2*order-1) {
				_btree_split(node, pos, order);
				if (pair->key > node->keys[pos]->key) {
					pos++;
				}
			}

			return _btree_insert_nonfull(node->children[pos], pair, order);
		}
	}
}

node_position btree_remove(BTree* bt, int key) {
	// Para mais informações, consulte a documentação,
	// em especial o pseudo-código B-Tree-Remove

	assert(bt != NULL);

	node_position pos = _btree_remove_node(bt->root, key, bt->order);
	if (bt->root->n_keys == 0 && pos.node != NULL && pos.node != bt->root) {

		bt->root = bt->root->children[0];
		assert(bt->root != NULL);
	}

	return pos;
}

node_position _btree_remove_node(node_t *node, int key, int order) {
	// Para mais informações, consulte a documentação,
	// em especial o pseudo-código B-Tree-Remove-Node

	int pos;
	if (_node_find_key(node, key, &pos)) {
		// Caso a chave está foi encontrada nesse nó

		if (node->is_leaf) {
			/*
			    Caso 1: Se a chave k está em um nó x e x é uma
			    folha, remova a chave k de x
			 */
			
			free(node->keys[pos]);
			node->n_keys--;

			_node_deslocate_keys_up(node, node, pos, node->n_keys, 0, 1);

			return _node_position_new(node, pos);
		}
		else {
			/*
			    Caso 2: Se a chave k está em um nó x e x é um nó
			    interno.
			 */
			node_t *left = node->children[pos];
			node_t *right = node->children[pos+1];
			if (left->n_keys >= order) {
				/*
				    a) Se o nó filho y que precede k no nó x
				    tem pelo menos t chaves, encontre o
				    predecessor k’ de k na subárvore
				    enraizada em y.
				    Remova k’, e substitua k por k’ em x.
				 */

				free(node->keys[pos]);

				node_position max = _node_find_max(left);
				pair_t* p = _pair_copy(max.node->keys[max.index]);

				node->keys[pos] = p;

				_btree_remove_node(left, p->key, order);
				return _node_position_new(node, pos);
			}
			else if (right->n_keys >= order) {
				/*
				    b) Caso simétrico ao 2a. Se o nó filho y que
				    precede k no nó x tem menos que t chaves,
				    examine o nó filho z que vem depois de
				    k no nó x.
				 */

				free(node->keys[pos]);

				node_position min = _node_find_min(right);
				pair_t* p = _pair_copy(min.node->keys[min.index]);
				node->keys[pos] = p;

				_btree_remove_node(right, p->key, order);
				return _node_position_new(node, pos);
			}
			else {
				/*
				    2c) Se ambos os nós filhos y e z possuem
				    apenas t-1 chaves, concatena-se k e todo o
				    conteúdo de z com y, de maneira que x perca
				    a chave k e o ponteiro para z
				 */
				
				left->keys[order-1] = node->keys[pos];

				_node_deslocate_keys_up(left, right, 0, order-1, order, 0);
				_node_deslocate_children_up(left, right, 0, order, order, 0);
				left->n_keys = 2*order - 1;

				_node_delete(right);

				_node_deslocate_keys_up(node, node, pos, node->n_keys-1, 0, 1);
				_node_deslocate_children_up(node, node, pos, node->n_keys-1, 1, 2);
				node->n_keys--;

				return _btree_remove_node(left, key, order);
			}
		}
	}
	else {
		if (node->is_leaf) {
			/*
			    key não foi encontrada em um nó folha => key não
			    pertence à árvore
			 */
			return _node_position_new(NULL, -1);
		}

		/*
		        Caso 3: se a chave k não está presente em um nó interno x,
		        determine a raiz x.ci da subárvore que deve conter k.
		 */

		node_t *next = node->children[pos];

		if (next->n_keys == order-1) {
			node_t *left = next;

			node_t *right;
			if (pos == node->n_keys) {
				node_t *tmp = left;
				left = node->children[pos-1];
				right = tmp;
			}
			else {
				right = node->children[pos+1];
			}

			if (left->n_keys >= order) {
				/*
					a-left) Se x.c[i] tiver apenas t-1 chaves, mas possui o irmão
					esquerdo imediato com pelo menos t chaves, mover uma chave de x
					para x.c[i].

					Mover para x uma chave do irmão imediato esquerdo de x.c[i].
					Mover os ponteiros associados para que apontem para os filhos
					corretos.
				 */
				
				node_position max = _node_find_max(left);
				pair_t* p = _pair_copy(max.node->keys[max.index]);

				_btree_remove_node(left, p->key, order);

				_btree_insert_nonfull(right, node->keys[pos-1], order);

				node->keys[pos-1] = p;

				return _btree_remove_node(right, key, order);
			}
			else if (right->n_keys >= order) {
				/*
					a-right) Se x.c[i] tiver apenas t-1 chaves, mas possui o irmão
					direito imediato com pelo menos t chaves, mover uma chave de x
					para x.c[i].

					Mover para x uma chave do irmão imediato direito de x.c[i].
					Mover os ponteiros associados para que apontem para os filhos
					corretos.
				 */
				
				node_position min = _node_find_min(right);
				pair_t* p = _pair_copy(min.node->keys[min.index]);

				
				_btree_remove_node(right, p->key, order);

				_btree_insert_nonfull(left, node->keys[pos-1], order);

				node->keys[pos-1] = p;

				return _btree_remove_node(left, key, order);
			}
			else {
				/*
					b) Se x.c[i] e ambos os seus irmãos imediatos tiverem t-1
					chaves, concatenar x.c[i] com um de seus irmãos.

					Essa concatenação envolve mover uma chave de x para o novo
					nó criado com a concatenação, para que ele se torne a chave
					mediana desse novo nó.
				 */
				
				left->keys[order-1] = node->keys[pos-1];
				_node_deslocate_keys_up(node, node, pos, node->n_keys-1, 0, 1);
				_node_deslocate_children_up(node, node, pos+1, node->n_keys, 0, 1);
				node->n_keys--;

				_node_deslocate_keys_up(left, right, 0, order-1, order, 0);
				_node_deslocate_children_up(left, right, 0, right->n_keys+1, order-1, 0);
				_node_delete(right);

				left->n_keys = 2*order-1;
				return _btree_remove_node(left, key, order);
			}
		}

		return _btree_remove_node(next, key, order);
	}
}

void btree_delete_s(BTree *bt) {
	// Deleta uma B-Tree sem chamar free(tree),
	// mas sim removendo todas as chaves que ela possui
	
	// TODO make this efficient - through DFS?
	while (bt->root->n_keys > 0) {
	    
		btree_remove(bt, bt->root->keys[0]->key);
	}

	_node_delete(bt->root);
}

void btree_delete_h(BTree *bt) {
	// Deleta a B-Tree e todas as suas chaves-valores.
	// A B-Tree deve ter sido alocada com uma função malloc(),
	// caso contrário, tem-se comportamento indefinido
	btree_delete_s(bt);
	free(bt);
}
