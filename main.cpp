#include "chat.h"
#include <memory>

int main()
{
	std::string logins[5] = { "anton", "julia", "lena", "serega", "ivan" };
	std::string passwords[5] = { "a", "j", "l", "s", "i" };
	std::string names[5] = { "anton", "julia", "lena", "serega", "ivan" };
	// auto register some random users so its easier to test chat

	Chat* chat = new Chat;

	chat->autoRegisterSomeRandomUsers(logins, passwords, names);

	std::cout << "\n";
	std::cout << "      *Welcome to Chat 2.0*" << std::endl;
	std::cout << "\n";

	bool chatOn = true;
	while (chatOn)
	{
		chatOn = chat->chatMenu();
	}

	delete chat;

	return 0;
}