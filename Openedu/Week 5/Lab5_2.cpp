#include "edx-io.hpp"
using namespace std;

//Структура хранит в себе введённое значение(приоритет) и номер строки, в которой оно было введено
struct number {
	long value;
	long input_time;
};

void swop(number* a, number* b) {
	number temp = *a;
	*a = *b;
	*b = temp;
}

//Обход кучи снизу с i-того элемента, нахождение его места в куче
void heapifyUp(number* array, long i, long* array_of_positions) {
	//Позиция родительского для i-того элемента в куче
	long parent = i / 2 - (1 - i % 2);
	//Пока не добрались до корня и пока родитель больше
	while (i != 0 && array[i].value < array[parent].value) {
		//Меняем местами ребёнка и родителя, сохраняя их позиции в массиве позиций
		array_of_positions[array[i].input_time] = parent;
		array_of_positions[array[parent].input_time] = i;
		swop(&array[i], &array[parent]);
		//Переопределяем местоположение элемента и его родителя
		i = parent;
		parent = i / 2 - (1 - i % 2);
	}
}

//Восстановление кучи сверху
void heapifyDown(number* array, long tail, long* array_of_positions) {
	//Позиция текущего элемента
	long position = 0;
	//Позиции его детей
	long left = 2 * (position + 1) - 1;
	long right = 2 * (position + 1);
	//Пока не дошли до конца очереди, проверяем, что хотя бы один ребёнок меньше родителя и при этом находится в очереди
	while (position != tail && ((array[position].value > array[left].value && left <= tail) || (array[position].value > array[right].value && right <= tail))) {
		//Находим наименьшего, при условии, что правый находится в очереди
		if (array[right].value < array[left].value && right <= tail) {
			//Меняем местами ребёнка и родителя, сохраняя их позиции в массиве позиций
			array_of_positions[array[position].input_time] = right;
			array_of_positions[array[right].input_time] = position;
			swop(&array[right], &array[position]);
			//Переопределяем позицию сортируемого элемента
			position = right;
		}
		else {
			array_of_positions[array[position].input_time] = left;
			array_of_positions[array[left].input_time] = position;
			swop(&array[left], &array[position]);
			position = left;
		}
		//Переопределяем детей сортируемого элемента
		left = 2 * (position + 1) - 1;
		right = 2 * (position + 1);
	}
}


int main() {
	long N;
	io >> N;
	//Очередь с приоритетами
	number* Queue = new number[N];
	long head = 0;
	long tail = -1;

	//Массив, индекс которого - номер строки, в которой ввели число, а значение - положение с очереди
	long* array = new long[N];
	
	char action;
	long a, temp;


	for (long i = 0; i < N; i++) {
		io >> action;
		switch (action)
		{
		case 'A':
			io >> a;
			//Добавляем в очередь структуру (значение, номер строки)
			Queue[++tail] = number{ a, i };
			//Записываем начальную позицию введённого числа
			array[i] = tail;
			//Располагаем наш элемент в куче по приоритету
			heapifyUp(Queue, tail, array);
			break;
		case 'X':
			if (head > tail) {
				io << '*' << '\n';
			}
			else {
				//Меняем местами первый и последний элемент, сохраняя при этом целостность массива array
				array[Queue[head].input_time] = tail;
				array[Queue[tail].input_time] = head;
				swop(&Queue[head], &Queue[tail]);

				io << Queue[tail--].value << '\n';

				//Восстанавливаем кучу
				heapifyDown(Queue, tail, array);
			}
			break;
		case 'D':
			io >> a;
			io >> temp;
			//Позиция элемента введённого в a-той строке сохранена в массиве array
			Queue[array[a - 1]].value = temp;
			//Располагаем измененный элемент в куче
			heapifyUp(Queue, array[a - 1], array);
			break;
		default:
			break;
		}

	}

	return 0;
}