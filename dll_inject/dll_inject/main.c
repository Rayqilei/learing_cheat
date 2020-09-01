#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void inject(int pid)
{
	HANDLE phd = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);


	HMODULE mhd = GetModuleHandleA("kernel32.dll");

	LPTHREAD_START_ROUTINE lpStartAddress = (LPTHREAD_START_ROUTINE)GetProcAddress(mhd, "LoadLibraryA");

	CreateRemoteThread(phd, NULL, 0, lpStartAddress, MEMORY, 0, NULL); // lpStartAddress : LPTHREAD_START_ROUTINE



}




int main()
{


	system("pause");
	return 0;
}