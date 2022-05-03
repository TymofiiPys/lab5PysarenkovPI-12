#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"

//Дана версія файлу має зчитувач словника із файлу, але getline видає мені крокозябри

void dictionary::dict::add(Word* tree, Word* w) {
	if (w->eng > tree->eng)
		if (tree->right)
			add(tree->right, w);
		else
		{
			tree->right = w;
			return;
		}
	else
		if (tree->left)
			add(tree->left, w);
		else
		{
			tree->left = w;
			return;
		}
}

void dictionary::dict::createDictionary() {
	std::cout << "Введіть слово у форматі:\n";
	std::cout << "Англійськийпереклад/Українськийпереклад/Кількістьзвернень\n";
	std::cout << "Для завершення вводу введіть слово end\n";
	for (;;) {
		std::string row, eng, ukr;
		int uses = 0;
		std::cin >> row;
		if (row == "end")
			break;
		int rl = row.length();
		int c = 0;
		std::string s;
		for (int i = 0; i < rl; i++) {
			if (row[i] != '/')
				s += row[i];
			if (row[i] == '/' || i == rl - 1) {
				switch (c) {
				case 0:
					eng = s;
					break;
				case 1:
					ukr = s;
					break;
				case 2:
					uses = std::stoi(s);
					break;
				}
				c++;
				s = "";
			}
		}
		Word* w = new Word(eng, ukr, uses);
		if (!Top)
			Top = w;
		else
			add(Top, w);
	}
	std::cout << "Словник створений успішно.\n\n";
}

void dictionary::dict::createDictionaryFromFile() {
	std::ifstream file("dict.txt");
	if(!file)
	{
		std::cout << "\nФайлу \"dict.txt\" не існує.\n\n";
		return;
	}
	int n = 0;
	std::string buff;
	while (!file.eof())
	{
		std::getline(file, buff);
		n++;
	}
	file.seekg(0, file.beg);
	for (int i = 0; i < n; i++) {
		std::string row, row1, eng, ukr;
		int uses = 0;
		std::getline(file, row); 
ф		int rl = row.length();
		for (int i = 0; i < rl; i++) {
			row1 += char(int(row[i]));
		}
		int c = 0;
		std::string s;
		for (int i = 0; i < rl; i++) {
			if (row[i] != '/')
				s += row[i];
			if (row[i] == '/' || i == rl - 1) {
				switch (c) {
				case 0:
					eng = s;
					break;
				case 1:
					ukr = s;
					break;
				case 2:
					uses = std::stoi(s);
					break;
				}
				c++;
				s = "";
			}
		}
		Word* w = new Word(eng, ukr, uses);
		if (!Top)
			Top = w;
		else
			add(Top, w);
	}
	std::cout << "Словник створений успішно.\n\n";
}

void dictionary::dict::output(Word* n) {
	if (!n)
		return;
	output(n->left);
	std::cout << n->eng << "\t" << n->ukr << "\t" << std::to_string(n->uses) << "\n";
	output(n->right);
}

void dictionary::dict::search(Word* tree, std::string eng) {
	if (!tree)
		return;
	if (eng > tree->eng)
		search(tree->right, eng);
	else if (eng < tree->eng)
		search(tree->left, eng);
	else
	{
		std::cout << "Переклад: " << tree->ukr << "\n";
		tree->uses++;
		found = true;
		return;
	}
}

void dictionary::dict::createNewTree()//Створення дерева, сформованого за кількістю показників
{
	Word* TopCopy = copytree(Top);
	Top1 = nullptr;
	while (true) {
		Word* w = findMax(TopCopy);
		if (w->uses == -1)//Якщо всі слова у старому дереві були додані до нового дерева, тобто в усіх слів в копії старого дерева показник звернень
			//змінений на -1, завершуємо цикл
			break;
		add(Top1, w);
		changeMax(TopCopy, w);
	}	
	std::cout << "Новий словник створений успішно.\n\n";
}

dictionary::dict::Word* dictionary::dict::copytree(Word* tree) {//Робимо копію початкового дерева, в якому і будемо змінювати показники звертань
	//слів, які уже занесено до нового дерева
	if (!tree)
		return nullptr;
	else
	{
		Word* a = new Word(tree->eng, tree->ukr, tree->uses);
		a->left = copytree(tree->left);
		a->right = copytree(tree->right);
		return a;
	}
}

dictionary::dict::Word* dictionary::dict::findMax(Word* tree) {//Пошук слова із максимальним показником звертань
	if (!tree)
		return new Word("", "", -1);
	Word *a = tree;
	Word* l = findMax(tree->left);
	Word* r = findMax(tree->right);
	if (l->uses > a->uses)
		a = new Word(tree->left->eng, tree->left->ukr, tree->left->uses);
	if (r->uses > a->uses)
		a = new Word(tree->right->eng, tree->right->ukr, tree->right->uses);
	return a;
}

void dictionary::dict::changeMax(Word* tree, Word* max) {
	if (max->eng > tree->eng)
		changeMax(tree->right, max);
	else if (max->eng < tree->eng)
		changeMax(tree->left, max);
	else {
		tree->uses = -1;//змінюємо кількість використань у КОПІЇ дерева, аби ігнорувати це слово при пошуку слова із наступним за 
		//ним найбільшим показником звертань
		return;
	}
}