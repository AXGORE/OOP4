#ifndef SUMMONER_H
#define SUMMONER_H
#include <iostream>
#include <queue>
#include <map>
#include"Creature.hpp"
#include "Vector.hpp"



namespace summon {
	/*template <class T>
	class IWork_data {
	public:
		virtual T get_data() = 0;
		virtual void set_data(T) = 0;
	private:
	}; */
	//template <class T>
	class School {
	protected:
		int prior;
		int vulns;
		int level;
		int req_exp;
		Creature* type[7];
		//School();
	public:
		    virtual void summon_creature(int& mana, int num, Creature*& cr);
			virtual Creature* return_creature(int num) = 0;
			virtual void level_up(int& a);
			virtual int get_level()const;
			virtual void show_creatures()const =0;
			virtual void s_cr(Creature*& cr, int num) = 0;
			// virtual void abil() = 0;
	};
	
	
	
	class Necr_school: public School {
	//necr_cr* type[7];
	public:
		//necr_cr* summon_creature(int& mana, int num);
		virtual void s_cr(Creature*& cr, int num);
		virtual void show_creatures()const;
		virtual Creature* return_creature(int num) {return type[num];}
		Necr_school();
	};
	class Daemon_school : public School {
		//cr* type[7];
	public:
		//cr* summon_creature(int& mana, int num);
		virtual void s_cr(Creature*& cr, int num);
		virtual Creature* return_creature(int num) { return type[num]; }
		virtual void show_creatures()const;
		Daemon_school();
	};
	
	class Animal_school : public School{
		//cr* type[7];
	public:
		//cr* summon_creature(int& mana, int num);
		virtual void s_cr(Creature*& cr, int num);
		virtual Creature* return_creature(int num) { return type[num]; }
		virtual void show_creatures()const;
		Animal_school();
	};
	class Element_school : public School{
		//cr* type[7];
	public:
		//cr* summon_creature(int& mana, int num);
		virtual void s_cr(Creature*& cr, int num);
		virtual Creature* return_creature(int num) { return type[num]; }
		virtual void show_creatures()const;
		Element_school();
	};
	class Surreal_school : public School {
		//cr* type[7];
	public:
		//cr* summon_creature(int& mana, int num);
		virtual void s_cr(Creature*& cr, int num);
		virtual Creature* return_creature(int num) { return type[num]; }
		virtual void show_creatures()const;
		Surreal_school();
	};

	class table {
		v::mapa<std::string, School*> sch;
		//School<necr_cr>* ntype;
	public:
		//void addschool(School& school);
		School* get_school(std::string a);
		void show_schools();
		//int  h(School& school) const;
		table();
	};
	class Summoner {
		int team;
		int energy;
		int HP;
		int Cur_Exp;
		table sch;
	public:
		int getteam()const;
		table* get_table();
		void get_exp(int ex);
		void save_energy();
		void summon_creature(std::string a, Creature*& cr);
		void learn_school(std::string a);
		void showstats()const;
		int takedamage(Creature& sub);
		Summoner(int i);
	};
}


#endif
