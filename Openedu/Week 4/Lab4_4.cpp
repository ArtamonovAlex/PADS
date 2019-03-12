#include "edx-io.hpp"

using namespace std;


int main() {
	long N;
	io >> N;
	char action;
	//Очередь для чисел
	long* queue = new long[N];
	long offset = -1;
	long head = 0;
	//Очередь для наименьших чисел
	long *minQueue = new long[N];
	long minOffset = -1;
	long minHead = 0;

	for (long i = 0; i < N; i++) {
		io >> action;
		switch (action)
		{
		case '+':
			io >> queue[++offset];
			//Элемент вставляется в очередь для наименьших чисел таким образом, 
			//чтобы все элементы спереди были меньше него
			while (minOffset - minHead >= 0 && minQueue[minOffset] > queue[offset]) {
				minOffset--;
			}
			minQueue[++minOffset] = queue[offset];
			continue;
		case '-':
			//Если удяляется наименьший элемент (самый первый в очереди наименьших),
			//голова очереди сдвигается к следующему
			if (queue[head] == minQueue[minHead]) {
				minHead++;
			}
			head++;
			continue;
		case '?':
			//Ввыводится первый элемент в очереди наименьших
			io << minQueue[minHead] << '\n';
			continue;
		}

	}
	return 0;
}