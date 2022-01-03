// CRC.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "CRC.hpp"

int main()
{
	auto oldCRC = CRCSecthion((PVOID)ApiWrapper::GetModuleAddress(0), ".text");
	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			std::cout << "CRC ->\t " << CRCSecthion((PVOID)ApiWrapper::GetModuleAddress(0), ".text") << '\n';

			if (CRCSecthion((PVOID)ApiWrapper::GetModuleAddress(0), ".text") != oldCRC)
			{
				std::cout << "Patch detect!\n";
				std::cout << "CRC old ->\t " << oldCRC << '\n';
				std::cout << "CRC new ->\t " << CRCSecthion((PVOID)ApiWrapper::GetModuleAddress(0), ".text") << '\n';
				std::cin.get();
				break;

			}
			Sleep(500);
		}
	}
}
