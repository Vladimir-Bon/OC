#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <iostream>
using namespace std;

int main() {
	HANDLE A, A1, B, B1, endWriter, endReader;
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
	endWriter = CreateEvent(NULL, FALSE, FALSE, "endW");
	if (endWriter == NULL)
		return GetLastError();
	endReader = CreateEvent(NULL, FALSE, FALSE, "endR");
	if (endReader == NULL)
		return GetLastError();
	char lpszAppNameW[] = "Lab4_Writer.exe";
	char lpszAppNameR[] = "Lab4_Reader.exe";
	int n, m_count;
	cout << "Number of process\n";
	cin >> n;
	cout << "Number of messages\n";
	cin >> m_count;
	HANDLE* Readers = new HANDLE[n];
	HANDLE* Writers = new HANDLE[n];
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	for (int i = 0; i < n; i++) {
		char* ch = new char[1];
		char* lpCommLine = new char[1];
		lpCommLine = strcpy(lpCommLine, "");
		ch = _itoa((i + 1), ch, 10);
		lpCommLine = strcat(lpCommLine, ch);
		ch = _itoa(m_count, ch, 10);
		lpCommLine = strcat(lpCommLine, " ");
		lpCommLine = strcat(lpCommLine, ch);
		if (!CreateProcess(lpszAppNameW, lpCommLine, NULL, NULL, FALSE,
			CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
		{
			_cputs("The new process is not created.\n");
			_cputs("Check a name of the process.\n");
			_cputs("Press any key to finish.\n");
			return 0;
		}
		Writers[i] = piApp.hProcess;
		if (!CreateProcess(lpszAppNameR, lpCommLine, NULL, NULL, FALSE,
			CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
		{
			_cputs("The new process is not created.\n");
			_cputs("Check a name of the process.\n");
			_cputs("Press any key to finish.\n");
			return 0;
		}
		Readers[i] = piApp.hProcess;
	}
	HANDLE mass[] = { A1, B1 };
	for (int i = 0; i < n * m_count; i++)
	{
		int ind = WaitForMultipleObjects(2, mass, FALSE, INFINITE) - WAIT_OBJECT_0;
		if (ind == 0)
		{
			cout << "Get message A from Reader\n";
		}
		if (ind == 1)
		{
			cout << "Get message B from Reader\n";
		}
	}
	cout << "Input any key to close processes\n";
	_getch();
	SetEvent(endWriter);
	SetEvent(endReader);
	CloseHandle(A);
	CloseHandle(B);
	CloseHandle(A1);
	CloseHandle(B1);
	CloseHandle(endWriter);
	CloseHandle(endReader);
	cout << "All processes have shut down\n";
	for (int i = 0; i < n; i++)
	{
		CloseHandle(Writers[i]);
		CloseHandle(Readers[i]);
	}
	return 0;
}