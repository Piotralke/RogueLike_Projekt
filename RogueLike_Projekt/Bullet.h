#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
	private:
		float shot_speed;
		float damage;
		sf::Vector2f direction;
		sf::Vector2f directionNormalized;
	public:
		sf::RectangleShape bullet;
		Bullet(sf::Vector2f size, sf::Vector2f position, float shot_speed, float rate_of_fire, sf::Vector2f direction, sf::Texture *texture, float rotation);
		void fire(float deltaTime);
		void Draw(sf::RenderWindow& window);
		float getDamage();
};