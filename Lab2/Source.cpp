#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <iostream>
#include <ctime>
using namespace std;

int main() {
	char* lpszCommandLine = new char[255];
	lpszCommandLine[0] = '\0';
	strcat(lpszCommandLine, "Project2 ");
	int n;
	cout << "Please, enter the size of array" << "\n";
	cin >> n;
	char* temp = new char[255];
	_itoa(n, temp, 10);
	strcat(lpszCommandLine, strcat(temp, " "));
	int* array = new int[n];
	cout << "enter elements of arry" << "\n";
	for (int i = 0; i < n; i++) {
		cin >> array[i];
		sprintf(temp, "%d", array[i]);
		strcat(lpszCommandLine, strcat(temp, " "));
		cout << array[i] << " ";
	}
	cout << "\n";
	strcat(lpszCommandLine, ".exe");
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USEFILLATTRIBUTE;
	si.dwFillAttribute = BACKGROUND_BLUE;
	if (!CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
	{
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		return 0;
	}
	WaitForSingleObject(piApp.hProcess, INFINITE);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	return 0;
}