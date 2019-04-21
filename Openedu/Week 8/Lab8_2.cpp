#include "edx-io.hpp"
#include <list>
#include <map>
#include <string>
using namespace std;

//Возвращает позицию предыдущего элемента для pos, если он есть, и -1 в обратном случае
int get_prev_pos(string* pos_string, int pos) {
	pos--;
	while (pos > 0 && pos_string[pos].empty())
	{
		pos--;
	}
	if (!pos_string[pos].empty() && pos > -1) {
		return pos;
	}
	else {
		return -1;
	}
}
//Возвращет позицию следующего элемента для pos, если он есть, и -1 в обратном случае
int get_next_pos(string* pos_string, int pos, long keys_counter) {
	pos++;
	while (pos < keys_counter && pos_string[pos].empty())
	{
		pos++;
	}
	if (!pos_string[pos].empty() && pos > -1 && pos < keys_counter) {
		return pos;
	}
	else {
		return -1;
	}
}

int main() {
	long N;
	io >> N;
	//Ассоциативный массив
	map<string, string> ht;
	//Массив, хранящий для каждого ключа порядок добавления в ассоциативный массив
	map<string, long> keys_pos;
	//Массив, хранящий ключи в остортированном по добавлению порядке
	string* pos_string = new string[N];
	//Счётчик введённых ключей
	long key_counter = 0;
	int pos, prev_pos;
	string command, key, element;

	for (long i = 0; i < N; i++) {
		io >> command >> key;
		switch (command[0])
		{
		case 'p':
			//put
			if (command[1] == 'u') {
				io >> element;
				if (!ht[key].empty()) {
					ht[key].assign(element);
				}
				else {
					ht[key].assign(element);
					keys_pos[key] = key_counter;
					pos_string[key_counter++] = key;
				}
				break;
			}
			//prev
			else {
				pos = keys_pos[key];
				prev_pos = get_prev_pos(pos_string, pos);
				if (prev_pos != -1) {
					io << ht[pos_string[prev_pos]] << "\n";
				}
				else
				{
					io << "<none>\n";
				}
				break;
			}
		case 'n':
			pos = keys_pos[key];
			if (pos <= 0 && pos_string[pos] != key) {
				prev_pos = -1;
			}
			else {
				prev_pos = get_next_pos(pos_string, pos, key_counter);
			}
			if (prev_pos != -1) {
				io << ht[pos_string[prev_pos]] << "\n";
			}
			else
			{
				io << "<none>\n";
			}
			break;
		case 'g':
			element = ht[key];
			if (!element.empty()) {
				io << element << "\n";
			}
			else {
				io << "<none>\n";
			}
			break;
		case 'd':
			ht[key].assign("");
			if (keys_pos[key] == -1 || (keys_pos[key] == 0 && pos_string[0] != key)) {

			}
			else {
				pos_string[keys_pos[key]] = "";
			}
			keys_pos[key] = -1;
			break;
		default:
			break;
		}
	}

	return 0;
}