#include <fstream>
using namespace std;

int main() {

	int n;

	ifstream input("input.txt");
	input >> n;

	//Инициализация двумерного массива, каждый элемент которого хранит состояние жителя в [x][1] и его идентификатор в [x][0]
	float** M = new float*[n];
	for (int i = 0; i < n; i++) {
		M[i] = new float[2];
		M[i][0] = i + 1;
		input >> M[i][1];
	}

	input.close();

	int j;
	float* temp;

	//Сортировка вставками
	for (int i = 1; i < n; i++) {
		j = i;
		while (j != 0 && M[j][1] < M[j - 1][1]) {
			temp = M[j];
			M[j] = M[j - 1];
			M[j - 1] = temp;
			j--;
		}
	}

	int middlePos = n / 2;
	int min = M[0][0];
	int middle = M[middlePos][0];
	int max = M[n - 1][0];

	ofstream output("output.txt");
	output << min << " " << middle << " " << max;
	output.close();

	return 0;
}