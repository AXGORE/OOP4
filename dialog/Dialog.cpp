#include "Dialog.h"
#include"Summoner.h"
#pragma comment(lib,"../Laba4/Debug/Laba4")
#include <iostream>
#include <stdexcept>
using namespace summon;
void makemap(field& f) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::cout << " " << f.getcoords(i, j).busy;
		}
		std::cout << "\n";
	}
}
void sum_dialog(Summoner& SUM,v::vector<Creature*>& creatures, int& n, v::vector<cr>& alive, v::vector<necr_cr>& necr,int& na, int& nn) {
	while (true) {
		const char* opt[] = { "Save energy","Learn schools","Summon creature","Show stats"};
		for (int i = 0; i < 4; i++) {
			std::cout << i + 1 << ": " << opt[i] << std::endl;
		}
		int act;
		int help = getNum(act, "int");
		if (help == -1) { return; }
		if ((act < 1 || act>4)) {
			std::cout << "Error, try again" << std::endl;
		}
		if (act == 1) {
			SUM.save_energy();
			return;
		}
		if (act == 2) {
			std::string help;
			SUM.get_table()->show_schools();
			std::cout << "\nChoose the school" << std::endl;
			std::cin >> help;
			try {
				SUM.learn_school(help);
			}
			catch(const std::exception & e) {
				std::cout << e.what() << std::endl;
			}
		}
		if (act == 3) {
			std::string help;
			SUM.get_table()->show_schools();
			std::cout << "\nChoose the school" << std::endl;
			std::cin >> help;
			More_cr(creatures);
			try {
			/*if (help == "Necr") {
					necr.resize(necr.getlen() + 1);
					necr[nn] = *SUM.summon_creature(help);
					nn++;
				}
				else {
					alive.resize(alive.getlen() + 1);
					alive[na] = *SUM.summon_creature(help);
					na++;
				}*/
				SUM.summon_creature(help,creatures[n]);
				creatures[n]->setteam(&SUM);
				n++;
			}
			//creatures[n].setstats(SUM.summon_creature(help)->getstats(*creatures[n].getname(),*creatures[n].ret_level()));
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl;
			}
			//creatures.resize(n);
			//necr.resize(nn);
			//alive.resize(na);
			return;
		}
		if (act == 4) {
			SUM.showstats();
		}
	}
}
int game() {
	int n=0;
	int nn = 0;
	int na = 0;
	field f(10,10);
	makemap(f);
	std::cout << "\n";
	showmap(f);
	//Creature* creatures=nullptr;
	v::vector<Creature*> creatures;
	v::vector<cr> alive;
	v::vector<necr_cr> necr;
	Summoner SUM(1);
	sum_dialog(SUM,creatures,n,alive,necr,nn,na);
	f.setcreature(1,1,creatures[0]);
	makemap(f);
	creatures[0]->move(f, 3, 3);
	std::cout << "\n";
	makemap(f);
	//creatures[0]->damage_summoner(SUM);
	//creatures[1]->fight(creatures[0]);
	//std::cout << creatures[0]->showname() << std::endl;
	//creatures[0]->showstats();
	//creatures[1]->showstats();
	//creatures[1].Ability();
	SUM.showstats();
	return 0;
}
void More_cr(v::vector<Creature*> &creatures) {
	creatures.resize(creatures.getlen()+1);
}
void showmap(field &f) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::cout << " " << f.getcoords(i, j).type;
		}
		std::cout << "\n";
	}
}