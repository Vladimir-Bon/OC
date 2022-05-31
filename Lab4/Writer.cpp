#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

HANDLE A, B, endWriter;
HANDLE hMutex;

int main(int argc, char* argv[])
{
	A = CreateEvent(NULL, FALSE, FALSE, "A");
	if (A == NULL)
		return GetLastError();
	B = CreateEvent(NULL, FALSE, FALSE, "B");
	if (B == NULL)
		return GetLastError();
	endWriter = CreateEvent(NULL, FALSE, FALSE, "endW");
	if (endWriter == NULL)
		return GetLastError();
	hMutex = CreateMutex(NULL, FALSE, "MutexW");
	if (hMutex == NULL)
		return GetLastError();

	int n = atoi(argv[0]);
	cout << "Writer #" << n << endl;
	int m_count = atoi(argv[1]);
	char message;
	WaitForSingleObject(hMutex, INFINITE);
	cout << "Input A or B\n";
	for (int i = 0; i < m_count; i++) {
		cin >> message;
		if (message == 'A') SetEvent(A);
		else if (message == 'B') SetEvent(B);
		else i--;
	}
	cout << "Completion of work\n";
	ReleaseMutex(hMutex);
	CloseHandle(A);
	CloseHandle(B);
	WaitForSingleObject(endWriter, INFINITE);
	return 0;
}