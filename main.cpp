#include "Chat.h"

int main()
{
	Chat chat; // Создаем объект чата, собственно сам чат, в котором по умолчанию функция старта чата false.

	chat.start(); // Запускаем чат переключая функцию старта в true.

	while (chat.ChatIsRunning()) // Основной цикл, который выполняется пока чат работает.
	{
		chat.showMainMenu(); // Вызываем главное меню.

		while (chat.getCurrentUser()) // Цикл выполняется пока текущий юзер онлайн.
		{
			chat.showUserMenu(); // Меню текущего юзера.
		}
	}

	return 0;
}