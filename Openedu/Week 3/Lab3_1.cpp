#include <fstream>
#include <vector>
using namespace std;

vector<long> sort(vector<long> list) {
	long j;
	long temp;
	for (long i = list.size() - 2; i >= 0; i--) {
		j = i;
		while (j != list.size() - 1 && list[j] < list[j + 1]) {
			temp = list[j];
			list[j] = list[j + 1];
			list[j + 1] = temp;
			j++;
		}
	}
	return list;
}

void bucketsort(long* array, long size, long max) {
	vector<long> *B = new vector<long>[size];
	long bucketsize = ((max / size) + 1);
	for (long i = 0; i < size; i++) {
		B[array[i] / bucketsize].push_back(array[i]);
	}
	long array_pos = 0;
	for (long i = 0; i < size / k; i++) {
		B[i] = sort(B[i]);
		while (!B[i].empty()) {
			array[array_pos] = B[i].back();
			B[i].pop_back();
			array_pos++;
		}
	}
}

int main() {
	int n, m;

	ifstream input("input.txt");
	input >> n >> m;

	long *A = new long[n];
	for (int i = 0; i < n; i++) {
		input >> A[i];
	}
	long *B = new long[m];
	long *C = new long[n * m];
	long max = 0;
	long pos;
	for (int i = 0; i < m; i++) {
		input >> B[i];
		for (int j = 0; j < n; j++) {
			pos = (i * n) + j;
			C[pos] = B[i] * A[j];
			if (C[pos] > max) {
				max = C[pos];
			}
		}
	}
	input.close();
	delete A;
	delete B;

	bucketsort(C, n*m, max);

	long long sum = 0;
	for (int i = 0; i < n * m; i += 10) {
		sum += C[i];
	}
	ofstream output("output.txt");
	output << sum;
	output.close();

	return 0;
}