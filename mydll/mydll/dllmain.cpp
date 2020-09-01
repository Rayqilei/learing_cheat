// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

extern "C" __declspec(dllexport)void fffff();

void fffff()
{
    printf("Hello world\n");
}





BOOL APIENTRY DllMain( HMODULE hModule,         //      调用该模组的模组句柄
                       DWORD  ul_reason_for_call,//     调用我的原因
                       LPVOID lpReserved        //      保留位置
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        fffff();
        //  当进程接入的时候
    case DLL_THREAD_ATTACH:
        //  当线程接入的时候
        fffff();
    case DLL_THREAD_DETACH:
        //  当线程分离的时候
    case DLL_PROCESS_DETACH:
        //  当进程分离的时候
        break;
    }
    return TRUE;
}

