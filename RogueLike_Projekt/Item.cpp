#include "Item.h"

Item::Item(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, float damage, float health,float maxHealth, float fire_delay, float shot_speed, float speed)
{
	item.setSize(size);
	item.setOrigin(item.getSize() / 2.0f);
	item.setPosition(position);
	item.setTexture(itemTexture);
	this->damage = damage;
	this->health = health;
	this->maxHealth = maxHealth;
	this->fire_delay = fire_delay;
	this->shot_speed = shot_speed;
	this->speed = speed;
}
void Item::giveItem(hero* player)
{
	player->setStatistics(damage, health,maxHealth, fire_delay, shot_speed, speed);
}
void Item::Draw(sf::RenderWindow& window)
{
	window.draw(item);
}