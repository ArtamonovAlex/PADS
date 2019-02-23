#include <fstream>
using namespace std;

int main() {

	int n;

	//���� ����� � ������ �������
	ifstream input("input.txt");
	input >> n;
	long* a = new long[n];
	for (int i = 0; i < n; i++) {
		input >> a[i];
	}
	input.close();

	ofstream output("output.txt");

	//������ ������� ������ ������� �� �����
	output << 1 << " ";

	int j;
	long temp;

	//�������� ���������� ���������
	for (int i = 1; i < n; i++) {
		j = i;
		while (j != 0 && a[j] < a[j - 1]) {
			temp = a[j];
			a[j] = a[j - 1];
			a[j - 1] = temp;
			j--;
		}
		//� ������� ������ � 0, � � ������ ������ ���� � 1
		output << j + 1;
		//����� ������� ����� ����� ���������� ������ ������ ������
		if (i != n - 1) output << " ";
	}
	//��������������� ������ ������ ���������� � ����� ������
	output << endl;

	//����� �������
	for (int i = 0; i < n; i++) {
		output << a[i];
		if (i != n - 1) output << " ";
	}

	output.close();

	return 0;
}