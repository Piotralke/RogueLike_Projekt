#pragma once
#include <SFML/Graphics.hpp>
#include "Room.h"
#include <queue>
#include <stack>
#include <iostream>
class generate_map : public room
{
protected:

    int rooms_counter = 0;
    int max_rooms;
    int min_rooms;
    std::queue <sf::Vector2i> RoomQueue;
    std::vector <sf::Vector2i> DeadEnd;
    bool placedSpecial = false;
    
public:
    generate_map();
    std::string random_layout(int i, int j);
    void init_grid();
    void max_level_counter(int level);
    int neighbour_count(int i, int j);
    bool visit(int i, int j);
    void wypiszkons();
    void wypisz(sf::RenderWindow& window,hero& player);
    void generate_layout();
};
