#include "edx-io.hpp"
using namespace std;


int main() {

	long N;
	io >> N;
	long* array = new long[N];
	for (long i = 0; i < N; i++) {
		io >> array[i];
	}
	bool isHeap = true;
	//Для каждого узла проверяем, что его дети больше него
	//Если хоть в одном случае это не так, значит данный массив - не куча
	for (long i = 1; i < N / 2 + N % 2; i++) {
		if (array[i - 1] > array[2 * i - 1] || array[i - 1] > array[2 * i]) {
			isHeap = false;
			break;
		}
	}
	if (isHeap) {
		io << "YES";
	}
	else {
		io << "NO";
	}
	return 0;
}