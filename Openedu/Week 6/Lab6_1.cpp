#include "edx-io.hpp"
using namespace std;

//Находит элемент, приближая правую границу к левой
long findEl(long* btree, long left, long right, long element, long size) {
	left--;
	right++;
	long middle;
	while (right > left + 1)
	{
		middle = (left + right) / 2;
		if (btree[middle] < element) {
			left = middle;
		}
		else {
			right = middle;
		}

	}
	if (right < size && btree[right] == element) {
		return right;
	}
	else {
		return -1;
	}
}
//Находит элемент приближая левую границу к правой
long findRight(long* btree, long left, long right, long element, long size) {
	left--;
	right++;
	long middle;
	while (right > left + 1)
	{
		middle = (left + right) / 2;
		if (btree[middle] <= element) {
			left = middle;
		}
		else {
			right = middle;
		}

	}
	if (left < size && btree[left] == element) {
		return left;
	}
	else {
		return -1;
	}
}


int main() {
	long N, M;

	//Вводим двоичное дерево
	io >> N;
	long* btree = new long[N];
	for (long i = 0; i < N; i++)
	{
		io >> btree[i];
	}
	//Вводим массив искомых чисел
	io >> M;
	long* queries = new long[M];
	for (long i = 0; i < M; i++)
	{
		io >> queries[i];
	}

	long cur_query, first, last, pos;

	//Для каждого числа из массива осуществляем поиск
	for (long i = 0; i < M; i++)
	{
		cur_query = queries[i];
		//Находим первый попавшийся удовлетворяющий элемент
		pos = findEl(btree, 0, N - 1, cur_query, N);
		last = first = pos;
		//Если такого элемента нет, просто выводим -1 -1
		if (pos != -1) {
			//Если есть ищем первое появление с приближением границы справа
			first = findEl(btree, 0, pos, cur_query, N);
			//А последнее с приближение границы слева
			last = findRight(btree, pos + 1, N - 1, cur_query, N);
			first++;
			last++;
		}

		io << first << " " << last << "\n";
	}

	return 0;
}