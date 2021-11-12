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
    std::queue <int> RoomQueue_i;
    std::queue <int> RoomQueue_j;
    std::stack <int> DeadEnd_i;
    std::stack <int> DeadEnd_j;
    bool placedSpecial = false;

public:
    generate_map();
    void init_grid();
    void max_level_counter(int level);
    int neighbour_count(int i, int j);
    bool visit(int i, int j);
    void wypisz();
    bool generate_layout();
};
