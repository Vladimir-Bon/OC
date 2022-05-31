#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	HANDLE hNamedPipe;
	int n, N, M;
	DWORD dwBytesRead;
	hNamedPipe = CreateFile(
		"\\\\DESKTOP-STEPA\\pipe\\pipe", // имя канала
		GENERIC_READ | GENERIC_WRITE, // читаем и записываем в канал
		FILE_SHARE_READ | FILE_SHARE_WRITE, // разрешаем чтение и запись в канал
		(LPSECURITY_ATTRIBUTES)NULL, // защита по умолчанию
		OPEN_EXISTING, // открываем существующий канал
		FILE_ATTRIBUTE_NORMAL, // атрибуты по умолчанию
		(HANDLE)NULL // дополнительных атрибутов нет
	);
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		cerr << "Connection with the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any char to finish the client: ";
		_getch();
		return 0;
	}
	if (!ReadFile(hNamedPipe, &n, sizeof(n), &dwBytesRead, NULL))
	{
		_cputs("Read from the pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	ReadFile(hNamedPipe, &N, sizeof(N), &dwBytesRead, NULL);
	ReadFile(hNamedPipe, &M, sizeof(M), &dwBytesRead, NULL);
	cout << "n: " << n << "\n";
	cout << "N: " << N << "\n";
	cout << "M: " << M << "\n";
	DWORD dwBytesWritten;
	for (int i = 0; i < n; i++) {
		long a = N + rand() % (M - N);
		cout << a << " ";
		if (!WriteFile(hNamedPipe, &a, sizeof(a), &dwBytesWritten, NULL))
		{
			_cputs("Write to file failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
	}
	CloseHandle(hNamedPipe);
	_cputs("\nPress \"q\" to exit.\n");
	while (1) {
		char ch = _getch();
		if (ch == 81 || ch == 113)
			return 0;
	}
}