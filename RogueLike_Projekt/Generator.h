#pragma once
#include <SFML/Graphics.hpp>
#include "Room.h"
#include <queue>
#include <stack>
#include <iostream>
/**
* \brief Klasa odpowiedzialna za generację poziomu
*/

class generate_map : public room
{
protected:

    int rooms_counter = 0; /**<\brief Zmienna określająca ile pokojów zostało wygenerowane*/
    int max_rooms;  /**<\brief Zmienna określająca maksymalną liczbę pokojów*/
    int min_rooms;  /**<\brief Zmienna określająca minimalną liczbę pokojów*/
    std::queue <sf::Vector2i> RoomQueue;    /**<\brief Kolejka przechowująca pokoje*/
    std::vector <sf::Vector2i> DeadEnd; /**<\brief Wektor przechowujący pokoje z jednymi drzwiami (Pokoje - ślepe zaułki)*/
    bool placedSpecial = false; /**<\brief Zmienna określająca, czy zostały umiejscowione specjalne pokoje*/
    
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
