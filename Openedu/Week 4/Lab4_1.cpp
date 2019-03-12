#include "edx-io.hpp"
using namespace std;


int main() {

	long N;
	io >> N;
	char action;

	long* stack = new long[N];
	long offset = -1;

	for (long i = 0; i < N; i++) {
		io >> action;
		if (action == '+') {
			offset++;
			io >> stack[offset];
		}
		else {
			io << stack[offset] << '\n';
			offset--;
		}
	}

	return 0;
}