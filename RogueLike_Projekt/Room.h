#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Collision.h"
#define SIZE 11
class room
{
protected:
    int grid[SIZE][SIZE];
    int room_type;
    sf::Texture doors_t;
    sf::Sprite doors_s;

public:
    sf::Texture background_t;
    sf::Sprite background_s;
    int check_doors(int i, int j);
    void Draw(sf::RenderWindow& window, sf::RectangleShape& door);
    void pick_room_layout(hero& player, Collision kolizja, sf::RenderWindow& window, int i, int j);
};
