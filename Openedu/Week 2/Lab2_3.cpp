#include <fstream>
using namespace std;

void swop(long* a, long* b) {
	long temp = *a;
	*a = *b;
	*b = temp;
}


int main() {

	ifstream input("input.txt");
	long n;
	input >> n;
	input.close();

	long* array = new long[n];
	//Каждый следующий элемент вставляется в конец массива, а затем меняется с центральным элементом
	//Тогда при сортировке будет максимальное число рекурсии - N
	for (long i = 0; i < n; i++)
	{
		array[i] = i + 1;
		if (i > 1) {
			swop(&array[i], &array[i / 2]);
		}
	}


	ofstream output("output.txt");

	for (long i = 0; i < n; i++) {
		output << array[i];
		if (i != n - 1) output << " ";
	}

	output.close();

	return 0;

}