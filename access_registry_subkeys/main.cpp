#include <stdio.h>
#include <Windows.h>
#include <winreg.h>
#include <winerror.h>

int main()
{
	HKEY registry_key_handle = NULL;
	char reg_path[] = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\LanguagePack";
	LSTATUS status_reg_op = RegOpenKeyExA(HKEY_LOCAL_MACHINE, (LPCSTR)reg_path, 0, KEY_READ, &registry_key_handle);

	if (status_reg_op != ERROR_SUCCESS)
	{
		printf("Error whilst trying to open key\n");
		return -5;
	}

	printf("Subkeys for key {%s} is:\n", reg_path);

	char subkey_name[256] = { 0 };
	DWORD name_len = 256;
	DWORD subkey_idx = 0;

	while (RegEnumKeyExA(registry_key_handle, subkey_idx, subkey_name, &name_len, NULL, NULL, NULL, NULL) != ERROR_NO_MORE_ITEMS)
	{
		printf("\t%d. %s\n", subkey_idx+1, subkey_name);
		subkey_idx+=1;
		name_len = 256;
	}

	return 0;
}