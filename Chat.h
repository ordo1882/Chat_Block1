#pragma once
#include "PrivateMessages.h"
#include "AllUsersMessages.h"
#include <exception>
#include <memory>
#include <vector>

class Chat
{
	bool _chatIsRunning = false; // ��������� ������ ����.
	vector<User> _users; // ������ ���� ������.
	vector<PrivateMessages> _privMessages; // ������ ��������� ���������.
	vector<AllUsersMessages> _allUsersMess; // ������ ��������� ������ ����.
	shared_ptr<User> _currentUser = nullptr; // ����� ��������� �� �������� �����.

	void login(); // ����� ����� � ���.
	void signUp(); // ������ �����������.
	void showAllUsersNames() const; // ����� ������ ������ ���� ������.
	void chatAllNow(); // ����� ������ � ����� �����.
	void showAllUsersChat() const; // ����� ������ ���� ��������� ������ ����.
	void chatCurrPersonNow(const string& person); // ����� ������ � ��������� �����.
	void showCurrPersonChat(const string& person); // ����� ������ ���� ��������� ���������� ����.

	shared_ptr<User> getUserByLogin(const string& login) const; // ����� �������� ������� ������ �����.
	shared_ptr<User> getUserByName(const string& name) const; // ����� �������� ������� ����� �����.

public:
	void start(); // ����� ������� ��������� ����.
	bool ChatIsRunning() const // ����� �������� ��������� ������ ����.
	{
		return _chatIsRunning;
	}
	shared_ptr<User> getCurrentUser() const // ����� �������� ������ �������� �����.
	{
		return _currentUser;
	}
	void showMainMenu(); // ����� ������ �������� ����.
	void showUserMenu(); // ����� ������ ���� �����.
};

struct UserLoginExp : public exception // ���������� ��� ��������������� ������.
{
	const char* what() const noexcept override
	{
		return "This login is not available";
	}
};

struct UserNameExp : public exception // ���������� ��� ��������������� �����.
{
	const char* what() const noexcept override
	{
		return "Error: user name is busy";
	}
};
