#include <iostream>
#include <SFML/Graphics.hpp>
#include "Dialog.h"
#include"Summoner.h"
#pragma comment(lib,"../Laba4/Debug/Laba4")

using namespace summon;
int main() {
	field f(10, 10);
	sf::RenderWindow window(sf::VideoMode(10 * 32, 10 * 32), "SFML WORK");
	sf::Image m_im;
	std::string s = "mountain.png";
	std::cout << s;
	sf::Texture m_t, g_t, h_t, f_t;
	m_im.loadFromFile(s);
	std::cout << s;
	sf::Image g_im;
	g_im.loadFromFile("grass.png");
	sf::Image h_im;
	h_im.loadFromFile("hill.png");
	sf::Image f_im;
	f_im.loadFromFile("forest.png");
	m_t.loadFromImage(m_im);
	g_t.loadFromImage(g_im);
	h_t.loadFromImage(h_im);
	f_t.loadFromImage(f_im);
	v::vector<v::vector<fieldstats>>::Iterator i;
	v::vector<fieldstats>::Iterator j;
	sf::Sprite sprite;
	int choice;
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		for (i = f.getv().begin(); i != f.getv().end(); i++) {
			for (j = (*i).begin(); j != (*i).end(); j++) {
				choice = j->type;
				switch (choice) {
				case 1:
					sprite.setTexture(g_t);
					break;
				case 2:
					sprite.setTexture(h_t);
					break;
				case 3:
					sprite.setTexture(f_t);
					break;
				case 4:
					sprite.setTexture(m_t);
					break;
				}
				window.draw(sprite);
			}
		}
		window.display();
	}
	game();
	return 0;
}