#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
	private:
		float shot_speed;
		float damage;
		int direction;
	public:
		sf::RectangleShape bullet;
		Bullet(sf::Vector2f size, sf::Vector2f position, float shot_speed, float rate_of_fire, int direction, sf::Texture *texture, float rotation);
		void fire(float deltaTime);
		void Draw(sf::RenderWindow& window);
};