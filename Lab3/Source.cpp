#include <Windows.h>
#include <process.h>
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

CRITICAL_SECTION cs;
HANDLE event1, event2;


struct Array {
	char* array;
	int length;
	int k;
	char sum = 0;

	Array(char* arr, int n, int k) {
		array = arr;
		length = n;
		this->k = k;
	}

	Array(Array* copy) {
		array = copy->array;
		length = copy->length;
		this->k = copy->k;
	}
};


DWORD WINAPI summElement(LPVOID value)
{
	EnterCriticalSection(&cs);
	WaitForSingleObject(event2, INFINITE);
	Array* Arr = (Array*)value;
	for (int i = 0; i < Arr->k; i++) {
		Arr->sum += Arr->array[i];
	}
	Arr->sum /= Arr->k;
	LeaveCriticalSection(&cs);
	return 0;
}

bool comp(char i, char j) { return (i < j); }

DWORD WINAPI work(LPVOID value)
{
	Array* Arr = (Array*)value;
	sort(Arr->array, Arr->array + Arr->k, comp);
	cout << "Enter sleep time\n";
	int s;
	cin >> s;
	char* array = new char[Arr->length];
	int t = 0;
	for (int i = 0; i < Arr->k; i++) {
		if (Arr->array[i] != Arr->array[i + 1] && Arr->array[i] != Arr->array[i - 1]) {
			array[t] = Arr->array[i];
			++t;
			Sleep(s);
		}
	}
	for (int i = 0; i < Arr->k; i++) {
		int count = 0;
		if (Arr->array[i] == Arr->array[i + 1])
			for (int j = i; Arr->array[j] == Arr->array[i] && j < Arr->k; j++, t++, count++)
				array[t] = Arr->array[j];
		if (count > 0)
			count--;
		i += count;
		Sleep(s);
	}
	for (int i = Arr->k; i < Arr->length; i++) {
		array[i] = Arr->array[i];
	}
	Arr->array = array;
	SetEvent(event1);
	return 0;
}


int main() {
	cout << "Enter dimension of array\n";
	int n;
	cin >> n;
	cout << "Enter elements of array\n";
	char* array = new char[n];
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}
	event1 = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (event1 == NULL)
		return GetLastError();
	event2 = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (event2 == NULL)
		return GetLastError();
	InitializeCriticalSection(&cs);
	int k;
	cout << "Enter k\n";
	cin >> k;
	Array* Arr = new Array(array, n, k);
	HANDLE hThread;
	DWORD IDThread;
	HANDLE hThread2;
	DWORD IDThread2;
	hThread = CreateThread(NULL, 0, work, (void*)Arr, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();
	hThread2 = CreateThread(NULL, 0, summElement, (void*)Arr, 0, &IDThread2);
	if (hThread2 == NULL)
		return GetLastError();
	WaitForSingleObject(event1, INFINITE);
	cout << "New array\n";
	for (int i = 0; i < Arr->k; i++) {
		cout << Arr->array[i] << " ";
	}
	cout << '\n';
	SetEvent(event2);
	EnterCriticalSection(&cs);
	cout << "Summ\n";
	cout << Arr->sum << '\n';
	LeaveCriticalSection(&cs);
	DeleteCriticalSection(&cs);
	cout << "Array from k\n";
	for (int i = Arr->k; i < Arr->length; i++) {
		cout << Arr->array[i] << " ";
	}
	CloseHandle(hThread);
	CloseHandle(hThread2);
}