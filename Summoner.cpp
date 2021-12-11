#include"Summoner.h"
#include <iostream>
#include <stdexcept>
#include <queue>


using namespace summon;


int School::get_level()const {
	return level;
}
void School::level_up(int& a) {
	if (a < req_exp) { throw std::logic_error("Not enough exp"); }
	a -= req_exp;
	level++;
	req_exp = 2 * req_exp;
}

void table::show_schools() {
	std::string s[] = { "Necr","Daemon","Animal","Elemental","Surreal"};
	for (int i = 0; i < 5; i++) {
		std::cout <<  i+1<< " " << s[i] << " level: " << (sch[s[i]])->get_level() << std::endl;
	}
}
void School::summon_creature(int& mana, int num, Creature*& cr) {
	if (mana < return_creature(num-1)->req_energ()) { throw std::logic_error("Not enough energy"); }
	mana = mana - return_creature(num-1)->req_energ();
	s_cr(cr,num);
	return;
}

School* table::get_school(std::string a){
	return sch[a];
}

table::table() {
	Necr_school* n=new Necr_school;
	sch.add_el("Necr",n);
	Daemon_school* d = new Daemon_school;
	sch.add_el("Daemon", d);
	Animal_school *a = new Animal_school;
	sch.add_el("Animal", a);
	Element_school* e = new Element_school;
	sch.add_el("Elemental", e);
	Surreal_school* s = new Surreal_school;
	sch.add_el("Surreal", s);
}

Necr_school::Necr_school() {
	level = 0;
	prior = 5;
	vulns = 3;
	type[0] = new skeletone;
	type[1] = new zombie;
	req_exp = 5;
}
void Necr_school::show_creatures()const {
	if (level == 0) { throw std::logic_error("Firstly you need to learn this school"); }
	for (int i = 0; i < level; i++) {
		std::cout << i + 1 << ": " << type[i]->showname() << std::endl;
	}
}
void Necr_school::s_cr(Creature*& cr, int num) {
	if (num == 1) { cr = new skeletone; }
	if (num == 2) { cr = new zombie; }
}
Daemon_school::Daemon_school() {
	prior = 4;
	vulns = 5;
	level = 0;
	type[0] = new demon;
	type[1] = new hell_hound;
	req_exp = 5;
}
void Daemon_school::show_creatures()const {
	if (level == 0) { throw std::logic_error("Firstly you need to learn this school"); }
	for (int i = 0; i < level; i++) {
		std::cout << i + 1 << ": " << type[i]->showname() << std::endl;
	}
}
void Daemon_school::s_cr(Creature*& cr, int num) {
	if (num == 1) { cr = new demon; }
	if (num == 2) { cr = new hell_hound; }
}
Animal_school::Animal_school() {
	level = 0;
	prior = 1;
	vulns = 4;
	type[0] = new rat;
	type[1] = new wolf;
	req_exp = 5;
}
void Animal_school::show_creatures()const {
	if (level == 0) { throw std::logic_error("Firstly you need to learn this school"); }
	for (int i = 0; i < level; i++) {
		std::cout << i + 1 << ": " << type[i]->showname() << std::endl;
	}
}
void Animal_school::s_cr(Creature*& cr, int num) {
	if (num == 1) { cr = new rat; }
	if (num == 2) { cr = new wolf; }
}
Element_school::Element_school() {
	level = 0;
	prior = 3;
	vulns = 2;
	type[0] = new air_elemental;
	type[1] = new water_elemental;
	req_exp = 5;
}
void Element_school::show_creatures()const {
	if (level == 0) { throw std::logic_error("Firstly you need to learn this school"); }
	for (int i = 0; i < level; i++) {
		std::cout << i + 1 << ": " << type[i]->showname() << std::endl;
	}
}
void Element_school::s_cr(Creature*& cr, int num) {
	if (num == 1) { cr = new air_elemental; }
	if (num == 2) { cr = new water_elemental; }
}
Surreal_school::Surreal_school() {
	level = 0;
	prior = 2;
	vulns = 1;
	type[0] = new dwarf;
	type[1] = new elf;
	req_exp = 5;
}
void Surreal_school::show_creatures()const {
	if (level == 0) { throw std::logic_error("Firstly you need to learn this school"); }
	for (int i = 0; i < level; i++) {
		std::cout << i + 1 << ": " << type[i]->showname() << std::endl;
	}
}
void Surreal_school::s_cr(Creature*& cr, int num) {
	if (num == 1) { cr = new dwarf; }
	if (num == 2) { cr = new elf; }
}
void Summoner::get_exp(int a) {
	Cur_Exp += a;
}
void Summoner::save_energy() {
	energy += 20;
}
void Summoner::summon_creature(std::string a, Creature*& cr) {
	School* help = sch.get_school(a);
	int b;
	std::cout << "Choose creature" << std::endl;
	help->show_creatures();
	std::cin >> b;
    help->summon_creature(energy,b,cr);
	return;
}
void Summoner::learn_school(std::string a) {
	sch.get_school(a)->level_up(Cur_Exp);
}
table* Summoner::get_table() {
	return &(this->sch);
}
void Summoner::showstats() const {
	std::cout << "HP: " << HP << std::endl;
	std::cout << "Energy: " << energy << std::endl;
	std::cout << "EXP: " << Cur_Exp << std::endl;
}
int Summoner::takedamage(Creature& sub) {
	HP -= sub.getlevel();
	if (HP <= 0) { return -1; }
	else return 1;
}
int Summoner::getteam()const {
	return team;
}
Summoner::Summoner(int i) {
	team = i;
	energy = 50;
	HP = 30;
	Cur_Exp = 10;
}
