#include "edx-io.hpp"
using namespace std;

struct node {
	long key, left, right;
};

//Определяет количество узлов в поддереве узла
long depth(node* tree, long i) {
	long d = 0;

	if (tree[i].left != 0) {
		d += depth(tree, tree[i].left);
	}
	if (tree[i].right != 0) {
		d += depth(tree, tree[i].right);
	}

	return ++d;
}

//Находит узел по значению
long find_node(node* tree, long del_value) {
	long i = 1;

	while (tree[i].key != del_value) {
		if (del_value < tree[i].key) {
			if (tree[i].left) {
				i = tree[i].left;
			}
			else {
				return 0;
			}
		}
		else {
			if (tree[i].right) {
				i = tree[i].right;
			}
			else {
				return 0;
			}
		}
	}

	return i;
}

//Удаляет узел и его поддерево по значению и возвращает количество элементов в дереве
long delete_node(node* tree, long del_value, long size, long* parents) {
	//Находим узел, который необходимо удалить
	long pos = find_node(tree, del_value);
	if (pos == 0) {
		return size;
	}
	else {
		long parent_pos = parents[pos];
		//Если узел является левым потомком, обнуляем левого потомка родителя
		if (tree[parent_pos].left == pos) {
			tree[parent_pos].left = 0;
		}
		//Если нет, то правого вотомка
		else {
			tree[parent_pos].right = 0;
		}
		
		return size - depth(tree, pos);
	}
}

int main() {

	long N, M;
	io >> N;

	node* tree = new node[N + 1];
	long* parents = new long[N + 1];

	for (long i = 1; i < N + 1; i++)
	{
		io >> tree[i].key >> tree[i].left >> tree[i].right;
		//При наличии левого и правого потомков, заносим данные об их родителе в массив parents
		if (tree[i].left != 0) {
			parents[tree[i].left] = i;
		}
		if (tree[i].right != 0) {
			parents[tree[i].right] = i;
		}
	}

	io >> M;

	long del_value;

	for (long i = 0; i < M; i++)
	{
		io >> del_value;
		//Для каждого вводимого значения вызываем функцию удаления элемента
		N = delete_node(tree, del_value, N, parents);
		io << N << "\n";

	}

	return 0;
}