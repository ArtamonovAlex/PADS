#include <fstream>
#include <queue>
#include <string>
#include <map>
using namespace std;


int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");

	queue<unsigned short> MainQueue = {};
	map<char, unsigned short> registers = {
		{'a', 0},
		{'b', 0},
		{'c', 0},
		{'d', 0},
		{'e', 0},
		{'f', 0},
		{'g', 0},
		{'h', 0},
		{'i', 0},
		{'j', 0},
		{'k', 0},
		{'l', 0},
		{'m', 0},
		{'n', 0},
		{'o', 0},
		{'p', 0},
		{'q', 0},
		{'r', 0},
		{'s', 0},
		{'t', 0},
		{'u', 0},
		{'v', 0},
		{'w', 0},
		{'x', 0},
		{'y', 0},
		{'z', 0}
	};
	map <string, long> labels;
	string *commands = new string[100001];
	//Получаем список команд
	long N = -1;
	while (!input.eof()) {
		input >> commands[++N];
		//Запоминаем все метки
		if (commands[N][0] == ':') {
			labels.insert(pair<string, long>(commands[N].substr(1), N));
		}
	}
	if (commands[N].empty()) {
		N--;
	}
	input.close();
	//Указатель на команду в списке
	long P = 0;
	unsigned short a, b;

	do {
		switch (commands[P][0])
		{
		case '+':
			a = MainQueue.front();
			MainQueue.pop();
			b = MainQueue.front();
			MainQueue.pop();
			MainQueue.push((a + b) % 65536);
			P++;
			break;
		case '-':
			a = MainQueue.front();
			MainQueue.pop();
			b = MainQueue.front();
			MainQueue.pop();
			MainQueue.push((a - b) % 65536);
			P++;
			break;
		case '*':
			a = MainQueue.front();
			MainQueue.pop();
			b = MainQueue.front();
			MainQueue.pop();
			MainQueue.push((a * b) % 65536);
			P++;
			break;
		case '/':
			a = MainQueue.front();
			MainQueue.pop();
			b = MainQueue.front();
			MainQueue.pop();
			if (b == 0) {
				MainQueue.push(0);
			}
			else {
				MainQueue.push(a / b);
			}
			P++;
			break;
		case '%':
			a = MainQueue.front();
			MainQueue.pop();
			b = MainQueue.front();
			MainQueue.pop();
			if (b == 0) {
				MainQueue.push(0);
			}
			else {
				MainQueue.push(a % b);
			}
			P++;
			break;
		case '>':
			a = MainQueue.front();
			MainQueue.pop();
			registers[commands[P][1]] = a;
			P++;
			break;
		case '<':
			MainQueue.push(registers[commands[P][1]]);
			P++;
			break;
		case 'P':
			if (commands[P].size() == 1) {
				output << MainQueue.front() << '\n';
				MainQueue.pop();
			}
			else {
				output << registers[commands[P][1]] << '\n';
			}
			P++;
			break;
		case 'C':
			if (commands[P].size() == 1) {
				output << (char)(MainQueue.front() % 256);
				MainQueue.pop();
			}
			else {
				output << (char)(registers[commands[P][1]] % 256);
			}
			P++;
			break;
		case ':':
			P++;
			break;
		case 'J':
			P = labels[commands[P].substr(1)] + 1;
			break;
		case 'Z':
			if (registers[commands[P][1]] == 0) {
				P = labels[commands[P].substr(2)] + 1;
			}
			else {
				P++;
			}
			break;
		case 'E':
			if (registers[commands[P][1]] == registers[commands[P][2]]) {
				P = labels[commands[P].substr(3)] + 1;
			}
			else {
				P++;
			}
			break;
		case 'G':
			if (registers[commands[P][1]] > registers[commands[P][2]]) {
				P = labels[commands[P].substr(3)] + 1;
			}
			else {
				P++;
			}
			break;
		case 'Q':
			P = N;
			P++;
			break;
		default:
			MainQueue.push(stoi(commands[P]));
			P++;
		}
		//Программа работает, пока не будет выполнена последняя команда
	} while (P <= N);
	output.close();

	return 0;
}