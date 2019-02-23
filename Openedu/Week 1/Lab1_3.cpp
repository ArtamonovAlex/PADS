#include <fstream>
using namespace std;

int main() {

	int n;

	//Ввод длины и самого массива
	ifstream input("input.txt");
	input >> n;
	long* a = new long[n];
	for (int i = 0; i < n; i++) {
		input >> a[i];
	}
	input.close();

	ofstream output("output.txt");

	//Первый элемент всегда остаётся на месте
	output << 1 << " ";

	int j;
	long temp;

	//Алгоритм сортировки вставками
	for (int i = 1; i < n; i++) {
		j = i;
		while (j != 0 && a[j] < a[j - 1]) {
			temp = a[j];
			a[j] = a[j - 1];
			a[j - 1] = temp;
			j--;
		}
		//В массиве индекс с 0, а в ответе должны быть с 1
		output << j + 1;
		//После каждого числа кроме последнего должен стоять пробел
		if (i != n - 1) output << " ";
	}
	//Отсортированный массив должен выводиться с новой строки
	output << endl;

	//Вывод массива
	for (int i = 0; i < n; i++) {
		output << a[i];
		if (i != n - 1) output << " ";
	}

	output.close();

	return 0;
}