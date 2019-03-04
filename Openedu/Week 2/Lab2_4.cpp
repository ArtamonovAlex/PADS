#include <fstream>
using namespace std;

void swop(long* a, long* b) {
	long temp = *a;
	*a = *b;
	*b = temp;
}

//Алгоритм быстрой сортировки
void quicksort(long* array, long left, long right, long k1, long k2) {
	//Если нужная область полностью находится в левом или правом подмассиве, то сортировка второго уже не нужна
	if (left > k2 || right < k1) return;

	long key = array[(left + right) / 2];
	long i = left;
	long j = right;
	do {
		while (array[i] < key) {
			i++;
		}
		while (array[j] > key) {
			j--;
		}
		if (i <= j) {
			swop(&array[i], &array[j]);
			i++;
			j--;
		}
	} while (i < j);
	if (left < j) quicksort(array, left, j, k1, k2);
	if (i < right) quicksort(array, i, right, k1, k2);
}

int main() {
	long n, k1, k2, A, B, C, a1, a2;

	ifstream input("input.txt");
	input >> n >> k1 >> k2 >> A >> B >> C >> a1 >> a2;
	input.close();

	long *array = new long[n];

	array[0] = a1;
	array[1] = a2;

	k1--;
	k2--;

	//Заполнение массива по формуле из задания
	for (long i = 2; i < n; i++) {
		array[i] = A * array[i - 2] + B * array[i - 1] + C;
	}
	//Сортировка массива
	quicksort(array, 0, n - 1, k1, k2);

	ofstream output("output.txt");
	//Вывод элементов от k1 до k2
	for (long i = k1; i <= k2; i++) {
		output << array[i];
		if (i != k2) output << " ";
	}
	output.close();

	return 0;
}