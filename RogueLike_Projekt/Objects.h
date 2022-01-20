#pragma once
#include "Collision.h"
#include <SFML/Graphics.hpp>
/**
*  Klasa reprezentuj¹ca obiekty na mapie gry
*/
class Object {
private:
	
public:
	bool shootable; /**< Zmienna okreœlaj¹ca, czy przez dany obiekt mo¿emy strzelaæ*/
	bool go_down; /**< Zmienna okreœlaj¹ca, czy przy kolizji z danym obiektem przejdziemy na nastêpny poziom (U¿ywane w przypadku utworzenia drabiny po pokonaniu bossa)*/
	sf::RectangleShape shape; /**<Prostok¹t bêd¹cy obszarem do wykrywania kolizji oraz do pobrania tekstury i wyœwietlania obiektu w grze*/
	Object(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, bool shootable, bool go_down=false);
	void Draw(sf::RenderWindow& window);
};