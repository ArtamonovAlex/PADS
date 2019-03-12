#include "edx-io.hpp"
#include <string>
using namespace std;


string check(string seq, char *stack, long offset) {
	for (int j = 0; j < seq.size(); j++) {
		switch (seq[j]) {
		case '(':
			stack[++offset] = seq[j];
			continue;
		case '[':
			stack[++offset] = seq[j];
			continue;
		case ')':
			if (offset < 0 || stack[offset] != '(') {
				return "NO\n";
			}
			offset--;
			continue;
		case ']':
			if (offset < 0 || stack[offset] != '[') {
				return "NO\n";
			}
			offset--;
			continue;
		}
	}
	if (offset == -1) {
		return "YES\n";
	}
	return "NO\n";
}

int main() {

	long N;
	string seq;
	io >> N;
	char* stack = new char[10000];


	for (long i = 0; i < N; i++) {
		long offset = -1;
		io >> seq;
		io << check(seq, stack, offset);
	}

	return 0;
}