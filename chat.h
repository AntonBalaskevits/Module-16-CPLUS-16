#pragma once

#include <map>
#include <utility>
#include <memory>
#include <string>
#include "User.h"
#include "sha1.h"
#include "chat_operator.h"

class Chat
{
public:
	Chat()
	{
		ChatOperator* newOperator = new ChatOperator;
		chat_operator_ = newOperator;
	}
	~Chat() 
	{
		ptr_to_hash_table_ = nullptr;
	};

	void registerNewUser();
	void startChat(); // main function where chat works

	bool checkHashWhitPassword(const std::string& login, const std::string& password);
	// checks login and password and if its matches return true
	bool checkIfLoginExists(const std::string& login);
	// if login is not present in user_hash_table return true
	uint* obtainHashFromPassword(const std::string& password);
	// obtaining hash from password using sha1()
	bool yesNoContinueQuestion();
	// simple logical function that can be reused 

	std::map<std::string, class User>* getPtrToHashTable();
	// sends user_hash_table_ reference to ChatOperator

	std::string findRecipientLoginByName(const std::string& recipientName);

	void displayRecipients(const std::string& excludingSenderName);

	bool checkIfRecipientNameExists(const std::string& recipientName);

	void autoRegisterSomeRandomUsers(const std::string* logins, const std::string* passwords,
		const std::string* names);

	bool chatMenu();

private:
	ChatOperator* chat_operator_ = nullptr;
	// recives and send messeges from and to users.
	// the idea was to create mail operator like in real world
	// when the mail company recives mail and then sends it to recipient

	std::map<std::string, class User> user_hash_table_;
	// data base for registred users

	std::map<std::string, class User>* ptr_to_hash_table_ = &user_hash_table_;
	// this ptr is used to gain access to a user_hash_table
	// in class ChatOperator

	int user_count_ = 0;
	// counter for registered users
};
