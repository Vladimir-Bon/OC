#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

int main()
{
	HANDLE hNamedPipe;
	SECURITY_ATTRIBUTES sa; // атрибуты защиты
	SECURITY_DESCRIPTOR sd; // дескриптор защиты
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE; // дескриптор канала ненаследуемый
	// инициализируем дескриптор защиты
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	// устанавливаем атрибуты защиты, разреша€ доступ всем пользовател€м
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	sa.lpSecurityDescriptor = &sd;
	hNamedPipe = CreateNamedPipe(
		"\\\\.\\pipe\\pipe",
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_WAIT, // синхронна€ передача сообщений
		1, // максимальное количество экземпл€ров канала
		0, // размер выходного буфера по умолчанию
		0, // размер входного буфера по умолчанию
		INFINITE, // клиент ждет св€зь бесконечно долго
		&sa // защита по умолчанию
	);
	// провер€ем на успешное создание
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		cerr << "Creation of the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any char to finish server: ";
		_getch();
		return 0;
	}
	cout << "The server is waiting for connection with a client.\n";
	if (!ConnectNamedPipe(hNamedPipe, // дескриптор канала
		(LPOVERLAPPED)NULL // св€зь синхронна€
	))
	{
		cerr << "The connection failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		_getch();
		return 0;
	}
	cout << "Input length of massiv\n";
	int n;
	cin >> n;
	cout << "Input N and M\n";
	int N, M;
	cin >> N;
	cin >> M;
	long* mass = new long[n];
	DWORD dwBytesWritten;
	if (!WriteFile(hNamedPipe, &n, sizeof(n), &dwBytesWritten, NULL))
	{
		_cputs("Write to file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	WriteFile(hNamedPipe, &N, sizeof(N), &dwBytesWritten, NULL);
	WriteFile(hNamedPipe, &M, sizeof(M), &dwBytesWritten, NULL);
	DWORD dwBytesRead;
	for (int i = 0; i < n; i++) {
		if (!ReadFile(hNamedPipe, &mass[i], sizeof(mass[i]), &dwBytesRead, NULL))
		{
			_cputs("Read from the pipe failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
		cout << mass[i] << " ";
	}
	CloseHandle(hNamedPipe);
	_cputs("\nPress \"q\" to exit.\n");
	while (1) {
		char ch = _getch();
		if (ch == 81 || ch == 113)
			return 0;
	}
}