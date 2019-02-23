#include <fstream>
using namespace std;

int main() {

	int n;

	ifstream input("input.txt");

	input >> n;
	long* M = new long[n];

	for (int i = 0; i < n; i++) {
		input >> M[i];
	}

	input.close();

	int j;
	long temp;
	int min;

	ofstream output("output.txt");

	for (int i = 0; i < n; i++) {
		j = i + 1;
		min = i;
		temp = M[i];
		//Для каждого i-того элемента осуществляется поиск наименьшего элемента справа от него
		while (j < n) {
			if (temp > M[j]) {
				temp = M[j];
				min = j;
			}
			j++;
		}
		//Если этот элемент найден, то он меняется с i-тым, получается, что элементы по возрастанию становятся с начала
		if (i != min) {
			M[min] = M[i];
			M[i] = temp;
			output << "Swap elements at indices " << i + 1 << " and " << min + 1 << "." << endl;
		}
	}
	output << "No more swaps needed." << endl;

	for (int i = 0; i < n; i++) {
		output << M[i];
		if (i != n - 1) output << " ";
	}

	output.close();

	return 0;
}