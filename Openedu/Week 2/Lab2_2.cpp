#include <fstream>
using namespace std;


//"Сливает" два отсортированных по возрастанию массива в один отсортированный по возрастанию
long* merge_arrays(long* array1, int length1, long* array2, int length2, long long &inversions) {
	int result_length = length1 + length2;
	long* result_array = new long[result_length];

	int i = 0;
	int j = 0;

	for (int counter = 0; counter < result_length; counter++) {
		if ((array1[i] <= array2[j] || j == length2) && i != length1) { //Если элемент "левого" массива меньше элемента "правого" или правый закончился,
			result_array[counter] = array1[i];							//и при условии, что не закончился левый, элемент левого массива ставится на следующую позицию
			i++;														//результирующего массива
		}
		else {															//В обратном случае в результирующий массив добавляется элемент правого массива
			result_array[counter] = array2[j];
			inversions += length1 - i;									//Все "оставшиеся" элементы левого массива будут больше этого элемента правого массива
			j++;
		}
	}
	return result_array;
}

//Сортирует массив определённой длины
long* sort_array(long* array, int length, long long &inversions) {
	if (length == 1) {
		return array;
	}

	//Деление массива на два подмассива, где первый <= второго
	int left_array_size, right_array_size;
	if (length % 2 == 1) {
		left_array_size = length / 2;
		right_array_size = length / 2 + 1;
	}
	else {
		left_array_size = length / 2;
		right_array_size = length / 2;
	}
	long* left_array = new long[left_array_size];
	long* right_array = new long[right_array_size];

	for (int i = 0; i < length; i++) {
		if (i < left_array_size) {
			left_array[i] = array[i];
		}
		else {
			right_array[i - left_array_size] = array[i];
		}
	}

	//Вызов функции для каждого из двух подмассивов для их сортировки
	left_array = sort_array(left_array, left_array_size, inversions);
	right_array = sort_array(right_array, right_array_size, inversions);

	//Слияние отсортированных массивов в один
	return merge_arrays(left_array, left_array_size, right_array, right_array_size, inversions);
}

long* read_array_from_file(string file_name, int &size) {
	ifstream input(file_name);
	input >> size;
	long* array = new long[size];

	for (int i = 0; i < size; i++) {
		input >> array[i];
	}

	input.close();
	return array;
}

int main() {

	int size;

	long* array = read_array_from_file("input.txt", size);
	long long inversions = 0;

	array = sort_array(array, size, inversions);

	ofstream output("output.txt");
	output << inversions;
	output.close();
	return 0;
}