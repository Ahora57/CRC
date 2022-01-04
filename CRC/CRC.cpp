// CRC.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "CRC.hpp"


int main()
{
	auto oldCRC = CRC::CRCSecthion((PVOID)ApiWrapper::GetModuleAddress(0));
	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			ApiWrapper::printf(L"CRC ->\t %x\n", CRC::CRCSecthion((PVOID)ApiWrapper::GetModuleAddress(0)));

			if (CRC::CRCSecthion((PVOID)ApiWrapper::GetModuleAddress(0)) != oldCRC)
			{
				ApiWrapper::printf(L"Patch detect!\n");
				ApiWrapper::printf(L"CRC old ->\t %x\n", oldCRC);
				ApiWrapper::printf(L"CRC new ->\t %x\n", CRC::CRCSecthion((PVOID)ApiWrapper::GetModuleAddress(0)) );
				ApiWrapper::cin();
				break;

			}
			Sleep(500);
		}
	}
}
