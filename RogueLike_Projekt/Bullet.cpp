#include "Bullet.h"

Bullet::Bullet(sf::Vector2f size, sf::Vector2f position, float shot_speed, float damage, int direction, sf::Texture *texture, float rotation)
{
	bullet.setSize(size);
	bullet.setOrigin(bullet.getSize() / 2.0f);
	bullet.setPosition(position);
	bullet.setTexture(texture);
	bullet.setRotation(rotation);
	this->shot_speed = shot_speed;
	this->damage = damage;
	this->direction = direction;
}
void Bullet::fire(float deltaTime)
{
	switch (direction)
	{
	case 1:	//gora
		bullet.move({ 0, -shot_speed * deltaTime });
		break;
	case 2:	//dol
		bullet.move({ 0, shot_speed * deltaTime });
		break;
	case 3:	//lewo
		bullet.move({ -shot_speed * deltaTime, 0 });
		break;
	case 4:	//prawo
		bullet.move({ shot_speed * deltaTime, 0 });
		break;
	}
	
}
void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(bullet);
}