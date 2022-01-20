#pragma once
#include "Collision.h"
#include <SFML/Graphics.hpp>
/**
*  Klasa reprezentująca obiekty na mapie gry
*/
class Object {
private:
	
public:
	bool shootable; /**< Zmienna określająca, czy przez dany obiekt możemy strzelać*/
	bool go_down; /**< Zmienna określająca, czy przy kolizji z danym obiektem przejdziemy na następny poziom (Używane w przypadku utworzenia drabiny po pokonaniu bossa)*/
	sf::RectangleShape shape; /**<Prostokąt będący obszarem do wykrywania kolizji oraz do pobrania tekstury i wyświetlania obiektu w grze*/
	Object(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, bool shootable, bool go_down=false);
	void Draw(sf::RenderWindow& window);
};