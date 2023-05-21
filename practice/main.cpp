#include <iostream>
#include "memory.h"

//const auto localPlayer1 = mem.Read<uintptr_t>(Base + 0xa4c);
//const auto localPlayer2 = mem.Read<uintptr_t>(Base + 0x464);
//const auto localPlayer3 = mem.Read<uintptr_t>(Base + 0x454);

bool b_sprint = false, b_battery = false, b_health = false, b_jump = false;

void menu()
{
	system("cls");
	std::cout << "\n [ F1 ] Always sprint       -> "		<< std::boolalpha << b_sprint << std::endl;
	std::cout << " [ F2 ] Unlimited batteries -> "		<< std::boolalpha << b_battery << std::endl;
	std::cout << " [ F3 ] Unlimited health    -> "		<< std::boolalpha << b_health << std::endl;

	std::cout << "\n [ UP ] Teleport up \n";
	std::cout << " [ DOWN ] Teleport down \n";
}

int main()
{

	Memory mem = Memory{ "OLGame.exe" };
	menu();
	while (true)
	{
		const auto modulebase		= mem.GetModuleAddress("OLGame.exe");
		const auto Base				= mem.Read<uintptr_t>(modulebase + 0x2020F38);
		const auto localPlayer		= mem.Read<uintptr_t>(Base + 0x248);
		const auto health			= mem.Read<uint32_t>(localPlayer + 0x37c);

		if (GetAsyncKeyState(VK_F1)) { b_sprint		= !b_sprint;	menu(); Sleep(100); };
		if (GetAsyncKeyState(VK_F2)) { b_battery	= !b_battery;	menu(); Sleep(100); };
		if (GetAsyncKeyState(VK_F3)) { b_health		= !b_health;	menu(); Sleep(100); };
		if (GetAsyncKeyState(VK_F4)) { b_jump		= !b_jump;		menu(); Sleep(100); };

		if (b_sprint)	{ mem.Write<int8_t>(Base + 0xAfA, 1); }
		if (b_battery)	{ mem.Write<uint32_t>(Base + 0xaa0, 5000); mem.Write<uint32_t>(Base + 0xaa4, 5000); } 
		if (b_health)	{ mem.Write<uint32_t>(localPlayer + 0x380, 5000); }

		if (GetAsyncKeyState(VK_UP))
		{
			const auto previousY = mem.Read<float>(localPlayer + 0x88);
			mem.Write<float>(localPlayer + 0x88, previousY + 20.0);
		}

		if (GetAsyncKeyState(VK_LEFT))
		{
			const auto previousY = mem.Read<float>(localPlayer + 0x84);
			mem.Write<float>(localPlayer + 0x84, previousY + 20.0);
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			const auto previousY = mem.Read<float>(localPlayer + 0x80);
			mem.Write<float>(localPlayer + 0x80, previousY + 20.0);
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			const auto previousY = mem.Read<float>(localPlayer + 0x88);
			mem.Write<float>(localPlayer + 0x88, previousY - 20.0);
		}


		Sleep(1);
	}

	return 0; 
}