#include "edx-io.hpp";
#include <list>
using namespace std;

//Удаляет k-тый элемент списка list1
auto delete_list_elem(list<long long>& list1, int k)
{
	list<long long>::iterator it = list1.begin();
	std::advance(it, k); // <-- advance итерирует переданный итератор на k позиций
	if (it != list1.end())
	{
		return list1.erase(it); // <--- Вернет итератор на k+1 элемент, перед it нет *
	}
	return it;
}

//Возвращает позицию элемента со значением value, если он есть, в обратном случае возвращает -1
int find_list_elem(list<long long> list1, long long value) {
	int counter = 0;
	int size = list1.size();
	for (long long number : list1) {
		if (number == value) {
			break;
		}
		else {
			counter++;
		}
	}
	if (counter == size) {
		return -1;
	}
	return counter;
}

int main() {
	long N;
	io >> N;
	//Создаём массив листов - закрытая адресация
	list<long long>* ht = new list<long long>[N];

	char command;
	long long element;
	long hash;
	bool is_in_list;
	for (long i = 0; i < N; i++) {
		io >> command >> element;
		hash = abs(element) % N;
		switch (command)
		{
		case 'A':
			//Если такое значение уже есть в списке, то ничего не делаем, если нет, то вставляем в начало списка
			is_in_list = false;
			for (long long number : ht[hash]) {
				if (number == element) {
					is_in_list = true;
				}
			}
			if (!is_in_list) {
				ht[hash].push_front(element);
			}
			break;
		case 'D':
			//Если такое значение есть в списке - удаляем его
			if (!ht[hash].empty()) {
				int pos = find_list_elem(ht[hash], element);
				if (pos != -1) {
					delete_list_elem(ht[hash], pos);
				}
			}
			break;
		default:
			if (!ht[hash].empty()) {
				int pos = find_list_elem(ht[hash], element);
				if (pos != -1) {
					io << "Y\n";
					break;
				}
			}
			io << "N\n";
			break;
		}
	}

	return 0;
}