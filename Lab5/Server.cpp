#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

int main()
{
	char lpszComLine[80];
	HANDLE hRead2;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hWritePipe, hReadPipe;
	SECURITY_ATTRIBUTES sa;
	hRead2 = CreateEvent(NULL, FALSE, FALSE, "Read2");
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
	{
		_cputs("Create pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	cout << "Input length of massiv\n";
	int n;
	cin >> n;
	cout << "Input N and M\n";
	int N, M;
	cin >> N;
	cin >> M;
	long* mass = new long[n];
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	wsprintf(lpszComLine, "Project2.exe %d %d", (int)hWritePipe, (int)hReadPipe);
	if (!CreateProcess(NULL, lpszComLine, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi
	))
	{
		_cputs("Create process failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	DWORD dwBytesWritten;
	if (!WriteFile(hWritePipe, &n, sizeof(n), &dwBytesWritten, NULL))
	{
		_cputs("Write to file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	WriteFile(hWritePipe, &N, sizeof(N), &dwBytesWritten, NULL);
	WriteFile(hWritePipe, &M, sizeof(M), &dwBytesWritten, NULL);
	DWORD dwBytesRead;
	WaitForSingleObject(hRead2, INFINITE);
	for (int i = 0; i < n; i++) {
		if (!ReadFile(hReadPipe, &mass[i], sizeof(mass[i]), &dwBytesRead, NULL))
		{
			_cputs("Read from the pipe failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
		cout << mass[i] << " ";
	}
	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	CloseHandle(hRead2);
	_cputs("\nPress \"q\" to exit.\n");
	while (1) {
		char ch = _getch();
		if (ch == 81 || ch == 113)
			return 0;
	}
}