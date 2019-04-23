#include "edx-io.hpp"
#include <string>
using namespace std;

//Перебором каждого символа находит первое вхождение строки P в T с позиции curr_pos
int find_substr(string P, string T, long curr_pos) {
	for (int i = curr_pos; i < T.length(); i++) {
		bool ok = true;
		for (int j = 0; j < P.length(); j++)
		{
			if (T[i + j] != P[j]) {
				ok = false;
				break;
			}
		}
		if (ok) {
			curr_pos = i;
			return curr_pos;
		}
	}
	return T.length();
}

int main() {

	string P, T;
	io >> P >> T;
	int counter = 0;
	int curr_pos = 0;
	int* positions = new int[T.length()];

	do {
		//Получаем позицию вхождения
		curr_pos = find_substr(P, T, curr_pos);
		//Если метод вернул значение принадлежащее строке - записываем его
		if (curr_pos < T.length()) {
			positions[counter++] = ++curr_pos;
		}
	} while (curr_pos < T.length());

	io << counter << "\n";
	for (int i = 0; i < counter; i++) {
		io << positions[i] << " ";
	}
	return 0;
}