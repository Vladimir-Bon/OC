#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	int n = atoi(argv[1]);
	int* array = new int[n];
	for (int i = 0; i < n; i++) {
		array[i] = atoi(argv[i + 2]);
		cout << array[i] << " ";
	}
	cout << "\n";
	int summ = 0;
	for (int i = 0; i < n; i++) {
		summ += array[i];
	}
	cout << "Summ " << summ;
	cin >> n;
	return 0;
}
