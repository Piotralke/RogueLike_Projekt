#include "SFML/Graphics.hpp"

class Collision
{
	protected:
		sf::Vector2f tmpPos;
	public:
		bool check_Collision(sf::RectangleShape& ob1, sf::RectangleShape& ob2);
};