#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"

class Item
{
	private:
		float damage;
		float health;
		float maxHealth;
		float fire_delay;
		float shot_speed;
		float speed;
	public:
		sf::RectangleShape item;
		Item(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, float damage, float health,float maxHealth, float fire_delay, float shot_speed, float speed);
		void giveItem(hero* player);
		void Draw(sf::RenderWindow& window);
};