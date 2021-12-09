#pragma once
#include <SFML/Graphics.hpp>

class Object {
private:

public:
	sf::RectangleShape shape;
	Object(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size);
	void Draw(sf::RenderWindow& window);
};