#include "Bullet.h"

Bullet::Bullet(sf::Vector2f size, sf::Vector2f position, float shot_speed, float damage, sf::Vector2f shotting_direction, sf::Texture *texture, float rotation)
{
	bullet.setSize(size);
	bullet.setOrigin(bullet.getSize() / 2.0f);
	bullet.setPosition(position);
	bullet.setTexture(texture);
	bullet.setRotation(rotation);
	this->shot_speed = shot_speed;
	this->damage = damage;
	direction = shotting_direction;
	directionNormalized = { direction.x / (float)sqrt(pow(direction.x, 2) + pow(direction.y, 2)), direction.y / (float)sqrt(pow(direction.x, 2) + pow(direction.y, 2)) };
}
void Bullet::fire(float deltaTime)
{
	bullet.move({ directionNormalized.x * shot_speed * deltaTime, directionNormalized.y * shot_speed * deltaTime });	
}
void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(bullet);
}

float Bullet::getDamage()
{
	return damage;
}