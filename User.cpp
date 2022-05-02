#include <string>
#include <memory>
#include "sha1.h"
#include "User.h"
#include <iostream>

void User::setName(const std::string& name)
{
	name_ = name;
}

uint* User::getHash()
{
	return hash_;
}

std::string User::getName()
{
	return name_;
}

void User::setEnvelope(const std::string& recipientName, const std::string& text)
{
	Envelope* newEnvelope = new Envelope(name_, recipientName, text);
	envelope_to_send_ = newEnvelope;
	// creating envelope
}

User::Envelope* User::sendEnvelope()
{	
	if (envelope_to_send_ == nullptr)
	{
		return nullptr;
	}
	else
	{
		return User::envelope_to_send_;
	}
}

void User::reciveEnvelope(User::Envelope* envelope)
{
	envelope_to_recive_ = envelope;

	if (envelope_to_recive_ == nullptr)
	{
		throw "error : envelope delivery failed! class User";
	}
}

void User::displayRecivedEnvelopeToUserInfo()
{
	User::Envelope* newEnvelope = new User::Envelope;

	if (envelope_to_recive_ == nullptr)
	{
		std::cout << "\n";
		std::cout << "your mail is empty" << std::endl;
		std::cout << "\n";
	}
	else
	{
		std::cout << "\n";
		std::cout << "hi " << name_ << " you have message in your mail!" << std::endl;
		std::cout << "message was addressed to : " << envelope_to_recive_->to_who_ << std::endl;
		std::cout << "messeage send from user  : " << envelope_to_recive_->from_who_ << std::endl;
		std::cout << "\n";
	}
}

void User::openTheEnvelope()
{
	if (envelope_to_recive_ == nullptr)
	{
		std::cout << "\n";
		std::cout << "envelope is corrupted" << std::endl;
		std::cout << "\n";
		return;
	}
	if (envelope_to_recive_->text_.empty())
	{
		std::cout << "\n";
		std::cout << "the message text is blank!" << std::endl;
		std::cout << "\n";
	}
	else
	{
		std::cout << "\n";
		std::cout << "message text is ->       : " << envelope_to_recive_->text_ << std::endl;
		std::cout << "\n";
	}
	envelope_to_recive_ = nullptr; // deleting envelope
}