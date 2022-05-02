#pragma once
#include "User.h"
#include "map"

class ChatOperator
{
public:
	ChatOperator() = default;
	~ChatOperator() 
	{
		recived_envelope_ = nullptr;
		send_envelope_ = nullptr;
		hashTableRef_ = nullptr;
	}

	void reciveEnvelope(User::Envelope* envelope);

	void setHashTableRef(std::map<std::string, class User>* hashTableRef);
	// to gain access to a user_hash_table that is located in private area of class Chat

	User::Envelope* sendEnvelope(const std::string& recipientName);

	User::Envelope* makeCopyOfEnvelope();
	// makes a copy of senders envelope message
	// in case when sender wants to send message to all users

	void sendEnvelopeToAllUsers(const std::string& excludingSendertName);
	// function that sends a copy of envelope to all users

	void destroyEnvelope();
	// when reciving and sending is done sets send_envelope_ to nullptr
private:
	User::Envelope* recived_envelope_ = nullptr;
	User::Envelope* send_envelope_ = nullptr;


	std::map<std::string, class User>* hashTableRef_ = nullptr;	
	// gaining accsess to original user_hash_table_ that is located in Chat class
};