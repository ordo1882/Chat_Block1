#pragma once
#include "User.h"

class AllUsersMessages
{
	const string _from;
	const string _text;

public:
	AllUsersMessages(const string& from, const string& text) : _from(from), _text(text)
	{
	}

	~AllUsersMessages() = default;

	const string& getFrom() const
	{
		return _from;
	}

	const string& getText() const
	{
		return _text;
	}
};