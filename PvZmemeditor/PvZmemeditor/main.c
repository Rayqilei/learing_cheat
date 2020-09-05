#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

static DWORD BaseAddr = 0x00755E0C;
static DWORD offset_1 = 0x868;
static DWORD offset_2 = 0x5578;

int main()
{
	//	窗口句柄
	HWND hGame = FindWindowA("MainWindow", "Plants vs. Zombies");
	if (hGame == NULL)
	{
		printf("Can't Find Game.\n");
		exit(1);
	}

	//	获得句柄的PID
	DWORD * dwDlg = NULL;
	GetWindowThreadProcessId(hGame, &dwDlg);
	if (&dwDlg == NULL)
	{
		printf("Can't get Game's PID.\n");
		exit(1);
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwDlg);
	if (hProcess == NULL)
	{
		printf("Can't get Game's HANDLE.\n");
		exit(1);
	}

	unsigned long temp = 0;
	unsigned value = 0;
	BOOL TF = ReadProcessMemory(hProcess, (void *)BaseAddr, &value, sizeof(DWORD), 0);
	if (TF == 0)
	{
		printf("BaseAddr \n");
		//exit(1);
	}

	unsigned long temp1 = 0;
	unsigned value1 = 0;
	TF = ReadProcessMemory(hProcess, (void*)(value + offset_1), &value1, sizeof(DWORD), 0);
	if (TF == 0)
	{
		printf("offset_1\n");
		//exit(1);
	}

	unsigned long temp2 = 0;
	unsigned value2 = 0;
	TF = ReadProcessMemory(hProcess, (void*)(offset_2 + value1), &value2, sizeof(DWORD), 0);
	if (TF == 0)
	{
		printf("offset_2\n");
		//exit(1);
	}
	//system("pause");
	printf("阳光值: %d\n",value2);


	//BOOL WriteProcessMemory(
	//	HANDLE  hProcess,
	//	LPVOID  lpBaseAddress,
	//	LPCVOID lpBuffer,
	//	SIZE_T  nSize,
	//	SIZE_T * lpNumberOfBytesWritten
	//);
	unsigned int ttt = 0;
	printf("输入你要修改的阳光值:");
	scanf_s("%d", &ttt);
	WriteProcessMemory(hProcess, (void*)(offset_2 + value1), &ttt, 4, 0);
	return 0;
}