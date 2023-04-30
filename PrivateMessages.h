#pragma once
#include "User.h"

class PrivateMessages
{
	const string _from;
	const string _to;
	const string _text;

public:
	PrivateMessages(const string& from, const string& to, const string& text) : _from(from), _to(to), _text(text)
	{
	}

	~PrivateMessages() = default;

	const string& getFrom() const
	{
		return _from;
	}

	const string& getTo() const
	{
		return _to;
	}

	const string& getText() const
	{
		return _text;
	}
};