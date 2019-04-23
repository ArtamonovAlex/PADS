#include <fstream>
#include <string>
using namespace std;

long count_words(string P, long pos) {
	char curr_letter = P[pos];
	long counter = 0;
	for (long i = pos + 2; i < P.length(); i++) {
		if (P[i] == curr_letter) {
			counter += i - pos - 1;
		}
	}
	return counter;
}

int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");

	string P = "";
	string tmp;

	while (!input.eof()) {
		input >> tmp;
		if (tmp != "") {
			P += tmp;
		}
		tmp = "";
	}
	long long counter = 0;

	for (long i = 0; i < P.length() - 2; i++) {
		counter += count_words(P, i);
	}

	output << counter;
	return 0;
}