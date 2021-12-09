#include "Objects.h"

Object::Object(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size)
{
	shape.setSize(size);
	shape.setOrigin(shape.getSize() / 2.0f);
	shape.setPosition(position);
	shape.setTexture(itemTexture);
}

void Object::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}