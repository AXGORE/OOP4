#ifndef CREATURE_HPP
#define CREATURE_HPP
#include <iostream>
#include "Field.hpp"

namespace summon {
	typedef class Summoner;
	struct nstats {
		int max_HP;
		float HP;
		float damage;
		int Quan;
		int max_speed;
		int speed;
		int req_en;
		int attack_rage;
		int def;
	};
	struct stats {
		int max_HP;
		float HP;
		float damage;
		int moral;
		int Quan;
		int max_speed;
		int speed;
		int req_en;
		int attack_rage;
		int def;
	};
	class Creature {
	protected:
		int prior;
		int vulns;
		int school;
		Summoner* team;
		std::string name;
		coords curr;
		int level;
	public:
		virtual void setteam(Summoner* a);
		virtual void setcoords(int x, int y) { 
			curr.x = x;
			curr.y = y;
		}
		virtual std::string showname()const;
		virtual void setname(std::string a);
		virtual int school_prior(Creature*& obj);
		virtual int getlevel() const;
		virtual Summoner* getteam() const { return team; }
		virtual int fight(Creature*& obj)=0;
		virtual int makedamage(Creature*& obj, int par)=0;
		virtual int damage_summoner(Summoner& obj)=0;
		virtual int takedamage(float d)=0;
		virtual void showstats() const = 0;
		virtual void move(field& f, int x, int y);
		//virtual void load_from_file()=0;
		//virtual void save_f(FILE* f)=0;
		virtual bool change_mp(int a) = 0;
		virtual bool alive()const = 0;
		//int school_prior(cr& obj);
		virtual int getmp()const=0;
		virtual int req_energ()const=0;
		virtual int c_att(Creature* obj) = 0;
	};
	class necr_cr: public Creature {
	protected:
		nstats st;
	public:
		virtual void setteam(Summoner* a) { return Creature::setteam(a); }
		
		virtual std::string showname()const { return Creature::showname(); }
		virtual void setname(std::string a) { return Creature::setname(a); }
		virtual int school_prior(Creature*& obj) { return Creature::school_prior(obj); }
		virtual int getlevel() const { return Creature::getlevel(); }
		virtual nstats getstats()const;
		virtual void showstats()const;
		virtual int getmp() const;
		virtual bool alive() const { return false; }
		virtual void setstats(nstats a);
		virtual bool change_mp(int a);
		virtual int fight(Creature*& obj);
		virtual int makedamage(Creature*& obj, int par);
		virtual int damage_summoner(Summoner& obj);
		virtual int takedamage(float d);
		virtual int c_att(Creature* obj);
		virtual int req_energ() const;
	};

	class cr: public Creature  {
	protected:
		stats st;
	public:
		//void setteam(int a);
		void setteam(Summoner* a) { return Creature::setteam(a); }
		virtual std::string showname()const { return Creature::showname(); }
		virtual void setname(std::string a) { return Creature::setname(a); }
		virtual int school_prior(Creature*& obj) { return Creature::school_prior(obj); }
		virtual int getlevel() const { return Creature::getlevel(); }
		virtual stats getstats()const;
		virtual bool alive() const { return true; }
		virtual int getmp() const;
		virtual void showstats()const;
		virtual bool change_mp(int a);
		//int getlevel() const;
		virtual void setstats(stats a);
		//virtual int fight(Creature*& obj);
		virtual int fight(Creature*& obj);
		virtual int makedamage(Creature*& obj, int par);
		virtual int damage_summoner(Summoner& obj);
		virtual int takedamage(float d);
		// void move(field);
		virtual void reset_moral(int a, int b);
		virtual void moral_rise();
		virtual int c_att(Creature* obj);
		virtual int req_energ()const;
	};
	class skeletone : public necr_cr {
	public:
		skeletone();
		virtual int fight(Creature*& obj) { return necr_cr::fight(obj); }
		virtual int makedamage(Creature*& obj, int par) { return necr_cr::makedamage(obj,par); }
		virtual int damage_summoner(Summoner& obj) {return necr_cr::damage_summoner(obj);}
		virtual int takedamage(float d) { return necr_cr::takedamage(d); }
		virtual int req_energ()const { return necr_cr::req_energ(); }
		virtual int c_att(Creature* obj) { return necr_cr::c_att(obj); }
	};
	class zombie : public necr_cr {
	public:
		zombie();
		virtual int fight(Creature*& obj) { return necr_cr::fight(obj); }
		virtual int makedamage(Creature*& obj, int par) { return necr_cr::makedamage(obj, par); }
		virtual int damage_summoner(Summoner& obj) { return necr_cr::damage_summoner(obj); }
		virtual int takedamage(float d) { return necr_cr::takedamage(d); }
		virtual int req_energ()const { return necr_cr::req_energ(); }
		virtual int c_att(Creature* obj) { return necr_cr::c_att(obj); }
	};
	class hell_hound : public cr {
	public:
		hell_hound();
		virtual int fight(Creature*& obj) { return cr::fight(obj); }
		virtual int makedamage(Creature*& obj, int par) { return cr::makedamage(obj, par); }
		virtual int damage_summoner(Summoner& obj) { return cr::damage_summoner(obj); }
		virtual int takedamage(float d) { return cr::takedamage(d); }
		virtual int req_energ()const { return cr::req_energ(); }
		virtual int c_att(Creature* obj) { return cr::c_att(obj); }
	};
	class demon : public cr {
	public:
		demon();
		virtual int fight(Creature*& obj) { return cr::fight(obj); }
		virtual int makedamage(Creature*& obj, int par) { return cr::makedamage(obj, par); }
		virtual int damage_summoner(Summoner& obj) { return cr::damage_summoner(obj); }
		virtual int takedamage(float d) { return cr::takedamage(d); }
		virtual int req_energ()const { return cr::req_energ(); }
		virtual int c_att(Creature* obj) { return cr::c_att(obj); }
	};
	class rat : public cr {
	public:
		rat();
		virtual int fight(Creature*& obj) { return cr::fight(obj); }
		virtual int makedamage(Creature*& obj, int par) { return cr::makedamage(obj, par); }
		virtual int damage_summoner(Summoner& obj) { return cr::damage_summoner(obj); }
		virtual int takedamage(float d) { return cr::takedamage(d); }
		virtual int req_energ()const { return cr::req_energ(); }
		virtual int c_att(Creature* obj) { return cr::c_att(obj); }
	};
	class wolf : public cr {
	public:
		wolf();
		virtual int fight(Creature*& obj) { return cr::fight(obj); }
		virtual int makedamage(Creature*& obj, int par) { return cr::makedamage(obj, par); }
		virtual int damage_summoner(Summoner& obj) { return cr::damage_summoner(obj); }
		virtual int takedamage(float d) { return cr::takedamage(d); }
		virtual int req_energ()const { return cr::req_energ(); }
		virtual int c_att(Creature* obj) { return cr::c_att(obj); }
	};
	class air_elemental : public cr {
	public:
		air_elemental();
		//virtual void Ability() { level = 1; };
		virtual int fight(Creature*& obj) { return cr::fight(obj); }
		virtual int makedamage(Creature*& obj, int par) { return cr::makedamage(obj, par); }
		virtual int damage_summoner(Summoner& obj) { return cr::damage_summoner(obj); }
		virtual int takedamage(float d) { return cr::takedamage(d); }
		virtual int req_energ()const { return cr::req_energ(); }
		virtual int c_att(Creature* obj) { return cr::c_att(obj); }
	};
	class water_elemental : public cr {
	public:
		water_elemental();
		virtual int fight(Creature*& obj) { return cr::fight(obj); }
		virtual int makedamage(Creature*& obj, int par) { return cr::makedamage(obj, par); }
		virtual int damage_summoner(Summoner& obj) { return cr::damage_summoner(obj); }
		virtual int takedamage(float d) { return cr::takedamage(d); }
		virtual int req_energ()const { return cr::req_energ(); }
		virtual int c_att(Creature* obj) { return cr::c_att(obj); }
	};
	class dwarf : public cr {
	public:
		dwarf();
		virtual int fight(Creature*& obj) { return cr::fight(obj); }
		virtual int makedamage(Creature*& obj, int par) { return cr::makedamage(obj, par); }
		virtual int damage_summoner(Summoner& obj) { return cr::damage_summoner(obj); }
		virtual int takedamage(float d) { return cr::takedamage(d); }
		virtual int req_energ()const { return cr::req_energ(); }
		virtual int c_att(Creature* obj) { return cr::c_att(obj); }
	};
	class elf : public cr {
	public:
		elf();
		virtual int fight(Creature*& obj) { return cr::fight(obj); }
		virtual int makedamage(Creature*& obj, int par) { return cr::makedamage(obj, par); }
		virtual int damage_summoner(Summoner& obj) { return cr::damage_summoner(obj); }
		virtual int takedamage(float d) { return cr::takedamage(d); }
		virtual int req_energ()const { return cr::req_energ(); }
		virtual int c_att(Creature* obj) { return cr::c_att(obj); }
	};

}

#endif // !CREATURE_HPP
