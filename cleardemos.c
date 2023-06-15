#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(_WIN32) || defined(__WIN32)

#define CLEARDEMOS_IMPL_FOUND 1
#define WIN32_LEAN_AND_MEAN
#undef UNICODE
#undef _UNICODE
#include <windows.h>

bool ClearDemoFiles(size_t* res)
{
	WIN32_FIND_DATA findData;
	HANDLE handle = FindFirstFile("./*", &findData);
	
	if (handle == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	
	*res = 0;
	
	do
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			continue;
		}
		
		char* dot = strrchr(findData.cFileName, '.');
		
		if (dot && strcmp(dot, ".dem") == 0)
		{
			DeleteFile(findData.cFileName);
			++*res;
		}
	} while (FindNextFile(handle, &findData) != 0);
	
	FindClose(handle);
	return TRUE;
}

#endif

#ifndef CLEARDEMOS_IMPL_FOUND
#error couldn't find implementation
#endif

int main(void)
{
	size_t res;
	
	if (!ClearDemoFiles(&res))
	{
		printf("Error occured when trying to clear demo files.\n");
		return EXIT_FAILURE;
	}
	
	printf("Demo files cleared: %zi\n", res);
	
#if defined(_WIN32) || defined(__WIN32)
	system("PAUSE");
#endif
	return EXIT_SUCCESS;
}