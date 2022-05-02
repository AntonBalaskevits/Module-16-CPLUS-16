#pragma once

#include <string>
#include "sha1.h"
#include <iostream>

class User
{
public:
	User(uint* hash) : hash_(hash) {}
	~User() 
	{
		delete envelope_to_send_;
		delete envelope_to_recive_;
		hash_ = nullptr;
	}

	struct Envelope
	{
		Envelope() = default;
		Envelope(const std::string& from, const std::string& to, const std::string& text)
			: from_who_(from), to_who_(to), text_(text) {}
		~Envelope() {}
	

		std::string from_who_;
		std::string to_who_;
		std::string text_;
	};
	Envelope* envelope_to_send_ = nullptr;
	Envelope* envelope_to_recive_ = nullptr;

	void setName(const std::string& name);
	std::string getName();

	uint* getHash();

	void setEnvelope(const std::string& recipientName, const std::string& text);
	Envelope* sendEnvelope();

	void reciveEnvelope(Envelope* envelope);

	void displayRecivedEnvelopeToUserInfo(); // function imitates situation when 
	// u as recipient of mail got the envelope and before you can unwrap what it is inside,
	// you need to check if it the envelope was addressed to you or not
	
	void openTheEnvelope();
	// couts the message inside the envelope

private:
	uint* hash_ = nullptr;
	// storing hash from password
	std::string name_;
	// storing user name
};
