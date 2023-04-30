#include "Chat.h"
#include <iostream>

void Chat::start() // Функция запуска чата.
{
	_chatIsRunning = true;
}

void Chat::showMainMenu() // Метод вызывающий гланое меню.
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

void Chat::login() // Метод входа в аккаунт.
{
	string login, password;

	do
	{
		cout << "Login: ";
		cin >> login;
		cout << "Password: ";
		cin >> password;

		_currentUser = getUserByLogin(login); // Метод проверки наличия существующего логина.

		if (_currentUser == nullptr || (password != _currentUser->getUserPassword())) // При отсутствии логина выдаем ошибку.
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

void Chat::signUp() // Метод регистрации аккаунта.
{
	string login, password, name;

	cout << "Login: ";
	cin >> login;

	// В комментариях ниже пытался заставить юзера вводить только одно слово для логина. Однако пока так и не нашел решение.
	// Потому пока данная проблемма программы осталась.

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

	if (getUserByLogin(login)) // Метод проверки наличия существующего логина.
	{
		throw UserLoginExp();
	}

	cout << "Password: ";
	cin >> password;
	cout << "Name: ";
	cin >> name;

	if (getUserByName(name)) // Метод проверки наличия существующего имени.
	{
		throw UserNameExp();
	}

	User user = User(login, password, name); // Создаемм класс юзера и вносим в него введенные данные.
	_users.push_back(user); // Добавляем юзера в массив вектор.
	_currentUser = make_shared<User>(user); // Создаем указатель на текущего юзера.
}

shared_ptr<User> Chat::getUserByLogin(const string& login) const // Реализация метода проверки наличия логина юзера.
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

shared_ptr<User> Chat::getUserByName(const string& name) const // Реализация метода проверки наличия имени юзера.
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

void Chat::showUserMenu() // Реализация метода меню текущего юзера.
{
	cout << endl << "\033[32m" << "Profile: " << _currentUser->getUserName() << "\033[0m" << endl; // Показываем текущий профиль.

	showAllUsersNames(); // Вызываем метод показывающий список всех существующих юзеров.

	while (_currentUser)
	{
		string person;
		cout << endl << "Choose a person you wanna talk or type '0' to Logout" << endl << ">> ";
		cin >> person;

		if (getUserByName(person)) // Если имя есть в списке, переходим приватный чат.
		{
			cin.ignore();
			chatCurrPersonNow(person);
			break;
		}

		else if (person == "ALL" || person == "All" || person == "all") // Условие для перехода в общий чат.
		{
			cin.ignore();
			chatAllNow();
			break;
		}

		else if (person == "0") // Условие для выхода в главное меню программы.
		{
			_currentUser = nullptr;
			break;
		}

		else // Условие, при котором сообщаем об отсутствии указанного имени.
		{
			cout << endl << "\033[31m" << "There is no user by name '" << person << "' in the list." << "\033[0m" << endl;
			return;
		}
	}
}

void Chat::showAllUsersNames() const // Реализация метода показывающего весь список юзеров на консоль.
{
	cout << "\033[36m" << ".... Chat list ...." << "\033[0m" << endl;
	for (auto& user : _users)
	{
		if (_currentUser->getUserLogin() != user.getUserLogin()) // Условие, при котором показываем всех юзеров, кроме текущего.
		{
			cout << "\033[35m" << user.getUserName() << "\033[0m" << endl;
		}
	}
	cout << "\033[35m" << "ALL" << "\033[0m" << endl;
}

void Chat::chatAllNow() // Реализация метода общего чата.
{
	while (_currentUser)
	{
		showAllUsersChat(); // Вызываем метод для показа всех сообщений в общем чате.

		cout << endl << "/~1/ Cancel sending the last message    /~0/ Back to menu" << endl << ">> "; // Меню общего чата.

		string text;
		cout << "Text: ";
		getline(cin, text);

		if (text == "~1") // Условие, при котором вызывается метод отмены отправки последнего сообщения текущего юзера из общего чата.
		{
			for (size_t message = _allUsersMess.size() - 1; message >= 0; --message)
			{
				if (_currentUser->getUserLogin() == _allUsersMess[message].getFrom())
				{
					_allUsersMess.pop_back(); // Недостаток - удаляет сообщения пока не дойдем до "чужих". Сообщения за "чужими" не удалятся.
				}
				break;
			}
			continue;
		}

		else if (text == "~0") // Вызывавем метод перехода обратно в меню.
		{
			showUserMenu(); 
			break;
		}

		else if (text == "") // В случае ввода пустой строки ничего не происходит.
		{
			continue;
		}

		_allUsersMess.push_back(AllUsersMessages{ _currentUser->getUserLogin(), text }); // Добавляем сообщение и его данные в вектор общего чата.
	}
}

void Chat::showAllUsersChat() const // Реализация метода показа всех сообщений общего чата.
{
	cout << endl << "\033[36m" << ".... Current chat with ALL ...." << "\033[0m" << endl << endl;

	string from;

	for (auto& message : _allUsersMess)
	{
		if (_currentUser->getUserLogin() == message.getFrom()) // Условие вывода сообщений текущего юзера.
		{
			cout << "\033[32m" << "[ " << message.getText() << " ]" << "\033[0m" << endl;
		}
		else // Условие вывода сообщений всех юзеров.
		{
			from = getUserByLogin(message.getFrom())->getUserName();
			cout << "\033[33m" << "        " << from << endl << "          [ " << message.getText() << " ]" << "\033[0m" << endl;
		}
	}
}

void Chat::chatCurrPersonNow(const string& person) // Реализация метода приватного чата.
{
	while (_currentUser)
	{
		showCurrPersonChat(person);

		cout << endl << "/~1/ Cancel sending the last message    /~0/ Back to menu" << endl << ">> ";

		string text;
		cout << "Text: ";
		getline(cin, text);

		if (text == "~1") // Условие, при котором вызывается метод отмены отправки последнего сообщения текущего юзера из приватного чата.
		{
			for (size_t message = _privMessages.size() - 1; message >= 0; --message)
			{
				if (_currentUser->getUserLogin() == _privMessages[message].getFrom())
				{
					_privMessages.pop_back(); // Недостаток - удаляет сообщения пока не дойдем до "чужих". Сообщения за "чужими" не удалятся.
				}
				break;
			}
			continue;
		}

		else if (text == "~0") // Вызывавем метод перехода обратно в меню.
		{
			showUserMenu();
			break;
		}

		else if (text == "") // В случае ввода пустой строки ничего не происходит.
		{
			continue;
		}

		_privMessages.push_back(PrivateMessages{ _currentUser->getUserLogin(), getUserByName(person)->getUserLogin(), text }); // Добавляем сообщение и его данные в вектор приватного чата.
	}
}

void Chat::showCurrPersonChat(const string& person) // Реализация метода показа всех сообщений приватного чата.
{
	cout << endl << "\033[36m" << ".... Current chat with " << person << " ...." << "\033[0m" << endl << endl;

	for (auto& message : _privMessages)
	{
		if ((_currentUser->getUserLogin() == message.getFrom()) && (getUserByLogin(message.getTo())->getUserName() == person)) // Условие вывода сообщений текущего юзера.
		{
			cout << "\033[32m" << "[ " << message.getText() << " ]" << "\033[0m" << endl;
		}

		else if ((_currentUser->getUserLogin() == message.getTo()) && (getUserByLogin(message.getFrom())->getUserName() == person)) // Условие вывода сообщений собеседника.
		{
			cout << "\033[33m" << "          [ " << message.getText() << " ]" << "\033[0m" << endl;
		}
	}
}