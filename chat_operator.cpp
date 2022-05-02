#include "User.h"
#include "chat_operator.h"
#include <iostream>

void ChatOperator::reciveEnvelope(User::Envelope* envelope)
{
	recived_envelope_ = envelope;

	if (recived_envelope_ == nullptr)
	{
		throw "receving envelope faild! class ChatOperator";
	}
}

void ChatOperator::setHashTableRef(std::map<std::string, class User>* hashTableRef)
{
	hashTableRef_ = hashTableRef;
}

User::Envelope* ChatOperator::sendEnvelope(const std::string& recipientName)
{
	std::map<std::string, class User>::iterator it = hashTableRef_->begin();
	// obtaining iterator to search users 

	for (; it != hashTableRef_->end(); it++)
	{
		if ((*it).second.getName() == recipientName)
		{  // searcing for recipient
			send_envelope_ = recived_envelope_;
			// if found, passing recidved envelope to send
			recived_envelope_ = nullptr;
			// reseting recived envelope

			return send_envelope_;
			// and sending envelope to recipient
		}
	}
	return nullptr;
	// if recipient is not found returns nullptr
}

User::Envelope* ChatOperator::makeCopyOfEnvelope()
{
	User::Envelope* newCopy = new User::Envelope;
	// creating a copy of envelope 
	// if in chat option send to "all" was selected
	// then this function will create a copy for all recipients
	// that are curerently registered

	newCopy = recived_envelope_;

	return newCopy;
}

void ChatOperator::sendEnvelopeToAllUsers(const std::string& excludingSenderName)
{
	std::map<std::string, class User>::iterator it = hashTableRef_->begin();

	for (; it != hashTableRef_->end(); it++)
	{
		if ((*it).second.getName() == excludingSenderName) 
		{ 
			// if name of user from who the message is send will match
			// it will skip that user, to avoid message being returned to sender back
			continue;
		}
		if (it != hashTableRef_->end())
		{
			(*it).second.reciveEnvelope(ChatOperator::makeCopyOfEnvelope());
			// sends a copy of envelope to all users
		}
		else
		{
			break;
		}
	}

	ChatOperator::destroyEnvelope();
}

void ChatOperator::destroyEnvelope()
{
	recived_envelope_ = nullptr;
}