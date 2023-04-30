#include "Chat.h"

int main()
{
	Chat chat; // ������� ������ ����, ���������� ��� ���, � ������� �� ��������� ������� ������ ���� false.

	chat.start(); // ��������� ��� ���������� ������� ������ � true.

	while (chat.ChatIsRunning()) // �������� ����, ������� ����������� ���� ��� ��������.
	{
		chat.showMainMenu(); // �������� ������� ����.

		while (chat.getCurrentUser()) // ���� ����������� ���� ������� ���� ������.
		{
			chat.showUserMenu(); // ���� �������� �����.
		}
	}

	return 0;
}