#include <iostream>
#include <Windows.h>
#include "dictionary.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	dictionary::dict d;
	std::cout << "�����-���������� �������\n\n";
	for (;;) {
		std::cout << "������ 1 ��� ����� �������� ������\n";
		std::cout << "2 - ������� ������� � ����� \"dict.txt\"\n";
		std::cout << "3 - ������ �������� �����\n";
		std::cout << "4 - ���������� ����� ������� �� ������� ��������\n";
		std::cout << "5 - ������� ���������� �������\n";
		std::cout << "6 - ������� ����� �������\n";
		std::cout << "0 - ����� � ��������\n";
		char c;
		std::cin >> c;
		switch (c) {
		case '1':
			d.Top = nullptr;
			d.createDictionary();
			break;
		case '2':
			d.Top = nullptr;
			d.createDictionaryFromFile();
			break;
		case '3':
		{
			if (!d.Top)
				std::cout << "\n�� �� �� ����� ������ ��������? ������� �������!\n";
			else
			{
				std::cout << "\n������ ����� ����������: ";
				std::string eng;
				std::cin >> eng;
				d.found = false;
				if (!d.Top1)
					d.search(d.Top, eng);
				else
					d.search(d.Top1, eng);
				if (!d.found)
					std::cout << "�������� �� ��������\n";
				std::cout << "\n";
			}
			break;
		}
		case '4':
			d.createNewTree();
			break;
		case '5':
			if (!d.Top)
			{
				std::cout << "\n������� �� �� ��������! ������ ���� ������ ��� ������\n\n";
				break;
			}
			std::cout << "\n";
			d.output(d.Top);
			std::cout << "\n";
			break;
		case '6':
			if (!d.Top)
			{
				std::cout << "\n����� ������� �� �� ��������!\n\n";
				break;
			}
			std::cout << "\n����. ��������, ���. ��������, ������� ��������\n";
			d.output(d.Top1);
			break;
		case '0':
			return 0;
		}
	}
	return 0;
}
