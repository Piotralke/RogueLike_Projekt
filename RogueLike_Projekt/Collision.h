#pragma once
#include "SFML/Graphics.hpp"

class Collision
{
	public:
		bool canCollide = true;
		bool check_Collision(sf::RectangleShape& ob1, sf::RectangleShape& ob2);
};