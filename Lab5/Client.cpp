#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	HANDLE hWritePipe, hReadPipe;
	HANDLE hRead2;
	hRead2 = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Read2");
	hWritePipe = (HANDLE)atoi(argv[1]);
	hReadPipe = (HANDLE)atoi(argv[2]);
	int n, N, M;
	DWORD dwBytesRead;
	if (!ReadFile(hReadPipe, &n, sizeof(n), &dwBytesRead, NULL))
	{
		_cputs("Read from the pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	ReadFile(hReadPipe, &N, sizeof(N), &dwBytesRead, NULL);
	ReadFile(hReadPipe, &M, sizeof(M), &dwBytesRead, NULL);
	cout << "n: " << n << "\n";
	cout << "N: " << N << "\n";
	cout << "M: " << M << "\n";
	DWORD dwBytesWritten;
	for (int i = 0; i < n; i++) {
		long a = N + rand() % (M - N);
		cout << a << " ";
		if (!WriteFile(hWritePipe, &a, sizeof(a), &dwBytesWritten, NULL))
		{
			_cputs("Write to file failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
	}
	SetEvent(hRead2);
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hRead2);
	_cputs("\nPress \"q\" to exit.\n");
	while (1) {
		char ch = _getch();
		if (ch == 81 || ch == 113)
			return 0;
	}
}