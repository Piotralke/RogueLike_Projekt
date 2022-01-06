#include "Objects.h"

Object::Object(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, bool shootable, bool go_down)
{
	shape.setSize(size);
	shape.setOrigin(shape.getSize() / 2.0f);
	shape.setPosition(position);
	shape.setTexture(itemTexture);
	this->shootable = shootable;
	this->go_down = go_down;
}

void Object::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}