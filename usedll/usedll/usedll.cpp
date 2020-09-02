// usedll.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

int main()
{
    std::cout << "Hello World!\n";
    HMODULE hModule = LoadLibraryA("mydll.dll");

    if (hModule != NULL)
    {
        std::cout << "Calling DLL success.\n";
        void(*function)() = (void(*)())GetProcAddress(hModule, "fffff");
        function();
    }
    //FreeLibrary(hModule);
    system("pause");
    return 0;
}
