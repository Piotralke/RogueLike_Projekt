#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Collision.h"
#define SIZE 11
class room
{
protected:
    struct room_properties
    {
        int exist;
        int type;
        bool visited;
        std::string sciezka;
    };
    room_properties grid[SIZE][SIZE];
    sf::Texture doors_t;
    sf::Sprite doors_s;

public:
    sf::Texture background_t;
    sf::Sprite background_s;
    sf::RectangleShape minimap_room;
    sf::RectangleShape hero_m;
    sf::Texture minimap_rt;
    sf::Texture hero_minimap;
    int check_doors(int i, int j);
    void Draw(sf::RenderWindow& window, sf::RectangleShape& door);
    void pick_room_layout(hero& player, Collision kolizja, sf::RenderWindow& window, std::vector<Bullet>& heroB, std::vector<Bullet>& monsterB);
};
