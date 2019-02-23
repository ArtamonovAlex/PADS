#include <fstream>
using namespace std;

int main() {
	long long a, b;

	ifstream input("input.txt");
	input >> a >> b;
	input.close();

	long long sum = a + b * b;

	ofstream output("output.txt");
	output << sum;
	output.close();

	return 0;
}