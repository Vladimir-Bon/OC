#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

HANDLE A, A1, B, B1, endReader;
HANDLE hSemaphore;

int main(int argc, char* argv[])
{
	A = CreateEvent(NULL, FALSE, FALSE, "A");
	if (A == NULL)
		return GetLastError();
	B = CreateEvent(NULL, FALSE, FALSE, "B");
	if (B == NULL)
		return GetLastError();
	A1 = CreateEvent(NULL, FALSE, FALSE, "A1");
	if (A1 == NULL)
		return GetLastError();
	B1 = CreateEvent(NULL, FALSE, FALSE, "B1");
	if (B1 == NULL)
		return GetLastError();
	endReader = CreateEvent(NULL, FALSE, FALSE, "endR");
	if (endReader == NULL)
		return GetLastError();
	hSemaphore = CreateSemaphore(NULL, 2, 2, "SemaphoreR");
	if (hSemaphore == NULL)
		return GetLastError();

	int n = atoi(argv[0]);
	int m_count = atoi(argv[1]);
	cout << "Reader #" << n << "\n";
	WaitForSingleObject(hSemaphore, INFINITE);
	cout << "active" << endl;
	HANDLE mass[] = { A, B };
	for (int i = 0; i < m_count; i++)
	{
		int ind = WaitForMultipleObjects(2, mass, FALSE, INFINITE) - WAIT_OBJECT_0;
		if (ind == 0)
		{
			cout << "Get message A from Writer\n";
			SetEvent(A1);
		}
		else if (ind == 1)
		{
			cout << "Get message B from Writer\n";
			SetEvent(B1);
		}
	}
	cout << "Completion of work\n";
	ReleaseSemaphore(hSemaphore, 1, NULL);
	CloseHandle(A);
	CloseHandle(B);
	WaitForSingleObject(endReader, INFINITE);
	return 0;
}