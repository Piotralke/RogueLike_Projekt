#pragma once
#include "Collision.h"
#include <SFML/Graphics.hpp>

class Object {
private:
	
public:
	bool shootable;
	bool go_down;
	sf::RectangleShape shape;
	Object(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, bool shootable, bool go_down=false);
	void Draw(sf::RenderWindow& window);
};