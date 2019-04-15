#include "edx-io.hpp"
using namespace std;

//Узел хранит позиции левого и правого узлов-потомков
struct node {
	int left, right;
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
	//Если высота этой вершины уже посчитана, то не нужно пересчитывать её снова
	if (height[i] != 200000) {
		return height[i];
	}
	else {
		long d = -1;
		//Если предок существует, то находим его глубину
		if (tree[i].left != 0) {
			d = max(depth(tree, tree[i].left, height), d);
		}
		if (tree[i].right != 0) {
			d = max(depth(tree, tree[i].right, height), d);
		}
		//Записываем посчитанную высоту в массив высот
		height[i] = ++d;
		return d;
	}
}

int main() {
	long N, K;


	io >> N;
	//Создаём массив узлов
	node* tree = new node[N + 1];
	//Создаём массив высот
	long* height = new long[N + 1];
	for (long i = 0; i < N + 1; i++) {
		height[i] = 200000;
	}

	for (long i = 1; i < N + 1; i++)
	{
		io >> K >> tree[i].left >> tree[i].right;
	}

	long right, left;
	for (long i = 1; i < N + 1; i++) {
		//Для каждого узла находим высоты левого и правого поддеревьев
		if (tree[i].right) {
			right = depth(tree, tree[i].right, height);
		}
		else {
			right = -1;
		}
		if (tree[i].left) {
			left = depth(tree, tree[i].left, height);
		}
		else {
			left = -1;
		}
		//Выводим баланс равный высота правого - высота левого
		io << right - left << "\n";
	}

	return 0;
}