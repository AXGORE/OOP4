#ifndef DIALOG_H
#define DIALOG_H

#include <iostream>
#include "Summoner.h"
#pragma comment(lib,"../Laba4/Debug/Laba4")

using namespace summon;
	template <class T>
	int getNum(T& a, const char* text) {
		bool flag = false;
		std::cout << text << std::endl;
		do {
			if (flag == true) {
				std::cout << "Error, try again:";
				flag = false;
			}
			std::cin >> a;
			if (std::cin.eof() || std::cin.bad()) {
				return -1;
			}
			else if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				flag = true;
			}

		} while (flag == true);
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		return 0;
	}
	int game();
	void showmap(field& f);
	void sum_dialog(Summoner& sum, v::vector<Creature*>& creatures, int& n, v::vector<cr>& alive, v::vector<necr_cr>& necr, int& na, int& nn);
	void More_cr(v::vector<Creature*>& creatures);
	void makemap(field& f);


#endif
