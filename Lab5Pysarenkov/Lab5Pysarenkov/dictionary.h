#pragma once
#include <string>

namespace dictionary {
	struct dict
	{
	private:
		struct Word
		{
			std::string eng;
			std::string ukr;
			int uses;
			Word* left;
			Word* right;
			Word* next;
			Word(std::string eng, std::string ukr, int uses) {
				this->eng = eng;
				this->ukr = ukr;
				this->uses = uses;
				this->left = nullptr;
				this->right = nullptr;
				this->next = nullptr;
			}
		};
	public:
		Word* Top = nullptr;
		Word* Top1 = nullptr;
		void createDictionary();
		void createDictionaryFromFile();
		void output(Word* n);
		void add(Word* tree, Word* w);
		void search(Word* tree, std::string eng);
		bool found;
		void createNewTree();
		Word* copytree(Word* tree);
		Word* findMax(Word* tree);
		void changeMax(Word* tree, Word* max);
	};
}