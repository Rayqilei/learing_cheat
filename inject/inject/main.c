#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void inject(int pID,const char * path)
{
	//通过pid来获取句柄
	HANDLE phd = OpenProcess(PROCESS_ALL_ACCESS, NULL, pID);
	if (phd == 0)
	{
		printf("OpenProcess raise Exception\n");
	}
	//在虚拟空间中申请一块地址给DLL
	LPVOID pReturnAddress = VirtualAllocEx(phd, NULL, strlen(path) + 1, MEM_COMMIT, PAGE_READWRITE);
	if (pReturnAddress == 0)
	{
		printf("VirtualAllocEx raise Exception\n");
		exit(1);
	}
	//写入路径到上一行的代码申请的内存中
	WriteProcessMemory(phd, pReturnAddress, path, strlen(path) + 1, NULL);

	//加载KERNEL，并且找到开始库文件中LoadLibrary的地址
	HMODULE mhd = LoadLibraryA("KERNEL32.DLL");
	if (mhd == NULL)
	{
		printf("LoadLibraryA raise Exception\n");
	}
	LPTHREAD_START_ROUTINE lpStartAddress = (LPTHREAD_START_ROUTINE)GetProcAddress(mhd, "LoadLibraryA");
	if (lpStartAddress == NULL)
	{
		printf("GetProcAddress raise Exception\n");
	}
	//创建远程的线程，并获取线程句柄
	HANDLE Thd = CreateRemoteThread(phd, NULL, 0, lpStartAddress, pReturnAddress, 0, NULL); 
	if (Thd == NULL)
	{
		printf("CreateRemoteThread raise Exception\n");
	}
	//等待信号,infinte为永久等待
	WaitForSingleObject(Thd, 2000);

	//free
	CloseHandle(Thd);
	CloseHandle(phd);
}




int main()
{
	//HANDLE hWindow =  FindWindowA("Valve001", "Counter-Strike");
	//if (hWindow == NULL)
	//{
	//	printf("FindWindow raise Exception\n");
	//	exit(1);
	//}
	//else
	//{
	//	printf("CS 's HWND is %p", hWindow);
	//}
	//DWORD pid = GetProcessId(hWindow);
	//if (pid == NULL)
	//{
	//	printf("GetProcessID raise Exception");
	//}
	const char* path = "C:\\Users\\Ray\\Desktop\\Github\\mydll\\Release\\zzzzzzzzzzzz.dll";
	inject(7832, path);
	system("pause");
	return 0;
}