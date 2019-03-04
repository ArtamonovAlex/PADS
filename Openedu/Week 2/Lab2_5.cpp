#include <fstream>
using namespace std;

void swop(long* a, long* b) {
	long temp = *a;
	*a = *b;
	*b = temp;
}

//Быстрая сортировка, модернизированная таким образом, чтобы сортировать массив, содержащий каждый К-тый элемент исходного массива
void quicksort(long* array, long left, long right, int step) {
	if (right == left) return;
	int middle;
	if (step == 1) {
		middle = (left + right) / 2;
	}
	else {
		int offset = left % step;
		middle = ((left / step + right / step) / 2) * step + offset;
	}
	long key = array[middle];
	long i = left;
	long j = right;
	do {
		while (array[i] < key) {
			i += step;
		}
		while (array[j] > key) {
			j -= step;
		}
		if (i <= j) {
			swop(&array[i], &array[j]);
			i += step;
			j -= step;
		}
	} while (i < j);
	if (left < j) quicksort(array, left, j, step);
	if (i < right) quicksort(array, i, right, step);
}

//Разбивает массив на K частей и вызывает сортировку для каждой
void sort(long *array, int size, int k) {
	if (k == 1) {
		quicksort(array, 0, size - 1, k);
		return;
	}
	int j;
	for (int i = 0; i < k; i++) {
		j = i;
		while (j < size) {
			j += k;
		}
		j -= k;
		quicksort(array, i, j, k);
	}
}

//Проверяет, отсортирован ли массив по неубыванию
bool is_sorted(long *array, int size) {
	for (int i = 1; i < size; i++) {
		if (array[i] < array[i - 1]) return false;
	}
	return true;
}

int main() {
	int n, k;

	ifstream input("input.txt");
	input >> n >> k;

	long *array = new long[n];
	for (int i = 0; i < n; i++) {
		input >> array[i];
	}

	input.close();

	sort(array, n, k);


	ofstream output("output.txt");
	if (is_sorted(array, n)) {
		output << "YES";
	}
	else {
		output << "NO";
	}
	output.close();

	return 0;
}