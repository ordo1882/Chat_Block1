#include "Chat.h"
#include <iostream>

void Chat::start() // ������� ������� ����.
{
	_chatIsRunning = true;
}

void Chat::showMainMenu() // ����� ���������� ������ ����.
{
	_currentUser = nullptr;

	char choise;

	do
	{
		cout << "\033[33m" << "/1/ Login" << endl;
		cout << "/2/ SignUp" << endl;
		cout << "\033[31m" << "/0/ Exit" << endl;
		cout << "\033[36m" << ">> " << "\033[0m";
		cin >> choise;

		switch (choise)
		{
		case '1':
			login();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case '0':
			_chatIsRunning = false;
			break;
		default:
			cout << "Choose 1 or 2..." << endl;
			break;
		}
	} while (!_currentUser && _chatIsRunning);
}

void Chat::login() // ����� ����� � �������.
{
	string login, password;

	do
	{
		cout << "Login: ";
		cin >> login;
		cout << "Password: ";
		cin >> password;

		_currentUser = getUserByLogin(login); // ����� �������� ������� ������������� ������.

		if (_currentUser == nullptr || (password != _currentUser->getUserPassword())) // ��� ���������� ������ ������ ������.
		{
			char choise;
			_currentUser = nullptr;
			cout << endl << "\033[31m" << "Login or password is not correct." << endl << "Press '0' to exit or any key to try again: " << "\033[0m";
			cin >> choise;

			if (choise == '0')
			{
				break;
			}
		}
	} while (!_currentUser);
}

void Chat::signUp() // ����� ����������� ��������.
{
	string login, password, name;

	cout << "Login: ";
	cin >> login;

	// � ������������ ���� ������� ��������� ����� ������� ������ ���� ����� ��� ������. ������ ���� ��� � �� ����� �������.
	// ������ ���� ������ ��������� ��������� ��������.

	/*cin.ignore(80, '\n');

	for (unsigned i = 0; i < login.length(); ++i)
	{
		if (login.at(i) = ' ')
		{
			cout << endl << "\033[31m" << "Login can't have more than one word." << "\033[0m";
			cin.clear();
			return;
		}
	}*/

	if (getUserByLogin(login)) // ����� �������� ������� ������������� ������.
	{
		throw UserLoginExp();
	}

	cout << "Password: ";
	cin >> password;
	cout << "Name: ";
	cin >> name;

	if (getUserByName(name)) // ����� �������� ������� ������������� �����.
	{
		throw UserNameExp();
	}

	User user = User(login, password, name); // �������� ����� ����� � ������ � ���� ��������� ������.
	_users.push_back(user); // ��������� ����� � ������ ������.
	_currentUser = make_shared<User>(user); // ������� ��������� �� �������� �����.
}

shared_ptr<User> Chat::getUserByLogin(const string& login) const // ���������� ������ �������� ������� ������ �����.
{
	for (auto& user : _users)
	{
		if (login == user.getUserLogin())
		{
			return make_shared<User>(user);
		}
	}

	return nullptr;
}

shared_ptr<User> Chat::getUserByName(const string& name) const // ���������� ������ �������� ������� ����� �����.
{
	for (auto& user : _users)
	{
		if (name == user.getUserName())
		{
			return make_shared<User>(user);
		}
	}

	return nullptr;
}

void Chat::showUserMenu() // ���������� ������ ���� �������� �����.
{
	cout << endl << "\033[32m" << "Profile: " << _currentUser->getUserName() << "\033[0m" << endl; // ���������� ������� �������.

	showAllUsersNames(); // �������� ����� ������������ ������ ���� ������������ ������.

	while (_currentUser)
	{
		string person;
		cout << endl << "Choose a person you wanna talk or type '0' to Logout" << endl << ">> ";
		cin >> person;

		if (getUserByName(person)) // ���� ��� ���� � ������, ��������� ��������� ���.
		{
			cin.ignore();
			chatCurrPersonNow(person);
			break;
		}

		else if (person == "ALL" || person == "All" || person == "all") // ������� ��� �������� � ����� ���.
		{
			cin.ignore();
			chatAllNow();
			break;
		}

		else if (person == "0") // ������� ��� ������ � ������� ���� ���������.
		{
			_currentUser = nullptr;
			break;
		}

		else // �������, ��� ������� �������� �� ���������� ���������� �����.
		{
			cout << endl << "\033[31m" << "There is no user by name '" << person << "' in the list." << "\033[0m" << endl;
			return;
		}
	}
}

void Chat::showAllUsersNames() const // ���������� ������ ������������� ���� ������ ������ �� �������.
{
	cout << "\033[36m" << ".... Chat list ...." << "\033[0m" << endl;
	for (auto& user : _users)
	{
		if (_currentUser->getUserLogin() != user.getUserLogin()) // �������, ��� ������� ���������� ���� ������, ����� ��������.
		{
			cout << "\033[35m" << user.getUserName() << "\033[0m" << endl;
		}
	}
	cout << "\033[35m" << "ALL" << "\033[0m" << endl;
}

void Chat::chatAllNow() // ���������� ������ ������ ����.
{
	while (_currentUser)
	{
		showAllUsersChat(); // �������� ����� ��� ������ ���� ��������� � ����� ����.

		cout << endl << "/~1/ Cancel sending the last message    /~0/ Back to menu" << endl << ">> "; // ���� ������ ����.

		string text;
		cout << "Text: ";
		getline(cin, text);

		if (text == "~1") // �������, ��� ������� ���������� ����� ������ �������� ���������� ��������� �������� ����� �� ������ ����.
		{
			for (size_t message = _allUsersMess.size() - 1; message >= 0; --message)
			{
				if (_currentUser->getUserLogin() == _allUsersMess[message].getFrom())
				{
					_allUsersMess.pop_back(); // ���������� - ������� ��������� ���� �� ������ �� "�����". ��������� �� "������" �� ��������.
				}
				break;
			}
			continue;
		}

		else if (text == "~0") // ��������� ����� �������� ������� � ����.
		{
			showUserMenu(); 
			break;
		}

		else if (text == "") // � ������ ����� ������ ������ ������ �� ����������.
		{
			continue;
		}

		_allUsersMess.push_back(AllUsersMessages{ _currentUser->getUserLogin(), text }); // ��������� ��������� � ��� ������ � ������ ������ ����.
	}
}

void Chat::showAllUsersChat() const // ���������� ������ ������ ���� ��������� ������ ����.
{
	cout << endl << "\033[36m" << ".... Current chat with ALL ...." << "\033[0m" << endl << endl;

	string from;

	for (auto& message : _allUsersMess)
	{
		if (_currentUser->getUserLogin() == message.getFrom()) // ������� ������ ��������� �������� �����.
		{
			cout << "\033[32m" << "[ " << message.getText() << " ]" << "\033[0m" << endl;
		}
		else // ������� ������ ��������� ���� ������.
		{
			from = getUserByLogin(message.getFrom())->getUserName();
			cout << "\033[33m" << "        " << from << endl << "          [ " << message.getText() << " ]" << "\033[0m" << endl;
		}
	}
}

void Chat::chatCurrPersonNow(const string& person) // ���������� ������ ���������� ����.
{
	while (_currentUser)
	{
		showCurrPersonChat(person);

		cout << endl << "/~1/ Cancel sending the last message    /~0/ Back to menu" << endl << ">> ";

		string text;
		cout << "Text: ";
		getline(cin, text);

		if (text == "~1") // �������, ��� ������� ���������� ����� ������ �������� ���������� ��������� �������� ����� �� ���������� ����.
		{
			for (size_t message = _privMessages.size() - 1; message >= 0; --message)
			{
				if (_currentUser->getUserLogin() == _privMessages[message].getFrom())
				{
					_privMessages.pop_back(); // ���������� - ������� ��������� ���� �� ������ �� "�����". ��������� �� "������" �� ��������.
				}
				break;
			}
			continue;
		}

		else if (text == "~0") // ��������� ����� �������� ������� � ����.
		{
			showUserMenu();
			break;
		}

		else if (text == "") // � ������ ����� ������ ������ ������ �� ����������.
		{
			continue;
		}

		_privMessages.push_back(PrivateMessages{ _currentUser->getUserLogin(), getUserByName(person)->getUserLogin(), text }); // ��������� ��������� � ��� ������ � ������ ���������� ����.
	}
}

void Chat::showCurrPersonChat(const string& person) // ���������� ������ ������ ���� ��������� ���������� ����.
{
	cout << endl << "\033[36m" << ".... Current chat with " << person << " ...." << "\033[0m" << endl << endl;

	for (auto& message : _privMessages)
	{
		if ((_currentUser->getUserLogin() == message.getFrom()) && (getUserByLogin(message.getTo())->getUserName() == person)) // ������� ������ ��������� �������� �����.
		{
			cout << "\033[32m" << "[ " << message.getText() << " ]" << "\033[0m" << endl;
		}

		else if ((_currentUser->getUserLogin() == message.getTo()) && (getUserByLogin(message.getFrom())->getUserName() == person)) // ������� ������ ��������� �����������.
		{
			cout << "\033[33m" << "          [ " << message.getText() << " ]" << "\033[0m" << endl;
		}
	}
}