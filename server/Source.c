#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 200

int main()
{
	system("chcp 1251 > null");
	LPSTR lpstrPipeName = L"\\\\.\\pipe\\MyPipe"; 
	HANDLE hNamePipe; // дескриптор файла
	BOOL flag_otvet = TRUE;
	char message[SIZE_BUFFER]; 
	DWORD size_buffer = SIZE_BUFFER; // размер буфера 
	DWORD actual_written; // сколько на самом деле было записано байт
	LPWSTR buffer = &message; 
	DWORD actual_readen; // сколько на самом деле было прочитано байт
	BOOL isSuccess;
	BOOL SuccessRead;
	while (TRUE)
	{

		hNamePipe = CreateFile(
			lpstrPipeName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
		);
		DWORD dwMode = PIPE_READMODE_MESSAGE; //перекл в режим чтения и обратно
		BOOL isSuccess = SetNamedPipeHandleState( //проверка доступа
			hNamePipe,
			&dwMode,
			NULL,
			NULL
		);
		if (!isSuccess)
		{
			printf("\nсервер не отвечает\n");
			flag_otvet = TRUE;
		}
		else
		{
			if (flag_otvet)
			{
				//месседжер
				//printf("\nвведите сообщение для сервера:\n");

				//бот/
				printf("\nвведите число для сервера:\n");

				gets(message);
				buffer = &message;
				WriteFile(hNamePipe, buffer, size_buffer, &actual_written, NULL); // запись в канал
				flag_otvet = FALSE;

			}
			//читать с серваера
			SuccessRead = ReadFile(hNamePipe, buffer, SIZE_BUFFER, &actual_readen, NULL);
			if (SuccessRead)
			{
				printf("\nОтвет:\n");
				printf(buffer);
				printf("\n");
				flag_otvet = TRUE;
			}
		}
		Sleep(100);
		CloseHandle(hNamePipe);
	}


}

