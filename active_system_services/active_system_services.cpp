#include <iostream>
#include <Windows.h>
#include <winsvc.h>

int main()
{
    SC_HANDLE servicesManagerHandle;
    
    servicesManagerHandle = OpenSCManager(
        NULL,
        NULL,
        SC_MANAGER_ENUMERATE_SERVICE
    );

    BYTE services[256000] = { 0 };
    DWORD no_services = 0, bytes_needed = 0, resume_handle = 0;

    EnumServicesStatusExA(
        servicesManagerHandle,
        SC_ENUM_PROCESS_INFO,
        SERVICE_WIN32,
        SERVICE_ACTIVE,
        (LPBYTE)(services),
        256000,
        &bytes_needed,
        &no_services,
        &resume_handle,
        NULL
    );

    LPENUM_SERVICE_STATUS_PROCESSA services_metadata = (LPENUM_SERVICE_STATUS_PROCESSA)services;

    for (DWORD i = 0;i < no_services;i++)
    {
        std::cout << "Service Name: " << services_metadata[i].lpServiceName << "\n";
        std::cout << "Display Name: " << services_metadata[i].lpDisplayName << "\n";
        std::cout << "Process ID:   " << services_metadata[i].ServiceStatusProcess.dwProcessId << "\n";
        std::cout << "--------------------------------------------------\n";
    
    }

    CloseServiceHandle(servicesManagerHandle);

    return 0;
}

