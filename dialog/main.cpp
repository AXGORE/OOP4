#include <iostream>
#include <SFML/Graphics.hpp>

#pragma comment(lib, "../Laba4/Debug/Laba4")

int main() {
    std::vector<std::vector<int>> f;
    f.resize(10);
    for (auto i: f) {
        i.resize(10);
    }
    for (auto i: f) {
        for (auto j: i) {
            j = 1;
        }
    }
    sf::RenderWindow window(sf::VideoMode(10 * 32, 10 * 32), "SFML WORK");
    sf::Image m_im;
    std::string s = "../dialog/mountain.png";
    std::cout << s;
    sf::Texture m_t, g_t, h_t, f_t;
    m_im.loadFromFile(s);
    std::cout << s;
    sf::Image g_im;
    g_im.loadFromFile("../dialog/grass.png");
    sf::Image h_im;
    //h_im.loadFromFile("../dialog/hill.png");
    sf::Image f_im;
    f_im.loadFromFile("../dialog/forest.png");
    m_t.loadFromImage(m_im);
    g_t.loadFromImage(g_im);
    //h_t.loadFromImage(h_im);
    f_t.loadFromImage(f_im);
    sf::Sprite sprite;
    int choice;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
				

        sprite.setTexture(f_t);
        sprite.setPosition(1, 1);
        window.draw(sprite);


        window.display();
    }
    return 0;
}