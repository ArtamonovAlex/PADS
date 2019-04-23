#include "edx-io.hpp"
using namespace std;

//Узел хранит позиции левого и правого узлов-потомков
struct node {
	long value, left, right;
};

//Возвращает максимальное из двух чисел
long max(long a, long b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

//Находит высоту i-того элемента дерева tree
long depth(node* tree, long i, long* height) {
	if (height[i] != 200000) {
		return height[i];
	}
	else {
		long d = -1;
		//Если предок существует, то находим его ывысоту
		if (tree[i].left != 0) {
			d = max(depth(tree, tree[i].left, height), d);
		}
		if (tree[i].right != 0) {
			d = max(depth(tree, tree[i].right, height), d);
		}
		//Возвращаем максимальную высоту предков + 1
		height[i] = ++d;
		return d;
	}
}
//Находит баланс pos-того узла
long balance(node* tree, long pos, long* height) {
	long left, right;
	if (tree[pos].right) {
		right = depth(tree, tree[pos].right, height);
	}
	else {
		right = -1;
	}
	if (tree[pos].left) {
		left = depth(tree, tree[pos].left, height);
	}
	else {
		left = -1;
	}
	return right - left;
}

long left_turn(node* tree, long* height) {
	long new_root;
	//Если баланс правого дочернего элемента равен -1 - совершаем большой поворот
	if (balance(tree, tree[1].right, height) == -1) {
		long B = tree[1].right;
		long C = tree[tree[1].right].left;
		tree[1].right = tree[C].left;
		tree[B].left = tree[C].right;
		tree[C].left = 1;
		tree[C].right = B;
		new_root = C;
	}
	else {
		//Если нет, то малый
		long tmp = tree[tree[1].right].left;
		tree[tree[1].right].left = 1;
		new_root = tree[1].right;
		tree[1].right = tmp;
	}
	return new_root;
}

long current_index = 1;

//Присваивает узлам возрастающие индексы начиная с родителя
void calculate_indexes(long root, long*& indexes, node* tree) {
	if (!root) {
		indexes[root] = 0;
		return;
	}
	indexes[root] = current_index++;
	calculate_indexes(tree[root].left, indexes, tree);
	calculate_indexes(tree[root].right, indexes, tree);
}
//Выводит дерево сортируя его по индексам массива indexes
void print_node(long root, long*& indexes, node* tree) {
	if (!root) { return; }

	io << tree[root].value << " " << indexes[tree[root].left] << " " << indexes[tree[root].right] << "\n";

	print_node(tree[root].left, indexes, tree);
	print_node(tree[root].right, indexes, tree);
}

int main() {
	long N;

	io >> N;
	//Создаём массив узлов
	node* tree = new node[N + 1];

	long* height = new long[N + 1];
	for (long i = 0; i < N + 1; i++) {
		height[i] = 200000;
	}

	for (long i = 1; i < N + 1; i++)
	{
		io >> tree[i].value >> tree[i].left >> tree[i].right;
	}

	long new_root = left_turn(tree, height);

	long* indexes = new long[N + 1];
	calculate_indexes(new_root, indexes, tree);
	io << N << "\n";
	print_node(new_root, indexes, tree);

	return 0;
}