#ifndef FIELD_HPP
#define FIELD_HPP
#include <iostream>
#include "Vector.hpp"

namespace summon {
	typedef class Creature;
	
	struct coords {
		int x;
		int y;
	};
	struct fieldstats {
		int x;
		int y;
		int type;
		int check;
		int par;
		int busy;
		int dist;
		Creature* obj;
		fieldstats* next;
	};
	struct way {
		way* prev;
		way* next;
		bool a;
		fieldstats st;
	};
	class field {
		v::vector<v::vector<fieldstats>> st;
		int max_x;
		int max_y;
		public:
			fieldstats getcoords(int a, int b);
			int check(int x, int y)const;
			int w_chec(int x, int y)const { return st[x][y].check; }
			int set_flag(int x, int y) { st[x][y].check = 1; }
			//void setcoords(int a, int b, int type);
			field(int x, int y);
			v::vector<v::vector<fieldstats>> getv()const { return st; }
			int countdist(int x1, int y1, int x2, int y2);
			void setcreature(int x, int y, Creature* obj);
			int getweight(int a, int b, int cx, int cy)const;
			void findway(int x1, int y1, int x2, int y2);
			void clear();
			void sort(v::vector<fieldstats>& v, int x, int y, int x2, int y2);
			//field(fieldstats** st);
			void change_distance(int dist, int x, int y, int x1, int y1);
	};




}


#endif // !FIELD_HPP

