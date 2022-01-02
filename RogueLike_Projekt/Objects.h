#pragma once
#include <SFML/Graphics.hpp>

class Object {
private:

public:
	bool shootable;
	sf::RectangleShape shape;
	Object(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, bool shootable);
	void Draw(sf::RenderWindow& window);
};