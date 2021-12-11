#include "Field.hpp"
#include <iostream>
#include <stdexcept>
#include <random>
#include "Creature.hpp"

using namespace summon;

field::field(int x, int y) {
	//v::vector<v::vector<fieldstats>>::Iterator a;
//	v::vector<v::vector<fieldstats>>::Iterator b;
	//b = st.end();
	max_x = x;
	max_y = y;
   st = v::vector<v::vector<fieldstats>>(max_x);
   for (int i = 0; i < max_x; i++) {
	   st[i] = v::vector<fieldstats>(max_y);
   }
	//for ( a = st.begin(); a <= b ; a++) {
	//	a->reinit(max_y);
	//}
	auto gen = []() {
		static std::mt19937 rng{ std::random_device()() };
		static std::uniform_int_distribution<int> distr(0,6);
		return distr(rng);
	};
	int t;
	for (int i = 0; i < max_x; i++) {
		for (int j = 0; j < max_y; j++) {
			st[i][j].x = i;
			st[i][j].y = j;
			st[i][j].busy = 0;
			st[i][j].check = 0;
			st[i][j].dist = -1;
			st[i][j].next = nullptr;
			switch (gen()) {
				case 0: { t = 1;
					break;
				}	
				case 1: { t = 2;
					break;
				}
				case 2: { t = 3;
					break;
				}
				case 3: { t = 4;
					break;
				}
				case 4: { t = 1;
					break;
				}
				case 5: { t = 2;
					break;
				}	
				case 6: { t = 3;
					break;
				}
			}
			st[i][j].type = t;
		}
		st[max_x / 2][0].busy = 1;
		st[max_x / 2][0].type = 1;
		st[max_x / 2][max_y - 1].busy = 1;
		st[max_x / 2][max_y - 1].type = 1;
	}
	
}

fieldstats field::getcoords(int a, int b) {
	return st[a][b];
}
int field::check(int x, int y)const {
	return  st[x][y].busy;
}
int field::getweight(int a, int b, int cx, int cy)const {
	if (a == cx && b == cy) { return 0; }
	if (st[a][b].busy == 1 ) { return -1; }
	if (st[a][b].type == 1) { return 1; }
	if (st[a][b].type == 4) { return -1; }
	if (st[a][b].type == 2 || st[a][b].type == 3) { return 2; }
}
void field::change_distance(int dist,int x,int y,int x1, int y1) {
	if (st[x][y].dist == -1 || st[x][y].dist > st[x1][y1].dist + dist) {
		st[x][y].dist = st[x1][y1].dist + dist;
		st[x][y].next = &st[x1][y1];
	}
}
void field::clear() {
	for (int i = 0; i < max_x; i++) {
		for (int j = 0; j < max_y; j++) {
			st[i][j].check = 0;
			st[i][j].dist = -1;
			st[i][j].next = nullptr;
		}
	}
}
int field::countdist(int x1, int y1, int x2, int y2) {
	return (st[x1][y1].x - st[x2][y2].x) * (st[x1][y1].x - st[x2][y2].x) + (st[x1][y1].y - st[x2][y2].y) * (st[x1][y1].y - st[x2][y2].y);
}
void field::sort(v::vector<fieldstats>& v, int x, int y, int x2, int y2) {
	int i;
	if (v.getlen() == 0) {
		i = 0;
	}
	else { i = 1; }
	while (i<v.getlen()) {
		if (v[i].dist + countdist(v[i].x,v[i].y,x2,y2)  > st[x][y].dist + countdist(st[x][y].x, st[x][y].y,x2,y2) ) { break; }
		i++;
	}
	v.add(i,st[x][y]);
}
void field::findway(int x1, int y1, int x2, int y2) {
	clear();
	v::vector<fieldstats> q;
	st[x1][y1].dist = getweight(x1,y1, x2, y2);
	q.push_back(st[x1][y1]);
	st[x1][y1].check = 2;
	while (!q.empty()) {
		int x = q.begin()->x;
		int y = q.begin()->y;
		//it = q.begin();
		if (x + 1 < max_x) {
			if (int d = getweight(x+1, y, x2, y2) != -1 && w_chec(x+1,y)!=3) {
				    change_distance(d, x + 1, y, x, y);
					st[x + 1][y].check = 2;
					sort(q,x+1,y,x2,y2);
					if (x+1 == x2 && y == y2) { break; }
			}
		}
		if (y + 1 < max_y) {
			if (int d = getweight(x, y+1, x2, y2) != -1 && w_chec(x, y+1) != 3) {
				change_distance(d, x, y+1, x, y);
				st[x][y+1].check = 2;
				if (x == x2 && y + 1 == y2) { break; }
				sort(q, x, y+1,x2,y2);
			}
		}
		if (x - 1 >= 0) {
			if (int d = getweight(x - 1, y, x2, y2) != -1 && w_chec(x - 1, y) != 3) {
				change_distance(d, x - 1, y, x, y);
				st[x - 1][y].check = 2;
				if (x - 1 == x2 && y == y2) { break; }
				sort(q, x - 1, y,x2,y2);
			}
		}
		if (y - 1 >= 0) {
			if (int d = getweight(x, y - 1, x2, y2) != -1 && w_chec(x, y - 1) != 3) {
				change_distance(d, x, y - 1, x, y);
				st[x][y - 1].check = 2;
				if (x == x2 && y - 1 == y2) { break; }
				sort(q, x, y-1,x2,y2);
			}
		}
		q.remove(0);
		st[x][y].check = 3;
	}
}
void field::setcreature(int x, int y, Creature* obj) {
	st[x][y].obj = obj;
	if (obj == nullptr) {
		st[x][y].busy = 0;
	}
	else { 
		st[x][y].busy = 1; 
	    obj->setcoords(x, y);
	}
}