#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;
//Находит сумму дистанций - разностей позиций каждого с каждым
//Формула: сумм(((n-1) - 2(i-1)) * pos[i - 1])
//i изменяется так, чтобы pos[i] > pos[i+1]
long long calculate_sum_distance(vector<long> positions) {
	long long sum = 0;
	long long temp;
	//Коэффициент слагаемого (n-1) - 2(i-1)
	long k = positions.size() - 1;
	for (long i = positions.size() - 1; i >= 0; i--) {
		temp = (long long)k * positions[i];
		sum += temp;
		k -= 2;
	}
	//Точки не включены, поэтому необходимо из каждой разности вычесть единицу
	for (long i = 1; i < positions.size(); i++)
	{
		sum -= i;
	}
	return sum;
}


int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");

	string P = "";
	string tmp;
	//Слепливаем строку в одну без пробелов
	while (!input.eof()) {
		input >> tmp;
		if (tmp != "") {
			P += tmp;
		}
		tmp = "";
	}
	//Ассоциативный массив списков, отсортированный по алфавиту
	map<char, vector<long>> letters;
	//Позицию каждой буквы в строке добавляем в соответствующий список
	for (long i = 0; i < P.length(); i++) {
		letters[P[i]].push_back(i);
	}
	long long counter = 0;
	//Для каждого списка с количесвом элементов > 1 находим сумму разностей его элементов
	for (char i = 'a'; i <= 'z'; i++) {
		if (letters.count(i) && letters[i].size() > 1) {
			counter += calculate_sum_distance(letters[i]);
		}
	}

	output << counter;
	return 0;
}