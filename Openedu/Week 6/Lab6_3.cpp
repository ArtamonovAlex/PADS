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

//Находит глубину i-того элемента дерева tree
long depth(node* tree, long i) {
	long d = 0;
	//Если предок существует, то находим его глубину
	if (tree[i].left != 0) {
		d = max(depth(tree, tree[i].left), d);
	}
	if (tree[i].right != 0) {
		d = max(depth(tree, tree[i].right), d);
	}
	//Возвращаем максимальную глубину предков + 1
	return ++d;
}

int main() {
	long N, K;

	io >> N;
	if (N != 0) {
		//Создаём массив узлов
		node* tree = new node[N + 1];

		for (long i = 1; i < N + 1; i++)
		{
			io >> K >> tree[i].left >> tree[i].right;
		}
		//Находим глубину 1 узла (корня)
		io << depth(tree, 1);
	}
	else
	{
		io << 0;
	}

	return 0;
}