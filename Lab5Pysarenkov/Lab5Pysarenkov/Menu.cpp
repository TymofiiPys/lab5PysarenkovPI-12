#include <iostream>
#include <Windows.h>
#include "dictionary.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	dictionary::dict d;
	std::cout << "Англо-український словник\n\n";
	for (;;) {
		std::cout << "Введіть 1 для вводу словника вручну\n";
		std::cout << "2 - зчитати словник з файлу \"dict.txt\"\n";
		std::cout << "3 - знайти переклад слова\n";
		std::cout << "4 - сформувати новий словник за кількістю звертань\n";
		std::cout << "5 - вивести початковий словник\n";
		std::cout << "6 - вивести новий словник\n";
		std::cout << "0 - вийти з програми\n";
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
				std::cout << "\nДе ви те слово шукати зібрались? Створіть словник!\n";
			else
			{
				std::cout << "\nВведіть слово англійською: ";
				std::string eng;
				std::cin >> eng;
				d.found = false;
				if (!d.Top1)
					d.search(d.Top, eng);
				else
					d.search(d.Top1, eng);
				if (!d.found)
					std::cout << "Переклад не знайдено\n";
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
				std::cout << "\nСловник ще не створено! Введіть його вручну або файлом\n\n";
				break;
			}
			std::cout << "\n";
			d.output(d.Top);
			std::cout << "\n";
			break;
		case '6':
			if (!d.Top)
			{
				std::cout << "\nНовий словник ще не створено!\n\n";
				break;
			}
			std::cout << "\nАнгл. переклад, укр. переклад, кількість звернень\n";
			d.output(d.Top1);
			break;
		case '0':
			return 0;
		}
	}
	return 0;
}
