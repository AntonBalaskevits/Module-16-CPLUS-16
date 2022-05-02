#include "chat.h"
#include "sha1.h"
#include <iostream>


void Chat::registerNewUser()
{


	std::string name;
	std::string login;
	std::string password;

	bool mainWhileLoopCondition = true; // while loop conditional variable
	while (mainWhileLoopCondition)
	{
		// getting input from user
		std::cout << "Please enter user credentials down below" << std::endl;
		std::cout << "Name     : ";
		std::cin >> name;
		std::cout << "Login    : ";
		std::cin >> login;
		std::cout << "Password : ";
		std::cin >> password;

		if (Chat::checkIfLoginExists(login)) // if login is not present in user_hash_table_ returns true
		{
			user_hash_table_.insert(std::pair<std::string, class User::User>
				(login, Chat::obtainHashFromPassword(password))); // step 1 : putting in User object

			std::map<std::string, class User::User>::iterator it = user_hash_table_.find(login);
			(*it).second.setName(name); // step 2 : setting up name

			user_count_++; // step 2: incrementing user count, to keep track of how many users are registered

			// outputing successful registration info
			std::cout << "\n";
			std::cout << "user name  : " << name << std::endl;
			std::cout << "user login : " << login << std::endl;
			std::cout << "registered successfully!" << std::endl;
			std::cout << "\n";

			mainWhileLoopCondition = Chat::yesNoContinueQuestion(); // step 4 : asking user if he/she wishes to continue?
		}
		else // login is already taken!
		{
			std::cout << "\n";
			std::cout << "This Login is already taken! Please use another login name." << std::endl;
			std::cout << "\n";
			mainWhileLoopCondition = Chat::yesNoContinueQuestion();
		}
	}
}

void Chat::startChat()
{
	chat_operator_->setHashTableRef(Chat::getPtrToHashTable());
	// passing a reference of a user_hash_table_ to ChatOperator

	std::cout << "\n";
	std::cout << "          *Chat 2.0 session started*" << std::endl;
	std::cout << "\n";

	std::map<std::string, class User>::iterator it_name;
	// for chat ending cout, to be able to show that user il logout

	bool mainWhileLoopCondition = true;
	while (mainWhileLoopCondition)
	{
		std::string login;
		std::string password;
		std::cout << "enter your login and password" << std::endl; // getting input from user
		std::cout << "login    : ";
		std::cin >> login;
		std::cout << "password : ";
		std::cin >> password;

		if (Chat::checkHashWhitPassword(login, password)) // checking login password, if true login successful
		{
			std::map<std::string, class User>::iterator it = user_hash_table_.find(login); // finding iterator

			it_name = it; // for chat ending message to cout when chat cycle is ended))

			std::cout << "user     : " << (*it).second.getName() << std::endl; // outputing some info
			std::cout << "successfully loged in!" << std::endl;
			std::cout << "\n";

			std::cout << "type in text here : "; // getting input from user
			std::string text;
			std::cin >> text;

			std::cout << "\n";
			std::cout << "choose all to send message to all," << std::endl;
			std::cout << "or type in specific name." << std::endl;
			std::cout << "type in recipient name here : ";
			std::string recipientName;
			std::cin >> recipientName;

			if (!Chat::checkIfRecipientNameExists(recipientName)) // filtering bad input
			{                                                     
				std::cout << "\n";
				std::cout << "error recipient name is absent in current data base!" << std::endl;

				mainWhileLoopCondition = Chat::yesNoContinueQuestion();
			}
			else
			{
				(*it).second.setEnvelope(recipientName, text); // saving the message in User::Envelope object
				try
				{
					chat_operator_->reciveEnvelope((*it).second.sendEnvelope()); // sending envelope to chat_operator
				}
				catch (const char* exception)
				{
					std::cout << exception << std::endl;
					// exception if recive envelope fill fail
				}

				if (recipientName == "all") // this part off cycle is dedicated to all recipients
				{
					//std::map<std::string, class User>::iterator it2 = user_hash_table_.find(login);
					chat_operator_->sendEnvelopeToAllUsers((*it).second.getName());
					// sending a copy to all users excluding sender name

					Chat::displayRecipients((*it).second.getName());

					std::cout << "to read message please provide your login and password" << std::endl;
					std::cout << "login    : ";
					std::cin >> login;
					std::cout << "password : ";
					std::cin >> password;
					// obteining recipient login

					std::map<std::string, class User>::iterator it2 = user_hash_table_.find(login);

					bool loginPassowordLoop = true;
					if (Chat::checkHashWhitPassword(login, password)) // final login login/password to check to be abble to read message
					{
						(*it2).second.displayRecivedEnvelopeToUserInfo();
						(*it2).second.openTheEnvelope();

						if (Chat::yesNoContinueQuestion())
						{
							// logical questions to user
							// if user choses yes 

							//loginPassowordLoop = false;
							mainWhileLoopCondition = true;
						}
						else
						{
							mainWhileLoopCondition = false;
							break;
						}
					}
					else
					{
						std::cout << std::endl;
						std::cout << "error : recipient name is absent from current data base!" << std::endl;
						std::cout << "\n";

						if (Chat::yesNoContinueQuestion())
						{
							mainWhileLoopCondition = true;
						}
						else
						{
							break;
						}
					}

					mainWhileLoopCondition = false;
					break;
				}
				else
				{
					std::map<std::string, class User>
						::iterator it2;

					it2 = user_hash_table_.find(Chat::findRecipientLoginByName(recipientName));
					// searcing for user login by name . name acts like address I suppose

					(*it2).second.reciveEnvelope(chat_operator_->sendEnvelope(recipientName));
					// after name found chat_operator sends envelope to recipient 

					bool loginPassowordLoop = true;
					while (loginPassowordLoop)
					{
						(*it2).second.displayRecivedEnvelopeToUserInfo();
						std::cout << "to read message please provide your login and password" << std::endl;
						std::cout << "login    : ";
						std::cin >> login;
						std::cout << "password : ";
						std::cin >> password;
						// obteining recipient login 

						if (Chat::checkHashWhitPassword(login, password)) // final login login/password to check to be abble to read message
						{
							(*it2).second.openTheEnvelope();

							if (Chat::yesNoContinueQuestion())
							{
								loginPassowordLoop = false;
								mainWhileLoopCondition = true;
							}
							else
							{
								mainWhileLoopCondition = false;
								break;
							}
						}
						else
						{
							std::cout << "login or password is incorrect!" << std::endl;
							if (Chat::yesNoContinueQuestion())
							{
								loginPassowordLoop = true;
							}
							else
							{
								break;
							}
						}
					}
				}
			}			
		}
		else
		{
			std::cout << "login or password is incorrect.Would you like try again ?" << std::endl;
			mainWhileLoopCondition = Chat::yesNoContinueQuestion();
		}
	}

	if (it_name != user_hash_table_.end())
	{
		std::cout << "user : " << (*it_name).second.getName() << " left the Chat" << std::endl;
	}
	else
	{
		std::cout << "\n";
		std::cout << "user login or password was incorrect." << std::endl;
		std::cout << "chat is unable to start whitout correct login and password." << std::endl;
		std::cout << "\n";
		// this message will be shown if user fails to input correct login or password
		// in the beginning of chat session
	}

	std::cout << "would you like to Continue Chat under diffirent login?" << std::endl;
	
	
	if (Chat::yesNoContinueQuestion())
	{
		Chat::startChat();
	}
	else
	{	
		std::cout << "chat ended. Thanks see u next time" << std::endl;
	}
}

bool Chat::checkHashWhitPassword(const std::string& login, const std::string& password)
{
	char* passwordCopyFromString = new char[password.size() + 1]; // copy of chars array from string
	for (int i = 0; i < password.size(); i++)
	{
		passwordCopyFromString[i] = password[i]; // copying chars from string
	}
	// creating a copy of chars from std::string password
	// becouse sha1(char* message, uint msize_bytes) takes in char* as a first parameter

	uint* hash = sha1(passwordCopyFromString, sizeof(password.size()) - 1); // obtaining hash 
	delete[] passwordCopyFromString; // deleting the copy

	std::map<std::string, class User::User>::iterator it = user_hash_table_.find(login);

	if (it != user_hash_table_.end())
	{
		int check = 0; // counter that checks user hash whit hash from input password
		for (int i = 0; i < 5; i++)
		{
			uint* UserHash = (*it).second.getHash(); // obtaining hash from user object 

			if (UserHash[i] == hash[i]) // compare hashes
			{
				check++;
			}
		}
		if (check == 5)
		{
			return true; // hash matches input password
		}
		else
		{
			return false; // hash is not matching
		}
	}
	else
	{
		return false; // if login is not found returns false
	}
}

bool Chat::checkIfLoginExists(const std::string& login)
{
	std::map<std::string, class User::User>::iterator it = user_hash_table_.find(login);

	if (it == user_hash_table_.end())
	{
		return true; // login is not exists
	}
	else
	{
		return false; // login exists
	}
}

uint* Chat::obtainHashFromPassword(const std::string& password)
{
	char* passwordCopyFromString = new char[password.size() + 1]; // copy of chars array from string
	for (int i = 0; i < password.size(); i++)
	{
		passwordCopyFromString[i] = password[i]; // copying chars from string
	}
	// creating a copy of chars from std::string password
	// becouse sha1(char* message, uint msize_bytes) takes in char* as a first parameter

	uint* hash = sha1(passwordCopyFromString, sizeof(password.size()) - 1); // obtaining hash 
	delete[] passwordCopyFromString; // deleting the copy

	return hash; // returning hash
}

bool Chat::yesNoContinueQuestion() // simple logical yes/no function
{
	char yesNo;
	std::cout << "enter 'y' to continue or 'n' to quit : ";
	std::cin >> yesNo;

	switch (yesNo)
	{
	case 'y':
		return true;
		break;
	case 'n':
		return false;
		break;
	default:
		std::cout << "You made illegal choice. Please try again" << std::endl;
		Chat::yesNoContinueQuestion();
		break;
	}
}

std::map<std::string, class User>* Chat::getPtrToHashTable()
{
	return ptr_to_hash_table_;
}

std::string Chat::findRecipientLoginByName(const std::string& recipientName)
{
	std::map<std::string, class User>::iterator it = user_hash_table_.begin();

	for (; it != user_hash_table_.end(); it++)
	{
		if ((*it).second.getName() == recipientName)
		{
			return (*it).first; // if found returns login
		}
	}

	return "login_not_found";
}

void Chat::displayRecipients(const std::string& excludingSenderName)
{
	std::map<std::string, class User>::iterator it = user_hash_table_.begin();

	for (; it != user_hash_table_.end(); it++)
	{
		if ((*it).second.getName() == excludingSenderName)
		{
			// if name of user from who the message is send will match
			// it will skip that user, to avoid sender name being displayed
			continue;
		}
		if (it != user_hash_table_.end())
		{
			std::cout << "\n";
			std::cout << "user name : " << (*it).second.getName() << std::endl;
		}
		else
		{
			break;
		}
	}
	std::cout << std::endl;
}

bool Chat::checkIfRecipientNameExists(const std::string& recipientName)
{
	if (recipientName == "all")
	{
		return true;
	}

	std::map<std::string, class User>::iterator it = user_hash_table_.begin();

	for (; it != user_hash_table_.end(); it++)
	{
		if (recipientName == (*it).second.getName())
		{
			return true;
		}
	}

	return false;
}

void Chat::autoRegisterSomeRandomUsers(const std::string* logins, const std::string* passwords,
	const std::string* names)
{
	std::map<std::string, class User>::iterator it;

	for (int i = 0; i < logins->size(); i++)
	{
		if (Chat::checkIfLoginExists(logins[i]))
		{
			user_hash_table_.insert(std::pair<std::string, class User::User>(logins[i],
				Chat::obtainHashFromPassword(passwords[i])));

			it = user_hash_table_.find(logins[i]);

			if (it != user_hash_table_.end())
			{
				(*it).second.setName(names[i]);
				user_count_++;
			}
		}
	}
}

bool Chat::chatMenu()
{
	std::cout << "\n";
	std::cout << "         *Chat 2.0 menu*" << std::endl;
	std::cout << "enter '1' to register new user" << std::endl;
	std::cout << "enter '2' to start Chat" << std::endl;
	std::cout << "enter '0' to quit" << std::endl;
	int choice = 0;
	std::cout << "enter your choice here : ";
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		Chat::registerNewUser();
		return true;
		break;
	case 2:
		Chat::startChat();
		return true;
		break;
	case 0:
		return false;
		break;
	default:
		std::cout << "you made illegal choice. Please try again." << std::endl;
		Chat::chatMenu();
		break;
	}
}

