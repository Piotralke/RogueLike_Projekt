#include "Item.h"

Item::Item(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, float damage, float health,float maxHealth, float fire_delay, float shot_speed, float speed, int money, int value, bool flying)
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
	this->money = money;
	this->value = value;
	this->flying = flying;
}
void Item::giveItem(hero* player)
{
	player->setStatistics(damage, health,maxHealth, fire_delay, shot_speed, speed, money,flying);
}
void Item::Draw(sf::RenderWindow& window, sf::Font& font)
{
	window.draw(item);
	if (value > 0)
	{
		sf::Text price_text;
		std::string price_string;
		price_text.setFont(font);
		price_text.setCharacterSize(8);
		price_text.setFillColor(sf::Color::White);
		price_string = std::to_string(value);
		price_text.setString(price_string);
		price_text.setPosition({ item.getPosition().x - 7.0f,item.getPosition().y+7.0f });
		window.draw(price_text);
	}
}
int Item::getMoney()
{
	return money;
}
int Item::getValue()
{
	return value;
}