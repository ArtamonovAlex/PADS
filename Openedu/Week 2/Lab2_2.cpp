#include <fstream>
using namespace std;


//"�������" ��� ��������������� �� ����������� ������� � ���� ��������������� �� �����������
long* merge_arrays(long* array1, int length1, long* array2, int length2, long long &inversions) {
	int result_length = length1 + length2;
	long* result_array = new long[result_length];

	int i = 0;
	int j = 0;

	for (int counter = 0; counter < result_length; counter++) {
		if ((array1[i] <= array2[j] || j == length2) && i != length1) { //���� ������� "������" ������� ������ �������� "�������" ��� ������ ����������,
			result_array[counter] = array1[i];							//� ��� �������, ��� �� ���������� �����, ������� ������ ������� �������� �� ��������� �������
			i++;														//��������������� �������
		}
		else {															//� �������� ������ � �������������� ������ ����������� ������� ������� �������
			result_array[counter] = array2[j];
			inversions += length1 - i;									//��� "����������" �������� ������ ������� ����� ������ ����� �������� ������� �������
			j++;
		}
	}
	return result_array;
}

//��������� ������ ����������� �����
long* sort_array(long* array, int length, long long &inversions) {
	if (length == 1) {
		return array;
	}

	//������� ������� �� ��� ����������, ��� ������ <= �������
	int left_array_size, right_array_size;
	if (length % 2 == 1) {
		left_array_size = length / 2;
		right_array_size = length / 2 + 1;
	}
	else {
		left_array_size = length / 2;
		right_array_size = length / 2;
	}
	long* left_array = new long[left_array_size];
	long* right_array = new long[right_array_size];

	for (int i = 0; i < length; i++) {
		if (i < left_array_size) {
			left_array[i] = array[i];
		}
		else {
			right_array[i - left_array_size] = array[i];
		}
	}

	//����� ������� ��� ������� �� ���� ����������� ��� �� ����������
	left_array = sort_array(left_array, left_array_size, inversions);
	right_array = sort_array(right_array, right_array_size, inversions);

	//������� ��������������� �������� � ����
	return merge_arrays(left_array, left_array_size, right_array, right_array_size, inversions);
}

long* read_array_from_file(string file_name, int &size) {
	ifstream input(file_name);
	input >> size;
	long* array = new long[size];

	for (int i = 0; i < size; i++) {
		input >> array[i];
	}

	input.close();
	return array;
}

int main() {

	int size;

	long* array = read_array_from_file("input.txt", size);
	long long inversions = 0;

	array = sort_array(array, size, inversions);

	ofstream output("output.txt");
	output << inversions;
	output.close();
	return 0;
}