#include "Objects.h"

Object::Object(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, bool shootable)
{
	shape.setSize(size);
	shape.setOrigin(shape.getSize() / 2.0f);
	shape.setPosition(position);
	shape.setTexture(itemTexture);
	this->shootable = shootable;
}

void Object::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}