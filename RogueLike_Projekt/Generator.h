#pragma once
#include <SFML/Graphics.hpp>
#include "Room.h"
#include <queue>
#include <stack>
#include <iostream>
/**
* Klasa odpowiedzialna za generacjê poziomu
*/

class generate_map : public room
{
protected:

    int rooms_counter = 0; /**<Zmienna okreœlaj¹ca ile pokojów zosta³o wygenerowane*/
    int max_rooms;  /**<Zmienna okreœlaj¹ca maksymaln¹ liczbê pokojów*/
    int min_rooms;  /**<Zmienna okreœlaj¹ca minimaln¹ liczbê pokojów*/
    std::queue <sf::Vector2i> RoomQueue;    /**<Kolejka przechowuj¹ca pokoje*/
    std::vector <sf::Vector2i> DeadEnd; /**<Wektor przechowuj¹cy pokoje z jednymi drzwiami (Pokoje - œlepe zau³ki)*/
    bool placedSpecial = false; /**<Zmienna okreœlaj¹ca, czy zosta³y umiejscowione specjalne pokoje*/
    
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
