#pragma once
#include "PrivateMessages.h"
#include "AllUsersMessages.h"
#include <exception>
#include <memory>
#include <vector>

class Chat
{
	bool _chatIsRunning = false; // Выражение работы чата.
	vector<User> _users; // Вектор всех юзеров.
	vector<PrivateMessages> _privMessages; // Вектор приватных сообщений.
	vector<AllUsersMessages> _allUsersMess; // Вектор сообщений общего чата.
	shared_ptr<User> _currentUser = nullptr; // Умный указатель на текущего юзера.

	void login(); // Метод входа в чат.
	void signUp(); // Метода регистрации.
	void showAllUsersNames() const; // Метод вывода списка всех юзеров.
	void chatAllNow(); // Метод работы с общим чатом.
	void showAllUsersChat() const; // Метод вывода всех сообщений общего чата.
	void chatCurrPersonNow(const string& person); // Метод работы с приватным чатом.
	void showCurrPersonChat(const string& person); // Метод вывода всех сообщений приватного чата.

	shared_ptr<User> getUserByLogin(const string& login) const; // Метод проверки наличия логина юзера.
	shared_ptr<User> getUserByName(const string& name) const; // Метод проверки наличия имени юзера.

public:
	void start(); // Метод запуска программы чата.
	bool ChatIsRunning() const // Метод проверки состояния работы чата.
	{
		return _chatIsRunning;
	}
	shared_ptr<User> getCurrentUser() const // Метод проверки логина текущего юзера.
	{
		return _currentUser;
	}
	void showMainMenu(); // Метод вызова главного меню.
	void showUserMenu(); // Метод вызова меню юзера.
};

struct UserLoginExp : public exception // Исключение для несуществующего логина.
{
	const char* what() const noexcept override
	{
		return "This login is not available";
	}
};

struct UserNameExp : public exception // Исключение для несуществующего имени.
{
	const char* what() const noexcept override
	{
		return "Error: user name is busy";
	}
};
