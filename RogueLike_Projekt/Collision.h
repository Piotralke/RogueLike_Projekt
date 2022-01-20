#pragma once
#include "SFML/Graphics.hpp"
/** Klasa odpowiedzialna za wykrywanie kolizji
* 
*/
class Collision
{
	public:
		bool check_Collision(sf::RectangleShape& ob1, sf::RectangleShape& ob2); 
};