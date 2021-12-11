#include <iostream>
#include "Creature.hpp"
#include "Summoner.h"
using namespace summon;

std::string Creature::showname()const {
	return name;
}
stats cr::getstats()const {
	return st;
}
void cr::showstats()const {
	std::cout << "\nTeam: " << team->getteam() << std::endl;
	std::cout << "Level: " << level<< std::endl;
	std::cout << "School: " << school << std::endl;
	std::cout << "Max HP: " << st.max_HP << std::endl;
	std::cout << "Curr HP: " << st.HP << std::endl;
	std::cout << "Damage: " << st.damage << std::endl;
	std::cout << "moral: " << st.moral << std::endl;
	std::cout << "Quantity: " << st.Quan << std::endl;
	std::cout << "Max speed: " << st.max_speed << std::endl;
	std::cout << "Current Movepoints: " << st.speed << std::endl;
	std::cout << "Defence: " << st.def << std::endl;
}
void Creature::setname(std::string a) {
	name = a;
}
void Creature::move(field& f,int x,int y) {
	f.findway(x,y,curr.x,curr.y);
	int help_x=f.getcoords(curr.x, curr.y).next->x;
	int help_y=f.getcoords(curr.x, curr.y).next->y;
	f.setcreature(curr.x, curr.y, nullptr);
	while (change_mp(f.getweight(help_x,help_y, curr.x, curr.y))) {
		curr.x = help_x;
		curr.y = help_y;
		help_x = f.getcoords(curr.x, curr.y).next->x;
	    help_y = f.getcoords(curr.x, curr.y).next->y;
	}
	f.setcreature(curr.x, curr.y, this);
	if (f.getcoords(curr.x, curr.y).next != nullptr) {
		if (f.getcoords(curr.x, curr.y).next->obj != nullptr && getmp() != 0) {
			if (getteam() != f.getcoords(curr.x, curr.y).next->obj->getteam()) {
				fight(f.getcoords(curr.x, curr.y).next->obj);
			}
		}
	}

}

int cr::getmp() const {
	return st.speed;
}
int necr_cr::getmp() const {
	return st.speed;
}
void cr::setstats(stats a) {
	st = a;
}
int cr::makedamage(Creature*& obj, int par) {
	float d = (this->st.damage * (100 + this->st.moral) * this->st.Quan) / 100;
	d = d * (100 + par * 20) / 100;
	return obj->takedamage(d);
}
int cr::takedamage(float d) {
	float dam = d * (100 - (st.def + st.moral)) / 100;
	int help_q = st.Quan;
	float help = st.max_HP * (st.Quan - 1) + st.HP;
	help = help - dam;
	if (help < 0) { return -1; }
	st.Quan = help / st.max_HP;
	st.HP = help - st.Quan * st.max_HP;
	st.Quan++;
	if (school != 1) {
		reset_moral(help_q, st.Quan);
	}
	return 1;
}
bool cr::change_mp(int a) {
	if (a == -1) { return false; }
	if (st.speed < a) { return false; }
	else { 
		st.speed -= a;
	    return true;
	}
}
bool necr_cr::change_mp(int a) {
	if (a == -1) { return false; }
	if (st.speed < a) { return false; }
	else {
		st.speed -= a;
		return true;
	}
}
int cr::damage_summoner(Summoner& obj) {
	int a = obj.takedamage(*this);
	this->st.speed = 0;
	return a;
}
int necr_cr::damage_summoner(Summoner& obj) {
	int a = obj.takedamage(*this);
	this->st.speed = 0;
	return a;
}
void cr::reset_moral(int prev, int curr) {
	st.moral += curr - prev;
}
int Creature::getlevel()const {
	return level;
};
void cr::moral_rise() {
	if (st.moral < 0) {
		st.moral++;
	}
	if (st.moral > 0) {
		st.moral--;
	}
}
void Creature::setteam(Summoner* a) {
	team = a;
}

int cr::fight(Creature*& obj) {
	if (st.attack_rage >= 2) {
		if (makedamage(obj, school_prior(obj)) == -1) {
			st.moral += 10;
			st.speed = 0;
			return 1;
		}
		else {
			st.speed = 0;
			return 0;
		}
	}
	else {
		if (makedamage(obj, school_prior(obj)) == -1) {
			if (school != 1) {
				st.moral += 10;
			}
			st.speed = 0;
			return 1;
		}
		else {
			if (obj->c_att(this)==-1) {
				return -1;
			}
			else {
				st.speed = 0;
				return 0;
			}
		}
	}
}

int cr::c_att(Creature* obj) {
	if (makedamage(obj, 1) == -1) {
		st.moral += 10;
		return -1;
	}
	else return 0;
}
int cr::req_energ() const {
	return st.req_en;
}
nstats necr_cr::getstats()const {
	return st;
}
void necr_cr::showstats()const {
	std::cout << "\nTeam: " << team->getteam() << std::endl;
	std::cout << "Level: " << level << std::endl;
	std::cout << "School: " << school << std::endl;
	std::cout << "Max HP: " << st.max_HP << std::endl;
	std::cout << "Curr HP: " << st.HP << std::endl;
	std::cout << "Damage: " << st.damage << std::endl;
	std::cout << "Quantity: " << st.Quan << std::endl;
	std::cout << "Max speed: " << st.max_speed << std::endl;
	std::cout << "Current Movepoints: " << st.speed << std::endl;
	std::cout << "Defence: " << st.def << std::endl;
}
void necr_cr::setstats(nstats a) {
	st = a;
}
int Creature::school_prior(Creature *& obj){
	if (this->prior == obj->vulns) { return 1; }
	if (this->vulns == obj->prior) { return -1; }
	return 0;
}
int necr_cr::makedamage(Creature*& obj, int par) {
	float d = (this->st.damage * this->st.Quan);
	d = d * (100 + par * 20) / 100;
	return obj->takedamage(d);
}
int necr_cr::takedamage(float d) {
	float dam = d * (100 - st.def ) / 100;
	int help_q = st.Quan;
	float help = st.max_HP * (st.Quan - 1) + st.HP;
	help = help - dam;
	if (help < 0) { return -1; }
	st.Quan = help / st.max_HP;
	st.HP = help - st.Quan * st.max_HP;
	st.Quan++;
	return 1;
}
int necr_cr::fight(Creature*& obj) {
	if (st.attack_rage >= 2) {
		if (makedamage(obj, school_prior(obj)) == -1) {
			st.speed = 0;
			return 1;
		}
		else {
			st.speed = 0;
			return 0;
		}
	}
	else {
		if (makedamage(obj, school_prior(obj)) == -1) {
			st.speed = 0;
			return 1;
		}
		else {
			if (obj->c_att(this)==-1) {
				return -1;
			}
			else {
				st.speed = 0;
				return 0;
			}
		}
	}
}
int necr_cr::c_att(Creature* obj) {
	if (makedamage(obj, 1) == -1) {
		return -1;
	}
	else return 0;
}

int necr_cr::req_energ() const {
	return st.req_en;
}
skeletone::skeletone() {
	prior = 5;
    vulns = 3;
	level = 1;
	name = "skeletone";
	school = 1;
	st.attack_rage = 1;
	st.Quan = 20;
	st.max_HP = 5;
	st.HP = 5;
	st.damage = 2;
	st.def = 3;
	st.max_speed = 2;
	st.speed = 2;
	st.req_en = 5;
}

demon::demon() {
	prior = 4;
	vulns = 5;
	level = 1;
	name = "demon";
	school = 2;
	st.attack_rage = 1;
	st.moral = 0;
	st.Quan = 30;
	st.max_HP = 3;
	st.HP = 3;
	st.damage = 1.5;
	st.def = 2;
	st.max_speed = 3;
	st.speed = 3;
	st.req_en = 5;
}
rat::rat() {
	prior = 1;
	vulns = 4;
	level = 1;
	name = "rat";
	school = 3;
	st.attack_rage = 1;
	st.moral = 0;
	st.Quan = 40;
	st.max_HP = 2;
	st.HP = 2;
	st.damage = 1;
	st.def = 0;
	st.max_speed = 4;
	st.speed = 4;
	st.req_en = 5;
}
air_elemental::air_elemental() {
	prior = 3;
	vulns = 2;
	level = 1;
	name = "air elemental";
	school = 4;
	st.attack_rage = 1;
	st.moral = 0;
	st.Quan = 20;
	st.max_HP = 7;
	st.HP = 7;
	st.damage = 3;
	st.def = 0;
	st.max_speed = 2;
	st.speed = 2;
	st.req_en = 5;
}
dwarf::dwarf() {
	prior = 2;
	vulns = 1;
	level = 1;
	name = "dwarf";
	school = 5;
	st.attack_rage = 1;
	st.moral = 0;
	st.Quan = 20;
	st.max_HP = 10;
	st.HP = 10;
	st.damage = 1;
	st.def = 5;
	st.max_speed = 1;
	st.speed = 1;
	st.req_en = 5;
}
zombie::zombie() {
	prior = 5;
	vulns = 3;
	level = 2;
	name = "zombie";
	school = 1;
	st.attack_rage = 1;
	st.Quan = 20;
	st.max_HP = 15;
	st.HP = 15;
	st.damage = 3;
	st.def = 8;
	st.max_speed = 1;
	st.speed = 1;
	st.req_en = 10;
}
hell_hound::hell_hound() {
	prior = 4;
	vulns = 5;
	level = 2;
	name = "hell_hound";
	school = 2;
	st.attack_rage = 1;
	st.moral = 0;
	st.Quan = 20;
	st.max_HP = 8;
	st.HP = 8;
	st.damage = 8;
	st.def = 3;
	st.max_speed = 3;
	st.speed = 3;
	st.req_en = 10;
}
wolf::wolf() {
	prior = 1;
	vulns = 4;
	level = 2;
	name = "wolf";
	school = 3;
	st.attack_rage = 1;
	st.moral = 0;
	st.Quan = 20;
	st.max_HP = 10;
	st.HP = 10;
	st.damage = 6;
	st.def = 3;
	st.max_speed = 3;
	st.speed = 3;
	st.req_en = 10;
}
water_elemental::water_elemental() {
	prior = 3;
	vulns = 2;
	level = 2;
	name = "water_elemental";
	school = 4;
	st.attack_rage = 2;
	st.moral = 0;
	st.Quan = 15;
	st.max_HP = 10;
	st.HP = 10;
	st.damage = 4;
	st.def = 0;
	st.max_speed = 2;
	st.speed = 2;
	st.req_en = 10;
}
elf::elf() {
	prior = 2;
	vulns = 1;
	level = 2;
	name = "elf";
	school = 5;
	st.attack_rage = 2;
	st.moral = 0;
	st.Quan = 15;
	st.max_HP = 5;
	st.HP = 5;
	st.damage = 7;
	st.def = 0;
	st.max_speed = 2;
	st.speed = 2;
	st.req_en = 10;
}

