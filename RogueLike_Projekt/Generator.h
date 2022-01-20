#pragma once
#include <SFML/Graphics.hpp>
#include "Room.h"
#include <queue>
#include <stack>
#include <iostream>
/**
* Klasa odpowiedzialna za generacj� poziomu
*/

class generate_map : public room
{
protected:

    int rooms_counter = 0; /**<Zmienna okre�laj�ca ile pokoj�w zosta�o wygenerowane*/
    int max_rooms;  /**<Zmienna okre�laj�ca maksymaln� liczb� pokoj�w*/
    int min_rooms;  /**<Zmienna okre�laj�ca minimaln� liczb� pokoj�w*/
    std::queue <sf::Vector2i> RoomQueue;    /**<Kolejka przechowuj�ca pokoje*/
    std::vector <sf::Vector2i> DeadEnd; /**<Wektor przechowuj�cy pokoje z jednymi drzwiami (Pokoje - �lepe zau�ki)*/
    bool placedSpecial = false; /**<Zmienna okre�laj�ca, czy zosta�y umiejscowione specjalne pokoje*/
    
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
