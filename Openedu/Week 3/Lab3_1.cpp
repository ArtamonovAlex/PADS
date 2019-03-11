#include <fstream>
using namespace std;

//Цифровая сортировка, в качестве разряда выбран 1 байт
void radix_sort(long *array, int size, int digit) {
	long *output = new long[size];
	long *count = new long[256];
	//Сортируем побайтово начиная с правого байта
	for (int pow = 0; pow <= digit; pow += 8) {
		//Сортировка подсчётом
		//1. Заполняем вспомогательный массив 0
		for (int i = 0; i < 256; i++) {
			count[i] = 0;
		}
		//2. Для каждого элемента (байта) считаем количество в исходном массиве
		for (int i = 0; i < size; i++) {
			count[(array[i] >> pow) & 255]++;
		}
		//3. Увеличиваем каждый следующий элемент вспомогательного массива на предыдущий,
		//в итоге под каждым элементом (байтом) хранится его позиция в отсортированном массиве
		for (int i = 1; i < 256; i++) {
			count[i] += count[i - 1];
		}
		//4. Заполняем новый массив проходя вспомоготельный с конца, при этом уменьшая количество равных элементов
		//чтобы корректно записывать одинаковые элементы
		for (int i = size - 1; i >= 0; i--) {
			output[count[(array[i] >> pow) & 255] - 1] = array[i];
			count[(array[i] >> pow) & 255]--;
		}

		for (int i = 0; i < size; i++) {
			array[i] = output[i];
		}
	}
}

int main() {
	int n, m;

	ifstream input("input.txt");
	input >> n >> m;

	long *A = new long[n];
	long *B = new long[m];
	long *C = new long[n * m];

	long maxA = 0;
	for (int i = 0; i < n; i++) {
		input >> A[i];
		//Находим максимальный элемент в первом массиве
		if (A[i] > maxA) {
			maxA = A[i];
		}
	}
	long maxB = 0;
	long pos;

	for (int i = 0; i < m; i++) {
		input >> B[i];
		//Заполнсяем массив С
		for (int j = 0; j < n; j++) {
			pos = (i * n) + j;
			C[pos] = B[i] * A[j];
		}
		//Находим максимальный элемент во втором массиве
		if (B[i] > maxB) {
			maxB = B[i];
		}
	}
	input.close();

	long maxNum = maxA * maxB;
	int digit = 1;
	//Считаем количество битов в максимальном числе
	while (maxNum >> digit > 0) {
		digit++;
	}
	digit--;

	radix_sort(C, n*m, digit);



	long long sum = 0;
	for (int i = 0; i < n * m; i += 10) {
		sum += C[i];
	}
	ofstream output("output.txt");
	output << sum;
	output.close();

	return 0;
}