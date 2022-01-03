﻿#pragma once
#include "Struct.h"


namespace ApiWrapper
{
	__forceinline   int strlen(const char* string)
	{
		int cnt = 0;
		if (string)
		{
			for (; *string != 0; ++string) ++cnt;
		}
		return cnt;
	}
	__forceinline  int  memcmp(const void* s1, const void* s2, unsigned __int64 n)
	{
		if (n != 0)
		{
			const unsigned char* p1 = (unsigned char*)s1, * p2 = (unsigned char*)s2;
			do
			{
				if (*p1++ != *p2++) return (*--p1 - *--p2);
			} while (--n != 0);
		}
		return 0;
	}

      __forceinline  int wtolower(int c)
        {
            if (c >= L'A' && c <= L'Z') return c - L'A' + L'a';
            if (c >= L'À' && c <= L'ß') return c - L'À' + L'à';
            if (c == L'¨') return L'¸';
            return c;
        }
    __forceinline int wstricmp(const wchar_t* cs, const wchar_t* ct)
    {
        if (cs && ct)
        {
            while (wtolower(*cs) == wtolower(*ct))
            {
                if (*cs == 0 && *ct == 0) return 0;
                if (*cs == 0 || *ct == 0) break;
                cs++;
                ct++;
            }
            return wtolower(*cs) - wtolower(*ct);
        }
        return -1;
    } 

    DWORD64 GetModuleAddress(const wchar_t* modName)
    {
         
        LDR_DATA_TABLE_ENTRY* modEntry = nullptr;





#ifdef _WIN64
        PEB* peb = (PEB*)__readgsqword(0x60);

#else
        PEB* peb = (PEB*)__readfsdword(0x30);
#endif



        LIST_ENTRY head = peb->Ldr->InMemoryOrderModuleList;

        LIST_ENTRY curr = head;

        for (auto curr = head; curr.Flink != &peb->Ldr->InMemoryOrderModuleList; curr = *curr.Flink)
        {
            LDR_DATA_TABLE_ENTRY* mod = (LDR_DATA_TABLE_ENTRY*)CONTAINING_RECORD(curr.Flink, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

            if (mod->BaseDllName.Buffer)
            {
                if (wstricmp(modName, mod->BaseDllName.Buffer))
                { 
                    modEntry = mod;
                    break;
                }
            }
        } 
        return (DWORD64)modEntry->DllBase;

    }
}